#include <bits/stdc++.h>
using namespace std;
vector<int> G[501];

const int oo = 0x3f3f3f3f;
vector<int>dist(501, oo);
void bfs_dists(int u) { 
    queue<int> fila;
    fila.push(u);
    dist[u] = 0; 
    while (!fila.empty()) {
        u = fila.front();
        fila.pop();
        for (auto v : G[u]) {
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
    int  M, N;
    cin >> M >> N;
    for (int i = 0; i < N; i++){
        int A, B;
        cin >> A >> B;
        G[A].push_back(B);
        G[B].push_back(A);
    }

    bfs_dists(1);
    int pp = 0;
    pp = dist[M];
    if (pp == oo){
        pp = -1;
    }

    cout << pp << endl;
}