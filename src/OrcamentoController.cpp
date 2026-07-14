#include "OrcamentoController.hpp"
#include "PrecoBaseDAO.hpp"

OrcamentoController::OrcamentoController() {}
OrcamentoController::OrcamentoController(const OrcamentoController&) {}
OrcamentoController& OrcamentoController::operator=(const OrcamentoController&) { return *this; }
OrcamentoController::~OrcamentoController() {}

std::vector<std::pair<std::string, double>> OrcamentoController::listarTiposDeGrama() {
    PrecoBaseDAO dao;
    dao.inicializarBanco();
    return dao.listarGramas();
}

bool OrcamentoController::calcularOrcamento(const std::string& tipoGrama,
                                            double metragem,
                                            Orcamento& orcamentoOut) {
    // Regra de validação: metragem estritamente positiva
    if (metragem <= 0.0)   return false;
    if (tipoGrama.empty()) return false;

    PrecoBaseDAO dao;
    dao.inicializarBanco();

    double precoUnitario = 0.0;
    if (!dao.buscarPrecoPorNome(tipoGrama, precoUnitario)) {
        return false; // tipo de grama não cadastrado
    }

    orcamentoOut = Orcamento(tipoGrama, metragem, precoUnitario);
    return orcamentoOut.metragemValida();
}

bool OrcamentoController::salvarOrcamentoDigital(Orcamento& orcamento, const std::string& emailCliente) {
    // Repassa a responsabilidade para o Model (o Handle do Orcamento)
    return orcamento.gerarOrcamentoDigital(emailCliente);
}

std::string OrcamentoController::buscarDetalhamento(int idOrcamento) {
    // Chama o método estático para retornar a string pro Qt exibir num QMessageBox ou QLabel
    return Orcamento::visualizarDetalhamento(idOrcamento);
}

bool OrcamentoController::carregarOrcamento(int idOrcamento, Orcamento& orcamentoOut) {
    return orcamentoOut.carregarPorId(idOrcamento);
}

bool OrcamentoController::aprovarOrcamento(int idOrcamento, const std::string& emailLogado) {
    Orcamento orc;
    if (!orc.carregarPorId(idOrcamento)) return false;
    return orc.aprovar(emailLogado);
}

bool OrcamentoController::recusarOrcamento(int idOrcamento, const std::string& emailLogado) {
    Orcamento orc;
    if (!orc.carregarPorId(idOrcamento)) return false;
    return orc.recusar(emailLogado);
}