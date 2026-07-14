#include "Plantio.hpp"

PlantioBody::PlantioBody() : local(""), dataHora(""), area(0.0), tipoGrama("") {}

PlantioBody::PlantioBody(QString local, QString dataHora, double area, QString tipoGrama, QMap<QString, double> insumos)
    : local(local), dataHora(dataHora), area(area), tipoGrama(tipoGrama), insumosAlocados(insumos) {}

PlantioBody::~PlantioBody() {}

bool PlantioBody::validar() const {
    return !local.trimmed().isEmpty() && !dataHora.trimmed().isEmpty() && area > 0.0;
}

QString PlantioBody::getLocal() const { return local; }
QString PlantioBody::getDataHora() const { return dataHora; }
double PlantioBody::getArea() const { return area; }
QString PlantioBody::getTipoGrama() const { return tipoGrama; }
QMap<QString, double> PlantioBody::getInsumos() const { return insumosAlocados; }

Plantio::Plantio() {}

Plantio::Plantio(QString local, QString dataHora, double area, QString tipoGrama, QMap<QString, double> insumos) {
    pImpl_->detach();
    pImpl_ = new PlantioBody(local, dataHora, area, tipoGrama, insumos);
    pImpl_->attach(); 
}

bool Plantio::validar() const { return pImpl_->validar(); }
QString Plantio::getLocal() const { return pImpl_->getLocal(); }
QString Plantio::getDataHora() const { return pImpl_->getDataHora(); }
double Plantio::getArea() const { return pImpl_->getArea(); }
QString Plantio::getTipoGrama() const { return pImpl_->getTipoGrama(); }
QMap<QString, double> Plantio::getInsumos() const { return pImpl_->getInsumos(); }