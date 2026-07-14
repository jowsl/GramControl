#include "Orcamento.hpp"
#include <sqlite3.h>
#include <iostream>
#include <sstream>
#include <iomanip>

#ifndef PROJECT_ROOT_DIR
#define PROJECT_ROOT_DIR "."
#endif

/**
 * @brief Helper para padronizar o caminho do banco de dados.
 * @return std::string com o caminho do arquivo .db do projeto.
 */
static std::string getDbPath() {
    return std::string(PROJECT_ROOT_DIR) + "/gramcontrol.db";
}

// ──────────────────────────────────────────────
// OrcamentoBody (Implementação Original Mantida)
// ──────────────────────────────────────────────

/**
 * @brief Construtor padrão.
 */
OrcamentoBody::OrcamentoBody()
    : tipoGrama(""), metragem(0.0), precoUnitario(0.0), id(-1), emailCliente(""), status("Novo") {}

/**
 * @brief Construtor com parâmetros.
 */
OrcamentoBody::OrcamentoBody(std::string tipo, double m2, double preco)
    : tipoGrama(tipo), metragem(m2), precoUnitario(preco), id(-1), emailCliente(""), status("Novo") {}

/**
 * @brief Destrutor padrão.
 */
OrcamentoBody::~OrcamentoBody() {}

/**
 * @brief Valida se a metragem informada é estritamente positiva.
 * @return true se válida, false caso contrário.
 */
bool OrcamentoBody::metragemValida() const {
    return metragem > 0.0;
}

/**
 * @brief Calcula o valor total do orçamento.
 * @return O valor de metragem multiplicada pelo precoUnitario. Retorna 0.0 se for inválido.
 */
double OrcamentoBody::calcularTotal() const {
    if (!metragemValida() || precoUnitario < 0.0) return 0.0;
    return metragem * precoUnitario;
}

double OrcamentoBody::getMetragem() const      { return metragem; }
double OrcamentoBody::getPrecoUnitario() const { return precoUnitario; }
std::string OrcamentoBody::getTipoGrama() const { return tipoGrama; }

int OrcamentoBody::getId() const { return id; }
std::string OrcamentoBody::getEmailCliente() const { return emailCliente; }
std::string OrcamentoBody::getStatus() const { return status; }


// ──────────────────────────────────────────────
// Novas Implementações do Body (Sprint 2)
// ──────────────────────────────────────────────

/**
 * @brief Persiste o orçamento digital no banco de dados SQLite.
 * 
 * Cria a tabela caso não exista e insere os dados do orçamento atual,
 * recuperando o ID gerado automaticamente e atualizando o status.
 * 
 * @param email O email do cliente vinculado ao orçamento.
 * @return true se a operação de inserção for bem-sucedida, false caso ocorra um erro de SQL.
 */
bool OrcamentoBody::gerarOrcamentoDigital(const std::string& email) {
    this->emailCliente = email;
    this->status = "Aguardando Aprovação";
    double total = calcularTotal();

    sqlite3* db;
    if (sqlite3_open(getDbPath().c_str(), &db) == SQLITE_OK) {
        const char* sqlCreate = "CREATE TABLE IF NOT EXISTS Orcamentos ("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                "emailCliente TEXT, "
                                "metragem REAL, "
                                "tipoGrama TEXT, "
                                "precoUnitario REAL, "
                                "valorTotal REAL, "
                                "status TEXT);";
        char* errMsg = nullptr;
        sqlite3_exec(db, sqlCreate, nullptr, nullptr, &errMsg);

        std::string sqlInsert = "INSERT INTO Orcamentos (emailCliente, metragem, tipoGrama, precoUnitario, valorTotal, status) VALUES ('" +
                     emailCliente + "', " + 
                     std::to_string(metragem) + ", '" + 
                     tipoGrama + "', " + 
                     std::to_string(precoUnitario) + ", " + 
                     std::to_string(total) + ", '" + 
                     status + "');";
                     
        if (sqlite3_exec(db, sqlInsert.c_str(), nullptr, nullptr, &errMsg) == SQLITE_OK) {
            this->id = sqlite3_last_insert_rowid(db); 
            sqlite3_close(db);
            return true;
        } else {
            std::cerr << "[ERRO DB] Falha ao gerar orcamento: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
        sqlite3_close(db);
    }
    return false;
}

/**
 * @brief Realiza a busca de um orçamento específico pelo ID no banco.
 * 
 * @param idBusca O ID do orçamento que se deseja detalhar.
 * @return std::string contendo os detalhes formatados ou mensagem de erro se não encontrado.
 */
std::string OrcamentoBody::visualizarDetalhamento(int idBusca) {
    std::string detalhes = "Orcamento nao encontrado.";
    sqlite3* db;
    if (sqlite3_open(getDbPath().c_str(), &db) == SQLITE_OK) {
        std::string sql = "SELECT emailCliente, metragem, tipoGrama, valorTotal, status FROM Orcamentos WHERE id = " + std::to_string(idBusca) + ";";
        sqlite3_stmt* stmt;
        
        // ESSA É A LINHA QUE FALTAVA PARA PREPARAR O PONTEIRO "stmt"
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
            
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                // Configura um formatador para 2 casas decimais
                std::stringstream streamMetragem, streamValor;
                streamMetragem << std::fixed << std::setprecision(2) << sqlite3_column_double(stmt, 1);
                streamValor << std::fixed << std::setprecision(2) << sqlite3_column_double(stmt, 3);

                detalhes = "--- Detalhes do Orcamento #" + std::to_string(idBusca) + " ---\n";
                detalhes += "Cliente Email: ";
                detalhes += reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                detalhes += "\nMetragem: " + streamMetragem.str() + " m2";
                detalhes += "\nGrama: ";
                detalhes += reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
                detalhes += "\nValor Total: R$ " + streamValor.str();
                detalhes += "\nStatus: ";
                detalhes += reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            }
        }
        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }
    return detalhes;
}

