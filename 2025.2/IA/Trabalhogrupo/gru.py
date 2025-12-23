import numpy as np
import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers
import matplotlib.pyplot as plt
from sklearn.metrics import classification_report, confusion_matrix, roc_auc_score


tf.random.set_seed(30)
np.random.seed(30)

# Definição dos hiperparâmetros
VOCAB_SIZE = 24000 #N MAX DE PALAVRAS CONSIDERADAS
SEQ_LEN = 250 #TAMANHO DAS SEQUENCIAS DE ENTRADAS
EMBEDDING_DIM = 150 #DIMENSÃO DO VALOR DE EMBEDDING 
GRU_U = 128 #N DE NEURONIOS NA CAMADA GRU
BATCH_SIZE = 128 #QTD DE EX PROCESSADOS POR VEZ
EPOCHS = 15


(x_train, y_train), (x_test, y_test) = keras.datasets.imdb.load_data(num_words=VOCAB_SIZE)

# Padroniza do tamanho das sequências, bota padding e as resenhas tem o mesmo tamanho
x_train = keras.preprocessing.sequence.pad_sequences(x_train, maxlen=SEQ_LEN, padding="post", truncating="post")
x_test  = keras.preprocessing.sequence.pad_sequences(x_test,  maxlen=SEQ_LEN, padding="post", truncating="post")

# Modelo GRU
def modelo_gru(vocab_size=VOCAB_SIZE, emb_dim=EMBEDDING_DIM, seq_len=SEQ_LEN, gru_u=GRU_U):

    # Entrada
    # palavras -> seq de inteiros
    inputs = keras.Input(shape=(seq_len,), dtype="int32")

    # cada idx de palavra vira um vetor contínuo
    x = layers.Embedding(vocab_size, emb_dim, input_length=seq_len)(inputs)
    
    # dropout desativa 20% das conexões da camada durante o treino pra evitar overfitting
    # return_sequences=False retorna so o resumo final
    x = layers.GRU(gru_u, dropout=0.2, recurrent_dropout=0.0, return_sequences=False)(x)

    # camada intermediaria
    # activation="relu" -> mantem valores positivos, zera negativos 
    x = layers.Dense(64, activation="relu")(x)

    # dropout dnv
    x = layers.Dropout(0.3)(x)

    # Camada de saída -> 1 neurônio com ativação sigmoide de probabilidade entre 0 e 1
    outputs = layers.Dense(1, activation="sigmoid")(x) 

    # Monta o modelo final
    model = keras.Model(inputs, outputs)

   
    model.compile(
        loss="binary_crossentropy", # perda 
        optimizer=keras.optimizers.Adam(learning_rate=1e-3),# otimizador 
        metrics=["accuracy", keras.metrics.AUC(name="auc")] # métricas 
    )
    return model


model = modelo_gru()
model.summary()

# Callbacks 
callbacks = [
    # interrompe o treino se AUC não melhorar por 2 épocas
    keras.callbacks.EarlyStopping(patience=2, restore_best_weights=True, monitor="val_auc", mode="max"),

    # reduz a taxa de aprendizado pela metade se a perda de validação parar de melhorar
    keras.callbacks.ReduceLROnPlateau(patience=1, factor=0.5, monitor="val_loss")
]

history = model.fit(
    x_train, y_train, # dados de entrada e saída
    validation_split=0.2, # separa 20% do treino para validação
    epochs=EPOCHS, # número máximo de épocas
    batch_size=BATCH_SIZE,# tamanho do lote
    callbacks=callbacks, # aplica os callbacks definidos acima
    verbose=1 # mostra barra de progresso
)


# Loss
plt.figure()
plt.plot(history.history["loss"], label="loss")
plt.plot(history.history["val_loss"], label="val_loss")
plt.legend()
plt.title("Loss durante o treino")
plt.xlabel("Época")
plt.ylabel("Loss")
plt.show()
plt.savefig("loss.png")


# Acurácia
plt.figure()
plt.plot(history.history["accuracy"], label="acc")
plt.plot(history.history["val_accuracy"], label="val_acc")
plt.legend()
plt.title("Acurácia durante o treino")
plt.xlabel("Época")
plt.ylabel("Acurácia")
plt.show()
plt.savefig("acc.png")


# Curvas de AUC 
plt.figure()
plt.plot(history.history["auc"], label="auc")
plt.plot(history.history["val_auc"], label="val_auc")
plt.legend()
plt.title("AUC durante o treino")
plt.xlabel("Época")
plt.ylabel("AUC")
plt.show()
plt.savefig("auc.png")

# Avaliação no conjunto de teste
# Calcula as probabilidades previstas 
y_prob = model.predict(x_test, batch_size=512).ravel()

# Converte probabilidades em classes 0/1 com limiar de 0.5
y_pred = (y_prob >= 0.5).astype(int)

# Calcula a métrica AUC no teste
print("Test AUC:", roc_auc_score(y_test, y_prob))

# Exibe relatório completo com precisão, recall e F1-score
print("Classification report:\n", classification_report(y_test, y_pred, digits=4))

# Matriz de confusão 
cm = confusion_matrix(y_test, y_pred)
cm
