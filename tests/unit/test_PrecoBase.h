#ifndef TEST_PRECOBASE_H
#define TEST_PRECOBASE_H

/**
 * @brief Testa a atualização de preço válido no sistema.
 *
 * Esta função verifica se a atualização de preço para um valor válido é realizada corretamente,
 * garantindo que o sistema aceite e persista o novo preço conforme esperado.
 */
void teste_atualizacao_preco_valido();

/**
 * @brief Testa a rejeição de preço negativo.
 */
void teste_atualizacao_preco_negativo();

/**
 * @brief Testa se getPreco retorna o valor correto.
 */
void teste_get_preco();

/**
 * @brief Testa se getNome retorna o nome correto.
 */
void teste_get_nome();

/**
 * @brief Testa os valores iniciais do construtor padrão.
 */
void teste_construtor_padrao();

/**
 * @brief Testa se o UPDATE de item inexistente retorna false.
 */
void teste_persistencia_item_inexistente();

/**
 * @brief Testa o Controller com preço válido.
 */
void teste_controller_preco_valido();

/**
 * @brief Testa o Controller com preço negativo.
 */
void teste_controller_preco_negativo();

/**
 * @brief Testa o Controller com item inexistente.
 */
void teste_controller_item_inexistente();

#endif // TEST_PRECOBASE_H