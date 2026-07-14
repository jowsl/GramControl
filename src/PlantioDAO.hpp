#ifndef PLANTIODAO_HPP
#define PLANTIODAO_HPP

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QString>
#include <QList>
#include "Plantio.hpp"

/**
 * @struct PlantioAgendado
 * @brief DTO simples usado para exibir plantios confirmados no calendário,
 *        sem precisar carregar o Handle/Body completo do Plantio.
 */
struct PlantioAgendado {
    int id;
    QString local;
    QString dataHora; // formato "yyyy-MM-dd HH:mm:ss"
    double area;
    QString tipoGrama;
};

class PlantioDAO {
public:
    PlantioDAO();
    ~PlantioDAO();

    bool inicializarBanco();
    bool inserirNoBanco(const Plantio& plantio);

    /**
     * @brief Lista todos os plantios confirmados cadastrados no banco,
     *        ordenados por data/hora, para exibição no calendário centralizado.
     * @return Lista de plantios agendados. Lista vazia em caso de erro ou
     *         se não houver plantios cadastrados.
     */
    QList<PlantioAgendado> listarPlantiosConfirmados();

private:
    QSqlDatabase db;
    PlantioDAO(const PlantioDAO&);
    PlantioDAO& operator=(const PlantioDAO&);
};

#endif // PLANTIODAO_HPP