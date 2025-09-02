import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

file_path = "Titanic-Dataset.xls"  # mesmo que seja CSV com extensão errada

# ==============================
# Leitura do arquivo
# ==============================
try:
    df = pd.read_csv(file_path)  # tenta como CSV
except Exception:
    df = pd.read_excel(file_path, engine="openpyxl")  # tenta como Excel

# ==============================
# Informações sobre Age
# ==============================
print("\n--- Informações da coluna Age ---")
print(df['Age'].info())

print("\n--- Estatísticas descritivas de Age ---")
print(df['Age'].describe())

# ==============================
# Valores ausentes
# ==============================
missing_age = df['Age'].isnull().sum()
print(f"\nValores ausentes em Age: {missing_age}")

# ==============================
# Análise univariada de Age
# ==============================
plt.figure(figsize=(8,5))
sns.histplot(df['Age'].dropna(), kde=True, bins=30, color='skyblue')
plt.title("Distribuição de Age")
plt.xlabel("Age")
plt.ylabel("Frequência")
plt.show()

# Boxplot para visualizar outliers
plt.figure(figsize=(6,4))
sns.boxplot(x=df['Age'], color='lightgreen')
plt.title("Boxplot de Age")
plt.xlabel("Age")
plt.show()
