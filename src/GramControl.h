#ifndef GRAMCONTROL_H
#define GRAMCONTROL_H

#include <vector>
#include <string>
#include "User.h"

class GramControl {
private:
    std::vector<User> usersDB;
    User* loggedUser;
    std::string dbFilePath; 

    void loadUsersFromFile(const std::string& filePath);
    void saveUsersToFile(const std::string& filePath);

public:
    GramControl();
    
    bool login(const std::string& email, const std::string& password);
    User* getLoggedUser();
    void logout();
    size_t generateHash(const std::string& password);

    // Funcionalidade da Sprint 1: Cadastrar e Associar Papéis [cite: 403, 404]
    bool registerUser(const std::string& email, const std::string& password, Profile profile);
    
    // Auxiliar para verificação
    void listUsers() const;
};

#endif