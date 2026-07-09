#ifndef TEST_CLIENTE_H
#define TEST_CLIENTE_H

/**
 * @file test_Cliente.hpp
 * @brief Arquivo de teste para a estrutura Customer.
 *
 * Este arquivo contém declarações de funções de teste para validar o comportamento da estrutura Customer,
 * incluindo casos de teste para clientes válidos e inválidos.
 */
void teste_cliente_valido();

/**
 * @brief Testa o cadastro de clientes sem nome ou telefone.
 *
 * Esta função verifica se a validação de clientes funciona corretamente quando o nome ou telefone está ausente.
 */
void teste_cliente_sem_nome_ou_telefone();

#endif // TEST_CLIENTE_H