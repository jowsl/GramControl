#include <cassert>
#include <iostream>
#include "../../src/Plantio.hpp"
#include "../../src/PlantioDAO.hpp"
#include "test_persistencia_plantio.hpp"

void teste_persistencia_insere_plantio() {
    PlantioDAO dao;
    
    // Inicializa as tabelas (plantios e insumos_alocados)
    assert(dao.inicializarBanco() == true);

    QMap<QString, double> insumos;
    insumos.insert("Adubo", 30.0);
    insumos.insert("Calcário", 15.0);

    Plantio plantio("Haras Vale", "2026-07-15 14:00:00", 200.0, "Grama Batatais", insumos);

    // Persiste no banco de dados
    assert(dao.inserirNoBanco(plantio) == true);

    std::cout << "Teste de persistencia (INSERT plantio e insumos) passou!" << std::endl;
}