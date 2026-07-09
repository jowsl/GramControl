#include <QApplication>
#include <QMessageBox>
#include "GramControl.h"
#include "ui/LoginWindow.h"
#include "ui/AdminWindow.h"
#include "AtualizarPrecoDialog.hpp"
#include "CadastrarClienteDialog.hpp"

/**
 * @brief Ponto de entrada da aplicação GramControl.
 *
 * Inicializa a interface gráfica, cria a instância principal do sistema
 * e conecta os fluxos de login e logout entre as janelas.
 *
 * @param argc Número de argumentos de linha de comando.
 * @param argv Vetor com os argumentos de linha de comando.
 * @return Código de saída da aplicação.
 */

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    GramControl system;

    LoginWindow loginWin(&system);
    AdminWindow adminWin(&system);

    QObject::connect(&loginWin, &LoginWindow::loginSuccessful, [&](int profile) {
        if (profile == 0) { // ADMINISTRATOR
            loginWin.hide();
            adminWin.show();
        } else if (profile == 1) { // SELLER / Vendedor
            loginWin.hide();
            CadastrarClienteDialog* cadastroWin = new CadastrarClienteDialog();
            cadastroWin->show();
        } else {
            QMessageBox::warning(&loginWin, "Aviso", "Logado com outro perfil. O escopo dessa interface pertence a outra equipe.");
            system.logout();
        }
    });

    QObject::connect(&adminWin, &AdminWindow::logoutRequested, [&]() {
        adminWin.hide();
        loginWin.show();
    });

    loginWin.show();

    return app.exec();
}