#ifndef PLANTIOCONTROLLER_HPP
#define PLANTIOCONTROLLER_HPP

#include <QString>
#include <QMap>
#include "Plantio.hpp"
#include "PlantioDAO.hpp"

class PlantioController {
public:
    PlantioController();
    ~PlantioController();
    PlantioController(const PlantioController& outro);
    PlantioController& operator=(const PlantioController& outro);

    bool requisitarCadastroPlantio(QString local, QString dataHora, double area, QString tipoGrama, QMap<QString, double> insumos);
};

#endif // PLANTIOCONTROLLER_HPP