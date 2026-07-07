#include <iostream>
#include <cassert>
#include "../../src/PrecoBase.hpp"

void teste_atualizacao_preco_valido() {
    // Setup: Começa com 8.00 conforme o documento
    PrecoBase gramaEsmeralda("Grama Esmeralda", 8.00);

    // Ação: Administrador altera o preço para 9.00
    bool sucesso = gramaEsmeralda.atualizarPreco(9.00);

    // Verificação: O sistema deve aceitar a alteração e registrar o novo valor
    assert(sucesso == true);
    assert(gramaEsmeralda.getPreco() == 9.00);

    std::cout << "Teste de atualizacao de preco passou com sucesso!" << std::endl;
}