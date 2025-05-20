#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T, L;
    cin >> T;

    while (T--){
        cin >> L;
        set<string> aulas;
        string matricula, disciplina;
        int erros = 0;
        while (L--){
            cin >> matricula >> disciplina;
            string aula = matricula + " " + disciplina;
            auto [it, inserido] = aulas.insert(aula);
            if (!inserido){
                erros++;
            }
        }
        if (erros == 0){
            cout << "Arquivo OK" << endl;
        } else{
            cout << "Corrompido com " << erros <<" erro(s)"<< endl;
        }
    }
}