// [SPRINT 2] Aprovar ou Recusar orçamento digitalmente

/**
 * @brief Carrega os campos de um orçamento persistido a partir do ID.
 * @param idBusca ID do orçamento a ser carregado.
 * @return true se encontrado; false caso contrário (ou erro ao abrir o banco).
 */
bool OrcamentoBody::carregarPorId(int idBusca) {
    sqlite3* db;
    if (sqlite3_open(getDbPath().c_str(), &db) != SQLITE_OK) {
        sqlite3_close(db);
        return false;
    }

    const char* sql = "SELECT emailCliente, metragem, tipoGrama, precoUnitario, status "
                       "FROM Orcamentos WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;
    bool encontrado = false;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, idBusca);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            emailCliente  = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            metragem      = sqlite3_column_double(stmt, 1);
            tipoGrama     = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            precoUnitario = sqlite3_column_double(stmt, 3);
            status        = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            id            = idBusca;
            encontrado    = true;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return encontrado;
}

/**
 * @brief Aplica a transição de status no banco, validando dono e status atual.
 *
 * A transição só é aplicada se: (1) o orçamento já foi carregado (id > 0),
 * (2) o e-mail informado é o mesmo do cliente dono do orçamento e
 * (3) o status atual, no banco, ainda é "Aguardando Aprovação" — a checagem
 * do status é feita atomicamente na cláusula WHERE do UPDATE para evitar
 * que o mesmo orçamento seja decidido duas vezes.
 *
 * @param emailLogado E-mail do cliente autenticado que está decidindo.
 * @param novoStatus  "Aprovado" ou "Recusado".
 * @return true se a transição foi persistida com sucesso.
 */
bool OrcamentoBody::transicionarStatus(const std::string& emailLogado, const std::string& novoStatus) {
    if (id <= 0) return false;
    if (emailCliente != emailLogado) return false;
    if (status != "Aguardando Aprovação") return false;

    sqlite3* db;
    if (sqlite3_open(getDbPath().c_str(), &db) != SQLITE_OK) {
        sqlite3_close(db);
        return false;
    }

    const char* sql = "UPDATE Orcamentos SET status = ? "
                       "WHERE id = ? AND status = 'Aguardando Aprovação';";
    sqlite3_stmt* stmt = nullptr;
    bool sucesso = false;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, novoStatus.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, id);

        if (sqlite3_step(stmt) == SQLITE_DONE && sqlite3_changes(db) > 0) {
            status  = novoStatus;
            sucesso = true;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return sucesso;
}

bool OrcamentoBody::aprovar(const std::string& emailLogado) {
    return transicionarStatus(emailLogado, "Aprovado");
}

bool OrcamentoBody::recusar(const std::string& emailLogado) {
    return transicionarStatus(emailLogado, "Recusado");
}

// ──────────────────────────────────────────────
// Orcamento (Handle - Delegação)
// ──────────────────────────────────────────────

Orcamento::Orcamento() {}

Orcamento::Orcamento(std::string tipoGrama, double metragem, double precoUnitario) {
    pImpl_->detach();
    pImpl_ = new OrcamentoBody(tipoGrama, metragem, precoUnitario);
    pImpl_->attach();
}

double Orcamento::calcularTotal() const   { return pImpl_->calcularTotal(); }
bool   Orcamento::metragemValida() const  { return pImpl_->metragemValida(); }
double Orcamento::getMetragem() const     { return pImpl_->getMetragem(); }
double Orcamento::getPrecoUnitario() const{ return pImpl_->getPrecoUnitario(); }
std::string Orcamento::getTipoGrama() const { return pImpl_->getTipoGrama(); }

int Orcamento::getId() const { return pImpl_->getId(); }
std::string Orcamento::getEmailCliente() const { return pImpl_->getEmailCliente(); }
std::string Orcamento::getStatus() const { return pImpl_->getStatus(); }

bool Orcamento::gerarOrcamentoDigital(const std::string& email) {
    return pImpl_->gerarOrcamentoDigital(email);
}

std::string Orcamento::visualizarDetalhamento(int idBusca) {
    return OrcamentoBody::visualizarDetalhamento(idBusca);
}

bool Orcamento::carregarPorId(int idBusca) {
    return pImpl_->carregarPorId(idBusca);
}

bool Orcamento::aprovar(const std::string& emailLogado) {
    return pImpl_->aprovar(emailLogado);
}

bool Orcamento::recusar(const std::string& emailLogado) {
    return pImpl_->recusar(emailLogado);
}