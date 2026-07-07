#include <iostream>
#include <cassert>
#include <string>
#include <ctime>
#include "test_login_reg.h"
#include "../../src/GramControl.h"

using namespace std;

void rodarTestesUnitarios() {
    GramControl system;

    cout << "--- INICIANDO BATERIA DE TESTES (HANDLE-BODY + SQLITE) ---" << endl;

    // TESTE 1: Falha no Login (Credenciais Inválidas)
    assert(system.login("admin@grama.com", "senha_errada") == false);
    assert(system.getLoggedUser() == nullptr);
    cout << "[PASS] Teste 1: Bloqueio de login com senha incorreta." << endl;

    // TESTE 2: Sucesso no Login e Validação de Perfil
    // *Nota: Para este teste passar, o admin@grama.com com senha admin123 
    // já deve existir no seu auth.db
    assert(system.login("admin@grama.com", "admin123") == true);
    assert(system.getLoggedUser() != nullptr);
    assert(system.getLoggedUser()->profile == ADMINISTRATOR);
    cout << "[PASS] Teste 2: Autenticacao de Administrador com sucesso." << endl;

    // TESTE 3: Regra de Negócio - Impedir E-mail Duplicado (Integridade do BD)
    assert(system.registerUser("admin@grama.com", "novasenha", SELLER) == false);
    cout << "[PASS] Teste 3: Bloqueio de cadastro duplicado." << endl;

    // TESTE 4: Cadastro com Sucesso no SQLite
    // Usamos o timestamp atual no e-mail para que o teste possa ser rodado 
    // 1000 vezes sem quebrar a restrição de PRIMARY KEY (e-mail unico) do SQLite
    string emailNovo = "cliente_" + to_string(time(nullptr)) + "@grama.com";
    assert(system.registerUser(emailNovo, "senha123", CUSTOMER) == true);
    cout << "[PASS] Teste 4: Cadastro de novo usuario no banco SQLite com sucesso." << endl;

    // TESTE 5: Isolamento de Permissão e Logout
    system.logout();
    assert(system.getLoggedUser() == nullptr); // Garante que deslogou
    
    // Loga com o usuário recém-criado (Perfil Cliente)
    assert(system.login(emailNovo, "senha123") == true); 
    assert(system.registerUser("hacker@grama.com", "123", CUSTOMER) == false);
    cout << "[PASS] Teste 5: Bloqueio de cadastro por usuario sem permissao." << endl;

    cout << "=== TODOS OS TESTES DE AUTENTICACAO PASSARAM! ===\n" << endl;
}