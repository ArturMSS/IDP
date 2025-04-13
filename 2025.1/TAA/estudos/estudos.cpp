#include <bits/stdc++.h>
using namespace std;

bool ehPossivel(const vector<long long>& a, long long horas, long long meio) {
    long long sessoes = 0;
    for (long long i : a) {
        sessoes += (i + meio - 1) / meio;
        if (sessoes > horas) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long cap, horas;
    cin >> cap >> horas;

    vector<long long> exes(cap);
    long long maxE = 0;
    for (int i = 0; i < cap; i++) {
        cin >> exes[i];
        maxE = max(maxE, exes[i]);
    }

    long long res = 1;
    long long comeco = 1, fim = maxE;
    while (comeco <= fim) {
        long long meio = (comeco + fim) / 2;
        if (!ehPossivel(exes, horas, meio)) {
            comeco = meio + 1;
            res = comeco;
        }else {
            fim = meio -1;
        }
    }

    cout << res;
    return 0;
}
