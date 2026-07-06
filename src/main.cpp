#include <QApplication>
#include "AtualizarPrecoDialog.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    AtualizarPrecoDialog dialog;
    return dialog.exec();
}