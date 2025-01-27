#include <iostream>
#include <vector>
#include <string>

using namespace std;


void mostrarMenu()
{
    string opciones[6] = { "Registrar Sensor de Voltaje","Registrar Controlador","Asociar Sensor a Controlador","Mostrar Estado del Sistema","Eliminar Sensor","Salir" };

    for (int i = 0; i < 6; i++)
    {
        cout << i + 1 << ". " << opciones[i] << endl;
    }
    cout << "Elige una opcion: ";
}




class Dispositivo
{
private:

    string nombre;
    int etiqueta;

public:

    Dispositivo(string nombre, int etiqueta);
    virtual void mostrarInformacion() = 0;
    virtual int getEtiqueta();
    virtual string getNombre();
    virtual ~Dispositivo() = default;
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



class Sensor :public Dispositivo
{
private:

    int voltaje;

public:

    Sensor(string nombre, int etiqueta, int voltaje);
    int mostrarVoltaje();
    void mostrarInformacion() override;
    ~Sensor();
};

Sensor::Sensor(string nombre, int etiqueta, int c) :Dispositivo(nombre, etiqueta)
{
    voltaje = c;
}

int Sensor::mostrarVoltaje()
{
    voltaje = 20 + rand() % 9;
    return voltaje;
}


void Sensor::mostrarInformacion() {

    mostrarVoltaje();
    cout << "Sensor: " << getNombre() << " \t| Etiqueta: " << getEtiqueta() << " \t| Voltaje: " << voltaje << "kV" << endl;
}


Sensor::~Sensor()
{
}


class Controlador :public Dispositivo
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

Controlador::Controlador(string nombre, int etiqueta) :Dispositivo(nombre, etiqueta)
{
}

Controlador::~Controlador()
{
    for (Sensor* sensor : sensores)
    {
        delete sensor;
    }
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
            delete* objeto;
            sensores.erase(objeto);
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "Sensor con ID " << etiquetaSensor << " no fue encontrado." << endl;
    }

}

void Controlador::mostrarSensores() {
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
    cout << "Controlador: " << getNombre() << " \t| Etiqueta: " << getEtiqueta() << endl;
}






































int main() {

    vector<Sensor*> sensores;
    vector<Controlador*> controladores;

    int opcion;
    cout << "*************************************************\n***********Bienvenido a la SubEstacion***********\n*******************Las Flores********************\n*************************************************";


    do {
        cout << endl;
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {

        case 1: {

            string nombre;
            int etiqueta;

            cout << "\nIntroduce el nombre del sensor de voltaje: ";
            cin >> nombre;
            cout << "Introduce la etiqueta del sensor de voltaje: ";
            cin >> etiqueta;

            bool etiquetaDuplicada = false;
            for (Sensor* s : sensores) {
                if (s->getEtiqueta() == etiqueta) {
                    etiquetaDuplicada = true;
                    break;
                }
            }

            if (etiquetaDuplicada) {
                cout << "\nError: Ya existe un sensor con la etiqueta " << etiqueta << "." << endl;
            }
            else {
                sensores.push_back(new Sensor(nombre, etiqueta, 0));
                cout << "\nSensor de voltaje registrado correctamente." << endl;
            }
            break;
        }
        case 2: {
            string nombre;
            int etiqueta;
            cout << "\nIntroduce el nombre del controlador: ";
            cin >> nombre;
            cout << "Introduce el etiqueta del controlador: ";
            cin >> etiqueta;

            controladores.push_back(new Controlador(nombre, etiqueta));
            cout << "\nControlador registrado correctamente." << endl;
            break;
        }
        case 3: {
            int sensorEtiqueta, controladortiqueta;
            cout << "\nIntroduce el etiqueta del sensor de voltaje a asociar: ";
            cin >> sensorEtiqueta;
            cout << "Introduce el etiqueta del controlador: ";
            cin >> controladortiqueta;

            Sensor* sensor = nullptr;
            Controlador* controlador = nullptr;

            for (Sensor* s : sensores) {
                if (s->getEtiqueta() == sensorEtiqueta) {
                    sensor = s;
                    break;
                }
            }

            for (Controlador* c : controladores) {
                if (c->getEtiqueta() == controladortiqueta) {
                    controlador = c;
                    break;
                }
            }

            if (sensor && controlador) {
                controlador->makSensor(sensor);
                cout << "\nSensor de voltaje asociado correctamente." << endl;
            }
            else {
                cout << "\nSensor o controlador no encontrado." << endl;
            }
            break;
        }
        case 4: {
            cout << "\nEstado del sistema:" << endl;
            for (Controlador* c : controladores) {
                c->mostrarInformacion();
                c->mostrarSensores();
                cout << endl;
            }


            break;
        }
        case 5: {
            int sensorEtiqueta;
            cout << "\nIntroduce la etiqueta del sensor de voltaje a eliminar: ";
            cin >> sensorEtiqueta;

            for (Controlador* c : controladores) {
                c->desasociarSensor(sensorEtiqueta);
            }

            for (auto it = sensores.begin(); it != sensores.end(); ) {
                if ((*it)->getEtiqueta() == sensorEtiqueta) {
                    delete* it;
                    it = sensores.erase(it);

                }
                else {
                    ++it;
                }
            }

            cout << "\nSensor de voltaje eliminado correctamente." << endl;


            break;
        }
        case 6:
            cout << "\nSaliendo del programa..." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
            break;
        }


    } while (opcion != 6);


    for (Sensor* s : sensores) {
        delete s;
    }

    for (Controlador* c : controladores) {
        delete c;
    }

    return 0;
}
