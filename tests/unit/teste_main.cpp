#include <iostream>
#include <cassert>
#include <ctime>
#include "../../src/GramControl.h"

using namespace std;

void rodarTestesUnitarios() {
    GramControl system;

    cout << "--- INICIANDO BATERIA DE TESTES (SPRINT 1) ---" << endl;

    // TESTE 1: Falha no Login (Credenciais Inválidas)
    // O sistema não deve permitir login com senha errada
    assert(system.login("admin@grama.com", "senha_errada") == false);
    assert(system.getLoggedUser() == nullptr);
    cout << "[PASS] Teste 1: Bloqueio de login com senha incorreta." << endl;

    // TESTE 2: Sucesso no Login e Validação de Perfil
    // O sistema deve logar o admin e carregar o perfil correto do JSON
    assert(system.login("admin@grama.com", "admin123") == true);
    assert(system.getLoggedUser() != nullptr);
    assert(system.getLoggedUser()->profile == ADMINISTRATOR);
    cout << "[PASS] Teste 2: Autenticacao de Administrador com sucesso." << endl;

    // TESTE 3: Regra de Negócio - Impedir E-mail Duplicado
    // O Administrador não pode cadastrar um e-mail que já existe
    assert(system.registerUser("vendedor@grama.com", "novasenha", SELLER) == false);
    cout << "[PASS] Teste 3: Bloqueio de cadastro duplicado." << endl;

    // TESTE 4: Isolamento de Permissão (Segurança)
    // Apenas Administradores podem cadastrar novos usuários
    system.logout();
    system.login("vendedor@grama.com", "vend123"); // Loga com perfil Vendedor
    assert(system.registerUser("hacker@grama.com", "123", CUSTOMER) == false);
    cout << "[PASS] Teste 4: Bloqueio de cadastro por usuario sem permissao." << endl;

    // TESTE 5: Cadastro com Sucesso (Opcional para rodar uma vez)
    // Como o assert interrompe a execução se falhar, este teste de sucesso deve usar 
    // um e-mail novo, senão vai falhar por duplicação na segunda vez que você rodar.
    system.logout();
    system.login("admin@grama.com", "admin123");
    
    // Geramos um email aleatório (usando timestamp) para o teste não quebrar se rodar duas vezes
    string emailTeste = "teste_" + to_string(time(nullptr)) + "@grama.com";
    assert(system.registerUser(emailTeste, "senha_teste", CUSTOMER) == true);
    cout << "[PASS] Teste 5: Cadastro de usuario feito pelo Admin com sucesso." << endl;

    cout << "\n=== TODOS OS TESTES PASSARAM COM SUCESSO! ===" << endl;
}

int main() {
    rodarTestesUnitarios();
    return 0;
}