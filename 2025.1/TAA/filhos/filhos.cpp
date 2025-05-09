#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N, C;
    cin >> N >> C;

    vector<int> arvore(N+1);
    for (int i = 1; i <= N; i++) {
        cin >> arvore[i];
    }

    while (C--){
        int indice;
        cin >> indice;

        if (indice <1 || indice > N || arvore[indice] == -1 || N <=1) {
            cout << "NULL" << endl;
            break;
        }

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