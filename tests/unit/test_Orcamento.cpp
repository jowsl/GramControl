#include <iostream>
#include <cassert>
#include <cmath>
#include "../../src/Orcamento.hpp"
#include "../../src/OrcamentoController.hpp"

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

    std::cout << "Teste calculo do valor parcial: OK" << std::endl;
}

void teste_orcamento_rejeita_metragem_invalida() {
    Orcamento zero("Grama Esmeralda", 0.0, 8.00);
    assert(zero.metragemValida() == false);
    assert(zero.calcularTotal() == 0.0);

    Orcamento neg("Grama Batatais", -10.0, 8.50);
    assert(neg.metragemValida() == false);
    assert(neg.calcularTotal() == 0.0);

    std::cout << "Teste metragem invalida: OK" << std::endl;
}

void teste_orcamento_multiplos_tipos_de_grama() {
    Orcamento esm("Grama Esmeralda", 100.0, 8.00);
    Orcamento bat("Grama Batatais",  100.0, 8.50);

    assert(std::fabs(esm.calcularTotal() - 800.00) < 1e-6);
    assert(std::fabs(bat.calcularTotal() - 850.00) < 1e-6);
    assert(bat.calcularTotal() > esm.calcularTotal());

    std::cout << "Teste multiplos tipos de grama: OK" << std::endl;
}

//sprint2

void teste_orcamento_gerar_digital() {
    Orcamento orc("Grama Esmeralda", 50.0, 10.00);
    std::string emailTeste = "unit@sprint2.com";
    
    assert(orc.gerarOrcamentoDigital(emailTeste) == true);
    assert(orc.getId() > 0); 
    assert(orc.getEmailCliente() == emailTeste);
    assert(orc.getStatus() == "Aguardando Aprovação");
    
    std::cout << "Teste geracao de orcamento no BD: OK" << std::endl;
}

void teste_orcamento_visualizar_detalhamento() {
    Orcamento orc("Grama Batatais", 10.0, 5.00);
    orc.gerarOrcamentoDigital("busca@sprint2.com");
    
    int id = orc.getId();
    std::string detalhes = Orcamento::visualizarDetalhamento(id);
    
    // Verifica se os dados vitais estão na string final
    assert(detalhes.find("busca@sprint2.com") != std::string::npos);
    assert(detalhes.find("Grama Batatais") != std::string::npos);
    
    std::string erroBusca = Orcamento::visualizarDetalhamento(-999);
    assert(erroBusca == "Orcamento nao encontrado.");

    std::cout << "Teste formatacao e busca no BD: OK" << std::endl;
}

//sprint2 - aprovar ou recusar orcamento digitalmente

void teste_orcamento_carregarPorId_encontrado() {
    Orcamento orcOriginal("Grama Esmeralda", 30.0, 8.00);
    orcOriginal.gerarOrcamentoDigital("carregar@sprint2.com");
    int id = orcOriginal.getId();

    Orcamento orcCarregado;
    assert(orcCarregado.carregarPorId(id) == true);
    assert(orcCarregado.getEmailCliente() == "carregar@sprint2.com");
    assert(orcCarregado.getTipoGrama() == "Grama Esmeralda");
    assert(std::fabs(orcCarregado.getMetragem() - 30.0) < 1e-6);
    assert(orcCarregado.getStatus() == "Aguardando Aprovação");

    std::cout << "Teste carregarPorId encontrado: OK" << std::endl;
}

void teste_orcamento_carregarPorId_inexistente() {
    Orcamento orc;
    assert(orc.carregarPorId(-999) == false);

    std::cout << "Teste carregarPorId inexistente: OK" << std::endl;
}

void teste_orcamento_aprovar_sucesso() {
    Orcamento orcOriginal("Grama Batatais", 20.0, 8.50);
    orcOriginal.gerarOrcamentoDigital("aprovar@sprint2.com");
    int id = orcOriginal.getId();

    Orcamento orc;
    orc.carregarPorId(id);
    assert(orc.aprovar("aprovar@sprint2.com") == true);
    assert(orc.getStatus() == "Aprovado");

    // Confirma que a transicao foi persistida no banco, nao so em memoria
    Orcamento reconsulta;
    reconsulta.carregarPorId(id);
    assert(reconsulta.getStatus() == "Aprovado");

    std::cout << "Teste aprovar com sucesso: OK" << std::endl;
}

