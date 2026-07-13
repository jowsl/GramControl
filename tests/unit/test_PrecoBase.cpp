#include <iostream>
#include <cassert>
#include "../../src/PrecoBase.hpp"
#include "../../src/PrecoBaseController.hpp"
#include "../../src/PrecoBaseDAO.hpp"

// Testes de PrecoBase (Model)

void teste_atualizacao_preco_valido() {
    PrecoBase grama("Grama Esmeralda", 8.00);
    bool sucesso = grama.atualizarPreco(9.00);
    assert(sucesso == true);
    assert(grama.getPreco() == 9.00);
    std::cout << "[PASS] atualizarPreco: preco valido aceito." << std::endl;
}

void teste_atualizacao_preco_negativo() {
    PrecoBase grama("Grama Batatais", 8.50);
    bool sucesso = grama.atualizarPreco(-5.00);
    assert(sucesso == false);
    assert(grama.getPreco() == 8.50); // preco nao deve ter mudado
    std::cout << "[PASS] atualizarPreco: preco negativo rejeitado." << std::endl;
}

void teste_get_preco() {
    PrecoBase grama("Grama Esmeralda", 8.00);
    assert(grama.getPreco() == 8.00);
    std::cout << "[PASS] getPreco: retorna valor correto." << std::endl;
}

void teste_get_nome() {
    PrecoBase grama("Grama Esmeralda", 8.00);
    assert(grama.getNome() == "Grama Esmeralda");
    std::cout << "[PASS] getNome: retorna nome correto." << std::endl;
}

void teste_construtor_padrao() {
    PrecoBase grama;
    assert(grama.getPreco() == 0.0);
    assert(grama.getNome() == "");
    std::cout << "[PASS] Construtor padrao: valores iniciais corretos." << std::endl;
}

// Testes de PrecoBaseDAO


void teste_persistencia_item_inexistente() {
    PrecoBaseDAO dao;
    assert(dao.inicializarBanco());
    PrecoBase grama("Item Que Nao Existe", 9.00);
    bool salvou = dao.atualizarNoBanco(grama);
    assert(salvou == false); // nao deve afetar nenhuma linha
    std::cout << "[PASS] atualizarNoBanco: item inexistente retorna false." << std::endl;
}

// Testes de PrecoBaseController

void teste_controller_preco_valido() {
    PrecoBaseController controller;
    bool sucesso = controller.requisitarAtualizacaoPreco("Grama Esmeralda", 9.00);
    assert(sucesso == true);
    std::cout << "[PASS] requisitarAtualizacaoPreco: preco valido salvo." << std::endl;
}

void teste_controller_preco_negativo() {
    PrecoBaseController controller;
    bool sucesso = controller.requisitarAtualizacaoPreco("Grama Esmeralda", -1.00);
    assert(sucesso == false);
    std::cout << "[PASS] requisitarAtualizacaoPreco: preco negativo rejeitado." << std::endl;
}

void teste_controller_item_inexistente() {
    PrecoBaseController controller;
    bool sucesso = controller.requisitarAtualizacaoPreco("Item Fantasma", 9.00);
    assert(sucesso == false);
    std::cout << "[PASS] requisitarAtualizacaoPreco: item inexistente retorna false." << std::endl;
}