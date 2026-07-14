#ifndef USER_H
#define USER_H

#include <string>

// Role/Profile definitions based on the requirements document
/**
 * @brief Enumeração que representa os diferentes perfis de usuário no sistema.
 *
 * Cada perfil define um conjunto de permissões e responsabilidades dentro do sistema.
 */
enum Profile {
    ADMINISTRATOR,
    SELLER,     // Vendedor
    PROVIDER,   // Prestador de Serviço
    CUSTOMER    // Cliente
};

/**
 * @brief Estrutura que representa um usuário cadastrado no sistema.
 *
 * Armazena os dados básicos de autenticação e perfil do usuário.
 */
struct User {
    /// Endereço de email do usuário.
    std::string email;

    /// Hash da senha do usuário.
    size_t passwordHash;

    /// Perfil do usuário.
    Profile profile;
};

#endif