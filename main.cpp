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

// Clases derivadas
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

// Función para agregar un libro
void agregarProducto(GestorBD &gestor) {
    string titulo, autor, editorial, genero, isbn;
    int paginas;
    double precio;

    cout << "Título: ";
    cin >> titulo;
    cout << "Autor: ";
    cin >> autor;
    cout << "Editorial: ";
    cin >> editorial;
    cout << "Género: ";
    cin >> genero;
    cout << "ISBN: ";
    cin >> isbn;
    cout << "Número de páginas: ";
    cin >> paginas;
    cout << "Precio: ";
    cin >> precio;

    Libro nuevoLibro(titulo, precio, autor, editorial, genero, isbn, paginas);

    string query = "INSERT INTO Libro (titulo, autor, editorial, genero, isbn, paginas, precio) VALUES ('" +
                   titulo + "','" + autor + "','" + editorial + "','" + genero + "','" + isbn + "'," +
                   to_string(paginas) + "," + to_string(precio) + ")";

    if (gestor.ejecutarConsulta(query))
        cout << "Libro agregado correctamente.\n";
    else
        cout << "Error al agregar el libro.\n";
}

// Función para consultar productos
void consultarProductos(GestorBD &gestor) {
    string query = "SELECT * FROM Libro";
    if (gestor.ejecutarConsulta(query))
        cout << "Consulta realizada correctamente.\n";
    else
        cout << "Error al realizar la consulta.\n";
}

// Función para modificar un producto
void modificarProducto(GestorBD &gestor) {
    string titulo, nuevoPrecio;
    cout << "Introduce el título del producto a modificar: ";
    cin >> titulo;
    cout << "Introduce el nuevo precio: ";
    cin >> nuevoPrecio;

    string query = "UPDATE Libro SET precio = " + nuevoPrecio + " WHERE titulo = '" + titulo + "'";
    if (gestor.ejecutarConsulta(query))
        cout << "Producto modificado correctamente.\n";
    else
        cout << "Error al modificar el producto.\n";
}

// Función para eliminar un producto
void eliminarProducto(GestorBD &gestor) {
    string titulo;
    cout << "Introduce el título del producto a eliminar: ";
    cin >> titulo;

    string query = "DELETE FROM Libro WHERE titulo = '" + titulo + "'";
    if (gestor.ejecutarConsulta(query))
        cout << "Producto eliminado correctamente.\n";
    else
        cout << "Error al eliminar el producto.\n";
}

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
            agregarProducto(gestor);
            break;
        case 2:
            consultarProductos(gestor);
            break;
        case 3:
            modificarProducto(gestor);
            break;
        case 4:
            eliminarProducto(gestor);
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
