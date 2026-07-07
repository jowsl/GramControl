 #include <QApplication>
#include "CadastrarClienteDialog.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    CadastrarClienteDialog dialog;
    return dialog.exec();
}