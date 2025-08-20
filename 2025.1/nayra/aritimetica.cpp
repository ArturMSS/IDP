#include <bits/stdc++.h>
using namespace std;

bool ehprimo(int n){
    bool primo = true;
    if (n == 1){
        return false;
    } else {
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                return false;
            }
        }
    }
    return true;
}

int mod_exp(int base, int expo, int mod) {
    int result = 1;
    base %= mod; // reduz a base se for maior que mod
    while (expo > 0) {
        if (expo & 1) // se o bit atual for 1
            result = (result * base) % mod;
        base = (base * base) % mod;
        expo >>= 1; // divide expoente por 2
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int N1, N2, N3;
    cin >> N1 >> N2 >> N3;
    if(N1 > 65535 || N2 > 65535 || N3 > 65535 || N1 < 1 || N2 < 1 || N3 < 1) {
        cout << "Entradas invalidas" << endl;
        return 0;
    }
    if (!ehprimo(N3)){
        cout << "O modulo nao eh primo." << endl;
        return 0;
    }

    cout << "A exponencial modular " << N1 << " elevado a " << N2 << "(mod "<< N3 << ") eh " << mod_exp(N1, N2, N3);
    
    return 0;
}