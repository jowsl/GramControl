#include "CadastrarClienteDialog.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

CadastrarClienteDialog::CadastrarClienteDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Grama Vendas - Cadastrar Cliente");
    resize(360, 320);

    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* titleLabel = new QLabel("<h2>Cadastrar Cliente</h2>", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    layout->addWidget(new QLabel("Nome:", this));
    nomeInput = new QLineEdit(this);
    layout->addWidget(nomeInput);

    layout->addWidget(new QLabel("Telefone:", this));
    telefoneInput = new QLineEdit(this);
    telefoneInput->setPlaceholderText("XX XXXXX-XXXX");
    layout->addWidget(telefoneInput);

    layout->addWidget(new QLabel("Endereço:", this));
    enderecoInput = new QLineEdit(this);
    layout->addWidget(enderecoInput);

    layout->addWidget(new QLabel("Email:", this));
    emailInput = new QLineEdit(this);
    layout->addWidget(emailInput);

    salvarButton = new QPushButton("Cadastrar Cliente", this);
    layout->addWidget(salvarButton);

    cancelarButton = new QPushButton("Cancelar", this);
    layout->addWidget(cancelarButton);

    connect(salvarButton, &QPushButton::clicked, this, &CadastrarClienteDialog::handleSalvar);
    connect(cancelarButton, &QPushButton::clicked, this, &CadastrarClienteDialog::reject);
}

void CadastrarClienteDialog::handleSalvar(){
    ClienteController controller;
    QString mensagemErro;

    bool sucesso = controller.cadastrarCliente(
        nomeInput->text(),
        telefoneInput->text(),
        enderecoInput->text(),
        emailInput->text(),
        mensagemErro
    );

    if(sucesso){
        QMessageBox::information(this, "Sucesso", "Cliente cadastrado com sucesso!");
        accept(); // Fecha o diálogo com sucesso
    } else {
        QMessageBox::critical(this, "Erro", mensagemErro);
    }
}