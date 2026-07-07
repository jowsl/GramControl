#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include "../GramControl.h"

class LoginWindow : public QWidget {
    Q_OBJECT
private:
    GramControl* system;
    QLineEdit* emailInput;
    QLineEdit* passwordInput;
    QPushButton* loginButton;

private slots:
    void handleLogin();

signals:
    void loginSuccessful(int profile);

public:
    LoginWindow(GramControl* ctrl, QWidget* parent = nullptr);
};

#endif