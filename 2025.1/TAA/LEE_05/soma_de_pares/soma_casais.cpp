#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    unsigned int N, alvo;
    cin >> N >> alvo;
    vector<int> valores(N);
    for (int i = 0; i < N; i++) cin >> valores[i];

    unordered_map<long long, int> vistos; // < valor , indice >
    for (int i = 0; i<N; i++){
        long long complemento = alvo - valores[i]; // cria o complemento de valor[i] cujo resultado é o alvo
        if (vistos.count(complemento)){ //checa se esse complemento existe no mapa criado(a primeira passagem nunca vai retornar verdadeiro)
            cout << complemento << " " << valores[i]; 
            return 0;
        }
        vistos[valores[i]] = i; // adiciona o valor presente em valores[i] ao mapa de elementos ja vistos
    }
    cout << "Nao existe" << endl;
    return 0;
}