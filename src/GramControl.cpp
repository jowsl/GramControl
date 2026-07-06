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
class GramControlImpl {
public:
    // Todas aquelas variáveis que ficavam no .h agora vivem aqui
    std::vector<User> usersDB;
    User* loggedUser;
    std::string dbFilePath;

    GramControlImpl() {
        loggedUser = nullptr;
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
        for (auto& user : usersDB) {
            if (user.email == email && user.passwordHash == attemptHash) {
                loggedUser = &user;
                return true;
            }
        }
        return false;
    }

    bool registerUser(const string& email, const string& password, Profile profile) {
        if (loggedUser == nullptr || loggedUser->profile != ADMINISTRATOR) {
        cerr << "[ERRO DE PERMISSAO] Apenas administradores podem cadastrar." << endl;
        return false;
        }

        for (const auto& u : usersDB) {
            if (u.email == email) {
                cerr << "[ERRO] E-mail ja cadastrado no sistema." << endl;
                return false;
            }
        }

        size_t hash = generateHash(password);
        usersDB.push_back({email, hash, profile});
        
        // Atualiza o salvamento para usar a nossa variável com o caminho absoluto
        saveUsersToFile(dbFilePath);

        //salva logs
        ofstream logFile(string(PROJECT_ROOT_DIR) + "/data/logs.txt", ios::app);
        if (logFile.is_open()) {
            auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
            string timeStr = ctime(&now);
            timeStr.pop_back(); // Remove a quebra de linha extra gerada pelo ctime
            
            logFile << "[" << timeStr << "] O Administrador " << loggedUser->email 
                    << " cadastrou o novo usuario: " << email << " (Perfil: " << profile << ")" << endl;
            logFile.close();
        }

        return true;
    }
    
};

// =========================================================================
// O "HANDLE": Delegação de chamadas (A Ponte)
// =========================================================================

// O construtor do Handle apenas aloca o Body na memória
GramControl::GramControl() : pImpl(new GramControlImpl()) {}

// O destrutor do Handle garante que não haverá vazamento de memória
GramControl::~GramControl() {
    delete pImpl;
}

// Todas as funções do Handle simplesmente repassam o trabalho para o pImpl
bool GramControl::login(const string& email, const string& password) {
    return pImpl->login(email, password);
}

User* GramControl::getLoggedUser() {
    return pImpl->loggedUser;
}

void GramControl::logout() {
    pImpl->loggedUser = nullptr;
}

size_t GramControl::generateHash(const string& password) {
    return pImpl->generateHash(password);
}

bool GramControl::registerUser(const string& email, const string& password, Profile profile) {
    return pImpl->registerUser(email, password, profile);
}

void GramControl::listUsers() const {
    cout << "\n--- USUARIOS NO SISTEMA ---" << endl;
    for (const auto& u : pImpl->usersDB) {
        cout << "- " << u.email << " | Perfil: " << u.profile << endl;
    }
}