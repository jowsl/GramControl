#ifndef CLIENTECONTROLLER_HPP
#define CLIENTECONTROLLER_HPP

#include <QString>
#include "Cliente.hpp"
#include "ClienteDAO.hpp"

/**
 * @class ClienteController
 * @brief Intermediario entre a interface (View) e o banco de dados (DAO) para o cadastro de clientes em campo.
 */

class ClienteController
{
    public:
        ClienteController();
        ~ClienteController();
        ClienteController(const ClienteController& outro);
        ClienteController& operator=(const ClienteController& outro);

        /**
         * @brief Requisita o cadastro de um novo cliente no sistema.
         * @param mensagemErro [out] motivo da falha, se houver.
         * @return true se o cadastro foi realizado com sucesso, false caso contrário.
         */
        bool cadastrarCliente(QString nome, QString telefone, QString endereco, QString email, QString& mensagemErro);
};


#endif // CLIENTECONTROLLER_HPP