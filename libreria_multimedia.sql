CREATE TABLE Prestamos (
    id INT AUTO_INCREMENT PRIMARY KEY,
    tipo_producto VARCHAR(50),
    id_producto INT,
    fecha_prestamo DATETIME,
    fecha_devolucion DATETIME,
    nombre_usuario VARCHAR(100)
);
