#include "ClienteController.hpp"

ClienteController::ClienteController(){}
ClienteController::ClienteController(const ClienteController& outro) {}
ClienteController& ClienteController::operator=(const ClienteController& outro) { 
    if (this != &outro) {
        // Sem atributos para copiar, pois a classe ClienteController não possui atributos.
    }
    return *this; 
}
ClienteController::~ClienteController() {}

bool ClienteController::cadastrarCliente(QString nome, QString telefone, QString endereco, QString email, QString& mensagemErro) {
    Cliente clienteModel(nome.trimmed(), telefone.trimmed(), endereco.trimmed(), email.trimmed());

    if(!clienteModel.validar()){
        mensagemErro = "Nome e telefone são obrigatórios.";
        return false;
    }

    ClienteDAO dao;
    dao.inicializarBanco();

    if(dao.existeTelefone(clienteModel.getTelefone())){
        mensagemErro = "O telefone informado ja esta cadastrado.";
        return false;
    }
    
    if(!dao.inserirNoBanco(clienteModel)){
        mensagemErro = "Falha ao salvar cliente no banco de dados.";
        return false;
    }

    return true;
}