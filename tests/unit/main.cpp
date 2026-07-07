#include "test_login_reg.h"
#include "test_persistencia.h"
#include "test_PrecoBase.h"
#include "test_Orcamento.h"

int main() {
    rodarTestesUnitarios();
    teste_persistencia_update_afeta_linha();
    teste_atualizacao_preco_valido();

    // Requisito 5.7 - Inserir Metragem e Tipo de Grama
    teste_orcamento_calcula_valor_parcial_corretamente();
    teste_orcamento_rejeita_metragem_invalida();
    teste_orcamento_multiplos_tipos_de_grama();

    return 0;
}
