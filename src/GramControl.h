#ifndef GRAMCONTROL_H
#define GRAMCONTROL_H

<<<<<<< HEAD
#include <string>
#include "User.h" // Necessário apenas por causa do enum Profile nas assinaturas

// 1. Forward Declaration: Avisamos ao compilador que existe um "Corpo" (Body), 
// mas não dizemos como ele é. Isso esconde a implementação!
class GramControlImpl;

// 2. A classe Handle: É a única coisa que as janelas do Qt vão enxergar.
class GramControl {
private:
    // O ponteiro do Handle-Body (Pimpl - Pointer to Implementation)
    GramControlImpl* pImpl; 

public:
    GramControl();
    ~GramControl(); // Essencial agora para liberar a memória do pImpl

    // As funções públicas continuam iguais, atuando como "pontes" para o Body
=======
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
    
>>>>>>> 2489b5e23edd8f68067dd31196e29a7b125f51d2
    bool login(const std::string& email, const std::string& password);
    User* getLoggedUser();
    void logout();
    size_t generateHash(const std::string& password);

<<<<<<< HEAD
    bool registerUser(const std::string& email, const std::string& password, Profile profile);
=======
    // Funcionalidade da Sprint 1: Cadastrar e Associar Papéis [cite: 403, 404]
    bool registerUser(const std::string& email, const std::string& password, Profile profile);
    
    // Auxiliar para verificação
>>>>>>> 2489b5e23edd8f68067dd31196e29a7b125f51d2
    void listUsers() const;
};

#endif