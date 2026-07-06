#ifndef PRECOBASE_HPP
#define PRECOBASE_HPP

#include <QString>
#include "handleBodySemDebug.h"

/**
 * @class PrecoBaseBody
 * @brief Body do padrão Handle/Body. Contém os dados e a lógica de negócio
 *        do preço base de gramas e insumos.
 */
class PrecoBaseBody : public Body {
public:
    /**
     * @brief Construtor padrão. Exigido pelo Handle<T>.
     */
    PrecoBaseBody();

    /**
     * @brief Construtor parametrizado.
     * @param nome Nome do item.
     * @param precoInicial Preço inicial do item.
     */
    PrecoBaseBody(QString nome, double precoInicial);

    /**
     * @brief Destrutor virtual.
     */
    virtual ~PrecoBaseBody();

    /**
     * @brief Valida e atualiza o preço.
     * @param novoPreco Novo valor (deve ser >= 0).
     * @return true se atualizado com sucesso.
     */
    bool atualizarPreco(double novoPreco);

    /**
     * @brief Retorna o preço atual.
     */
    double getPreco() const;

    /**
     * @brief Retorna o nome do item.
     */
    QString getNome() const;

private:
    /// @brief Cópia não permitida (Body não é copiável).
    PrecoBaseBody(const PrecoBaseBody&);

    /// @brief Atribuição não permitida (Body não é copiável).
    PrecoBaseBody& operator=(const PrecoBaseBody&);
    QString nomeItem;
    double  precoAtual;
};

/**
 * @class PrecoBase
 * @brief Handle do padrão Handle/Body. Interface pública para manipulação
 *        do preço base de gramas e insumos no sistema GramControl.
 *
 * Delega todas as operações para PrecoBaseBody via pImpl_.
 */
class PrecoBase : public Handle<PrecoBaseBody> {
public:
    /**
     * @brief Construtor padrão.
     */
    PrecoBase();

    /**
     * @brief Construtor parametrizado.
     * @param nome Nome do item (ex: "Grama Esmeralda").
     * @param precoInicial Preço inicial atribuído ao item.
     */
    PrecoBase(QString nome, double precoInicial);

    /**
     * @brief Atualiza o preço base após validação de regra de negócio.
     * @param novoPreco Novo valor a ser atribuído.
     * @return true se o preço for >= 0 e atualizado com sucesso.
     */
    bool atualizarPreco(double novoPreco);

    /**
     * @brief Retorna o preço atual do item.
     */
    double getPreco() const;

    /**
     * @brief Retorna o nome do item.
     */
    QString getNome() const;
};

#endif