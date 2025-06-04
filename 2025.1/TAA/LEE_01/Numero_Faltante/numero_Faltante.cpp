#include <iostream>
using namespace std;
int main(){
    int n;
    cin>> n;

    long long soma_esperada = (long long) n*(n+1)/2; // formula de soma de sequencia
    long long soma_real = 0;
    //lendo todos os numeros inseridos
    for (int i = 0; i < n - 1; i++) {
        int num;
        cin >> num;
        soma_real += num;
    }

    // O número faltante é a diferença entre a soma esperada e a soma real
    cout << soma_esperada - soma_real << endl;    
    return 0;
}