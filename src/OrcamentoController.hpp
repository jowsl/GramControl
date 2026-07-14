#ifndef ORCAMENTOCONTROLLER_HPP
#define ORCAMENTOCONTROLLER_HPP

#include <string>
#include <vector>
#include <utility>
#include "Orcamento.hpp"

/**
 * @class OrcamentoController
 * @brief Controlador do caso de uso "Inserir Metragem e Tipo de Grama"
 *        (Requisito 5.7). Consulta o catálogo de preços cadastrados e
 *        calcula o valor parcial do serviço.
 */
class OrcamentoController {
public:
    OrcamentoController();
    ~OrcamentoController();
    OrcamentoController(const OrcamentoController& outro);
    OrcamentoController& operator=(const OrcamentoController& outro);

    /**
     * @brief Lista as variedades de grama cadastradas para popular a view.
     * @return Vetor de pares (nome, preco unitário em R$/m²).
     */
    std::vector<std::pair<std::string, double>> listarTiposDeGrama();

    /**
     * @brief Calcula o valor parcial do orçamento a partir da metragem e
     *        do tipo de grama selecionado, utilizando o preço cadastrado.
     *
     * @param tipoGrama    Nome da variedade de grama (deve existir no catálogo).
     * @param metragem     Metragem do terreno em m² (deve ser > 0).
     * @param orcamentoOut Orçamento resultante, preenchido em caso de sucesso.
     * @return true quando os parâmetros são válidos e o preço foi localizado
     *         no banco de dados; false caso contrário.
     */
    bool calcularOrcamento(const std::string& tipoGrama,
                           double metragem,
                           Orcamento& orcamentoOut);

    // Retorna true se salvou com sucesso
    /**
     * @brief Salva o orçamento digital no banco de dados, associando-o ao
     *        e-mail do cliente.
     */
    bool salvarOrcamentoDigital(Orcamento& orcamento, const std::string& emailCliente);
    
    // Retorna os dados formatados
    /**
     * @brief Busca o detalhamento do orçamento no banco de dados, a partir
     *        do ID do orçamento.
     *
     * @param idOrcamento ID do orçamento a ser buscado.
     * @return String formatada com os detalhes do orçamento, ou uma mensagem
     *         de erro caso o ID não seja encontrado.
     */
    std::string buscarDetalhamento(int idOrcamento);

    // [SPRINT 2] Aprovar ou Recusar orçamento digitalmente

    /**
     * @brief Carrega um orçamento persistido pelo ID, para exibição na tela
     *        de aprovação do Cliente.
     * @param idOrcamento  ID do orçamento a ser carregado.
     * @param orcamentoOut Orçamento preenchido em caso de sucesso.
     * @return true se o orçamento foi encontrado.
     */
    bool carregarOrcamento(int idOrcamento, Orcamento& orcamentoOut);

    /**
     * @brief Aprova um orçamento em nome do cliente autenticado.
     * @param idOrcamento  ID do orçamento a ser aprovado.
     * @param emailLogado  E-mail do cliente autenticado (dono do orçamento).
     * @return true se o orçamento existia, pertencia ao e-mail informado e
     *         estava "Aguardando Aprovação".
     */
    bool aprovarOrcamento(int idOrcamento, const std::string& emailLogado);

    /**
     * @brief Recusa um orçamento em nome do cliente autenticado.
     * @param idOrcamento  ID do orçamento a ser recusado.
     * @param emailLogado  E-mail do cliente autenticado (dono do orçamento).
     * @return true se o orçamento existia, pertencia ao e-mail informado e
     *         estava "Aguardando Aprovação".
     */
    bool recusarOrcamento(int idOrcamento, const std::string& emailLogado);
};

#endif
