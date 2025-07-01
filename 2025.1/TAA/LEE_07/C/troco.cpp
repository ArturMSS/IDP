#include <bits/stdc++.h>
using namespace std;

static const int oo = 0x3f3f3f3f;
int main(){
    ios::sync_with_stdio(false);
    int M, C;
    cin >> M >> C;
    vector<int> dol(C);

    for(int i = 0; i <C ; i++){
        cin >> dol[i];
    }

    sort(dol.begin(), dol.end(), greater<int>());

    vector <int> qtd (M+1 , oo);
    qtd[0] = 0;
    for(int d : dol){
        if(d > M) continue;
        for(int m = d; m <= M; m++){
            if (qtd[m - d] != oo){
                qtd[m] = min(qtd[m], qtd[m - d] + 1);
            }
        }
    }
    
    if(qtd[M] != oo){
        cout << qtd[M] << endl;
    } else{
        cout << "impossivel" << endl;
    }
}