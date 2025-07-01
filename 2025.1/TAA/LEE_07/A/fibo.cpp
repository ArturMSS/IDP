#include <bits/stdc++.h>
using namespace std;

unsigned long long MOD = 1000000007;
unsigned long long memo[10001];

unsigned long long fibonacci(unsigned int N){
    memo[0] = 0;
    memo[1] = 1;
    for(unsigned int i = 2; i <= N; ++i)
        memo[i] = (memo[i - 1] + memo[i - 2]) % MOD;
    return memo[N];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    vector<unsigned int> fibos(T);
    unsigned int mx = 0;
    for(int i = 0; i < T; ++i){
        cin >> fibos[i];
        if(fibos[i] > mx) mx = fibos[i];
    }
    if(mx > 10000) mx = 10000;
    fibonacci(mx);
    for(auto a : fibos)
        cout << memo[a] << "\n";
    return 0;
}
