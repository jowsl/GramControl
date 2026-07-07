#ifndef USER_H
#define USER_H

#include <string>

// Role/Profile definitions based on the requirements document
enum Profile {
    ADMINISTRATOR,
    SELLER,     // Vendedor
    PROVIDER,   // Prestador de Serviço
    CUSTOMER    // Cliente
};

struct User {
    std::string email;
    size_t passwordHash;
    Profile profile;
};

#endif