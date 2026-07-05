#include "GramControl.h"
#include <fstream>
#include <iostream>
#include <functional>
#include "../includes/json.hpp"

// Garante um fallback caso o CMake falhe ao injetar a variável
#ifndef PROJECT_ROOT_DIR
#define PROJECT_ROOT_DIR "."
#endif

using namespace std;
using json = nlohmann::json;

GramControl::GramControl() {
    loggedUser = nullptr;
    
    // Monta o caminho absoluto apontando direto para a sua pasta src/data
    dbFilePath = string(PROJECT_ROOT_DIR) + "/data/data.json";
    
    loadUsersFromFile(dbFilePath); 
}

// Para manter consistência no JSON, vamos assumir que ele já guarda a senha em plain text 
// para o mock da Sprint 1, ou que salva e lê a estrutura atual.
void GramControl::loadUsersFromFile(const string& filePath) {
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

void GramControl::saveUsersToFile(const string& filePath) {
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

size_t GramControl::generateHash(const string& password) {
    return hash<string>{}(password);
}

bool GramControl::login(const string& email, const string& password) {
    size_t attemptHash = generateHash(password);
    for (auto& user : usersDB) {
        if (user.email == email && user.passwordHash == attemptHash) {
            loggedUser = &user;
            return true;
        }
    }
    return false;
}

User* GramControl::getLoggedUser() { return loggedUser; }
void GramControl::logout() { loggedUser = nullptr; }

// Implementação do Cadastrar Usuário e Associar Papéis 
bool GramControl::registerUser(const string& email, const string& password, Profile profile) {
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
    return true;
}

void GramControl::listUsers() const {
    cout << "\n--- USUARIOS NO SISTEMA ---" << endl;
    for (const auto& u : usersDB) {
        cout << "- " << u.email << " | Perfil: " << u.profile << endl;
    }
}