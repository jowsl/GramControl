#include <QApplication>
#include <QMessageBox>
#include "GramControl.h"
#include "ui/LoginWindow.h"
#include "ui/AdminWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    GramControl system;

    LoginWindow loginWin(&system);
    AdminWindow adminWin(&system);

    // Orchestrating screen flows with Lambda functions connected to signals
    QObject::connect(&loginWin, &LoginWindow::loginSuccessful, [&](int profile) {
        if (profile == 0) { // ADMINISTRATOR
            loginWin.hide();
            adminWin.show();
        } else {
            // Context handling for other profiles belonging to other team groups
            QMessageBox::warning(&loginWin, "Aviso", "Logado com outro perfil. O escopo dessa interface pertence a outra equipe.");
            system.logout();
        }
    });

    QObject::connect(&adminWin, &AdminWindow::logoutRequested, [&]() {
        adminWin.hide();
        loginWin.show();
    });

    // Start showing the primary interface window
    loginWin.show();

    return app.exec();
#include "AtualizarPrecoDialog.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    AtualizarPrecoDialog dialog;
    return dialog.exec();
}