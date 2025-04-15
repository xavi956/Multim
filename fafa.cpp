#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Vehiculo {
protected:
    int id;
    string matricula;
    string marca;
    string modelo;
    int anio;
    int kilometros;

public:
    Vehiculo(int _id, string _matricula, string _marca, string _modelo, int _anio, int _kilometros)
        : id(_id), matricula(_matricula), marca(_marca), modelo(_modelo), anio(_anio), kilometros(_kilometros) {}

    virtual void mostrarInfo() {1
        cout << "(" << id << ") " << "Matricula: " << matricula << ", Marca: " << marca << ", Modelo: " << modelo
            << ", Año: " << anio << ", Kilometros: " << kilometros << endl;
    }

    virtual void realizarMantenimiento() = 0;
};

class Coche : public Vehiculo {
private:
    int numPuertas;
    int cilindrada;

public:
    Coche(int _id, string _matricula, string _marca, string _modelo, int _anio, int _kilometros, int _numPuertas, int _cilindrada)
        : Vehiculo(_id, _matricula, _marca, _modelo, _anio, _kilometros), numPuertas(_numPuertas), cilindrada(_cilindrada) {}

    void mostrarInfo() override {
        Vehiculo::mostrarInfo();
        cout << "Puertas: " << numPuertas << ", Cilindrada: " << cilindrada << " cc" << endl;
    }

    void realizarMantenimiento() override {
        cout << "Realizando cambio de aceite y revisión de frenos para coche." << endl;
    }
};

class Moto : public Vehiculo {
private:
    string tipoManillar;
    int cilindrada;

public:
    Moto(int _id, string _matricula, string _marca, string _modelo, int _anio, int _kilometros, string _tipoManillar, int _cilindrada)
        : Vehiculo(_id, _matricula, _marca, _modelo, _anio, _kilometros), tipoManillar(_tipoManillar), cilindrada(_cilindrada) {}

    void mostrarInfo()  {
        Vehiculo::mostrarInfo();
        cout << "Manillar: " << tipoManillar << ", Cilindrada: " << cilindrada << " cc" << endl;
    }

    void realizarMantenimiento()  {
        cout << "Revisión de cadena y aceite de motor para moto." << endl;
    }
};

class Camion : public Vehiculo {
private:
    int capacidadCarga;

public:
    Camion(int _id, string _matricula, string _marca, string _modelo, int _anio, int _kilometros, int _capacidadCarga)
        : Vehiculo(_id, _matricula, _marca, _modelo, _anio, _kilometros), capacidadCarga(_capacidadCarga) {}

    void mostrarInfo()  {
        Vehiculo::mostrarInfo();
        cout << "Capacidad de carga: " << capacidadCarga << " kg" << endl;
    }

    void realizarMantenimiento()  {
        cout << "Revision de frenos, neumaticos y suspension para camion." << endl;
    }
};

int main() {
    vector<Vehiculo*> taller;//taller es el contenedor-->los objetos de taller son de Vehiculo

    Coche coche1(1, "1234ABC", "Toyota", "Corolla", 2020, 50000, 4, 1600);
    Moto moto1(2, "5678DEF", "Yamaha", "MT-07", 2021, 15000, "Deportivo", 700);
    Camion camion1(3, "9101GHI", "Volvo", "FH16", 2019, 120000, 25000);

    taller.push_back(&coche1);
    taller.push_back(&moto1);
    taller.push_back(&camion1);

    for (size_t i = 0; i < taller.size(); ++i) {
        Vehiculo* vehiculo = taller[i];
        vehiculo->mostrarInfo();
        cout << "____________________"<< "\n\n";
    }


    cout << "Presiona Enter para salir...";
    cin.get();

    return 0;
}
