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
        virtual int getEtiqueta()const;
        virtual string getNombre()const;
        virtual ~Dispositivo()=default;
};

Dispositivo::Dispositivo(string b, int a)
{
    etiqueta = a;
    nombre = b;
}

int Dispositivo::getEtiqueta() const
{
    return etiqueta;
}

string Dispositivo::getNombre() const
{
    return nombre;
}


#endif
