#ifndef DISPOSITIVO_H
#define DISPOSITIVO_H

#include <iostream>
#include <string>

using namespace std;

class Dispositivo
{
    private:

        string nombre;
        int etiqueta;

    public:

        Dispositivo(string nombre,int etiqueta);
        virtual void mostrarInformacion()=0;
        virtual int getEtiqueta();
        virtual string getNombre();
        virtual ~Dispositivo()=default;
};

Dispositivo::Dispositivo(string b, int a)
{
    etiqueta = a;
    nombre = b;
}

int Dispositivo::getEtiqueta()
{
    return etiqueta;
}

string Dispositivo::getNombre()
{
    return nombre;
}


#endif