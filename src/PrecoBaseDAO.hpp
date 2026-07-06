#ifndef PRECOBASEDAO_HPP
#define PRECOBASEDAO_HPP

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QString>
#include "PrecoBase.hpp"

/**
 * @class PrecoBaseDAO
 * @brief Data Access Object para gerenciar a persistência dos preços no banco SQLite.
 */
class PrecoBaseDAO {
private:
    QSqlDatabase db;

public:
    /**
     * @brief Construtor que inicializa e conecta ao banco de dados SQLite local.
     */
    PrecoBaseDAO();

    /**
     * @brief Destrutor que fecha a conexão com o banco.
     */
    ~PrecoBaseDAO();

    /**
     * @brief Cria a tabela de preços caso ela não exista.
     */
    bool inicializarBanco();

    /**
     * @brief Atualiza o preço de um item no banco de dados.
     * @param preco Objeto PrecoBase contendo o nome e o novo valor.
     * @return true se o UPDATE for bem sucedido, false caso contrário.
     */
    bool atualizarNoBanco(const PrecoBase& preco);
};

#endif