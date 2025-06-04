#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> A(N);
    for (int &x : A) cin >> x;

    unordered_map<int, vector<pair<int, int>>> soma_pares;

    unordered_map<int, int> total_quadruplas;

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            soma_pares[A[i] + A[j]].emplace_back(i, j);
        }
    }

    for (auto &[s1, pares1] : soma_pares) {
        for (auto &[s2, pares2] : soma_pares) {
            if (s2 < s1) continue; 

            for (auto &[i1, j1] : pares1) {
                for (auto &[i2, j2] : pares2) {
                    
                    set<int> idxs = {i1, j1, i2, j2};
                    if (idxs.size() < 4) continue;

                    int soma_total = s1 + s2;
                    total_quadruplas[soma_total]++;
                }
            }
        }
    }

   
    int Q;
    cin >> Q;
    while (Q--) {
        int q;
        cin >> q;
        cout << total_quadruplas[q] << '\n';
    }

    return 0;
}
