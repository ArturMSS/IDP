#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> G;
vector<vector<int>> J;
const int oo = 0x3f3f3f3f;
vector<int>dist;
vector<bool>cam;

void bfs_dists(vector<vector<int>> A,int u) { 
    queue<int> fila;
    dist.assign(dist.size(), oo);
    fila.push(u);
    dist[u] = 0; 
    while (!fila.empty()) {
        u = fila.front();
        fila.pop();
        for (auto v : A[u]) {
            if (dist[v] == oo) {
                fila.push(v);
                dist[v] = dist[u] + 1;
            }
        }
    }
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
 
    int N, M, C;
    cin >> N >> M >> C;
 
    G.assign(N + 1, vector<int>());
    J.assign(N + 1, vector<int>()); 
    cam.assign(N + 1, false);
    dist.assign(N + 1, oo);
 
    for (int i = 0; i < C; i++) {
        int P;
        cin >> P;
        cam[P] = true;
    }
 
    for (int i = 0; i < M; i++) {
        int A, B;
        cin >> A >> B;
        J[A].push_back(B);
        J[B].push_back(A);
        if (!cam[A] && !cam[B]) {
            G[A].push_back(B);
            G[B].push_back(A);
        }
    }
 
    int patio, saida, chave;
    cin >> patio >> saida >> chave;
 
    bfs_dists(G, patio);
    int pp = dist[chave];
    int pp1 = pp * 2;
    dist.assign(N + 1, oo);
    bfs_dists(J, patio);
    int pp2 = dist[saida];
 
    if (pp == oo || pp2 == oo) {
        cout << "impossivel fugir" << endl;
    } else {
        cout << pp1 << " " << pp2 << endl; 
    }
}