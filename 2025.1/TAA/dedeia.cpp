#include <bits/stdc++.h>
using namespace std;

int pd[1005][1005];
int cartas[1005];

int solver(int l, int r) {
    if (l > r) {
        return 0;
    }
    if (l == r){
        return cartas[l];  //uma carta restante
    }
    if (pd[l][r] != -1) {
        return pd[l][r];
    }

    int res = 0;
    // pontua esq descarta prox da esq
    res = max(res, cartas[l] + solver(l + 2, r));

    //pontua esq descarta da dir
    res = max(res, cartas[l] + solver(l + 1, r - 1));

    //pontua direita e descarta da esq
    res = max(res, cartas[r] + solver(l + 1, r - 1));

    //pontua dir descarta prox da dir
    res = max(res, cartas[r] + solver(l, r - 2));

    return pd[l][r] = res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin >> N;
    for (int i = 0; i < N; i++) cin >> cartas[i];

    memset(pd, -1, sizeof(pd));
    cout << solver(0, N - 1) << "\n";

    return 0;
}