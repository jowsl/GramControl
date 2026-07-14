#ifndef PLANTIO_HPP
#define PLANTIO_HPP

#include <QString>
#include <QMap>
#include "handleBodySemDebug.h"

class PlantioBody : public Body {
public:
    PlantioBody();
    PlantioBody(QString local, QString dataHora, double area, QString tipoGrama, QMap<QString, double> insumos = QMap<QString, double>());
    virtual ~PlantioBody();

    bool validar() const;
    QString getLocal() const;
    QString getDataHora() const;
    double getArea() const;
    QString getTipoGrama() const;
    QMap<QString, double> getInsumos() const;

private:
    PlantioBody(const PlantioBody&); 
    PlantioBody& operator=(const PlantioBody&); 

    QString local;
    QString dataHora;
    double area;
    QString tipoGrama;
    QMap<QString, double> insumosAlocados; 
};

class Plantio : public Handle<PlantioBody> {
public:
    Plantio();
    Plantio(QString local, QString dataHora, double area, QString tipoGrama, QMap<QString, double> insumos = QMap<QString, double>());

    bool validar() const;
    QString getLocal() const;
    QString getDataHora() const;
    double getArea() const;
    QString getTipoGrama() const;
    QMap<QString, double> getInsumos() const;
};

#endif // PLANTIO_HPP