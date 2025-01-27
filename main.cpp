#include <iostream>
#include "clases/Sensor.h"
#include "clases/Controlador.h"
#include "funciones/Menu.h"

using namespace std;

int main() {

    vector<Sensor*> sensores; 
    vector<Controlador*> controladores; 

    int opcion;
    cout<<"*************************************************\n***********Bienvenido a la SubEstacion***********\n*******************Las Flores********************\n*************************************************";


    do {
        cout<<endl;
        mostrarMenu();
        cin >> opcion;

        switch (opcion){

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
                } else {
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
            } else {
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
                        delete *it; // Liberar memoria
                        it = sensores.erase(it); // Eliminar de la lista
                        
                    } else {
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