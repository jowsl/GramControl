#ifndef ATUALIZARPRECODIALOG_HPP
#define ATUALIZARPRECODIALOG_HPP

#include <QDialog>
#include "ui/ui_AtualizarPreco.h"
#include "PrecoBaseController.hpp"

/**
 * @class AtualizarPrecoDialog
 * @brief Janela de diálogo (View) para atualização do preço base de gramas e insumos.
 *
 * Esta classe representa a interface gráfica do caso de uso "Atualizar tabela de
 * preços base". Captura o nome do item e o novo preço informados pelo Administrador
 * e delega a persistência ao PrecoBaseController, exibindo o resultado da operação.
 */
class AtualizarPrecoDialog : public QDialog, public Ui::Dialog {
    Q_OBJECT
public:
    /**
     * @brief Construtor. Monta a interface e conecta o botão de confirmação ao slot de salvamento.
     * @param parent Widget pai responsável pela gestão de memória (padrão: nullptr).
     */
    AtualizarPrecoDialog(QWidget *parent = nullptr);

private slots:
    /**
     * @brief Slot acionado ao confirmar o diálogo.
     *
     * Recupera o nome do item e o novo preço dos campos da interface, requisita a
     * atualização ao PrecoBaseController e exibe uma mensagem de sucesso ou erro
     * conforme o retorno da operação.
     */
    void salvarPreco();
};
#endif