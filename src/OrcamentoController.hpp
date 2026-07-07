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
};

#endif
