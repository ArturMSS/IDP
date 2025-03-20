import pandas as pd # type: ignore
import numpy as np
import matplotlib.pyplot as plt
import statistics
import seaborn as sns # type: ignore
#from scipy import stats

sns.set_theme(style="darkgrid")

def carregar_dados(caminho_arquivo):
    # Carrega o arquivo Excel e substitui valores nulos por 0.
    return pd.read_excel(caminho_arquivo).fillna(0)

def calcular_amplitude(df):
    return df.max() - df.min()


def frequencia(df):
    # Verifica se o tipo dos dados é numérico
    if pd.api.types.is_numeric_dtype(df):
        # Cria um range de valores de acordo com o mínimo e máximo da coluna
        all_values = pd.Series(range(int(df.min()), int(df.max()) + 1))
        # A frequência de valores em uma coluna, incluindo valores com 0 frequência
        freq = df.value_counts().reindex(all_values, fill_value=0).sort_index()
    else:
        # Para colunas com valores não numéricos, simplesmente conta as frequências
        freq = df.value_counts().sort_index()
    return freq


def imprimir(df,label):
    print(f"{label}\n{df.to_string(header=False)}\n{'-'*30}") # Usa to_string() para remover Name e dtype e header = False para não ler o nome da coluna

def calcular_bins(df, amplitude_classe, precision=2):
    min_val = df.min()
    max_val = df.max()
    # Calcula os intervalos de classe (bins) e ajusta o último intervalo para incluir o maior valor.
    num_classes = int(np.ceil(calcular_amplitude(df) / amplitude_classe)) # np.ceil arredonda o resultado para cima
    bins = [round(min_val + i * amplitude_classe, precision) for i in range(num_classes + 1)]
    bins[-1] = round(max_val + 0.01, precision) # Garante que o maior valor seja incluído
    
    # Converte os valores dos bins para float e arredonda de acordo com a precisão especificada
    bins = [round(float(bin_val), precision) for bin_val in bins]
    return bins

def agrupar_frequencia_classes(df, amplitude_classe):
    bins = calcular_bins(df, amplitude_classe)
    # Agrupa dados dentro das classes
    df = pd.cut(df, bins=bins, right=False) # Use cut when you need to segment and sort data values into bins. right=False, faz o intervalo ser aberto na direita ao inves de na esquerda
    return frequencia(df)

def porcentagem(df):
    porcentagem = round((df / df.sum()) * 100, 2)
    return porcentagem.astype(str) + '%'

def analisar(df, label, label2):
    imprimir(df, label)
    imprimir(porcentagem(df), label2)

# Exibir o histograma
def histograma(df, label, label2,titulo):
    plt.hist(df, color='c',edgecolor='black') 
    plt.xlabel(label)
    plt.ylabel(label2)
    plt.title(titulo)
    plt.show()

def boxplot(df, label):
    plt.boxplot(df)
    plt.title(label)
    plt.show()

def medidas(df, label):
    media = statistics.mean(df)
    mediana = statistics.median(df)
    moda = statistics.mode(df)
    variancia = (df).var()
    desvioP = (df).std()
    print (f"Em relação ao(s) {label}: \n A média é: {media} \n A mediana é: {mediana}\n A moda é: {moda}\n A variância é: {variancia}\n O Desvio padrão é {desvioP} \n{'-'*30}\n ")

# Caminho do arquivo
caminho_arquivo = r"C:\Users\rutra\Downloads\Tabela de salários.xlsx"

# Carrega os dados
df = carregar_dados(caminho_arquivo)


# Análise de Salários
salarios = df['Salario (x Sal Min)']
print(f"Maior salário: {salarios.max()}, Menor salário: {salarios.min()}")
amplitude_salarios = calcular_amplitude(salarios)
print(f"Amplitude dos salários: {amplitude_salarios}")
freq_classes = agrupar_frequencia_classes(salarios, 4)
analisar(freq_classes,'Faixas salariais:', 'Percentual relativo de sálarios:')
histograma(salarios,'Salário(xSalmin)', 'Frequencia', 'Faixas salariais')
boxplot(salarios, 'Boxplot Salários')
medidas(salarios,'Salários')

# Análise de Número de Filhos
n_filhos = df['N de Filhos']
print(f"Maior número de filhos: {int(n_filhos.max())}, Menor número de filhos: {int(n_filhos.min())}")
amplitude_filhos = calcular_amplitude(n_filhos)
print(f"Amplitude no número de filhos: {amplitude_filhos}")
freq = frequencia(n_filhos)
analisar(freq, 'Número de filhos:', 'percentual relativo do número de filhos:')
histograma(n_filhos,'numero de filhos', 'frequencia','Número de filhos')
boxplot(n_filhos, 'Boxplot N de filhos')
medidas(n_filhos, 'Número de filhos')

# Análise de Grau de Instrução
grau_instrucao = df['Grau de Instrução']
freq = frequencia(grau_instrucao)
analisar(freq, 'Grau de instrução:', 'Percentual relativo do grau de instrução:')
histograma(grau_instrucao, 'Grau de instrução', 'Frequência', 'Grau de instrução')


# Análise de Estado Civil
estado_civil = df['Estado Civil']
freq = frequencia(estado_civil)
analisar(freq, 'Estado Civil:', 'Percentual relativo do estado civil:')
histograma(estado_civil, 'Estado civil', 'frequencia', 'Estado civil')


# Análise de Idade
idade = df['Idade (em anos)']
print(f"Pessoa mais velha: {idade.max()} anos, Pessoa mais nova: {idade.min()} anos")
amplitude_idade = calcular_amplitude(idade)
print(f"Amplitude de idade: {amplitude_idade}")
freq_classes = agrupar_frequencia_classes(idade, 5)
analisar(freq_classes, 'Faixas etárias:', 'Percentual relativo das faixas etárias:')
histograma(idade,'Idade', 'Frequencia','Idade (em anos)')
boxplot(idade, 'Idade')
medidas(idade, 'Idade')

# Análise de Região de Procedência
regiao = df['Região de Procedência']
freq = frequencia(regiao)
analisar (freq, 'Região de procedência:', 'Percentual relativo das regiões de procedência:')
histograma(regiao, 'Região de procedência', 'Frequencia', 'Regiões de procedência')

# Análise comparativa de dados
sns.histplot(df, x = salarios, kde = True, hue = estado_civil)
plt.show()
sns.histplot(df, x = salarios, kde = True, hue = n_filhos  )
plt.show()
