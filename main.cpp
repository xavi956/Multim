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
        cout << "Libro: " << titulo << ", Autor: " << autor << ", Precio: " << precio << "\u20ac\n";
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
        cout << "CD: " << titulo << ", Artista: " << artista << ", Precio: " << precio << "\u20ac\n";
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
        cout << "DVD: " << titulo << ", Director: " << director << ", Duraci\u00f3n: " << duracion << " min, Precio: " << precio << "\u20ac\n";
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
             << ", Precio: " << precio << "\u20ac\n";
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
            cout << "Conexi\u00f3n exitosa a la base de datos.\n";
        else
            cout << "Error de conexi\u00f3n a la base de datos.\n";
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
        cout << "Ingrese t\u00edtulo: "; getline(cin, titulo);
        cout << "Ingrese autor: "; getline(cin, autor);
        cout << "Ingrese editorial: "; getline(cin, editorial);
        cout << "Ingrese g\u00e9nero: "; getline(cin, genero);
        cout << "Ingrese ISBN: "; getline(cin, isbn);
        cout << "Ingrese n\u00famero de p\u00e1ginas: "; cin >> paginas;
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
        cout << "Ingrese t\u00edtulo: "; getline(cin, titulo);
        cout << "Ingrese artista: "; getline(cin, artista);
        cout << "Ingrese g\u00e9nero: "; getline(cin, genero);
        cout << "Ingrese n\u00famero de canciones: "; cin >> canciones;
        cout << "Ingrese precio: "; cin >> precio;

        string consulta = "INSERT INTO CD (titulo, artista, genero, canciones, precio) VALUES ('" +
            titulo + "', '" + artista + "', '" + genero + "', " + to_string(canciones) + ", " + to_string(precio) + ")";
        if (gestor.ejecutarConsulta(consulta))
            cout << "CD agregado correctamente.\n";
    }
    else if (tipo == 3) {
        string director;
        int duracion;
        cout << "Ingrese t\u00edtulo: "; getline(cin, titulo);
        cout << "Ingrese director: "; getline(cin, director);
        cout << "Ingrese g\u00e9nero: "; getline(cin, genero);
        cout << "Ingrese duraci\u00f3n en minutos: "; cin >> duracion;
        cout << "Ingrese precio: "; cin >> precio;

        string consulta = "INSERT INTO DVD (titulo, director, genero, duracion, precio) VALUES ('" +
            titulo + "', '" + director + "', '" + genero + "', " + to_string(duracion) + ", " + to_string(precio) + ")";
        if (gestor.ejecutarConsulta(consulta))
            cout << "DVD agregado correctamente.\n";
    }
    else if (tipo == 4) {
        string desarrollador, plataforma;
        int edad;
        cout << "Ingrese t\u00edtulo: "; getline(cin, titulo);
        cout << "Ingrese desarrollador: "; getline(cin, desarrollador);
        cout << "Ingrese g\u00e9nero: "; getline(cin, genero);
        cout << "Ingrese plataforma: "; getline(cin, plataforma);
        cout << "Ingrese edad recomendada: "; cin >> edad;
        cout << "Ingrese precio: "; cin >> precio;

        string consulta = "INSERT INTO JuegoPlayStation (titulo, desarrollador, genero, plataforma, edad_Recomendada, precio) VALUES ('" +
            titulo + "', '" + desarrollador + "', '" + genero + "', '" + plataforma + "', " + to_string(edad) + ", " + to_string(precio) + ")";
        if (gestor.ejecutarConsulta(consulta))
            cout << "Juego agregado correctamente.\n";
    }
    else {
        cout << "Opcion no v\u00e1lida.\n";
    }
}

// main()
int main() {
    GestorBD gestor;
    int opcion;
    do {
        cout << "\n1. Agregar producto\n2. Salir\nSeleccione una opci\u00f3n: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            agregarProducto(gestor);
            break;
        case 2:
            cout << "Saliendo del sistema...\n";
            break;
        default:
            cout << "Opci\u00f3n no v\u00e1lida.\n";
        }
    } while (opcion != 2);
    return 0;
}
