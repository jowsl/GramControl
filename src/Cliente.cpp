#include "Cliente.hpp"

//---------- ClienteBody ----------//
ClienteBody::ClienteBody()
    : nome(""), telefone(""), endereco(""), email("") {}

ClienteBody::ClienteBody(QString nome, QString telefone, QString endereco, QString email)
    : nome(nome), telefone(telefone), endereco(endereco), email(email) {}

ClienteBody::~ClienteBody() {}

bool ClienteBody::validar() const {
    return !nome.trimmed().isEmpty() && !telefone.trimmed().isEmpty();
}

QString ClienteBody::getNome() const {return nome;}
QString ClienteBody::getTelefone() const {return telefone;}
QString ClienteBody::getEndereco() const {return endereco;}
QString ClienteBody::getEmail() const {return email;}

//---------- Cliente (Handle) ----------//
Cliente::Cliente() {}

Cliente::Cliente(QString nome, QString telefone, QString endereco, QString email){
    pImpl_->detach(); // Detach é chamado para liberar a referência anterior, se houver. Isso é importante para evitar vazamentos de memória.
    pImpl_ = new ClienteBody(nome, telefone, endereco, email);
    pImpl_->attach(); // Attach é chamado para aumentar a contagem de referência do novo objeto ClienteBody.
}

bool Cliente::validar() const { return pImpl_->validar(); }
QString Cliente::getNome() const { return pImpl_->getNome(); }
QString Cliente::getTelefone() const { return pImpl_->getTelefone(); }
QString Cliente::getEndereco() const { return pImpl_->getEndereco(); }
QString Cliente::getEmail() const { return pImpl_->getEmail(); }