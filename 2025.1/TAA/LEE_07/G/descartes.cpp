#include <bits/stdc++.h>
using namespace std;
static const int MOD = 1000000007;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> cartas(N);
    for(int i = 0; i < N; i++){
        cin >> cartas[i];
    }

    static int dp[1000][1000][2];
    for(int len = 1; len <= N; ++len){
        for(int l = 0; l + len - 1 < N; ++l){
            int r = l + len - 1;
            if(len == 1){
                dp[l][r][0] = 0; // esqueci que sempre é 2 em 2
                dp[l][r][1] = 0;
            } else {
                            
                dp[l][r][0] = max( // escolhe
                    cartas[l] + dp[l+1][r][1],
                    cartas[r] + dp[l][r-1][1]
                );
                            
                dp[l][r][1] = max(// descartas 
                    dp[l+1][r][0],
                    dp[l][r-1][0]
                );
            }
        }
    }

    cout << dp[0][N-1][0] << endl;
}
