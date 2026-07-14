/********************************************************************************
** Form generated from reading UI file 'CadastrarPlantio.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CADASTRARPLANTIO_H
#define UI_CADASTRARPLANTIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CadastrarPlantioDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelLocal;
    QLineEdit *inputLocal;
    QLabel *labelData;
    QDateTimeEdit *inputDataHora;
    QLabel *labelArea;
    QDoubleSpinBox *inputArea;
    QLabel *labelGrama;
    QComboBox *comboTipoGrama;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnSalvar;
    QPushButton *btnCancelar;

    void setupUi(QDialog *CadastrarPlantioDialog)
    {
        if (CadastrarPlantioDialog->objectName().isEmpty())
            CadastrarPlantioDialog->setObjectName(QString::fromUtf8("CadastrarPlantioDialog"));
        CadastrarPlantioDialog->resize(400, 350);
        verticalLayout = new QVBoxLayout(CadastrarPlantioDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelLocal = new QLabel(CadastrarPlantioDialog);
        labelLocal->setObjectName(QString::fromUtf8("labelLocal"));

        verticalLayout->addWidget(labelLocal);

        inputLocal = new QLineEdit(CadastrarPlantioDialog);
        inputLocal->setObjectName(QString::fromUtf8("inputLocal"));

        verticalLayout->addWidget(inputLocal);

        labelData = new QLabel(CadastrarPlantioDialog);
        labelData->setObjectName(QString::fromUtf8("labelData"));

        verticalLayout->addWidget(labelData);

        inputDataHora = new QDateTimeEdit(CadastrarPlantioDialog);
        inputDataHora->setObjectName(QString::fromUtf8("inputDataHora"));

        verticalLayout->addWidget(inputDataHora);

        labelArea = new QLabel(CadastrarPlantioDialog);
        labelArea->setObjectName(QString::fromUtf8("labelArea"));

        verticalLayout->addWidget(labelArea);

        inputArea = new QDoubleSpinBox(CadastrarPlantioDialog);
        inputArea->setObjectName(QString::fromUtf8("inputArea"));
        inputArea->setMaximum(999999.989999999990687);

        verticalLayout->addWidget(inputArea);

        labelGrama = new QLabel(CadastrarPlantioDialog);
        labelGrama->setObjectName(QString::fromUtf8("labelGrama"));

        verticalLayout->addWidget(labelGrama);

        comboTipoGrama = new QComboBox(CadastrarPlantioDialog);
        comboTipoGrama->setObjectName(QString::fromUtf8("comboTipoGrama"));

        verticalLayout->addWidget(comboTipoGrama);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnSalvar = new QPushButton(CadastrarPlantioDialog);
        btnSalvar->setObjectName(QString::fromUtf8("btnSalvar"));

        horizontalLayout->addWidget(btnSalvar);

        btnCancelar = new QPushButton(CadastrarPlantioDialog);
        btnCancelar->setObjectName(QString::fromUtf8("btnCancelar"));

        horizontalLayout->addWidget(btnCancelar);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(CadastrarPlantioDialog);

        QMetaObject::connectSlotsByName(CadastrarPlantioDialog);
    } // setupUi

    void retranslateUi(QDialog *CadastrarPlantioDialog)
    {
        CadastrarPlantioDialog->setWindowTitle(QCoreApplication::translate("CadastrarPlantioDialog", "Cadastrar Plantio Confirmado", nullptr));
        labelLocal->setText(QCoreApplication::translate("CadastrarPlantioDialog", "Local do Plantio:", nullptr));
        labelData->setText(QCoreApplication::translate("CadastrarPlantioDialog", "Data e Hora:", nullptr));
        labelArea->setText(QCoreApplication::translate("CadastrarPlantioDialog", "\303\201rea (m\302\262):", nullptr));
        labelGrama->setText(QCoreApplication::translate("CadastrarPlantioDialog", "Tipo de Grama:", nullptr));
        btnSalvar->setText(QCoreApplication::translate("CadastrarPlantioDialog", "Salvar", nullptr));
        btnCancelar->setText(QCoreApplication::translate("CadastrarPlantioDialog", "Cancelar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CadastrarPlantioDialog: public Ui_CadastrarPlantioDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CADASTRARPLANTIO_H
