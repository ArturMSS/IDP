CREATE TABLE Times (
    id SERIAL PRIMARY KEY,
    nome VARCHAR(100) UNIQUE
);

CREATE TABLE Estadios (
    id SERIAL PRIMARY KEY,
    nome VARCHAR(100) UNIQUE,
    publico_recorde INT,
    capacidade INT,
    time_id INT UNIQUE REFERENCES Times(id)
);

CREATE TABLE Jogadores (
    id SERIAL PRIMARY KEY,
    nome VARCHAR(100),
    idade INT,
    titular BOOLEAN,
    time_atual_id INT REFERENCES Times(id)
);

CREATE TABLE Times_Jogadores (
    jogador_id INT REFERENCES Jogadores(id),
    time_id INT REFERENCES Times(id),
    PRIMARY KEY (jogador_id, time_id)
);

-- Inserindo o time
INSERT INTO Times (nome) VALUES ('Corinthians') RETURNING id;

-- Inserindo o estádio
INSERT INTO Estadios (nome, publico_recorde, capacidade, time_id)
VALUES ('Neo Quimica Arena', 63267, NULL, (SELECT id FROM Times WHERE nome = 'Corinthians'));

-- Inserindo os jogadores
INSERT INTO Jogadores (nome, idade, titular, time_atual_id)
VALUES ('Cássio', 33, TRUE, (SELECT id FROM Times WHERE nome = 'Corinthians')) RETURNING id;

INSERT INTO Jogadores (nome, idade, titular, time_atual_id)
VALUES ('Luan', 27, FALSE, (SELECT id FROM Times WHERE nome = 'Corinthians')) RETURNING id;

-- Associando jogadores a seus times anteriores
INSERT INTO Times_Jogadores (jogador_id, time_id)
VALUES ((SELECT id FROM Jogadores WHERE nome = 'Cássio'), (SELECT id FROM Times WHERE nome = 'Grêmio')),
       ((SELECT id FROM Jogadores WHERE nome = 'Cássio'), (SELECT id FROM Times WHERE nome = 'PSV')),
       ((SELECT id FROM Jogadores WHERE nome = 'Cássio'), (SELECT id FROM Times WHERE nome = 'Corinthians')),
       ((SELECT id FROM Jogadores WHERE nome = 'Luan'), (SELECT id FROM Times WHERE nome = 'Grêmio')),
       ((SELECT id FROM Jogadores WHERE nome = 'Luan'), (SELECT id FROM Times WHERE nome = 'Corinthians'));
