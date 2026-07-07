#include "test_login_reg.h"
#include "test_persistencia.h"
#include "test_PrecoBase.h"

int main() {
    rodarTestesUnitarios();
    teste_persistencia_update_afeta_linha();
    teste_atualizacao_preco_valido();
    return 0;
}