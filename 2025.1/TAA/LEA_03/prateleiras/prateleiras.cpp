#include <bits/stdc++.h>
using namespace std;

struct prateleiras {
    string nome;
    int tamanho;
};

bool compararStrings(const prateleiras &a, const prateleiras &b) {
    if (a.tamanho != b.tamanho) {
        return a.tamanho < b.tamanho;
    } else {
       return a.nome < b.nome;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    vector<prateleiras> livros;
    string nome;

    for (int i = 0; i < N; i++) {
        cin >> nome;
        livros.push_back({nome, (int)nome.size()});
    }

    sort(livros.begin(), livros.end(), compararStrings);

    for (int i = 0; i < N; i++) {
        cout << livros[i].nome << '\n';
    }
}
