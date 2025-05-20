-- Criação das tabelas
CREATE TABLE IF NOT EXISTS marcas (
    id_marca INTEGER PRIMARY KEY AUTOINCREMENT,
    nome_marca VARCHAR(100) NOT NULL
);

CREATE TABLE IF NOT EXISTS modelos (
    id_modelo INTEGER PRIMARY KEY AUTOINCREMENT,
    id_marca INTEGER,
    nome_modelo VARCHAR(100) NOT NULL,
    ano INTEGER NOT NULL,
    portas INTEGER NOT NULL,
    FOREIGN KEY (id_marca) REFERENCES marcas(id_marca)
);

CREATE TABLE IF NOT EXISTS motores (
    id_motor INTEGER PRIMARY KEY AUTOINCREMENT,
    litros DECIMAL(3,1) NOT NULL
);

CREATE TABLE IF NOT EXISTS combustiveis (
    id_combustivel INTEGER PRIMARY KEY AUTOINCREMENT,
    tipo_combustivel VARCHAR(50) NOT NULL
);

CREATE TABLE IF NOT EXISTS cambios (
    id_cambio INTEGER PRIMARY KEY AUTOINCREMENT,
    tipo_cambio VARCHAR(50) NOT NULL
);

CREATE TABLE IF NOT EXISTS carros (
    id_carro INTEGER PRIMARY KEY AUTOINCREMENT,
    id_modelo INTEGER,
    id_motor INTEGER,
    id_combustivel INTEGER,
    id_cambio INTEGER,
    preco DECIMAL(10,2) NOT NULL,
    quilometragem INTEGER NOT NULL,
    proprietarios INTEGER NOT NULL,
    FOREIGN KEY (id_modelo) REFERENCES modelos(id_modelo),
    FOREIGN KEY (id_motor) REFERENCES motores(id_motor),
    FOREIGN KEY (id_combustivel) REFERENCES combustiveis(id_combustivel),
    FOREIGN KEY (id_cambio) REFERENCES cambios(id_cambio)
);