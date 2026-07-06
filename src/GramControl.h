#ifndef GRAMCONTROL_H
#define GRAMCONTROL_H

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
    bool login(const std::string& email, const std::string& password);
    User* getLoggedUser();
    void logout();
    size_t generateHash(const std::string& password);

    bool registerUser(const std::string& email, const std::string& password, Profile profile);
    void listUsers() const;
};

#endif