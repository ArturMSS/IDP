#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int qtd_F , qtd_P;
    cin >> qtd_F >> qtd_P;
    map<string, set<string>> aluno;
    while (qtd_F--){
        string nome, op1, op2, op3;
        cin >> nome >> op1 >> op2 >> op3;
        aluno[nome] = {op1, op2, op3};
    }
    while (qtd_P--){
        string nome, brinde;
        cin >> nome >> brinde;
        auto it = aluno.find(nome);
        if (it == aluno.end()) {
            cout << nome << " queria ganhar qualquer coisa e ganhou " << brinde << "!" << endl;
        } else {
            if (it->second.count(brinde)) {
                cout << nome << " conseguiu ganhar " << brinde << "!" << endl;
            } else {
                cout << nome << " infelizmente ganhou " << brinde << "..." << endl;
            }
        }
    }
}