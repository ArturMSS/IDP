#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int alunos;
    cin >> alunos;

    set<string> itens; 
    string item;

    while (alunos--) {
        int qtd;
        cin >> qtd;
        while (qtd--) {
            cin >> item;

            auto [it, inserido] = itens.insert(item);
            if (inserido) {
                cout << "adicionando " << item << endl;
            } else {
                cout << item << " ja tem" << endl;
            }
        }
    }

    cout << "Itens do churrasco:" << endl;
    for (const string& v : itens) {
        cout << v << endl;
    }
}
