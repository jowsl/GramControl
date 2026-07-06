/********************************************************************************
** Form generated from reading UI file 'AtualizarPreco.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ATUALIZARPRECO_H
#define UI_ATUALIZARPRECO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *widget;
    QFormLayout *formLayout;
    QLabel *NomeDoItem;
    QLineEdit *inputNomeItem;
    QLabel *NovoPreco;
    QDoubleSpinBox *inputNovoPreco;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(400, 300);
        widget = new QWidget(Dialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(31, 12, 171, 106));
        formLayout = new QFormLayout(widget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        NomeDoItem = new QLabel(widget);
        NomeDoItem->setObjectName(QString::fromUtf8("NomeDoItem"));

        formLayout->setWidget(0, QFormLayout::LabelRole, NomeDoItem);

        inputNomeItem = new QLineEdit(widget);
        inputNomeItem->setObjectName(QString::fromUtf8("inputNomeItem"));

        formLayout->setWidget(1, QFormLayout::SpanningRole, inputNomeItem);

        NovoPreco = new QLabel(widget);
        NovoPreco->setObjectName(QString::fromUtf8("NovoPreco"));

        formLayout->setWidget(2, QFormLayout::LabelRole, NovoPreco);

        inputNovoPreco = new QDoubleSpinBox(widget);
        inputNovoPreco->setObjectName(QString::fromUtf8("inputNovoPreco"));

        formLayout->setWidget(2, QFormLayout::FieldRole, inputNovoPreco);

        buttonBox = new QDialogButtonBox(widget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(3, QFormLayout::SpanningRole, buttonBox);


        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        NomeDoItem->setText(QCoreApplication::translate("Dialog", "Nome do Item", nullptr));
        NovoPreco->setText(QCoreApplication::translate("Dialog", "Novo Pre\303\247o (R$):", nullptr));
        inputNovoPreco->setPrefix(QString());
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ATUALIZARPRECO_H
