#ifndef PORTALAPROVACAODIALOG_H
#define PORTALAPROVACAODIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "../OrcamentoController.hpp"

/**
 * @class PortalAprovacaoDialog
 * @brief View do caso de uso "Aprovar ou Recusar orçamento digitalmente"
 *        (Serviço de Atendimento ao Cliente).
 *
 * Interface simplificada do Gram Portal (Tabela 4 do DER) onde o Cliente
 * autenticado informa o ID do orçamento recebido, visualiza o resumo da
 * proposta e decide aprová-la ou recusá-la.
 */
class PortalAprovacaoDialog : public QDialog {
    Q_OBJECT
public:
    /**
     * @param emailLogado E-mail do Cliente autenticado (dono dos orçamentos).
     * @param parent Widget pai, se houver.
     */
    explicit PortalAprovacaoDialog(const QString& emailLogado, QWidget* parent = nullptr);

private slots:
    void handleBuscar();
    void handleAprovar();
    void handleRecusar();

private:
    void atualizarBotoesDecisao();

    QString emailLogado;
    int     idCarregado;
    Orcamento orcamentoAtual;

    QLineEdit*   inputId;
    QPushButton* btnBuscar;
    QLabel*      labelResumo;
    QPushButton* btnAprovar;
    QPushButton* btnRecusar;
    QPushButton* btnFechar;
};

#endif
