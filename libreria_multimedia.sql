CREATE DATABASE libreria_multimedia;

USE libreria_multimedia;

CREATE TABLE Libro (
    id INT PRIMARY KEY AUTO_INCREMENT,
    titulo VARCHAR(100),
    autor VARCHAR(100),
    editorial VARCHAR(100),
    genero VARCHAR(50),
    isbn VARCHAR(20),
    paginas INT,
    precio DECIMAL(10, 2)
);

CREATE TABLE CD (
    id INT PRIMARY KEY AUTO_INCREMENT,
    titulo VARCHAR(100),
    artista VARCHAR(100),
    genero VARCHAR(50),
    canciones INT,
    precio DECIMAL(10, 2)
);

CREATE TABLE DVD (
    id INT PRIMARY KEY AUTO_INCREMENT,
    titulo VARCHAR(100),
    director VARCHAR(100),
    genero VARCHAR(50),
    duracion INT,
    precio DECIMAL(10, 2)
);

CREATE TABLE JuegoPlayStation (
    id INT PRIMARY KEY AUTO_INCREMENT,
    titulo VARCHAR(100),
    desarrollador VARCHAR(100),
    genero VARCHAR(50),
    plataforma VARCHAR(50),
    edad_recomendada INT,
    precio DECIMAL(10, 2)
);
