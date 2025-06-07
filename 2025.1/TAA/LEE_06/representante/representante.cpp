#include <bits/stdc++.h>
using namespace std;
int N;
vector<int> G[601];
vector<bool> visitados(601);

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
    cin >> N >> M; // N é global

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