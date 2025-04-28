#include <bits/stdc++.h>
using namespace std;

struct coordenadas {
    long long X, Y;
    coordenadas() : X(-1), Y(-1) {} // construtor padrão (necessário para std::map)
    coordenadas(long long x, long long y) : X(x), Y(y) {}
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long N, Q, M, val;
    cin >> N >> M >> Q;

    unordered_map<long long, coordenadas> posicoes;
    posicoes.reserve(N*M);

    for (long long i = 0; i < N; i++) {
        for (long long j = 0; j < M; j++) {
            cin >> val;
            if (posicoes.find(val) == posicoes.end()) {
                posicoes[val] = coordenadas(i, j);
            }
        }
    }

    for (int i = 0; i < Q; i++) {
        cin >> val;
        if (posicoes.find(val) != posicoes.end()) {
            cout << posicoes[val].X << " " << posicoes[val].Y << "\n";
        } else {
            cout << "-1 -1\n";
        }
    }

    return 0;
}
