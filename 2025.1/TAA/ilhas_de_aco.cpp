#include <bits/stdc++.h>
using namespace std;
int N;
vector<int> G[501];
vector<bool> visitados(501);

const int oo = 0x3f3f3f3f;
vector<int>dist(501, oo);
void bfs_dists(int u) {
    queue<int> fila;
    fila.push(u);
    dist[u] = 0;
    while (!fila.empty()) {
        u = fila.front();
        fila.pop();
        for (auto v: G[u]) {
            if (dist[v] == oo) {
                    fila.push(v);
                    dist[v] = dist[u] + 1;
                }
            }
    }
}

int dfs(int u, int origem){
    visitados[u] = true; 
    int qtd = 1;
    for(auto v:G[u]){
        if(!visitados[v]){
            qtd += dfs(v, u);
            
        }
    }
    return qtd;
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
    int maior = 0;
    for(int i =  1; i <=N ; i++){
        if(!visitados[i]){
            maior = max(dfs(i, -1), maior);
        }
    }

    cout << "O grupo mais numeroso tem " << maior << " aluno(s)" << endl;
}