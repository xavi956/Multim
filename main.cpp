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

// Clase CD
class CD : public Producto {
private:
    string artista, genero;
    int canciones;

public:
    CD(string t, double p, string a, string g, int n)
        : Producto(t, p), artista(a), genero(g), canciones(n) {}

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
        cout << "DVD: " << titulo << ", Director: " << director << ", Duración: " << duracion << " min, Precio: " << precio << "€\n";
    }

    string obtenerTipo() override { return "DVD"; }
};

// Clase JuegoPlayStation
class JuegoPlayStation : public Producto {
private:
    string desarrollador, genero, plataforma;
    int edadRecomendada;

public:
    JuegoPlayStation(string t, double p, string d, string g, string plat, int edad)
        : Producto(t, p), desarrollador(d), genero(g), plataforma(plat), edadRecomendada(edad) {}

    void mostrarDatos() override {
        cout << "Juego PS: " << titulo << ", Desarrollador: " << desarrollador
            << ", Plataforma: " << plataforma << ", Edad Recomendada: " << edadRecomendada
            << ", Precio: " << precio << "€\n";
    }

    string obtenerTipo() override { return "JuegoPlayStation"; }
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

void agregarProducto(GestorBD& gestor) {
    cout << "Seleccione el tipo de producto:\n1. Libro\n2. CD\n3. DVD\n4. Juego de PlayStation\n";
    int tipo;
    cin >> tipo;
    cin.ignore();

    string titulo, genero;
    double precio;

    if (tipo == 1) {
        string autor, editorial, isbn;
        int paginas;
        cout << "Ingrese título: "; getline(cin, titulo);
        cout << "Ingrese autor: "; getline(cin, autor);
        cout << "Ingrese editorial: "; getline(cin, editorial);
        cout << "Ingrese género: "; getline(cin, genero);
        cout << "Ingrese ISBN: "; getline(cin, isbn);
        cout << "Ingrese número de páginas: "; cin >> paginas;
        cout << "Ingrese precio: "; cin >> precio;

        string consulta = "INSERT INTO Libro (titulo, autor, editorial, genero, isbn, paginas, precio) VALUES ('" +
            titulo + "', '" + autor + "', '" + editorial + "', '" + genero + "', '" + isbn + "', " +
            to_string(paginas) + ", " + to_string(precio) + ")";
        if (gestor.ejecutarConsulta(consulta))
            cout << "Libro agregado correctamente.\n";
    }
    else if (tipo == 2) {
        string artista;
        int canciones;
        cout << "Ingrese título: "; getline(cin, titulo);
        cout << "Ingrese artista: "; getline(cin, artista);
        cout << "Ingrese género: "; getline(cin, genero);
        cout << "Ingrese número de canciones: "; cin >> canciones;
        cout << "Ingrese precio: "; cin >> precio;

        string consulta = "INSERT INTO CD (titulo, artista, genero, canciones, precio) VALUES ('" +
            titulo + "', '" + artista + "', '" + genero + "', " + to_string(canciones) + ", " + to_string(precio) + ")";
        if (gestor.ejecutarConsulta(consulta))
            cout << "CD agregado correctamente.\n";
    }
    else if (tipo == 3) {
        string director;
        int duracion;
        cout << "Ingrese título: "; getline(cin, titulo);
        cout << "Ingrese director: "; getline(cin, director);
        cout << "Ingrese género: "; getline(cin, genero);
        cout << "Ingrese duración en minutos: "; cin >> duracion;
        cout << "Ingrese precio: "; cin >> precio;

        string consulta = "INSERT INTO DVD (titulo, director, genero, duracion, precio) VALUES ('" +
            titulo + "', '" + director + "', '" + genero + "', " + to_string(duracion) + ", " + to_string(precio) + ")";
        if (gestor.ejecutarConsulta(consulta))
            cout << "DVD agregado correctamente.\n";
    }
    else if (tipo == 4) {
        string desarrollador, plataforma;
        int edad;
        cout << "Ingrese título: "; getline(cin, titulo);
        cout << "Ingrese desarrollador: "; getline(cin, desarrollador);
        cout << "Ingrese género: "; getline(cin, genero);
        cout << "Ingrese plataforma: "; getline(cin, plataforma);
        cout << "Ingrese edad recomendada: "; cin >> edad;
        cout << "Ingrese precio: "; cin >> precio;

        string consulta = "INSERT INTO JuegoPlayStation (titulo, desarrollador, genero, plataforma, edad_Recomendada, precio) VALUES ('" +
            titulo + "', '" + desarrollador + "', '" + genero + "', '" + plataforma + "', " + to_string(edad) + ", " + to_string(precio) + ")";
        if (gestor.ejecutarConsulta(consulta))
            cout << "Juego agregado correctamente.\n";
    }
    else {
        cout << "Opción no válida.\n";
    }
}

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

void modificarProducto(GestorBD& gestor) {
    cout << "Seleccione el tipo de producto a modificar:\n1. Libro\n2. CD\n3. DVD\n4. Juego de PlayStation\n";
    int tipo;
    cin >> tipo;
    cin.ignore();

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

    cout << "Ingrese el ID del producto a modificar: ";
    string id;
    getline(cin, id);

    cout << "Ingrese el nombre del campo a modificar";
    string campo;
    if (tipo == 1) {
        cout << "(titulo, autor, editorial, genero, isbn, paginas, precio: )";
    }
    else if (tipo == 2) {
        cout << "(titulo, artista, genero, canciones, precio: )";
    }
    else if (tipo == 3) {
        cout << "(titulo, director, genero, duracion, precio: )";
    }
    else if (tipo == 4) {
        cout << "(titulo, desarrollador, genero, plataforma, edad_Recomendada, precio: )";
    }
    else {
        cout << "opcion no valida";
        return;
    }
    getline(cin, campo);

    cout << "Ingrese el nuevo valor: ";
    string nuevoValor;
    getline(cin, nuevoValor);

    string consultaUpdate;
    if (campo == "precio" || campo == "paginas" || campo == "canciones" || campo == "duracion" || campo == "edad_Recomendada") {
        consultaUpdate = "UPDATE " + tabla + " SET " + campo + " = " + nuevoValor + " WHERE id = " + id;
    }
    else {
        consultaUpdate = "UPDATE " + tabla + " SET " + campo + " = '" + nuevoValor + "' WHERE id = " + id;
    }

    if (gestor.ejecutarConsulta(consultaUpdate)) {
        cout << "Producto modificado correctamente.\n";
    }
}

void eliminarProducto(GestorBD& gestor) {
    cout << "Seleccione el tipo de producto a eliminar:\n1. Libro\n2. CD\n3. DVD\n4. Juego de PlayStation\n";
    int tipo;
    cin >> tipo;
    cin.ignore();

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

    cout << "Ingrese el ID del producto a eliminar: ";
    string id;
    getline(cin, id);

    string borrar = "DELETE FROM " + tabla + " WHERE id = " + id;
    if (gestor.ejecutarConsulta(borrar)) {
        cout << "Producto eliminado correctamente.\n";
    }
}
void consultarHistorial(GestorBD& gestor) {
}

int main() {
    GestorBD gestor;
    int opcion;
    do {
        cout << "\n1. Agregar producto\n2. Consultar productos\n3. Modificar producto\n4. Eliminar producto \n5.Mostrar prestamos \n6. Salir\nSeleccione una opcion: ";
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
            consultarHistorial(gestor);
            break;
        case 6:
            cout << "Saliendo del sistema...\n";
            break;
        default:
            cout << "Opcio  n no válida.\n";
        }
    } while (opcion != 5);
    return 0;
}
