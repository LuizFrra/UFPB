CREATE DATABASE Locadora;

CREATE TABLE Cliente
(
    ID int AUTO_INCREMENT,
    Nome varchar(30) NOT NULL,
    SobreNome varchar(30) NOT NULL,
    Telefone varchar(10) NOT NULL,
    Endereco varchar(50) NOT NULL,
    PRIMARY KEY(ID)
);

CREATE TABLE FITA
(
    ID int AUTO_INCREMENT PRIMARY KEY, 
    IDFilme int NOT NULL,
    FOREIGN KEY(IDFilme) REFERENCES Filme(ID)
);

CREATE TABLE Alugados
(
    IDCliente int NOT NULL,
    IDFita int NOT NULL UNIQUE,
    FOREIGN KEY(IDCliente) REFERENCES Cliente(ID),
    FOREIGN KEY(IDFita) REFERENCES FITA(ID),
    PRIMARY KEY(IDCliente, IDFita)  
);

CREATE TABLE Categoria
(
    ID int AUTO_INCREMENT PRIMARY KEY,
    Tipo varchar(25) NOT NULL UNIQUE
);

CREATE TABLE Filme
(
    ID int AUTO_INCREMENT PRIMARY KEY,
    IDCategoria int NOT NULL,
    Nome varchar(50) NOT NULL UNIQUE,
    FOREIGN KEY(IDCategoria) REFERENCES Categoria(ID)
);

CREATE TABLE Estrelas
(
    ID int AUTO_INCREMENT PRIMARY KEY,
    IDFilme int NOT NULL,
    NomeFicticio varchar(100) NOT NULL,
    NomeReal varchar(100) NOT NULL,
    DataDeNascimento DATE NOT NULL,
    FOREIGN KEY(IdFilme) REFERENCES Filme(ID)
);


