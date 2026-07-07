#include "Orcamento.hpp"

// ──────────────────────────────────────────────
// OrcamentoBody
// ──────────────────────────────────────────────

OrcamentoBody::OrcamentoBody()
    : tipoGrama(""), metragem(0.0), precoUnitario(0.0) {}

OrcamentoBody::OrcamentoBody(std::string tipo, double m2, double preco)
    : tipoGrama(tipo), metragem(m2), precoUnitario(preco) {}

OrcamentoBody::~OrcamentoBody() {}

bool OrcamentoBody::metragemValida() const {
    return metragem > 0.0;
}

double OrcamentoBody::calcularTotal() const {
    if (!metragemValida() || precoUnitario < 0.0) return 0.0;
    return metragem * precoUnitario;
}

double OrcamentoBody::getMetragem() const      { return metragem; }
double OrcamentoBody::getPrecoUnitario() const { return precoUnitario; }
std::string OrcamentoBody::getTipoGrama() const { return tipoGrama; }

// ──────────────────────────────────────────────
// Orcamento (Handle)
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
