#include <iostream>
#include <cassert>
#include "test_login_reg.h"
#include "../../src/GramControl.h"

using namespace std;

void rodarTestesUnitarios() {
    GramControl system;

    cout << "--- INICIANDO BATERIA DE TESTES COM HANDLE-BODY ---" << endl;

    // TESTE 1: Falha no Login (Credenciais Inválidas)
    assert(system.login("admin@grama.com", "senha_errada") == false);
    assert(system.getLoggedUser() == nullptr);
    cout << "[PASS] Teste 1: Bloqueio de login com senha incorreta." << endl;

    // TESTE 2: Sucesso no Login e Validação de Perfil
    assert(system.login("admin@grama.com", "admin123") == true);
    assert(system.getLoggedUser() != nullptr);
    assert(system.getLoggedUser()->profile == ADMINISTRATOR);
    cout << "[PASS] Teste 2: Autenticacao de Administrador com sucesso." << endl;

    // TESTE 3: Regra de Negócio - Impedir E-mail Duplicado
    assert(system.registerUser("vendedor@grama.com", "novasenha", SELLER) == false);
    cout << "[PASS] Teste 3: Bloqueio de cadastro duplicado." << endl;

    // TESTE 4: Isolamento de Permissão (Segurança)
    system.logout();
    system.login("vendedor@grama.com", "vend123"); 
    assert(system.registerUser("hacker@grama.com", "123", CUSTOMER) == false);
    cout << "[PASS] Teste 4: Bloqueio de cadastro por usuario sem permissao." << endl;

    cout << "\n=== TODOS OS TESTES PASSARAM COM SUCESSO! ===" << endl;
}