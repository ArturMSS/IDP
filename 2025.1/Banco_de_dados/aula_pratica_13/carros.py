import json
import csv
import sqlite3

def executar_sql(arquivo_sql, cursor):
    with open(arquivo_sql, 'r', encoding='utf-8') as f:
        sql_script = f.read()
    cursor.executescript(sql_script)

def exportar_dados():
    conn = sqlite3.connect('carros.db')
    cursor = conn.cursor()

    executar_sql('ddl.sql', cursor)
    executar_sql('dml.sql', cursor)

    with open('dql.sql', 'r', encoding='utf-8') as f:
        dql_queries = f.read().strip().split(';')

    lista_dicts = []
    for query in dql_queries:
        if query.strip():
            cursor.execute(query)
            colunas = [desc[0] for desc in cursor.description]
            registros = cursor.fetchall()
            for linha in registros:
                registro_dict = dict(zip(colunas, linha))
                lista_dicts.append(registro_dict)

    # Exportar JSON (pode manter igual)
    with open('carros.json', 'w', encoding='utf-8') as fjson:
        json.dump(lista_dicts, fjson, ensure_ascii=False, indent=2)

    # Ajustar nomes dos campos para o CSV (remover espaços, caracteres especiais)
    # Exemplo simples: trocar espaços por underline (se houver)
    fieldnames = lista_dicts[0].keys() if lista_dicts else []
    fieldnames_csv = [f.replace(' ', '_').lower() for f in fieldnames]

    if lista_dicts:
        with open('carros.csv', 'w', newline='', encoding='utf-8') as fcsv:
            writer = csv.writer(fcsv, delimiter=',')
            writer.writerow(fieldnames_csv)  # cabeçalho

            for registro in lista_dicts:
                linha = []
                for campo in fieldnames:
                    valor = registro[campo]
                    # Ajustar valores para o formato Looker Studio
                    if isinstance(valor, float):
                        # usar ponto decimal (já padrão em float)
                        linha.append(valor)
                    elif isinstance(valor, int):
                        linha.append(valor)
                    elif valor is None:
                        linha.append('')
                    else:
                        linha.append(str(valor))
                writer.writerow(linha)

    print(f"{len(lista_dicts)} registros exportados para carros.json e carros.csv")

    cursor.close()
    conn.close()

if __name__ == "__main__":
    exportar_dados()
