#include <bits/stdc++.h>
using namespace std;

struct Detento {
    string nome;
    int codigo;
    int crimes = 0;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    map<string, Detento> detentos;

    while (true) {
        string nome;
        int codigo;
        cin >> nome >> codigo;

        if (nome == "fim" && codigo == 0) break;

        if (detentos.count(nome)) {
            cout << nome << " eh reincidente com " << detentos[nome].crimes << " crime(s)" << endl;
            detentos[nome].crimes++;
        } else {
            detentos[nome] = {nome, codigo, 1};
            cout << nome << " eh reu primario" << endl;
        }
    }

    return 0;
}
