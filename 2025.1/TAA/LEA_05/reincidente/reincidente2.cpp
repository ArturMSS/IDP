#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    map<string, int> detentos;

    while (true) {
        string nome;
        int codigo;
        cin >> nome >> codigo;

        if (nome == "fim" && codigo == 0) break;
        int &crimes = detentos[nome]; 

        if (crimes == 0) {
            cout << nome << " eh reu primario" << endl;
        } else {
            cout << nome << " eh reincidente com " << (crimes) << " crime(s)" << endl;
        }
        crimes++; 
    }

    return 0;
}
