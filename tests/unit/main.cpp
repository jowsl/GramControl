#include <iostream>
#include <QCoreApplication>
#include "test_login_reg.h"
#include "test_persistencia.h"
#include "test_PrecoBase.h"
#include "test_Orcamento.h"
#include "test_Cliente.hpp"
#include "test_persistencia_cliente.hpp"

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
    teste_cliente_valido();
    teste_cliente_sem_nome_ou_telefone();
    teste_persistencia_insere_cliente();

    return 0;
}