CREATE TABLE carros (
    id INT PRIMARY KEY,
    modelo VARCHAR(100),
    preco DECIMAL(10,2),
    ano int;
    cor char(50),
    quilometragem int,
    litragem int,
    tipo_combustivel char(50),
    cambio char(50),
    FOREIGN KEY (modelo) REFERENCES marca(modelo)
);

