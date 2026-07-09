#include <iostream>
#include <cassert>
#include <string>
#include <ctime>
#include "test_login_reg.h"
#include "../../src/GramControl.h"

using namespace std;

void rodarTestesUnitarios() {
    GramControl system;

    cout << "--- INICIANDO TESTES UNITARIOS POR FUNCAO (GRAMCONTROL) ---" << endl;

    // 1. Teste Unitário da função: generateHash()
    // Objetivo: Garantir que o motor de hash é determinístico e diferencia senhas.
    size_t hash1 = system.generateHash("senha123");
    size_t hash2 = system.generateHash("senha123");
    size_t hash3 = system.generateHash("outrasenha");
    assert(hash1 == hash2); 
    assert(hash1 != hash3); 
    cout << "[PASS] Unit Test: generateHash()" << endl;

    // 2. Teste Unitário da função: login()
    // Objetivo: Testar os retornos booleanos de sucesso e falha da autenticação.
    assert(system.login("admin@grama.com", "senha_errada") == false);
    assert(system.login("admin@grama.com", "admin123") == true);
    cout << "[PASS] Unit Test: login()" << endl;

    // 3. Teste Unitário da função: getLoggedUser()
    // Objetivo: Validar a recuperação do ponteiro de memória do usuário correto.
    User* user = system.getLoggedUser();
    assert(user != nullptr);
    assert(user->email == "admin@grama.com");
    assert(user->profile == ADMINISTRATOR);
    cout << "[PASS] Unit Test: getLoggedUser()" << endl;

    // 4. Teste Unitário da função: logout()
    // Objetivo: Garantir que o estado interno (ponteiro) é limpo.
    system.logout();
    assert(system.getLoggedUser() == nullptr);
    cout << "[PASS] Unit Test: logout()" << endl;

    // 5. Teste Unitário da função: registerUser()
    // Objetivo: Validar os três caminhos de execução da função (Sucesso, Falha Duplicata, Falha Permissão).
    system.login("admin@grama.com", "admin123"); // Setup para ter permissão
    string emailNovo = "unit_test_" + to_string(time(nullptr)) + "@grama.com";

    assert(system.registerUser(emailNovo, "senha123", CUSTOMER) == true); 
    assert(system.registerUser("admin@grama.com", "nova", SELLER) == false); 

    system.logout();
    system.login(emailNovo, "senha123"); // Setup para testar recusa de permissão
    assert(system.registerUser("hacker@grama.com", "123", SELLER) == false); 
    cout << "[PASS] Unit Test: registerUser()" << endl;

    // 6. Teste Unitário da função: listUsers()
    // Objetivo: Como é um método void que apenas escreve no terminal, 
    // o teste garante que a função roda até o fim sem causar Segmentation Fault.
    cout << "     -> "; // Espaçamento visual para a saída da função não colar no log
    system.listUsers();
    cout << "[PASS] Unit Test: listUsers() [Execucao estavel sem crash]" << endl;

    cout << "=== TODOS OS TESTES UNITARIOS DE GRAMCONTROL PASSARAM! ===\n" << endl;
}