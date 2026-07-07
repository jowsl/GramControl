#include "test_login_reg.h"
#include "test_persistencia.h"
#include "test_PrecoBase.h"
#include "test_Cliente.hpp"
#include "test_persistencia_cliente.hpp"

int main() {
    rodarTestesUnitarios();
    teste_persistencia_update_afeta_linha();
    teste_atualizacao_preco_valido();
    teste_cliente_valido();
    teste_cliente_sem_nome_ou_telefone();
    teste_persistencia_insere_cliente();
    return 0;
}