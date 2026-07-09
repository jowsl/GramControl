#ifndef IAUTH_HPP
#define IAUTH_HPP

#include <string>
#include "User.h" 

// Interface pura: separação total da implementação concreta
/**
 * @brief Interface de autenticação para o sistema GramControl.
 *
 * Esta interface define os métodos necessários para autenticação e gerenciamento de usuários.
 * Qualquer classe que implemente esta interface deve fornecer implementações concretas
 * para os métodos declarados aqui.
 */
class IAuth {
public:
    /**
     * @brief Destrutor virtual para garantir a destruição correta das instâncias.
     */
    virtual ~IAuth() = default;
    /**
     * @brief Realiza o login do usuário.
     * @param email O email do usuário.
     * @param password A senha do usuário.
     * @return true se o login for bem-sucedido, false caso contrário.
     */
    virtual bool login(const std::string& email, const std::string& password) = 0;
    /**
     * @brief Obtém o usuário logado.
     * @return Um ponteiro para o usuário logado ou nullptr se nenhum usuário estiver logado.
     */
    virtual User* getLoggedUser() = 0;
    /**
     * @brief Realiza o logout do usuário.
     */
    virtual void logout() = 0;
    /**
     * @brief Gera um hash para a senha fornecida.
     * @param password A senha para a qual gerar o hash.
     * @return O hash gerado.
     */
    virtual size_t generateHash(const std::string& password) = 0;
    /**
     * @brief Registra um novo usuário.
     * @param email O email do novo usuário.
     * @param password A senha do novo usuário.
     * @param profile O perfil do novo usuário.
     * @return true se o registro for bem-sucedido, false caso contrário.
     */
    virtual bool registerUser(const std::string& email, const std::string& password, Profile profile) = 0;
    /**
     * @brief Lista todos os usuários.
     */
    virtual void listUsers() const = 0;
};

#endif