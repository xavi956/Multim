int opcion;
do {
    cout << "\n1. Agregar producto\n2. Consultar productos\n3. Modificar producto\n4. Eliminar producto\n5. Salir\n";
    cout << "Seleccione una opción: ";

    if (!(cin >> opcion)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada inválida.\n";
        continue;
    }

    cin.ignore(); // limpia el buffer tras leer número

    switch (opcion) {
    case 1:
        agregarProducto(gestor);
        break;
    case 2:
        consultarProductos(gestor);
        break;
    case 5:
        cout << "Saliendo del sistema...\n";
        break;
    default:
        cout << "Opción no válida.\n";
    }
} while (opcion != 5);
