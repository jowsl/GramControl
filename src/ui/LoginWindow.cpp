#include "LoginWindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

LoginWindow::LoginWindow(GramControl* ctrl, QWidget* parent) : QWidget(parent), system(ctrl) {
    setWindowTitle("GramControl - Login");
    resize(350, 250);

    // Layout configuration
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* titleLabel = new QLabel("=== LOGIN SCREEN ===", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    layout->addWidget(new QLabel("E-mail:", this));
    emailInput = new QLineEdit(this);
    layout->addWidget(emailInput);

    layout->addWidget(new QLabel("Password:", this));
    passwordInput = new QLineEdit(this);
    passwordInput->setEchoMode(QLineEdit::Password); // Masks password input
    layout->addWidget(passwordInput);

    loginButton = new QPushButton("LOGIN", this);
    layout->addWidget(loginButton);

    // Connect event using Qt Signals and Slots
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::handleLogin);
    // Conecta o Enter no campo de senha ou e-mail direto para a função de login
    connect(emailInput, &QLineEdit::returnPressed, this, &LoginWindow::handleLogin);
    connect(passwordInput, &QLineEdit::returnPressed, this, &LoginWindow::handleLogin);
}

void LoginWindow::handleLogin() {
    QString email = emailInput->text();
    QString password = passwordInput->text();

    // Invokes the backend logic validated in the terminal stage
    if (system->login(email.toStdString(), password.toStdString())) {
        QMessageBox::information(this, "Success", "Login successful!");
        emailInput->clear();
        passwordInput->clear();
        emit loginSuccessful(static_cast<int>(system->getLoggedUser()->profile));
    } else {
        // Implements the error requirement from the specifications document
        QMessageBox::critical(this, "Error", "Invalid credentials. Please try again.");
    }
}