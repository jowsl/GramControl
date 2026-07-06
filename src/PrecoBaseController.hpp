#ifndef PRECOBASECONTROLLER_HPP
#define PRECOBASECONTROLLER_HPP

#include <QString>
#include "PrecoBase.hpp"
#include "PrecoBaseDAO.hpp"

/**
 * @class PrecoBaseController
 * @brief Controlador responsável por intermediar a comunicação entre a interface (View) e o banco de dados (DAO) para os Preços Base.
 */
class PrecoBaseController {
public:
    /**
     * @brief Construtor padrão.
     */
    PrecoBaseController();

    /**
     * @brief Destrutor padrão.
     */
    ~PrecoBaseController();

    /**
     * @brief Construtor de cópia (Forma Canônica).
     * @param outro Objeto a ser copiado.
     */
    PrecoBaseController(const PrecoBaseController& outro);

    /**
     * @brief Operador de atribuição (Forma Canônica).
     * @param outro Objeto a ser atribuído.
     * @return Referência para o próprio objeto.
     */
    PrecoBaseController& operator=(const PrecoBaseController& outro);
    
    /**
     * @brief Requisita a atualização do preço de um item no sistema.
     * @param nomeItem Nome do item a ser atualizado (ex: "Grama Esmeralda").
     * @param novoPreco Novo valor numérico a ser salvo.
     * @return true se a atualização no banco foi bem-sucedida, false caso contrário.
     */
    bool requisitarAtualizacaoPreco(QString nomeItem, double novoPreco);
};

#endif