#include "PrecoBaseDAO.hpp"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

// Construtor padrão
PrecoBaseDAO::PrecoBaseDAO() {
    // Verifica se a conexão já existe para evitar criar duplicatas
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("gramcontrol.db");
    }
    
    // Abre o banco se estiver fechado
    if (!db.isOpen()) {
        if (!db.open()) {
            qDebug() << "[ERRO] Não foi possível abrir o arquivo gramcontrol.db!";
        }
    }
}

// Destrutor
PrecoBaseDAO::~PrecoBaseDAO() {
}

// Inicializador do banco
bool PrecoBaseDAO::inicializarBanco() {
    QSqlQuery query(db);

    // Cria a tabela caso não exista
    if (!query.exec("CREATE TABLE IF NOT EXISTS precos_base (nome TEXT PRIMARY KEY, valor REAL)")) {
        qDebug() << "[ERRO SQL] ->" << query.lastError().text();
        return false;
    }

    // Semeia o catálogo base (não sobrescreve preços já editados)
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


// Método de atualização limpo para produção
bool PrecoBaseDAO::atualizarNoBanco(const PrecoBase& preco) {
    if (!db.isOpen()) {
        qDebug() << "[ERRO] Banco de dados fechado!";
        return false;
    }

    QSqlQuery query(db); 
    
    // Query correta utilizando a coluna 'valor' conforme o seu schema
    query.prepare("UPDATE precos_base SET valor = :valor WHERE nome = :nome");
    query.bindValue(":valor", preco.getPreco());
    query.bindValue(":nome", preco.getNome()); 

    if (!query.exec()) {
        // Mantemos apenas o log de erro para facilitar a vida do desenvolvedor caso algo quebre no futuro
        qDebug() << "[ERRO SQL] ->" << query.lastError().text();
        return false;
    }

    return query.numRowsAffected() > 0;
}