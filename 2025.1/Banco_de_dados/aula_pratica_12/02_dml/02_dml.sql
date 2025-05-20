INSERT INTO alunos (id, nome, note) VALUES 
(1, 'artur', 10.00),
(2, 'Helenna', 7.00),
(3, 'Andreia', 4.00);

DELETE * FROM alunos WHERE nota < 5;

UPDATE alunos SET nota = 7 WHERE id = 1;