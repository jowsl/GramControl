#include "PrecoBase.hpp"

// PrecoBaseBody


PrecoBaseBody::PrecoBaseBody()
    : nomeItem(""), precoAtual(0.0) {}

PrecoBaseBody::PrecoBaseBody(QString nome, double precoInicial)
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

QString PrecoBaseBody::getNome() const {
    return nomeItem;
}

// PrecoBase (Handle)

PrecoBase::PrecoBase() {}   // Handle<T>() já cria o Body padrão

PrecoBase::PrecoBase(QString nome, double precoInicial) {
    // O Handle padrão já criou um Body vazio via pImpl_.
    // Precisamos substituí-lo por um Body com dados.
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

QString PrecoBase::getNome() const {
    return pImpl_->getNome();
}