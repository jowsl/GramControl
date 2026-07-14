#include "PlantioController.hpp"

PlantioController::PlantioController() {}
PlantioController::~PlantioController() {}
PlantioController::PlantioController(const PlantioController& outro) {}
PlantioController& PlantioController::operator=(const PlantioController& outro) { return *this; }

bool PlantioController::requisitarCadastroPlantio(QString local, QString dataHora, double area, QString tipoGrama, QMap<QString, double> insumos) {
    Plantio plantioModel(local, dataHora, area, tipoGrama, insumos);

    if (!plantioModel.validar()) {
        return false;
    }

    PlantioDAO dao;
    dao.inicializarBanco();
    return dao.inserirNoBanco(plantioModel);
}

QList<PlantioAgendado> PlantioController::listarPlantiosConfirmados() {
    PlantioDAO dao;
    dao.inicializarBanco();
    return dao.listarPlantiosConfirmados();
}