#ifndef CADASTRARCLIENTEDIALOG_HPP
#define CADASTRARCLIENTEDIALOG_HPP

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include "ClienteController.hpp"

/**
 * @class CadastrarClienteDialog
 * @brief View do caso de uso "Cadastrar Cliente em Campo".
 */
class CadastrarClienteDialog : public QDialog
{
    Q_OBJECT
    
    public:
        // explicit: Previne a conversão implícita de tipos, garantindo que o construtor seja chamado apenas com um ponteiro QWidget ou nullptr.
        explicit CadastrarClienteDialog(QWidget *parent = nullptr);
    private:
        QLineEdit* nomeInput;
        QLineEdit* telefoneInput;
        QLineEdit* enderecoInput;
        QLineEdit* emailInput;
        QPushButton* salvarButton;
        QPushButton* cancelarButton;

    private slots:
        void handleSalvar();
};

#endif // CADASTRARCLIENTEDIALOG_HPP
