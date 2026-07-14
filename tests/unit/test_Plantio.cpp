#include <iostream>
#include <cassert>
#include "../../src/Plantio.hpp"
#include "test_Plantio.hpp"

void teste_plantio_valido() {
    QMap<QString, double> insumos;
    insumos.insert("Adubo", 20.0);
    insumos.insert("Calcário", 10.0);

    // Instancia o Handle/Body com dados válidos
    Plantio plantio("Sitio das Pedras", "2026-07-15 08:00:00", 450.0, "Grama Esmeralda", insumos);
    
    assert(plantio.validar() == true);
    assert(plantio.getLocal() == "Sitio das Pedras");
    assert(plantio.getDataHora() == "2026-07-15 08:00:00");
    assert(plantio.getArea() == 450.0);
    assert(plantio.getTipoGrama() == "Grama Esmeralda");
    assert(plantio.getInsumos().value("Adubo") == 20.0);
    assert(plantio.getInsumos().value("Calcário") == 10.0);
    
    std::cout << "Teste de modelo de plantio valido passou!" << std::endl;
}

void teste_plantio_dados_invalidos() {
    // Cenário 1: Local vazio
    Plantio semLocal("", "2026-07-15 08:00:00", 100.0, "Grama Esmeralda");
    assert(semLocal.validar() == false);

    // Cenário 2: Área negativa ou zerada
    Plantio areaInvalida("Sítio das Pedras", "2026-07-15 08:00:00", 0.0, "Grama Esmeralda");
    assert(areaInvalida.validar() == false);

    // Cenário 3: Data vazia
    Plantio semData("Sítio das Pedras", "", 250.0, "Grama Batatais");
    assert(semData.validar() == false);

    std::cout << "Teste de bloqueio de plantio invalido passou!" << std::endl;
}