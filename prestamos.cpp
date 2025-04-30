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
