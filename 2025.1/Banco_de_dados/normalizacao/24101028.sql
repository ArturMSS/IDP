CREATE TABLE Cliente (
    cpf_cliente CHAR(11) PRIMARY KEY,
    nome_cliente VARCHAR(100),
    endereco_cliente VARCHAR(255)
);

CREATE TABLE Produto (
    cod_produto INT PRIMARY KEY,
    nome_produto VARCHAR(100),
    categoria_produto VARCHAR(50),
    preco_unitario DECIMAL(10,2)
);

CREATE TABLE Vendedor (
    cpf_vendedor CHAR(11) PRIMARY KEY,
    nome_vendedor VARCHAR(100),
    regional_vendedor VARCHAR(100)
);

CREATE TABLE Venda(
    id_venda INT PRIMARY KEY,
    data DATE,
    cpf_cliente CHAR(11),
    cod_produto INT,
    quantidade INT,
    cpf_vendedor CHAR(11),
    FOREIGN KEY (cpf_cliente) REFERENCES Cliente(cpf_cliente),
    FOREIGN KEY (cod_produto) REFERENCES Produto(cod_produto),
    FOREIGN KEY (cpf_vendedor) REFERENCES Vendedor(cpf_vendedor)
);

INSERT INTO Cliente(cpf_cliente, nome_cliente, endereco_cliente) VALUES
('12345678901', 'Maria Souza', 'Rua A, 123'),
('32165498700', 'Carlos Mendes', 'Av. Central, 456'),
('45612378900', 'Bruna Rocha', 'Rua B, 789');

INSERT INTO Produto (cod_produto, nome_produto, categoria_produto, preco_unitario) VALUES
(101, 'Caneta Azul', 'Papelaria', 2.50),
(102, 'Caderno 200fl', 'Papelaria', 15.00),
(103, 'Mochila Escolar', 'Mochilas', 120.00);

INSERT INTO Vendedor (cpf_vendedor, nome_vendedor, regional_vendedor) VALUES
('98765432100', 'João Lima', 'Sul'),
('11122233344', 'Ana Paula', 'Norte');

INSERT INTO Venda (id_venda, data, cpf_cliente, cod_produto, quantidade, cpf_vendedor) VALUES
(1, '2025-05-01', '12345678901', 101, 10, '98765432100'),
(2, '2025-05-01', '32165498700', 102, 5, '98765432100'),
(3, '2025-05-02', '12345678901', 103, 1, '11122233344'),
(4, '2025-05-03', '45612378900', 101, 15, '98765432100'),
(5, '2025-05-03', '32165498700', 103, 2, '11122233344');