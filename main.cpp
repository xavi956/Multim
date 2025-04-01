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

    void agregarLibro() {
        string titulo, autor, editorial, genero, isbn;
        int paginas;
        double precio;

        cout << "Ingrese título: "; cin.ignore(); getline(cin, titulo);
        cout << "Ingrese autor: "; getline(cin, autor);
        cout << "Ingrese editorial: "; getline(cin, editorial);
        cout << "Ingrese género: "; getline(cin, genero);
        cout << "Ingrese ISBN: "; getline(cin, isbn);
        cout << "Ingrese número de páginas: "; cin >> paginas;
        cout << "Ingrese precio: "; cin >> precio;

        string consulta = "INSERT INTO Libro (titulo, autor, editorial, genero, isbn, paginas, precio) VALUES ('" + titulo + "', '" + autor + "', '" + editorial + "', '" + genero + "', '" + isbn + "', " + to_string(paginas) + ", " + to_string(precio) + ")";

        if (ejecutarConsulta(consulta)) {
            cout << "Libro agregado correctamente.\n";
        }
    }

    void consultarLibros() {
        if (mysql_query(conn, "SELECT * FROM Libro")) {
            cerr << "Error en la consulta: " << mysql_error(conn) << endl;
            return;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (!res) {
            cerr << "Error al obtener los resultados.\n";
            return;
        }

        MYSQL_ROW row;
        cout << "\nLibros disponibles:\n";
        while ((row = mysql_fetch_row(res))) {
            cout << "ID: " << row[0] << " | Título: " << row[1] << " | Autor: " << row[2] << " | Editorial: " << row[3] << " | Género: " << row[4] << " | ISBN: " << row[5] << " | Páginas: " << row[6] << " | Precio: " << row[7] << "€\n";
        }
        mysql_free_result(res);
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
        cout << "\n1. Agregar libro\n2. Consultar libros\n3. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            gestor.agregarLibro();
            break;
        case 2:
            gestor.consultarLibros();
            break;
        case 3:
            cout << "Saliendo del sistema...\n";
            break;
        default:
            cout << "Opción no válida.\n";
        }

    } while (opcion != 3);

    return 0;
}
