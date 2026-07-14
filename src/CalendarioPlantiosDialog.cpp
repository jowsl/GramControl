#include "CalendarioPlantiosDialog.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateTime>
#include <QTextCharFormat>
#include <QBrush>
#include <QColor>

CalendarioPlantiosDialog::CalendarioPlantiosDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Calendario de Plantios Confirmados");
    resize(640, 420);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* titleLabel = new QLabel("=== CALENDARIO DE PLANTIOS CONFIRMADOS ===", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    QHBoxLayout* contentLayout = new QHBoxLayout();

    calendario = new QCalendarWidget(this);
    calendario->setGridVisible(true);
    contentLayout->addWidget(calendario, 2);

    QVBoxLayout* listaLayout = new QVBoxLayout();
    labelTituloLista = new QLabel("Selecione um dia destacado para ver os plantios.", this);
    labelTituloLista->setWordWrap(true);
    listaLayout->addWidget(labelTituloLista);

    listaPlantiosDoDia = new QListWidget(this);
    listaLayout->addWidget(listaPlantiosDoDia);

    contentLayout->addLayout(listaLayout, 1);
    mainLayout->addLayout(contentLayout);

    connect(calendario, &QCalendarWidget::clicked, this, &CalendarioPlantiosDialog::exibirPlantiosDoDia);

    carregarPlantios();
    destacarDiasComPlantio();

    if (!plantiosPorData.isEmpty()) {
        QDate primeiraData = plantiosPorData.keys().first();
        calendario->setSelectedDate(primeiraData);
        exibirPlantiosDoDia(primeiraData);
    }
}

void CalendarioPlantiosDialog::carregarPlantios() {
    plantiosPorData.clear();

    QList<PlantioAgendado> plantios = controller.listarPlantiosConfirmados();
    for (const PlantioAgendado& p : plantios) {
        QDateTime dt = QDateTime::fromString(p.dataHora, "yyyy-MM-dd HH:mm:ss");
        if (!dt.isValid()) continue;
        plantiosPorData[dt.date()].append(p);
    }
}

void CalendarioPlantiosDialog::destacarDiasComPlantio() {
    // Limpa qualquer formatação anterior
    QTextCharFormat formatoPadrao;
    calendario->setDateTextFormat(QDate(), formatoPadrao);

    QTextCharFormat formatoDestaque;
    formatoDestaque.setBackground(QBrush(QColor(76, 175, 80))); // verde - plantio confirmado
    formatoDestaque.setForeground(QBrush(Qt::white));
    formatoDestaque.setFontWeight(QFont::Bold);

    for (auto it = plantiosPorData.constBegin(); it != plantiosPorData.constEnd(); ++it) {
        calendario->setDateTextFormat(it.key(), formatoDestaque);
    }
}

void CalendarioPlantiosDialog::exibirPlantiosDoDia(const QDate& data) {
    listaPlantiosDoDia->clear();

    if (!plantiosPorData.contains(data) || plantiosPorData[data].isEmpty()) {
        labelTituloLista->setText(QString("Nenhum plantio confirmado em %1.").arg(data.toString("dd/MM/yyyy")));
        return;
    }

    labelTituloLista->setText(QString("Plantios confirmados em %1:").arg(data.toString("dd/MM/yyyy")));

    for (const PlantioAgendado& p : plantiosPorData[data]) {
        QDateTime dt = QDateTime::fromString(p.dataHora, "yyyy-MM-dd HH:mm:ss");
        QString horario = dt.isValid() ? dt.toString("HH:mm") : "--:--";

        QString item = QString("%1 - %2 (%3 m2, %4)")
                            .arg(horario, p.local, QString::number(p.area, 'f', 1), p.tipoGrama);
        listaPlantiosDoDia->addItem(item);
    }
}
