#include <iostream>
#include <cassert>
#include "../../src/Cliente.hpp"
#include "test_Cliente.hpp"

void teste_cliente_valido() {
    Cliente cliente("João da Silva", "34999999999", "Rua das Flores, 222");
    assert(cliente.validar() == true);
    assert(cliente.getNome() == "João da Silva");
    std::cout << "Teste de cadastro de cliente valido passou" << std::endl;
}

void teste_cliente_sem_nome_ou_telefone(){
    Cliente semNome("", "31999999999", "Rua Direita, 352");
    assert(semNome.validar() == false);

    Cliente semTelefone("Maria de Souza", "", "Rua das Palmeiras, 123");
    assert(semTelefone.validar() == false);
    std::cout << "Teste de bloqueio de cadastro incompleto passou" << std::endl;
}
