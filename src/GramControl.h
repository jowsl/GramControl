#ifndef GRAMCONTROL_H
#define GRAMCONTROL_H

#include <string>
#include "User.h"
#include "handleBodySemDebug.h" // Inclui o arquivo do professor

class GramControlImpl; // Forward declaration continua

// O seu Handle agora HERDA do Handle do professor
class GramControl : public Handle<GramControlImpl> {
public:
    GramControl();
    ~GramControl();

    // Apenas as funções públicas de negócio ficam expostas
    bool login(const std::string& email, const std::string& password);
    User* getLoggedUser();
    void logout();
    size_t generateHash(const std::string& password);
    bool registerUser(const std::string& email, const std::string& password, Profile profile);
    void listUsers() const;
};

#endif