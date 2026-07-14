#ifndef CALENDARIOPLANTIOSDIALOG_HPP
#define CALENDARIOPLANTIOSDIALOG_HPP

#include <QDialog>
#include <QCalendarWidget>
#include <QListWidget>
#include <QLabel>
#include <QMap>
#include <QDate>
#include "PlantioController.hpp"
#include "PlantioDAO.hpp"

/**
 * @class CalendarioPlantiosDialog
 * @brief View do caso de uso "Disponibilizar calendário de plantios confirmados".
 *
 * Exibe um calendário centralizado destacando os dias que possuem instalações
 * de grama já confirmadas (orçamento aprovado pelo cliente). Ao selecionar um
 * dia destacado, a lista lateral mostra o horário e o local de cada plantio
 * agendado naquela data.
 */
class CalendarioPlantiosDialog : public QDialog {
    Q_OBJECT

public:
    explicit CalendarioPlantiosDialog(QWidget* parent = nullptr);

private slots:
    void exibirPlantiosDoDia(const QDate& data);

private:
    void carregarPlantios();
    void destacarDiasComPlantio();

    PlantioController controller;
    QMap<QDate, QList<PlantioAgendado>> plantiosPorData;

    QCalendarWidget* calendario;
    QListWidget*     listaPlantiosDoDia;
    QLabel*          labelTituloLista;
};

#endif // CALENDARIOPLANTIOSDIALOG_HPP
