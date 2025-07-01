#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> C(N);
    for(int i = 0; i < N; i++)
        cin >> C[i];

    // dp[l][r][0=pick,1=discard]
    static int dp[1000][1000][2];

    for(int len = 1; len <= N; ++len){
        for(int l = 0; l + len - 1 < N; ++l){
            int r = l + len - 1;
            if(len == 1){
                dp[l][r][0] = C[l];
                dp[l][r][1] = 0;
            } else {
                // pick
                dp[l][r][0] = max(
                    C[l] + dp[l+1][r][1],
                    C[r] + dp[l][r-1][1]
                );
                // discard
                dp[l][r][1] = max(
                    dp[l+1][r][0],
                    dp[l][r-1][0]
                );
            }
        }
    }

    cout << dp[0][N-1][0] << "\n";
    return 0;
}