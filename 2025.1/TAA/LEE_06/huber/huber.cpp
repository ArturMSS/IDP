#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> G[801];
const int oo = 0x3f3f3f3f;
int dist[801];

void dijkstra(int origem){
    memset(dist, oo, sizeof(dist));
    dist[origem] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, origem});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) {
            continue;
        }
        for (auto [v, w]: G[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({ dist[v], v });
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int  N, M;
    cin >> N >> M;
    for (int i = 0; i < M; i++){
        int A, B, P;
        cin >> A >> B >> P;
        G[A].push_back({B, P});
        G[B].push_back({A,P});
    }

    dijkstra(1);
    int pp = 0;
    pp = dist[N];
    if(pp != oo){
        cout << "Distancia para chegar em casa: " << pp << endl;
    } else {
        cout << "Preso no IDP" << endl;
    }
}