void teste_orcamento_aprovar_ja_decidido() {
    Orcamento orcOriginal("Grama Esmeralda", 15.0, 8.00);
    orcOriginal.gerarOrcamentoDigital("jadecidido@sprint2.com");
    int id = orcOriginal.getId();

    Orcamento orc1;
    orc1.carregarPorId(id);
    assert(orc1.aprovar("jadecidido@sprint2.com") == true);

    Orcamento orc2;
    orc2.carregarPorId(id);
    assert(orc2.aprovar("jadecidido@sprint2.com") == false);

    std::cout << "Teste aprovar orcamento ja decidido: OK" << std::endl;
}

void teste_orcamento_aprovar_id_inexistente() {
    Orcamento orc; // nunca carregado (id = -1)
    assert(orc.aprovar("qualquer@sprint2.com") == false);

    std::cout << "Teste aprovar sem carregar antes: OK" << std::endl;
}

void teste_orcamento_recusar_sucesso() {
    Orcamento orcOriginal("Grama Batatais", 25.0, 8.50);
    orcOriginal.gerarOrcamentoDigital("recusar@sprint2.com");
    int id = orcOriginal.getId();

    Orcamento orc;
    orc.carregarPorId(id);
    assert(orc.recusar("recusar@sprint2.com") == true);
    assert(orc.getStatus() == "Recusado");

    std::cout << "Teste recusar com sucesso: OK" << std::endl;
}

void teste_orcamento_recusar_ja_decidido() {
    Orcamento orcOriginal("Grama Esmeralda", 12.0, 8.00);
    orcOriginal.gerarOrcamentoDigital("recusajadecidido@sprint2.com");
    int id = orcOriginal.getId();

    Orcamento orc1;
    orc1.carregarPorId(id);
    assert(orc1.recusar("recusajadecidido@sprint2.com") == true);

    Orcamento orc2;
    orc2.carregarPorId(id);
    assert(orc2.recusar("recusajadecidido@sprint2.com") == false);

    std::cout << "Teste recusar orcamento ja decidido: OK" << std::endl;
}

void teste_orcamento_decisao_email_nao_confere() {
    Orcamento orcOriginal("Grama Batatais", 18.0, 8.50);
    orcOriginal.gerarOrcamentoDigital("dono@sprint2.com");
    int id = orcOriginal.getId();

    Orcamento orc;
    orc.carregarPorId(id);
    assert(orc.aprovar("outro_cliente@sprint2.com") == false);
    assert(orc.recusar("outro_cliente@sprint2.com") == false);
    assert(orc.getStatus() == "Aguardando Aprovação");

    std::cout << "Teste decisao com e-mail divergente: OK" << std::endl;
}

void teste_controller_carregarOrcamento() {
    Orcamento orcOriginal("Grama Esmeralda", 40.0, 8.00);
    orcOriginal.gerarOrcamentoDigital("controller_carregar@sprint2.com");
    int id = orcOriginal.getId();

    OrcamentoController controller;
    Orcamento orcOut;
    assert(controller.carregarOrcamento(id, orcOut) == true);
    assert(orcOut.getEmailCliente() == "controller_carregar@sprint2.com");
    assert(controller.carregarOrcamento(-999, orcOut) == false);

    std::cout << "Teste controller carregarOrcamento: OK" << std::endl;
}

void teste_controller_aprovarOrcamento_sucesso() {
    Orcamento orcOriginal("Grama Batatais", 22.0, 8.50);
    orcOriginal.gerarOrcamentoDigital("controller_aprovar@sprint2.com");
    int id = orcOriginal.getId();

    OrcamentoController controller;
    assert(controller.aprovarOrcamento(id, "controller_aprovar@sprint2.com") == true);
    assert(controller.aprovarOrcamento(id, "controller_aprovar@sprint2.com") == false);

    std::cout << "Teste controller aprovarOrcamento: OK" << std::endl;
}

void teste_controller_recusarOrcamento_sucesso() {
    Orcamento orcOriginal("Grama Esmeralda", 8.0, 8.00);
    orcOriginal.gerarOrcamentoDigital("controller_recusar@sprint2.com");
    int id = orcOriginal.getId();

    OrcamentoController controller;
    assert(controller.recusarOrcamento(id, "controller_recusar@sprint2.com") == true);
    assert(controller.recusarOrcamento(id, "controller_recusar@sprint2.com") == false);

    std::cout << "Teste controller recusarOrcamento: OK" << std::endl;
}