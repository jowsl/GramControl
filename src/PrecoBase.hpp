#ifndef PRECOBASE_HPP
#define PRECOBASE_HPP

#include <string>
#include "handleBodySemDebug.h"

/**
 * @class PrecoBaseBody
 * @brief Body do padrão Handle/Body. Contém os dados e a lógica de negócio
 *        do preço base de gramas e insumos.
 */
class PrecoBaseBody : public Body {
public:
    PrecoBaseBody();
    PrecoBaseBody(std::string nome, double precoInicial);
    virtual ~PrecoBaseBody();
    bool atualizarPreco(double novoPreco);
    double getPreco() const;
    std::string getNome() const;

private:
    /// @brief Cópia não permitida.
    PrecoBaseBody(const PrecoBaseBody&);
    /// @brief Atribuição não permitida.
    PrecoBaseBody& operator=(const PrecoBaseBody&);

    std::string nomeItem;   ///< Nome descritivo da variedade de grama ou insumo.
    double      precoAtual; ///< Valor atual do item por metro quadrado ou unidade.
};

/**
 * @class PrecoBase
 * @brief Handle do padrão Handle/Body. Interface pública para manipulação
 *        do preço base de gramas e insumos no sistema GramControl.
 */
class PrecoBase : public Handle<PrecoBaseBody> {
public:
    PrecoBase();
    PrecoBase(std::string nome, double precoInicial);
    bool atualizarPreco(double novoPreco);
    double getPreco() const;
    std::string getNome() const;
};

#endif