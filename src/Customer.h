#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

/**
 * @brief Estrutura que representa um cliente cadastrado no sistema.
 *
 * Armazena os dados básicos de contato utilizados em operações de cadastro,
 * consulta e manutenção de clientes.
 */
struct Customer {
    /// Nome completo do cliente.
    std::string name;

    /// Número de telefone do cliente.
    std::string phone;

    /// Endereço principal do cliente.
    std::string address;
};

#endif