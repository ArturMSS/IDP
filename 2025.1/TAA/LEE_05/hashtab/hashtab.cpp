#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int M, C;
    map <int, vector<int>> endereco;
    cin >> M >> C;
    while(C--){
        int V;
        cin >> V;
        int D = (V%M);
        endereco[D].push_back(V); 
    }

    for (int i = 0; i<M; i++){
        cout << i << " -> " ;
        for (int v : endereco[i]){
            cout << v << " -> ";
        }
        cout << "\\" << endl;
    }
}