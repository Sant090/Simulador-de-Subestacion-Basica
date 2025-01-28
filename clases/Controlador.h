#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "Sensor.h"
#include "Dispositivo.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Controlador:public Dispositivo
{
private:
    vector<Sensor*> sensores;
public:
    Controlador(string nombre, int etiqueta);
    void makSensor(Sensor* Sensor);
    void delSensor(int etiquetaSensor);
    void mostrarSensores();
    void desasociarSensor(int etiquetaSensor);
    void mostrarInformacion() override;
    
    ~Controlador();
};

Controlador::Controlador(string nombre, int etiqueta):Dispositivo(nombre,etiqueta)
{
}

Controlador::~Controlador()
{
    sensores.clear();
}



void Controlador::makSensor(Sensor* Sensor)
{
    sensores.push_back(Sensor);
}

void Controlador::delSensor(int etiquetaSensor)
{

    bool encontrado = false;
    for (auto objeto = sensores.begin(); objeto != sensores.end(); ++objeto) {
        if ((*objeto)->getEtiqueta() == etiquetaSensor) {
            delete *objeto;
            sensores.erase(objeto);
            encontrado = true;
            break; 
        }
    }

    if (!encontrado) {
        cout << "Sensor con ID " << etiquetaSensor << " no fue encontrado." << endl;
    }
    
}

void Controlador::mostrarSensores(){
    if (sensores.empty()) {
        cout << "No hay sensores de voltaje asociados a este controlador." << endl;
        return;
    }

    cout << "Sensores de Voltaje asociados:" << endl;
    for (Sensor* Sensor : sensores) {
        Sensor->mostrarInformacion();
    }
}

void Controlador::desasociarSensor(int etiquetaSensor) {
    for (auto it = sensores.begin(); it != sensores.end(); ++it) {
        if ((*it)->getEtiqueta() == etiquetaSensor) {
            sensores.erase(it); 
            break;             
        }
    }
}


void Controlador::mostrarInformacion() {
    cout << "Controlador: " << getNombre()<< " \t| Etiqueta: " << getEtiqueta() << endl;
}

#endif
