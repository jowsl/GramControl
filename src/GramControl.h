#ifndef GRAMCONTROL_H
#define GRAMCONTROL_H

#include <string>
#include "User.h"
#include "handleBodySemDebug.h" // Inclui o arquivo do professor
#include "IAuth.h" // Inclui a interface IAuth

class GramControlImpl; // Forward declaration continua

// O seu Handle agora HERDA do Handle do professor
/**
 * @brief Classe de controle do sistema GramControl.
 *
 * Esta classe é responsável por gerenciar as operações relacionadas aos usuários,
 * incluindo login, logout, registro e listagem de usuários.
 */
class GramControl : public IAuth, public Handle<GramControlImpl> {
public:
    GramControl();
    ~GramControl() override;

    // Apenas as funções públicas de negócio ficam expostas
    bool login(const std::string& email, const std::string& password) override;
    User* getLoggedUser() override;
    void logout() override;
    size_t generateHash(const std::string& password) override;
    bool registerUser(const std::string& email, const std::string& password, Profile profile) override;
    void listUsers() const override;
};

#endif