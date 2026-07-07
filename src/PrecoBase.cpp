#include "PrecoBase.hpp"

// ──────────────────────────────────────────────
// PrecoBaseBody
// ──────────────────────────────────────────────

PrecoBaseBody::PrecoBaseBody()
    : nomeItem(""), precoAtual(0.0) {}

PrecoBaseBody::PrecoBaseBody(std::string nome, double precoInicial)
    : nomeItem(nome), precoAtual(precoInicial) {}

PrecoBaseBody::~PrecoBaseBody() {}

bool PrecoBaseBody::atualizarPreco(double novoPreco) {
    if (novoPreco < 0.0) return false;
    precoAtual = novoPreco;
    return true;
}

double PrecoBaseBody::getPreco() const {
    return precoAtual;
}

std::string PrecoBaseBody::getNome() const {
    return nomeItem;
}

// ──────────────────────────────────────────────
// PrecoBase (Handle)
// ──────────────────────────────────────────────

PrecoBase::PrecoBase() {}

PrecoBase::PrecoBase(std::string nome, double precoInicial) {
    pImpl_->detach();
    pImpl_ = new PrecoBaseBody(nome, precoInicial);
    pImpl_->attach();
}

bool PrecoBase::atualizarPreco(double novoPreco) {
    return pImpl_->atualizarPreco(novoPreco);
}

double PrecoBase::getPreco() const {
    return pImpl_->getPreco();
}

std::string PrecoBase::getNome() const {
    return pImpl_->getNome();
}