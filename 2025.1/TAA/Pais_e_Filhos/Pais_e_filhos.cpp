#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, C;
    cin >> N;

    vector<int> arvore(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> arvore[i];
    }
    cin >> C;
    while (C--) {
        int indice;
        cin >> indice;

        if (indice < 1 || indice > N || N <=1) {
            cout << "NULL"; 
            break;
        } else if (indice == 1) {
            cout << "RAIZ"; 
        } else {
            int pai = indice / 2; 
            cout << arvore[pai]; 
        }
        cout << " - ";
        int esquerda = 2 * indice;
        int direita = 2 * indice +1;

        if (esquerda <= N && arvore[esquerda] != -1)
            cout << arvore[esquerda] << " ";
        else
            cout << "NULL ";
        if (direita <= N && arvore[direita] != -1)
            cout << arvore[direita] << endl;
        else
            cout << "NULL" << endl;
    
    }

    return 0;
}
