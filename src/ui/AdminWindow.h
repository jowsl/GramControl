#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include "../GramControl.h"

class AdminWindow : public QWidget {
    Q_OBJECT
private:
    GramControl* system;
    QLineEdit* emailInput;
    QLineEdit* passwordInput;
    QComboBox* profileCombo;
    QPushButton* registerButton;
    QPushButton* logoutButton;

private slots:
    void handleRegister();
    void handleLogout();

signals:
    void logoutRequested();

public:
    AdminWindow(GramControl* ctrl, QWidget* parent = nullptr);
};

#endif