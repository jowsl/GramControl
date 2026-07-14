#ifndef TEST_PLANTIO_HPP
#define TEST_PLANTIO_HPP

/**
 * @file test_Plantio.hpp
 * @brief Arquivo de teste para a estrutura Plantio (Handle/Body).
 *
 * Este arquivo contém declarações de funções de teste para validar o comportamento do modelo Plantio,
 * incluindo casos de teste com dados válidos e inválidos.
 */

/**
 * @brief Testa a instanciação e validação de um plantio com dados corretos.
 */
void teste_plantio_valido();

/**
 * @brief Testa as regras de negócio de validação de dados inconsistentes (área inválida ou sem local).
 */
void teste_plantio_dados_invalidos();

#endif // TEST_PLANTIO_HPP