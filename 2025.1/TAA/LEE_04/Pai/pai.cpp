#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, C;
    cin >> N >> C;

    vector<int> arvore(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> arvore[i];
    }

    while (C--) {
        int indice;
        cin >> indice;

        if (indice < 1 || indice > N || N <=1) {
            cout << "NULL" << endl; 
        } else if (indice == 1) {
            cout << "RAIZ" << endl; 
        } else {
            int pai = indice / 2; 
            cout << arvore[pai] << endl; 
        }
    }
    
    return 0;
}
