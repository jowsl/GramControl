#include "ClienteDAO.hpp"
#include <QDebug>
#include <QVariant>

ClienteDAO::ClienteDAO(){
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("gramcontrol.db");
    }

    if (!db.open()){
        if(!db.open()){
            qDebug() << "[ERRO] Nao foi possivel abrir o arquivo gramcontrol.db!";
        }
    }
}

ClienteDAO::~ClienteDAO() {}

bool ClienteDAO::inicializarBanco(){
    QSqlQuery query(db);

    if(!query.exec(
            "CREATE TABLE IF NOT EXISTS clientes ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "nome TEXT NOT NULL,"
            "telefone TEXT NOT NULL UNIQUE,"
            "endereco TEXT, "
            "email TEXT)")) {

        qDebug() << "[ERRO SQL] -> " << query.lastError().text();
        return false;
    }
    return true;
}

bool ClienteDAO::inserirNoBanco(const Cliente& cliente){
    if (!db.open()) {
        qDebug() << "[ERRO] Banco de dados fechado!";
        return false;
    }
    
    QSqlQuery query(db);
    query.prepare(
        "INSERT INTO clientes (nome, telefone, endereco, email) "
        "VALUES (:nome, :telefone, :endereco, :email)");

    query.bindValue(":nome", cliente.getNome());
    query.bindValue(":telefone", cliente.getTelefone());
    query.bindValue(":endereco", cliente.getEndereco());
    query.bindValue(":email", cliente.getEmail());

    if(!query.exec()) {
        qDebug() << "[ERRO SQL] -> " << query.lastError().text();
        return false;
    }
    return query.numRowsAffected() > 0;
}

bool ClienteDAO::existeTelefone(const QString& telefone){
    if(!db.open()) return false;

    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM clientes WHERE telefone = :telefone");
    query.bindValue(":telefone", telefone);

    if (!query.exec() || !query.next()) {
        qDebug() << "[ERRO SQL] -> " << query.lastError().text();
        return false;
    }
    return query.value(0).toInt() > 0;
}

// Forma Canonica - copia bloqueada no header, definicoes vazias aqui
ClienteDAO::ClienteDAO(const ClienteDAO&) {}
ClienteDAO& ClienteDAO::operator=(const ClienteDAO&) { return *this; }