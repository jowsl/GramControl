#include "PrecoBaseDAO.hpp"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QVariant>
#include <QDebug>
#include <QString>
#include <QList>
#include <QPair>

PrecoBaseDAO::PrecoBaseDAO() {}

PrecoBaseDAO::~PrecoBaseDAO() {}

bool PrecoBaseDAO::inicializarBanco() {
    // Qt fica confinado ao .cpp — o .hpp não sabe que Qt existe
    QSqlDatabase db;
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("gramcontrol.db");
    }

    if (!db.isOpen()) {
        if (!db.open()) {
            qDebug() << "[ERRO] Nao foi possivel abrir gramcontrol.db!";
            return false;
        }
    }

    QSqlQuery query(db);

    if (!query.exec("CREATE TABLE IF NOT EXISTS precos_base (nome TEXT PRIMARY KEY, valor REAL)")) {
        qDebug() << "[ERRO SQL] ->" << query.lastError().text();
        return false;
    }

    query.prepare("INSERT OR IGNORE INTO precos_base (nome, valor) VALUES (:nome, :valor)");

    const QList<QPair<QString, double>> catalogoInicial = {
        {"Grama Esmeralda",   8.00},
        {"Grama Batatais",    8.50},
        {"Adubo / Substrato", 2.00}
    };

    for (const auto& item : catalogoInicial) {
        query.bindValue(":nome",  item.first);
        query.bindValue(":valor", item.second);
        if (!query.exec()) {
            qDebug() << "[ERRO SQL SEED] ->" << query.lastError().text();
            return false;
        }
    }

    return true;
}

bool PrecoBaseDAO::atualizarNoBanco(const PrecoBase& preco) {
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");

    if (!db.isOpen()) {
        qDebug() << "[ERRO] Banco de dados fechado!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE precos_base SET valor = :valor WHERE nome = :nome");
    query.bindValue(":valor", preco.getPreco());
    query.bindValue(":nome",  QString::fromStdString(preco.getNome()));

    if (!query.exec()) {
        qDebug() << "[ERRO SQL] ->" << query.lastError().text();
        return false;
    }

    return query.numRowsAffected() > 0;
}

// Forma Canônica — cópia bloqueada
PrecoBaseDAO::PrecoBaseDAO(const PrecoBaseDAO&) {}
PrecoBaseDAO& PrecoBaseDAO::operator=(const PrecoBaseDAO&) { return *this; }