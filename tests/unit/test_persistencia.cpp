#include <cassert>
#include <iostream>
#include "../../src/PrecoBase.hpp"
#include "../../src/PrecoBaseDAO.hpp"

void teste_persistencia_update_afeta_linha() {
    PrecoBaseDAO dao;
    assert(dao.inicializarBanco());   // agora a tabela já vem com a Grama Esmeralda

    // Cenário do critério de aceitação: altera Grama Esmeralda para 9.00
    PrecoBase grama("Grama Esmeralda", 9.00);
    bool salvou = dao.atualizarNoBanco(grama);

    // ANTES da correção: false (0 linhas afetadas). DEPOIS: true.
    assert(salvou == true);

    std::cout << "Teste de persistencia (UPDATE afeta linha) passou!" << std::endl;
}