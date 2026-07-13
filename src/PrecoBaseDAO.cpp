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

bool PrecoBaseDAO::buscarPrecoPorNome(const std::string& nomeItem, double& precoOut) {
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    if (!db.isOpen()) {
        qDebug() << "[ERRO] Banco de dados fechado!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("SELECT valor FROM precos_base WHERE nome = :nome");
    query.bindValue(":nome", QString::fromStdString(nomeItem));

    if (!query.exec()) {
        qDebug() << "[ERRO SQL] ->" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        precoOut = query.value(0).toDouble();
        return true;
    }
    return false;
}

std::vector<std::pair<std::string, double>> PrecoBaseDAO::listarGramas() {
    std::vector<std::pair<std::string, double>> resultado;

    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    if (!db.isOpen()) {
        qDebug() << "[ERRO] Banco de dados fechado!";
        return resultado;
    }

    QSqlQuery query(db);
    // Filtra apenas variedades de grama do catálogo
    if (!query.exec("SELECT nome, valor FROM precos_base WHERE nome LIKE 'Grama %' ORDER BY nome")) {
        qDebug() << "[ERRO SQL] ->" << query.lastError().text();
        return resultado;
    }

    while (query.next()) {
        std::string nome = query.value(0).toString().toStdString();
        double valor     = query.value(1).toDouble();
        resultado.push_back({nome, valor});
    }
    return resultado;
}

// Forma Canônica — cópia bloqueada
PrecoBaseDAO::PrecoBaseDAO(const PrecoBaseDAO&) {}
PrecoBaseDAO& PrecoBaseDAO::operator=(const PrecoBaseDAO&) { return *this; }
