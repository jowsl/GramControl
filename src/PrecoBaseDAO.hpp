#ifndef PRECOBASEDAO_HPP
#define PRECOBASEDAO_HPP

#include <string>
#include "PrecoBase.hpp"

/**
 * @class PrecoBaseDAO
 * @brief Data Access Object para gerenciar a persistência dos preços no banco SQLite.
 */
class PrecoBaseDAO {
public:
    PrecoBaseDAO();
    ~PrecoBaseDAO();

    /**
     * @brief Cria a tabela de preços e semeia o catálogo base, caso não existam.
     */
    bool inicializarBanco();

    /**
     * @brief Atualiza o preço de um item no banco de dados.
     * @param preco Objeto PrecoBase contendo o nome e o novo valor.
     * @return true se o UPDATE afetar ao menos uma linha.
     */
    bool atualizarNoBanco(const PrecoBase& preco);

private:
    /// @brief Cópia não permitida.
    PrecoBaseDAO(const PrecoBaseDAO&);
    /// @brief Atribuição não permitida.
    PrecoBaseDAO& operator=(const PrecoBaseDAO&);
};

#endif