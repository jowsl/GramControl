#ifndef ORCAMENTODIALOG_HPP
#define ORCAMENTODIALOG_HPP

#include <QDialog>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include "OrcamentoController.hpp"

/**
 * @class OrcamentoDialog
 * @brief View do caso de uso "Inserir Metragem e Tipo de Grama" (Req. 5.7).
 *
 * Permite ao vendedor informar a metragem do terreno e selecionar a
 * variedade de grama desejada. Aciona o OrcamentoController para calcular
 * o valor parcial do serviço usando os preços cadastrados.
 */
class OrcamentoDialog : public QDialog {
    Q_OBJECT
public:
    explicit OrcamentoDialog(QWidget* parent = nullptr);

private slots:
    void calcularOrcamento();
    void gerarOrcamentoDigital();

private:
    void carregarTiposDeGrama();

    QLineEdit*      inputEmail;
    QDoubleSpinBox* inputMetragem;
    QComboBox*      comboTipoGrama;
    QPushButton*    btnCalcular;
    QPushButton*    btnGerarDigital;
    QPushButton*    btnFechar;
    QLabel*         labelResultado;
    QLabel*         labelPrecoUnitario;
};

#endif
