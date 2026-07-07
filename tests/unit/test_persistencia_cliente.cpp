#include <cassert>
#include <iostream>
#include <QCoreApplication>
#include "../../src/Cliente.hpp"
#include "../../src/ClienteDAO.hpp"

void teste_persistencia_insere_cliente(){
    ClienteDAO dao;
    assert(dao.inicializarBanco());

    QString telefoneTeste = "31999990000";
    Cliente cliente("Cliente de Teste", telefoneTeste, "Rua de Teste, 123");
    
    if(!dao.existeTelefone(telefoneTeste)){
        assert(dao.inserirNoBanco(cliente) == true);
    }
    assert(dao.existeTelefone(telefoneTeste) == true);
    std::cout << "Teste de persistencia (INSERT cliente) passou!" << std::endl;
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    teste_persistencia_insere_cliente();
    return 0;
}