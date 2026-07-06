#include "PrecoBase.hpp"

PrecoBase::PrecoBase() : nomeItem(""), precoAtual(0.0) {}

PrecoBase::PrecoBase(QString nome, double precoInicial) : nomeItem(nome), precoAtual(precoInicial) {}

PrecoBase::~PrecoBase() {}

PrecoBase::PrecoBase(const PrecoBase& outro) {
    nomeItem = outro.nomeItem;
    precoAtual = outro.precoAtual;
}

PrecoBase& PrecoBase::operator=(const PrecoBase& outro) {
    if (this != &outro) {
        nomeItem = outro.nomeItem;
        precoAtual = outro.precoAtual;
    }
    return *this;
}

bool PrecoBase::atualizarPreco(double novoPreco) {
    if (novoPreco < 0.0) {
        return false;
    }
    precoAtual = novoPreco;
    return true;
}

double PrecoBase::getPreco() const {
    return precoAtual;
}

QString PrecoBase::getNome() const {
    return nomeItem;
}