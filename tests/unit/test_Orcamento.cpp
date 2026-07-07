#include <iostream>
#include <cassert>
#include <cmath>
#include "../../src/Orcamento.hpp"

// Requisito 5.7 - Criterio de Aceitacao:
// "Ao informar uma metragem valida e selecionar uma variedade de grama, o sistema
//  deve calcular corretamente o valor parcial do servico utilizando os precos
//  cadastrados e apresentar o resultado ao usuario."

void teste_orcamento_calcula_valor_parcial_corretamente() {
    // Setup: 50 m2 de Grama Esmeralda a R$ 8,00/m2 -> R$ 400,00
    Orcamento orc("Grama Esmeralda", 50.0, 8.00);

    assert(orc.metragemValida() == true);
    assert(orc.getMetragem() == 50.0);
    assert(orc.getPrecoUnitario() == 8.00);
    assert(orc.getTipoGrama() == "Grama Esmeralda");
    assert(std::fabs(orc.calcularTotal() - 400.00) < 1e-6);

    std::cout << "Teste [5.7] calculo do valor parcial: OK" << std::endl;
}

void teste_orcamento_rejeita_metragem_invalida() {
    Orcamento zero("Grama Esmeralda", 0.0, 8.00);
    assert(zero.metragemValida() == false);
    assert(zero.calcularTotal() == 0.0);

    Orcamento neg("Grama Batatais", -10.0, 8.50);
    assert(neg.metragemValida() == false);
    assert(neg.calcularTotal() == 0.0);

    std::cout << "Teste [5.7] metragem invalida: OK" << std::endl;
}

void teste_orcamento_multiplos_tipos_de_grama() {
    Orcamento esm("Grama Esmeralda", 100.0, 8.00);
    Orcamento bat("Grama Batatais",  100.0, 8.50);

    assert(std::fabs(esm.calcularTotal() - 800.00) < 1e-6);
    assert(std::fabs(bat.calcularTotal() - 850.00) < 1e-6);
    assert(bat.calcularTotal() > esm.calcularTotal());

    std::cout << "Teste [5.7] multiplos tipos de grama: OK" << std::endl;
}
