#include <iostream>
using namespace std;


int somarDigitos(string N){
    // Código para soma dos dígitos
    int soma = 0;
    for (char c : N) {
        soma += (c - '0');  // Soma os dígitos
    }
    return soma;
}

int main() {
    int D;
    
    while (true){
        cin >> D;  // quantidade de digitos
        if (D == -1) break;  // Finaliza a entrada quando D for -1
        
        string N;
        cin >> N;  // numero que vai ser checado

        int soma = somarDigitos(N);
        if (soma%3 ==0){
            cout << soma << " " <<"sim"<< endl;
        } else {
            cout << soma << " " <<"nao"<< endl;
        }
    }
    return 0;
}