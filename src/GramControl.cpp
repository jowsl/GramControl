#include "GramControl.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <functional>
#include "../includes/json.hpp"

using namespace std;
using json = nlohmann::json;

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
        dbFilePath = string(PROJECT_ROOT_DIR) + "/data/data.json";
        loadUsersFromFile(dbFilePath);
    }

    // Métodos internos que não precisam ser vistos por ninguém de fora
    void loadUsersFromFile(const std::string& filePath) {
        ifstream file(filePath);
        if (!file.is_open()) return;

        try {
            json j;
            file >> j; 
            for (const auto& item : j["users"]) {
                string email = item["email"];
                size_t hash;
                
                // Verifica se o JSON tem a senha em texto (como na 1ª vez) ou já tem o hash salvo
                if (item.contains("password")) {
                    string plainPassword = item["password"];
                    hash = generateHash(plainPassword);
                } else {
                    hash = item["passwordHash"];
                }
                
                int profileInt = item["profile"];
                usersDB.push_back({email, hash, static_cast<Profile>(profileInt)});
            }
        } catch (json::parse_error& e) {
            cerr << "[ERROR] JSON: " << e.what() << endl;
        }
        file.close();
    }

    void saveUsersToFile(const std::string& filePath) {
        json j;
        for (const auto& u : usersDB) {
            j["users"].push_back({
                {"email", u.email},
                {"passwordHash", u.passwordHash}, // Agora salva o hash numérico verdadeiro!
                {"profile", static_cast<int>(u.profile)}
            });
        }
        
        ofstream file(filePath);
        if (file.is_open()) {
            file << j.dump(4);
            file.close();
        }
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
        // Se alguém estiver logado, cria um ponteiro seguro e fresco na hora
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

        // SALVA O NOME DO ADMIN ANTES DO VETOR SE MOVER!
        string adminEmail = currentUser->email; 

        size_t hash = generateHash(password);
        usersDB.push_back({email, hash, profile}); // Aqui o vetor pode se mover
        saveUsersToFile(dbFilePath);

        // LOG DE AUDITORIA
        ofstream logFile(string(PROJECT_ROOT_DIR) + "/data/logs.txt", ios::app);
        if (logFile.is_open()) {
            auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
            string timeStr = ctime(&now);
            timeStr.pop_back();
            
            // Usa a variável adminEmail que salvamos lá em cima de forma segura
            logFile << "[" << timeStr << "] O Admin " << adminEmail 
                    << " cadastrou: " << email << " (Perfil: " << profile << ")" << endl;
            logFile.close();
        }

        return true;
    }
    
};

// =========================================================================
// O "HANDLE": Delegação de chamadas (A Ponte)
// =========================================================================

GramControl::GramControl() {}
GramControl::~GramControl() {}

// Todas as funções do Handle simplesmente repassam o trabalho para o pImpl
bool GramControl::login(const string& email, const string& password) {
    return pImpl_->login(email, password); // Atenção ao underline aqui!
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
    cout << "\n--- USUARIOS NO SISTEMA ---" << endl;
    for (const auto& u : pImpl_->usersDB) {
        cout << "- " << u.email << " | Perfil: " << u.profile << endl;
    }
}