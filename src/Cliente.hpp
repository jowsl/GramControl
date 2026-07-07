#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <QString>
#include "handleBodySemDebug.h"

/**
 * @class ClienteBody
 * @brief Body do padrão Hadle/Body. Contém os dados do clietne cadastrado em campo pelo Vendedor.
 * Sprint 1 - Cadastrar Cliente em Campo).
 */

 class ClienteBody : public Body
{
    public:
        ClienteBody();
        ClienteBody(QString nome, QString telefone, QString endereco, QString email = QString());
        virtual ~ClienteBody();

        /// @brief Valida se os campos obrigatorio (nome e telefone) foram preenchidos.
        bool validar() const;

        QString getNome() const;
        QString getTelefone() const;
        QString getEndereco() const;
        QString getEmail() const;

        private:
            ClienteBody(const ClienteBody&); // não permite cópia
            ClienteBody& operator=(const ClienteBody&); // não permite atribuição

            QString nome;
            QString telefone;
            QString endereco;
            QString email;
};

/**
 * @class Cliente
 * @brief Handle do padrão Hadle/Body. Interface publica para manipulacao do cadastro do cliente no sistema GramControl.
 */

 class Cliente : public Handle<ClienteBody>
{
    public:
        Cliente();
        Cliente(QString nome, QString telefone, QString endereco, QString email = QString());

        bool validar() const;
        QString getNome() const;
        QString getTelefone() const;
        QString getEndereco() const;
        QString getEmail() const;
};

#endif // CLIENTE_HPP