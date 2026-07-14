#include "CadastrarPlantioDialog.hpp"
#include "ui_CadastrarPlantio.h" // Ficheiro criado automaticamente pelo CMake
#include <QMessageBox>

CadastrarPlantioDialog::CadastrarPlantioDialog(QWidget *parent) : 
    QDialog(parent), 
    ui(new Ui::CadastrarPlantioDialog) 
{
    ui->setupUi(this);

    // Preenche as opções de grama no combo box da tela
    ui->comboTipoGrama->addItems({"Esmeralda", "Batatais", "São Carlos", "Santo Agostinho"});

    // Faz as conexões dos botões usando os elementos do arquivo .ui
    connect(ui->btnSalvar, &QPushButton::clicked, this, &CadastrarPlantioDialog::salvarPlantio);
    connect(ui->btnCancelar, &QPushButton::clicked, this, &QDialog::reject);
}

CadastrarPlantioDialog::~CadastrarPlantioDialog() {
    delete ui;
}

void CadastrarPlantioDialog::salvarPlantio() {
    QString local = ui->inputLocal->text();
    QString dataHora = ui->inputDataHora->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    double area = ui->inputArea->value();
    QString tipoGrama = ui->comboTipoGrama->currentText();
    
    QMap<QString, double> insumos;
    insumos.insert("Adubo", area * 0.5); // Regra simples de exemplo

    if (controller.requisitarCadastroPlantio(local, dataHora, area, tipoGrama, insumos)) {
        QMessageBox::information(this, "Sucesso", "Plantio cadastrado com sucesso!");
        accept();
    } else {
        QMessageBox::critical(this, "Erro", "Falha ao cadastrar o plantio. Verifique os dados.");
    }
}