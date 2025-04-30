#include <iostream>
#include <mysql.h>
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

// Clase GestorBD
class GestorBD {
private:
    MYSQL* conn;

public:
    GestorBD() {
        conn = mysql_init(0);
        conn = mysql_real_connect(conn, "10.20.40.75", "user09", "Uab98134", "user09_db", 3306, NULL, 0);
        mysql_set_character_set(conn, "utf8");
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

    MYSQL_RES* ejecutarConsultaSelect(string consulta) {
        if (mysql_query(conn, consulta.c_str()) == 0)
            return mysql_store_result(conn);
        else {
            cerr << "Error en la consulta: " << mysql_error(conn) << endl;
            return nullptr;
        }
    }

    ~GestorBD() {
        mysql_close(conn);
    }
};

// agregar un producto
void agregarProducto(GestorBD& gestor) {
    cout << "Seleccione el tipo de producto:\n1. Libro\n2. CD\n3. DVD\n4. Juego de PlayStation\n";
    int tipo;
    cin >> tipo;
    cin.ignore();

    string titulo, autor, editorial, genero, isbn;
    int paginas;
    double precio;

    if (tipo == 1) { // Agregar Libro
        cout << "Ingrese título: ";
        getline(cin, titulo);
        cout << "Ingrese autor: ";
        getline(cin, autor);
        cout << "Ingrese editorial: ";
        getline(cin, editorial);
        cout << "Ingrese género: ";
        getline(cin, genero);
        cout << "Ingrese ISBN: ";
        getline(cin, isbn);
        cout << "Ingrese número de páginas: ";
        cin >> paginas;
        cout << "Ingrese precio: ";
        cin >> precio;

        string consulta = "INSERT INTO Libro (titulo, autor, editorial, genero, isbn, paginas, precio) VALUES ('" +
            titulo + "', '" + autor + "', '" + editorial + "', '" + genero + "', '" + isbn + "', " +
            to_string(paginas) + ", " + to_string(precio) + ")";

        if (gestor.ejecutarConsulta(consulta)) {
            cout << "Libro agregado correctamente.\n";
        }
    }
    else {
        cout << "Opción no implementada aún.\n";
    }
}

// consultar productos
void consultarProductos(GestorBD& gestor) {
    cout << "Seleccione el tipo de producto a consultar:\n1. Libro\n2. CD\n3. DVD\n4. Juego de PlayStation\n";
    int tipo;
    cin >> tipo;

    string tabla;
    if (tipo == 1) tabla = "Libro";
    else if (tipo == 2) tabla = "CD";
    else if (tipo == 3) tabla = "DVD";
    else if (tipo == 4) tabla = "JuegoPlayStation";
    else {
        cout << "Tipo de producto no válido.\n";
        return;
    }

    string consulta = "SELECT * FROM " + tabla;
    MYSQL_RES* resultado = gestor.ejecutarConsultaSelect(consulta);
    if (!resultado) return;

    MYSQL_ROW fila;
    while ((fila = mysql_fetch_row(resultado))) {
        for (int i = 0; i < mysql_num_fields(resultado); i++) {
            cout << (fila[i] ? fila[i] : "NULL") << " | ";
        }
        cout << endl;
    }
    mysql_free_result(resultado);
}
void consultarHistorial(GestorBD& gestor) {
    cout << "Seleccione el tipo de producto:\n1. Libro\n2. CD\n3. DVD\n4. Juego de PlayStation\n";
    int tipo;
    cin >> tipo;
    cin.ignore();

    string tipoProducto;
    if (tipo == 1) tipoProducto = "Libro";
    else if (tipo == 2) tipoProducto = "CD";
    else if (tipo == 3) tipoProducto = "DVD";
    else if (tipo == 4) tipoProducto = "JuegoPlayStation";
    else {
        cout << "Tipo de producto no válido.\n";
        return;
    }

    cout << "Ingrese el ID del producto: ";
    string idProducto;
    getline(cin, idProducto);

    string consulta = "SELECT id, fecha_prestamo, fecha_devolucion, nombre_usuario FROM Prestamos "
        "WHERE tipo_producto = '" + tipoProducto + "' AND id_producto = " + idProducto;

    MYSQL_RES* resultado = gestor.ejecutarConsultaSelect(consulta);
    if (!resultado) return;

    MYSQL_ROW fila;
    cout << "\nHistorial de préstamos:\n";
    while ((fila = mysql_fetch_row(resultado))) {
        cout << "ID: " << (fila[0] ? fila[0] : "NULL")
            << ", Fecha préstamo: " << (fila[1] ? fila[1] : "NULL")
            << ", Fecha devolución: " << (fila[2] ? fila[2] : "NULL")
            << ", Usuario: " << (fila[3] ? fila[3] : "NULL") << endl;
    }
    mysql_free_result(resultado);
}

// Menú principal
int main() {
    GestorBD gestor;
    int opcion;
    do {
        cout << "\n1. Agregar producto\n2. Consultar productos\n3. Modificar producto\n4. Eliminar producto\n5. Mostrar historial\n6. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            agregarProducto(gestor);
            break;
        case 2:
            consultarProductos(gestor);
            break;
        case 5:
            consultarHistorial(gestor);
            break;
        case 6:
            cout << "Saliendo del sistema...\n";
            break;
        default:
            cout << "Opción no válida.\n";
        }
    } while (opcion != 5);
    return 0;
}
