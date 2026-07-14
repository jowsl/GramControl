#ifndef CADASTRARPLANTIODIALOG_HPP
#define CADASTRARPLANTIODIALOG_HPP

#include <QDialog>
#include "PlantioController.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class CadastrarPlantioDialog; }
QT_END_NAMESPACE

class CadastrarPlantioDialog : public QDialog {
    Q_OBJECT

public:
    explicit CadastrarPlantioDialog(QWidget *parent = nullptr);
    ~CadastrarPlantioDialog();

private slots:
    void salvarPlantio();

private:
    Ui::CadastrarPlantioDialog *ui;
    PlantioController controller;
};

#endif // CADASTRARPLANTIODIALOG_HPP