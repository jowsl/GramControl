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
public:
    /**
     * @brief Construtor que inicializa e conecta ao banco de dados SQLite local.
     */
    PrecoBaseDAO();

    /**
     * @brief Destrutor.
     */
    ~PrecoBaseDAO();

    /**
     * @brief Cria a tabela de preços e semeia o catálogo base, caso não existam.
     * @return true se a inicialização for bem-sucedida.
     */
    bool inicializarBanco();

    /**
     * @brief Atualiza o preço de um item no banco de dados.
     * @param preco Objeto PrecoBase contendo o nome e o novo valor.
     * @return true se o UPDATE afetar ao menos uma linha, false caso contrário.
     */
    bool atualizarNoBanco(const PrecoBase& preco);

private:
    QSqlDatabase db; ///< Conexão com o banco de dados SQLite.

    /// @brief Cópia não permitida (conexão de banco não é copiável).
    PrecoBaseDAO(const PrecoBaseDAO&);

    /// @brief Atribuição não permitida (conexão de banco não é copiável).
    PrecoBaseDAO& operator=(const PrecoBaseDAO&);
};

#endif