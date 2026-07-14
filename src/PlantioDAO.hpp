#ifndef PLANTIODAO_HPP
#define PLANTIODAO_HPP

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QString>
#include "Plantio.hpp"

class PlantioDAO {
public:
    PlantioDAO();
    ~PlantioDAO();

    bool inicializarBanco();
    bool inserirNoBanco(const Plantio& plantio);

private:
    QSqlDatabase db;
    PlantioDAO(const PlantioDAO&);
    PlantioDAO& operator=(const PlantioDAO&);
};

#endif // PLANTIODAO_HPP