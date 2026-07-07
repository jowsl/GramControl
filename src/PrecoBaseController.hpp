#ifndef PRECOBASECONTROLLER_HPP
#define PRECOBASECONTROLLER_HPP

#include <string>
#include "PrecoBase.hpp"
#include "PrecoBaseDAO.hpp"

/**
 * @class PrecoBaseController
 * @brief Controlador responsável por intermediar a View e o DAO para os Preços Base.
 */
class PrecoBaseController {
public:
    PrecoBaseController();
    ~PrecoBaseController();
    PrecoBaseController(const PrecoBaseController& outro);
    PrecoBaseController& operator=(const PrecoBaseController& outro);

    /**
     * @brief Requisita a atualização do preço de um item no sistema.
     * @param nomeItem Nome do item a ser atualizado.
     * @param novoPreco Novo valor numérico a ser salvo.
     * @return true se a atualização foi bem-sucedida.
     */
    bool requisitarAtualizacaoPreco(std::string nomeItem, double novoPreco);
};

#endif