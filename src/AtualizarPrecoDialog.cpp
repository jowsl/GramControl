#include "AtualizarPrecoDialog.hpp"
#include <QMessageBox>

AtualizarPrecoDialog::AtualizarPrecoDialog(QWidget *parent) : QDialog(parent) {
    setupUi(this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &AtualizarPrecoDialog::salvarPreco);
}

void AtualizarPrecoDialog::salvarPreco() {
    PrecoBaseController controller;
    // Converte QString → std::string aqui na View, não no backend
    std::string nome = inputNomeItem->text().toStdString();
    double novoPreco = inputNovoPreco->value();

    if (controller.requisitarAtualizacaoPreco(nome, novoPreco)) {
        QMessageBox::information(this, "Sucesso", "Preço salvo com sucesso!");
        accept();
    } else {
        QMessageBox::warning(this, "Erro", "Falha ao salvar no banco de dados.");
    }
}