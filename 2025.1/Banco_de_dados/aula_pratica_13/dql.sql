SELECT
  carros.id_carro,
  modelos.nome_modelo,
  modelos.ano,
  marcas.nome_marca,
  motores.litros,
  combustiveis.tipo_combustivel,
  cambios.tipo_cambio,
  carros.preco,
  carros.quilometragem,
  carros.proprietarios,
  modelos.portas
FROM carros
JOIN modelos ON carros.id_modelo = modelos.id_modelo
JOIN marcas ON modelos.id_marca = marcas.id_marca
JOIN motores ON carros.id_motor = motores.id_motor
JOIN combustiveis ON carros.id_combustivel = combustiveis.id_combustivel
JOIN cambios ON carros.id_cambio = cambios.id_cambio;