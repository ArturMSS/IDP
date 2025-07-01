#include <bits/stdc++.h>
using namespace std;
    
int main(){
    ios::sync_with_stdio(false);
    int M, C;
    cin >> M >> C;
    vector<int> dol(C);
     
    for(int i = 0; i <C ; i++){
        cin >> dol[i];
    }
     
    sort(dol.begin(), dol.end(), greater<int>());
     
    vector <bool> simnao (M+1 , false);
    simnao[0] = true;
    for(int d : dol){
        if(d > M) continue;
        for(int m = M; m >= d; --m){
            if (simnao[m - d]){
                simnao[m] = true;
            }
        }
        if(simnao[M]) break;
    }
   
    if(simnao[M]){
        cout << "SIM" << endl;
    } else{
        cout << "NAO" << endl;
    }
}