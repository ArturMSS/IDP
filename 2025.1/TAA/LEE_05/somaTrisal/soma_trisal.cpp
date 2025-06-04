#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    unsigned int N, alvo;
    cin >> N >> alvo;
    vector<int> valores(N);
    for (int i = 0; i < N; i++) cin >> valores[i];
    sort(valores.begin(), valores.end());

    for (int i = 0; i < N -2; i++){
        int left = i+1; //segundo elemento(pois o valores[i] começa no primeiro)
        int right = N-1; //ultimo elemento
        while (left<right){
            long long soma = valores[i] + valores[left] + valores[right];
            if (soma == alvo) {
                cout << valores[i] << " " << valores[left] << " " << valores[right] ;
                return 0;
            } else if (soma < alvo) {
                left++;
            } else {
                right--;
            }
        }

    }
    cout << "Nao existe" << endl;
    return 0;
}

