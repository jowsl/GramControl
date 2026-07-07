#ifndef CLIENTEDAO_HPP
#define CLIENTEDAO_HPP

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QString>
#include "Cliente.hpp"

/**
 * @class ClienteDAO
 * @brief Data Acess Object para gerenciar a persistencia de clientes no banco SQLite
 */

class ClienteDAO
{
    public:
        ClienteDAO();
        ~ClienteDAO();

        bool inicializarBanco();
        bool inserirNoBanco(const Cliente& cliente);
        bool existeTelefone(const QString& telefone);
    
    private:
        QSqlDatabase db;
        
        ClienteDAO(const ClienteDAO&);
        ClienteDAO& operator=(const ClienteDAO&);
};

#endif // CLIENTEDAO_HPP