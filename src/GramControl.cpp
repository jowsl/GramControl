#include "GramControl.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <functional>
#include <chrono>
#include <ctime>
#include <sqlite3.h> // Incluindo o SQLite nativo do C++

using namespace std;

#ifndef PROJECT_ROOT_DIR
#define PROJECT_ROOT_DIR "."
#endif

// =========================================================================
// O "BODY": A implementação real escondida de todo o resto do sistema
// =========================================================================
class GramControlImpl : public Body {
public:
    std::vector<User> usersDB;
    int loggedUserIndex;
    std::string dbFilePath;

    GramControlImpl() {
        loggedUserIndex = -1;
        // Apontando para o seu banco isolado na pasta data
        dbFilePath = string(PROJECT_ROOT_DIR) + "/data/auth.db";
        initDatabase();
        loadUsersFromDB();
    }

void initDatabase() {
        sqlite3* db;
        if (sqlite3_open(dbFilePath.c_str(), &db) == SQLITE_OK) {
            // 1. Garante que a tabela existe
            const char* sqlCreate = "CREATE TABLE IF NOT EXISTS Usuarios ("
                                    "email TEXT PRIMARY KEY, "
                                    "passwordHash TEXT, " 
                                    "profile INTEGER);";
            char* errMsg = nullptr;
            sqlite3_exec(db, sqlCreate, nullptr, nullptr, &errMsg);

            // 2. Insere o Admin padrão automaticamente se ele não existir
            // O "INSERT OR IGNORE" impede que o SQLite dê erro por e-mail duplicado nas próximas execuções
            size_t adminHash = generateHash("admin123");
            string sqlAdmin = "INSERT OR IGNORE INTO Usuarios (email, passwordHash, profile) VALUES ("
                              "'admin@grama.com', '" + to_string(adminHash) + "', 0);"; // 0 = ADMINISTRADOR

            sqlite3_exec(db, sqlAdmin.c_str(), nullptr, nullptr, &errMsg);
            
            if (errMsg) sqlite3_free(errMsg);
            sqlite3_close(db);
        } else {
            cerr << "[ERRO DB] Falha ao criar/abrir banco: " << sqlite3_errmsg(db) << endl;
        }
    }

    void loadUsersFromDB() {
        usersDB.clear();
        sqlite3* db;
        if (sqlite3_open(dbFilePath.c_str(), &db) == SQLITE_OK) {
            const char* sql = "SELECT email, passwordHash, profile FROM Usuarios;";
            sqlite3_stmt* stmt;
            
            if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
                while (sqlite3_step(stmt) == SQLITE_ROW) {
                    string email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                    string hashStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                    size_t hash = stoull(hashStr); 
                    int profileInt = sqlite3_column_int(stmt, 2);
                    
                    usersDB.push_back({email, hash, static_cast<Profile>(profileInt)});
                }
            }
            sqlite3_finalize(stmt);
            sqlite3_close(db);
        }
    }

    bool insertUserDB(const string& email, size_t hash, Profile profile) {
        sqlite3* db;
        bool success = false;
        if (sqlite3_open(dbFilePath.c_str(), &db) == SQLITE_OK) {
            string sql = "INSERT INTO Usuarios (email, passwordHash, profile) VALUES ('" +
                         email + "', '" + to_string(hash) + "', " + to_string(static_cast<int>(profile)) + ");";
            
            char* errMsg = nullptr;
            if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) == SQLITE_OK) {
                success = true;
            } else {
                cerr << "[ERRO DB] " << errMsg << endl;
                sqlite3_free(errMsg);
            }
            sqlite3_close(db);
        }
        return success;
    }

    size_t generateHash(const string& password) {
        return hash<string>{}(password);
    }
    
    bool login(const string& email, const string& password) {
        size_t attemptHash = generateHash(password);
        for (size_t i = 0; i < usersDB.size(); i++) {
            if (usersDB[i].email == email && usersDB[i].passwordHash == attemptHash) {
                loggedUserIndex = i; // Salva apenas a posição!
                return true;
            }
        }
        return false;
    }

    User* getLoggedUser() {
        if (loggedUserIndex >= 0 && loggedUserIndex < (int)usersDB.size()) {
            return &usersDB[loggedUserIndex]; 
        }
        return nullptr;
    }

    bool registerUser(const string& email, const string& password, Profile profile) {
        User* currentUser = getLoggedUser();

        if (currentUser == nullptr || currentUser->profile != ADMINISTRATOR) {
            cerr << "[ERRO DE PERMISSAO] Apenas administradores podem cadastrar." << endl;
            return false;
        }

        for (const auto& u : usersDB) {
            if (u.email == email) {
                cerr << "[ERRO] E-mail ja cadastrado." << endl;
                return false;
            }
        }

        string adminEmail = currentUser->email; 
        size_t hash = generateHash(password);

        if (insertUserDB(email, hash, profile)) {
            usersDB.push_back({email, hash, profile}); 
            
            ofstream logFile(string(PROJECT_ROOT_DIR) + "/data/logs.txt", ios::app);
            if (logFile.is_open()) {
                auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
                string timeStr = ctime(&now);
                timeStr.pop_back();
                logFile << "[" << timeStr << "] O Admin " << adminEmail 
                        << " cadastrou: " << email << " (Perfil: " << profile << ")" << endl;
                logFile.close();
            }
            return true;
        }
        return false;
    }

    void listUsers() const {
        cout << "\n--- USUARIOS NO SISTEMA ---" << endl;
        for (const auto& u : usersDB) {
            cout << "- " << u.email << " | Perfil: " << u.profile << endl;
        }
    }
};

// =========================================================================
// O "HANDLE": Delegação de chamadas (A Ponte)
// =========================================================================

GramControl::GramControl() {}
GramControl::~GramControl() {}

bool GramControl::login(const string& email, const string& password) {
    return pImpl_->login(email, password);
}

User* GramControl::getLoggedUser() {
    return pImpl_->getLoggedUser();
}

void GramControl::logout() {
    pImpl_->loggedUserIndex = -1;
}

size_t GramControl::generateHash(const string& password) {
    return pImpl_->generateHash(password);
}

bool GramControl::registerUser(const string& email, const string& password, Profile profile) {
    return pImpl_->registerUser(email, password, profile);
}

void GramControl::listUsers() const {
    pImpl_->listUsers();
}