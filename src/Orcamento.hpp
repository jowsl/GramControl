#ifndef ORCAMENTO_HPP
#define ORCAMENTO_HPP

#include <string>
#include "handleBodySemDebug.h"

//foward declaration
void teste_orcamento_gerar_digital();
void teste_orcamento_visualizar_detalhamento();

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
    //testes como friend do body
    friend void teste_orcamento_gerar_digital();
    friend void teste_orcamento_visualizar_detalhamento();

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

    // --- NOVAS FUNCIONALIDADES SPRINT 2 ---
    int getId() const;
    /**
     * @brief Retorna o email do cliente.
     * @return Email do cliente.
     */
    std::string getEmailCliente() const;
    /**
     * @brief Retorna o status do orçamento.
     * @return Status do orçamento.
     */
    std::string getStatus() const;

    // [SPRINT 2] Funcionalidade 1: Salva no banco e gera o registro
    /**
     * @brief Gera o orçamento digital e salva no banco de dados.
     * @param email Email do cliente para envio do orçamento digital.
     * @return true se o orçamento digital foi gerado e salvo com sucesso, false caso
     */
    bool gerarOrcamentoDigital(const std::string& email);

    // [SPRINT 2] Funcionalidade 2: Busca no banco e retorna formatado
    /**
     * @brief Visualiza o detalhamento de um orçamento específico.
     * @param idBusca ID do orçamento a ser visualizado.
     * @return String contendo o detalhamento do orçamento.
     */
    static std::string visualizarDetalhamento(int idBusca);

    // [SPRINT 2] Funcionalidade 3: Aprovar ou Recusar orçamento digitalmente
    /**
     * @brief Carrega os dados de um orçamento já persistido a partir do seu ID.
     * @param idBusca ID do orçamento a ser carregado.
     * @return true se o orçamento foi encontrado e os campos foram preenchidos.
     */
    bool carregarPorId(int idBusca);

    /**
     * @brief Aprova o orçamento, desde que esteja "Aguardando Aprovação" e
     *        pertença ao cliente informado.
     * @param emailLogado E-mail do cliente autenticado que está decidindo.
     * @return true se a transição de status foi persistida com sucesso.
     */
    bool aprovar(const std::string& emailLogado);

    /**
     * @brief Recusa o orçamento, desde que esteja "Aguardando Aprovação" e
     *        pertença ao cliente informado.
     * @param emailLogado E-mail do cliente autenticado que está decidindo.
     * @return true se a transição de status foi persistida com sucesso.
     */
    bool recusar(const std::string& emailLogado);

private:

    /// @brief Cópia não permitida.
    OrcamentoBody(const OrcamentoBody&);
    /// @brief Atribuição não permitida.
    OrcamentoBody& operator=(const OrcamentoBody&);

    /// @brief Aplica a transição de status no banco, validando dono e status atual.
    bool transicionarStatus(const std::string& emailLogado, const std::string& novoStatus);

    std::string tipoGrama;
    double      metragem;
    double      precoUnitario;

    // Novos atributos de persistência
    int id;
    std::string emailCliente;
    std::string status;
};

/**
 * @class Orcamento
 * @brief Handle do padrão Handle/Body. Interface pública para o cálculo do
 *        orçamento parcial de instalação de grama (Requisito 5.7).
 */
class Orcamento : public Handle<OrcamentoBody> {
    //fiends com o handle para testes
    friend void teste_orcamento_gerar_digital();
    friend void teste_orcamento_visualizar_detalhamento();

public:
    Orcamento();
    Orcamento(std::string tipoGrama, double metragem, double precoUnitario);

    double calcularTotal() const;
    bool   metragemValida() const;
    double getMetragem() const;
    double getPrecoUnitario() const;
    std::string getTipoGrama() const;

    // --- NOVAS FUNCIONALIDADES SPRINT 2 ---
    int getId() const;
    std::string getEmailCliente() const;
    std::string getStatus() const;

    bool gerarOrcamentoDigital(const std::string& email);
    static std::string visualizarDetalhamento(int idBusca);

    // [SPRINT 2] Funcionalidade 3: Aprovar ou Recusar orçamento digitalmente
    bool carregarPorId(int idBusca);
    bool aprovar(const std::string& emailLogado);
    bool recusar(const std::string& emailLogado);
};

#endif