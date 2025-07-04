#include <bits/stdc++.h>
using namespace std;
int N = 200;
typedef tuple<int, int, int> tiii;
vector<bool> visitado(N + 1, false);
vector<pair<int, int>> G[201];

vector<pair<int, int>> prim(int origem) {
    priority_queue<tiii, vector<tiii>, greater<tiii>> pq;
    vector<pair<int, int>> mst;

    pq.push({0, origem, origem}); 
    while (!pq.empty()) {
        auto [p, u, v] = pq.top(); pq.pop();
        if (visitado[v]) {
            continue;
        }
        
        visitado[v] = true;
        mst.push_back({u, v});
        for (auto [r, w]: G[v]) {
            if (!visitado[r]) {
                pq.push({w, v, r}); 
            }
        }
    }
    return mst;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int  casos;
    cin >> casos;

    while(casos--){
        int T, M;
        cin >> T >> M;
        for (int i = 0; i < M; i++){
            int A, B, P;
            cin >> A >> B >> P;
            G[A].push_back({B, P});
            G[B].push_back({A,P});
        }
        vector<pair<int, int>> mst = prim(1);

        int tot = 0;
        for (auto [u, v] : mst) {
            for (auto [vizinho, peso] : G[u]) {
                if (vizinho == v) {
                    tot += peso;
                    break;
                }
            }
        }
        cout << tot << endl;
        for (int i = 0; i <= T; i++) {
            G[i].clear(); //limpar pra n explodir teste 2
        }
        visitado.assign(N + 1, false); 
    }
}
