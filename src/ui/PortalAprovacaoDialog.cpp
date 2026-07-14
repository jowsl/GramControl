#include "PortalAprovacaoDialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QIntValidator>

PortalAprovacaoDialog::PortalAprovacaoDialog(const QString& emailLogado, QWidget* parent)
    : QDialog(parent), emailLogado(emailLogado), idCarregado(-1) {
    setWindowTitle("Grama Portal - Aprovacao de Orcamento");
    resize(420, 320);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* titulo = new QLabel("=== PORTAL DE APROVACAO ===", this);
    titulo->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titulo);

    QFormLayout* form = new QFormLayout();
    inputId = new QLineEdit(this);
    inputId->setPlaceholderText("Ex: 123");
    inputId->setValidator(new QIntValidator(1, 1000000, this));
    btnBuscar = new QPushButton("Buscar Orcamento", this);

    QHBoxLayout* linhaBusca = new QHBoxLayout();
    linhaBusca->addWidget(inputId);
    linhaBusca->addWidget(btnBuscar);
    form->addRow("ID do Orcamento:", linhaBusca);
    mainLayout->addLayout(form);

    labelResumo = new QLabel("Informe o ID do orcamento recebido para visualizar a proposta.", this);
    labelResumo->setWordWrap(true);
    labelResumo->setAlignment(Qt::AlignLeft);
    mainLayout->addWidget(labelResumo);

    QHBoxLayout* botoesDecisao = new QHBoxLayout();
    btnRecusar = new QPushButton("Recusar", this);
    btnAprovar = new QPushButton("Aprovar", this);
    botoesDecisao->addWidget(btnRecusar);
    botoesDecisao->addWidget(btnAprovar);
    mainLayout->addLayout(botoesDecisao);

    btnFechar = new QPushButton("Fechar", this);
    mainLayout->addWidget(btnFechar);

    connect(btnBuscar,  &QPushButton::clicked, this, &PortalAprovacaoDialog::handleBuscar);
    connect(btnAprovar, &QPushButton::clicked, this, &PortalAprovacaoDialog::handleAprovar);
    connect(btnRecusar, &QPushButton::clicked, this, &PortalAprovacaoDialog::handleRecusar);
    connect(btnFechar,  &QPushButton::clicked, this, &QDialog::accept);

    atualizarBotoesDecisao();
}

void PortalAprovacaoDialog::atualizarBotoesDecisao() {
    bool podeDecidir = idCarregado > 0
                     && orcamentoAtual.getStatus() == "Aguardando Aprovação"
                     && orcamentoAtual.getEmailCliente() == emailLogado.toStdString();

    btnAprovar->setEnabled(podeDecidir);
    btnRecusar->setEnabled(podeDecidir);
}

void PortalAprovacaoDialog::handleBuscar() {
    bool ok = false;
    int id = inputId->text().toInt(&ok);

    if (!ok || id <= 0) {
        QMessageBox::warning(this, "ID invalido", "Informe um ID de orcamento valido.");
        return;
    }

    OrcamentoController controller;
    if (!controller.carregarOrcamento(id, orcamentoAtual)) {
        idCarregado = -1;
        labelResumo->setText("Orcamento nao encontrado. Verifique o ID informado.");
        atualizarBotoesDecisao();
        return;
    }

    idCarregado = id;
    labelResumo->setText(QString::fromStdString(controller.buscarDetalhamento(id)));

    if (orcamentoAtual.getEmailCliente() != emailLogado.toStdString()) {
        labelResumo->setText(labelResumo->text() + "\n\n(Este orcamento pertence a outro cliente.)");
    } else if (orcamentoAtual.getStatus() != "Aguardando Aprovação") {
        labelResumo->setText(labelResumo->text() + "\n\n(Este orcamento ja foi decidido.)");
    }

    atualizarBotoesDecisao();
}

void PortalAprovacaoDialog::handleAprovar() {
    OrcamentoController controller;
    if (!controller.aprovarOrcamento(idCarregado, emailLogado.toStdString())) {
        QMessageBox::critical(this, "Erro",
            "Nao foi possivel aprovar este orcamento. Ele pode ja ter sido decidido.");
        return;
    }

    QMessageBox::information(this, "Orcamento aprovado", "Orcamento aprovado com sucesso!");
    controller.carregarOrcamento(idCarregado, orcamentoAtual);
    labelResumo->setText(QString::fromStdString(controller.buscarDetalhamento(idCarregado)));
    atualizarBotoesDecisao();
}

void PortalAprovacaoDialog::handleRecusar() {
    OrcamentoController controller;
    if (!controller.recusarOrcamento(idCarregado, emailLogado.toStdString())) {
        QMessageBox::critical(this, "Erro",
            "Nao foi possivel recusar este orcamento. Ele pode ja ter sido decidido.");
        return;
    }

    QMessageBox::information(this, "Orcamento recusado", "Orcamento recusado.");
    controller.carregarOrcamento(idCarregado, orcamentoAtual);
    labelResumo->setText(QString::fromStdString(controller.buscarDetalhamento(idCarregado)));
    atualizarBotoesDecisao();
}
