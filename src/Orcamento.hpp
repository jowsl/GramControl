#ifndef ORCAMENTO_HPP
#define ORCAMENTO_HPP

#include <string>
#include "handleBodySemDebug.h"

/**
 * @class OrcamentoBody
 * @brief Body do padrão Handle/Body. Contém os dados e a lógica de negócio
 *        do orçamento parcial de instalação de grama.
 *
 * Representa o cálculo do Requisito 5.7 — Inserir Metragem e Tipo de Grama —
 * combinando a metragem informada pelo vendedor com o preço unitário do
 * tipo de grama escolhido.
 */
class OrcamentoBody : public Body {
public:
    OrcamentoBody();
    OrcamentoBody(std::string tipoGrama, double metragem, double precoUnitario);
    virtual ~OrcamentoBody();

    /**
     * @brief Recalcula o valor total do orçamento (metragem * precoUnitario).
     * @return Valor parcial do serviço, em reais. Retorna 0.0 quando a metragem
     *         ou o preço unitário forem inválidos.
     */
    double calcularTotal() const;

    /**
     * @brief Valida se a metragem informada é aceita pelo sistema.
     * @return true quando a metragem é estritamente positiva.
     */
    bool metragemValida() const;

    double getMetragem() const;
    double getPrecoUnitario() const;
    std::string getTipoGrama() const;

private:
    /// @brief Cópia não permitida.
    OrcamentoBody(const OrcamentoBody&);
    /// @brief Atribuição não permitida.
    OrcamentoBody& operator=(const OrcamentoBody&);

    std::string tipoGrama;      ///< Nome da variedade de grama selecionada.
    double      metragem;       ///< Metragem (m²) informada pelo vendedor.
    double      precoUnitario;  ///< Preço por m² recuperado do catálogo.
};

/**
 * @class Orcamento
 * @brief Handle do padrão Handle/Body. Interface pública para o cálculo do
 *        orçamento parcial de instalação de grama (Requisito 5.7).
 */
class Orcamento : public Handle<OrcamentoBody> {
public:
    Orcamento();
    Orcamento(std::string tipoGrama, double metragem, double precoUnitario);

    double calcularTotal() const;
    bool   metragemValida() const;
    double getMetragem() const;
    double getPrecoUnitario() const;
    std::string getTipoGrama() const;
};

#endif
