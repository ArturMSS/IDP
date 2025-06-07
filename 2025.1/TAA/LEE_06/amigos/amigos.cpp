#include <bits/stdc++.h>
using namespace std;
int N;
vector<int> G[801];
vector<bool> visitados(801);

void dfs(int u, int origem){
    visitados[u] = true;

    for(auto v : G[u]){
        if(!visitados[v]){
            dfs(v, u);
        }
    }
}

int componentes_conectados(){
    int quantidade = 0;
    for (int u = 1; u <= N; u++) {
        if (!visitados[u]) {
            quantidade++;
            dfs(u, -1);
        }
    }
    return quantidade;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int  M;
    cin >> N >> M;
    for (int i = 0; i<M; i++){
        int A, B;
        cin >> A >> B;
        G[A].push_back(B);
        G[B].push_back(A);
    }
    int total = componentes_conectados();

    if (total == 1) {
        cout << "Todo mundo eh amigo de todo mundo" << endl;
    } else {
        cout << "Varios grupos de amigos" << endl;
    }
}