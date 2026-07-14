#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include "../GramControl.h"
#include "../AtualizarPrecoDialog.hpp"

class AdminWindow : public QWidget {
    Q_OBJECT
private:
    GramControl* system;
    QLineEdit* emailInput;
    QLineEdit* passwordInput;
    QComboBox* profileCombo;
    QPushButton* registerButton;
    QPushButton* logoutButton;
    QPushButton* atualizarPrecosButton;
    QPushButton* gerarOrcamentoButton;   // Req. 5.7 - Inserir Metragem e Tipo de Grama
    QPushButton* cadastrarPlantioButton;
    QPushButton* calendarioPlantiosButton; // Calendário de plantios confirmados

private slots:
    void handleRegister();
    void handleLogout();
    void handleAtualizarPrecos();
    void handleGerarOrcamento();   // Req. 5.7
    void handleCadastrarPlantio(); 
    void handleCalendarioPlantios(); // Disponibilizar calendário de plantios confirmados

signals:
    void logoutRequested();

public:
    AdminWindow(GramControl* ctrl, QWidget* parent = nullptr);
};
#endif
