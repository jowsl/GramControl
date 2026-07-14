#include "PlantioDAO.hpp"
#include <QDebug>
#include <QVariant>

PlantioDAO::PlantioDAO() {
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("gramcontrol.db");
    }
}

PlantioDAO::~PlantioDAO() {}

bool PlantioDAO::inicializarBanco() {
    QSqlQuery query(db);
    if (!query.exec("CREATE TABLE IF NOT EXISTS plantios (id INTEGER PRIMARY KEY AUTOINCREMENT, local TEXT NOT NULL, data_hora TEXT NOT NULL, area REAL NOT NULL, tipo_grama TEXT NOT NULL)")) {
        return false;
    }
    if (!query.exec("CREATE TABLE IF NOT EXISTS insumos_alocados (id INTEGER PRIMARY KEY AUTOINCREMENT, plantio_id INTEGER NOT NULL, nome_insumo TEXT NOT NULL, quantidade REAL NOT NULL, FOREIGN KEY(plantio_id) REFERENCES plantios(id) ON DELETE CASCADE)")) {
        return false;
    }
    return true;
}

bool PlantioDAO::inserirNoBanco(const Plantio& plantio) {
    if (!db.isOpen() && !db.open()) return false;

    QSqlQuery query(db);
    db.transaction();

    query.prepare("INSERT INTO plantios (local, data_hora, area, tipo_grama) VALUES (:local, :data_hora, :area, :tipo_grama)");
    query.bindValue(":local", plantio.getLocal());
    query.bindValue(":data_hora", plantio.getDataHora());
    query.bindValue(":area", plantio.getArea());
    query.bindValue(":tipo_grama", plantio.getTipoGrama());

    if (!query.exec()) {
        db.rollback();
        return false;
    }

    qlonglong plantioId = query.lastInsertId();
    QMap<QString, double> insumos = plantio.getInsumos();
    for (auto it = insumos.constBegin(); it != insumos.constEnd(); ++it) {
        QSqlQuery queryInsumo(db);
        queryInsumo.prepare("INSERT INTO insumos_alocados (plantio_id, nome_insumo, quantidade) VALUES (:plantio_id, :nome_insumo, :quantidade)");
        queryInsumo.bindValue(":plantio_id", plantioId);
        queryInsumo.bindValue(":nome_insumo", it.key());
        queryInsumo.bindValue(":quantidade", it.value());
        if (!queryInsumo.exec()) {
            db.rollback();
            return false;
        }
    }
    return db.commit();
}

PlantioDAO::PlantioDAO(const PlantioDAO&) {}
PlantioDAO& PlantioDAO::operator=(const PlantioDAO&) { return *this; }