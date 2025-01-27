#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>
#include <string>
#include "Dispositivo.h"
using namespace std;

class Sensor:public Dispositivo
{
    private:

        int voltaje;

    public:

        Sensor(string nombre,int etiqueta, int voltaje);
        void leerDato();
        int mostrarVoltaje();
        void mostrarInformacion() override;
        ~Sensor();
};

Sensor::Sensor(string nombre, int etiqueta, int c):Dispositivo(nombre, etiqueta)
{
    voltaje=c;
}

int Sensor::mostrarVoltaje()
{
    voltaje = 20 + rand() % 9;
    return voltaje;
}


void Sensor::mostrarInformacion() {

    mostrarVoltaje();
    cout << "Sensor: " << getNombre() << " \t| Etiqueta: " << getEtiqueta() << " \t| Voltaje: " << voltaje << "V" << endl;
}


Sensor::~Sensor()
{
}






#endif
