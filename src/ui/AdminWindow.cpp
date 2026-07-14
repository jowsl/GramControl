#include "AdminWindow.h"
#include "OrcamentoDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include "OrcamentoController.hpp"
#include <QInputDialog>

AdminWindow::AdminWindow(GramControl* ctrl, QWidget* parent) : QWidget(parent), system(ctrl) {
    setWindowTitle("GramAdmin - Perfis");
    resize(400, 400);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* titleLabel = new QLabel("=== GRAMADMIN - ADMINISTRACAO DE PERFIS ===", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    mainLayout->addWidget(new QLabel("New User E-mail:", this));
    emailInput = new QLineEdit(this);
    mainLayout->addWidget(emailInput);

    mainLayout->addWidget(new QLabel("New User Password:", this));
    passwordInput = new QLineEdit(this);
    passwordInput->setEchoMode(QLineEdit::Password);
    mainLayout->addWidget(passwordInput);

    mainLayout->addWidget(new QLabel("Associate Role:", this));
    profileCombo = new QComboBox(this);
    profileCombo->addItem("Administrador", 0);
    profileCombo->addItem("Vendedor", 1);
    profileCombo->addItem("Prestador de Servico", 2);
    profileCombo->addItem("Cliente", 3);
    mainLayout->addWidget(profileCombo);

    registerButton = new QPushButton("Cadastrar Novo Usuario", this);
    mainLayout->addWidget(registerButton);

    logoutButton = new QPushButton("Fazer Logout", this);
    mainLayout->addWidget(logoutButton);

    atualizarPrecosButton = new QPushButton("Atualizar Tabela de Precos", this);
    mainLayout->addWidget(atualizarPrecosButton);
    connect(atualizarPrecosButton, &QPushButton::clicked, this, &AdminWindow::handleAtualizarPrecos);

    // Req. 5.7 - Inserir Metragem e Tipo de Grama
    gerarOrcamentoButton = new QPushButton("Gerar Orcamento (Metragem + Tipo de Grama)", this);
    mainLayout->addWidget(gerarOrcamentoButton);
    connect(gerarOrcamentoButton, &QPushButton::clicked, this, &AdminWindow::handleGerarOrcamento);

    // NOVO BOTAO AQUI:
    visualizarOrcamentoButton = new QPushButton("Visualizar Orcamento por ID", this);
    mainLayout->addWidget(visualizarOrcamentoButton);
    connect(visualizarOrcamentoButton, &QPushButton::clicked, this, &AdminWindow::handleVisualizarOrcamento);
}

void AdminWindow::handleRegister() {
    std::string email = emailInput->text().toStdString();
    std::string password = passwordInput->text().toStdString();

    if (email.empty() || password.empty()) {
        QMessageBox::warning(this, "Aviso", "Por favor, preencha o e-mail e a senha do novo usuario.");
        return;
    }

    int profileValue = profileCombo->currentData().toInt();
    Profile profile = static_cast<Profile>(profileValue);

    if (system->registerUser(email, password, profile)) {
        QMessageBox::information(this, "Success", "Usuario cadastrado e salvo no JSON!");
        emailInput->clear();
        passwordInput->clear();
    } else {
        QMessageBox::critical(this, "Error", "Falha ao cadastrar usuario. Verifique as permissoes ou duplicidade.");
    }
}

void AdminWindow::handleLogout() {
    system->logout();
    emit logoutRequested();
}

void AdminWindow::handleAtualizarPrecos() {
    AtualizarPrecoDialog dialog(this);
    dialog.exec();
}

void AdminWindow::handleGerarOrcamento() {
    OrcamentoDialog dialog(this);
    dialog.exec();
}

void AdminWindow::handleVisualizarOrcamento() {
    bool ok;
    // Abre uma caixa de diálogo pedindo um número inteiro (ID)
    int idBusca = QInputDialog::getInt(this, "Visualizar Orcamento", 
                                       "Digite o ID do Orcamento:", 
                                       1, 1, 1000000, 1, &ok);
    
    // Se o usuário clicou em OK e digitou um número
    if (ok) {
        OrcamentoController controller;
        std::string detalhes = controller.buscarDetalhamento(idBusca);
        QMessageBox::information(this, "Detalhes do Orcamento", QString::fromStdString(detalhes));
    }
}