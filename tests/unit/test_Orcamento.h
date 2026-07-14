#ifndef TEST_ORCAMENTO_H
#define TEST_ORCAMENTO_H

// Testes referentes ao Requisito 5.7 - Inserir Metragem e Tipo de Grama.
void teste_orcamento_calcula_valor_parcial_corretamente();
void teste_orcamento_rejeita_metragem_invalida();
void teste_orcamento_multiplos_tipos_de_grama();


void teste_orcamento_gerar_digital();
void teste_orcamento_visualizar_detalhamento();

// Testes referentes a "Aprovar ou Recusar orcamento digitalmente" (Sprint 2).
void teste_orcamento_carregarPorId_encontrado();
void teste_orcamento_carregarPorId_inexistente();
void teste_orcamento_aprovar_sucesso();
void teste_orcamento_aprovar_ja_decidido();
void teste_orcamento_aprovar_id_inexistente();
void teste_orcamento_recusar_sucesso();
void teste_orcamento_recusar_ja_decidido();
void teste_orcamento_decisao_email_nao_confere();

void teste_controller_carregarOrcamento();
void teste_controller_aprovarOrcamento_sucesso();
void teste_controller_recusarOrcamento_sucesso();

#endif // TEST_ORCAMENTO_H
