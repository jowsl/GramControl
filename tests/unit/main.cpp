#include <iostream>
#include "test_login_reg.h"
#include "test_persistencia.h"
#include "test_PrecoBase.h"

int main() {
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

    return 0;
}