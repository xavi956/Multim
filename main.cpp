#include <iostream>
#include <mysql/mysql.h>
#include <string>
using namespace std;

// Clase base Producto
class Producto {
protected:
    string titulo;
    double precio;

public:
    Producto(string t, double p) : titulo(t), precio(p) {}
    virtual void mostrarDatos() = 0;
    virtual string obtenerTipo() = 0;
    string getTitulo() { return titulo; }
    double getPrecio() { return precio; }
};

// Clase Libro
class Libro : public Producto {
private:
    string autor, editorial, genero, isbn;
    int paginas;

public:
    Libro(string t, double p, string a, string e, string g, string i, int pag)
        : Producto(t, p), autor(a), editorial(e), genero(g), isbn(i), paginas(pag) {}

    void mostrarDatos() override {
        cout << "Libro: " << titulo << ", Autor: " << autor << ", Precio: " << precio << "€\n";
    }

    string obtenerTipo() override { return "Libro"; }
};

// Clase CD
class CD : public Producto {
private:
    string artista, genero;
    int canciones;

public:
    CD(string t, double p, string ar, string g, int c)
        : Producto(t, p), artista(ar), genero(g), canciones(c) {}

    void mostrarDatos() override {
        cout << "CD: " << titulo << ", Artista: " << artista << ", Precio: " << precio << "€\n";
    }

    string obtenerTipo() override { return "CD"; }
};

// Clase DVD
class DVD : public Producto {
private:
    string director, genero;
    int duracion;

public:
    DVD(string t, double p, string d, string g, int dur)
        : Producto(t, p), director(d), genero(g), duracion(dur) {}

    void mostrarDatos() override {
        cout << "DVD: " << titulo << ", Director: " << director << ", Precio: " << precio << "€\n";
    }

    string obtenerTipo() override { return "DVD"; }
};

// Clase Juego de PlayStation
class JuegoPlayStation : public Producto {
private:
    string desarrollador, genero, plataforma;
    int edadRecomendada;

public:
    JuegoPlayStation(string t, double p, string d, string g, string plat, int edad)
        : Producto(t, p), desarrollador(d), genero(g), plataforma(plat), edadRecomendada(edad) {}

    void mostrarDatos() override {
        cout << "Juego de PlayStation: " << titulo << ", Desarrollador: " << desarrollador << ", Precio: " << precio << "€\n";
    }

    string obtenerTipo() override { return "JuegoPlayStation"; }
};

// Clase para gestionar la base de datos
class GestorBD {
private:
    MYSQL* conn;

public:
    GestorBD() {
        conn = mysql_init(0);
        conn = mysql_real_connect(conn, "localhost", "root", "password", "libreria_multimedia", 3306, NULL, 0);

        if (conn)
            cout << "Conexión exitosa a la base de datos.\n";
        else
            cout << "Error de conexión a la base de datos.\n";
    }

    bool ejecutarConsulta(string consulta) {
        if (mysql_query(conn, consulta.c_str()) == 0)
            return true;
        else {
            cerr << "Error en la consulta: " << mysql_error(conn) << endl;
            return false;
        }
    }

    ~GestorBD() {
        mysql_close(conn);
    }
};

// Menú principal
int main() {
    GestorBD gestor;

    int opcion;
    do {
        cout << "\n1. Agregar producto\n2. Consultar productos\n3. Modificar producto\n4. Eliminar producto\n5. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Seleccione el tipo de producto:\n1. Libro\n2. CD\n3. DVD\n4. Juego de PlayStation\n";
            int tipo;
            cin >> tipo;
            if (tipo == 1) {
                // Aquí llamaríamos a la función para agregar Libro (a completar)
            } else if (tipo == 2) {
                // Aquí llamaríamos a la función para agregar CD (a completar)
            } else if (tipo == 3) {
                // Aquí llamaríamos a la función para agregar DVD (a completar)
            } else if (tipo == 4) {
                // Aquí llamaríamos a la función para agregar Juego de PlayStation (a completar)
            } else {
                cout << "Tipo de producto no válido.\n";
            }
            break;
        case 5:
            cout << "Saliendo del sistema...\n";
            break;
        default:
            cout << "Opción no válida.\n";
        }

    } while (opcion != 5);

    return 0;
}
