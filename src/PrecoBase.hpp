#ifndef PRECOBASE_HPP
#define PRECOBASE_HPP

#include <QString>

/**
 * @class PrecoBase
 * @brief Classe de modelo (Model) que representa o preço base de gramas e insumos.
 *
 * Esta classe segue a Forma Canônica de Coplien e gerencia as validações de regra
 * de negócio para os preços base do sistema GramControl.
 */
class PrecoBase {
private:
    QString nomeItem;   /**< Nome descritivo da variedade de grama ou insumo */
    double precoAtual;  /**< Valor atual do item por metro quadrado ou unidade */

public:
    /**
     * @brief Construtor Padrão.
     */
    PrecoBase();

    /**
     * @brief Construtor Parametrizado.
     * @param nome O nome do item em formato QString.
     * @param precoInicial O preço inicial atribuído ao item.
     */
    PrecoBase(QString nome, double precoInicial);

    /**
     * @brief Destrutor virtual.
     */
    virtual ~PrecoBase();

    /**
     * @brief Construtor de Cópia.
     * @param outro O objeto PrecoBase a ser copiado.
     */
    PrecoBase(const PrecoBase& outro);

    /**
     * @brief Operador de Atribuição.
     * @param outro O objeto PrecoBase a ser atribuído.
     * @return Referência para o próprio objeto atualizado.
     */
    PrecoBase& operator=(const PrecoBase& outro);

    /**
     * @brief Atualiza o preço base do item após validação de regra de negócio.
     * @param novoPreco O novo valor a ser atribuído.
     * @return true se o preço for atualizado com sucesso (não negativo), false caso contrário.
     */
    bool atualizarPreco(double novoPreco);

    /**
     * @brief Retorna o preço atual do item.
     * @return double contendo o preço.
     */
    double getPreco() const;

    /**
     * @brief Retorna o nome do item.
     * @return QString contendo o nome do item.
     */
    QString getNome() const;
};

#endif