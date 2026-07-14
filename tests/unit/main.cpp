#include <iostream>
#include <QCoreApplication>
#include "test_login_reg.h"
#include "test_persistencia.h"
#include "test_PrecoBase.h"
#include "test_Orcamento.h"
#include "test_Cliente.hpp"
#include "test_persistencia_cliente.hpp"
#include "test_Plantio.hpp"
#include "test_persistencia_plantio.hpp"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    rodarTestesUnitarios();

    std::cout << "\n--- TESTES DE PRECO BASE ---" << std::endl;
    teste_construtor_padrao();
    teste_get_preco();
    teste_get_nome();
    teste_atualizacao_preco_valido();
    teste_atualizacao_preco_negativo();

    std::cout << "\n--- TESTES DE DAO ---" << std::endl;
    teste_persistencia_update_afeta_linha();
    teste_persistencia_item_inexistente();

    std::cout << "\n--- TESTES DE CONTROLLER ---" << std::endl;
    teste_controller_preco_valido();
    teste_controller_preco_negativo();
    teste_controller_item_inexistente();

    std::cout << "\n--- TESTES DE ORCAMENTO E CLIENTE ---" << std::endl;
    teste_orcamento_calcula_valor_parcial_corretamente();
    teste_orcamento_rejeita_metragem_invalida();
    teste_orcamento_multiplos_tipos_de_grama();
    
    // Testes Sprint 2 - Banco de Dados
    teste_orcamento_gerar_digital();
    teste_orcamento_visualizar_detalhamento();

    // Testes Sprint 2 - Aprovar ou Recusar orcamento digitalmente
    teste_orcamento_carregarPorId_encontrado();
    teste_orcamento_carregarPorId_inexistente();
    teste_orcamento_aprovar_sucesso();
    teste_orcamento_aprovar_ja_decidido();
    teste_orcamento_aprovar_id_inexistente();
    teste_orcamento_recusar_sucesso();
    teste_orcamento_recusar_ja_decidido();
    teste_orcamento_decisao_email_nao_confere();
    teste_controller_carregarOrcamento();
    teste_controller_aprovarOrcamento_sucesso();
    teste_controller_recusarOrcamento_sucesso();

    teste_cliente_valido();
    teste_cliente_sem_nome_ou_telefone();
    teste_persistencia_insere_cliente();

    // ... outros testes existentes ...

    std::cout << "\n--- TESTES DE LOGÍSTICA E PLANTIO ---" << std::endl;
    teste_plantio_valido();
    teste_plantio_dados_invalidos();
    teste_persistencia_insere_plantio();

    return 0;
}