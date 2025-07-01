#include <bits/stdc++.h>
using namespace std;
static const int MOD = 1000000007;
    
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long L, C;
    cin >> L >> C;
    vector<string> tabul(L);
    for(int i = 0 ; i<L ; i++){
        cin >> tabul[i];
    }
    
    
    vector<vector<int>> cam(L, vector<int>(C, 0));
    cam[0][0] = 1;
    for(int i = 0; i < L; i++){
        for(int j = 0; j< C; j++){
            if (tabul[i][j] == '#'){
                cam[i][j] = 0;
                continue;
            }
            if(i>0){
                cam[i][j] = (cam[i][j] + cam[i-1][j]) % MOD;
            }
            if(j>0){
                cam[i][j] = (cam[i][j] + cam[i][j-1]) % MOD;                
            }
        }
    }
    
    int camFin = cam[L-1][C-1];
    if(camFin == 0){
        cout << -1 << endl;
    } else {
        cout << camFin << endl;
    }
    return 0;
}