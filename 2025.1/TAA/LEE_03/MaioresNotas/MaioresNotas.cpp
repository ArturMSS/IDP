#include <bits/stdc++.h>
using namespace std;


int main(){

    ios_base::sync_with_stdio(false);
    long long a, b, corte;
    cin >> a >> b ;
    vector <int> notas(a);
    for(int i = 0; i < a; i++){
        cin >> notas[i];
    }
    while (b--){
        cin >> corte;
        auto maior = upper_bound(notas.begin(), notas.end(), corte);
        int qtd_maiores = notas.end() - maior;
        cout << qtd_maiores << " notas maiores que " << corte << endl;
    }
    return 0;
}

