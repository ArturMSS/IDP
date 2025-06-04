#include <bits/stdc++.h>
using namespace std;
int matriz[100][100];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int V;
    cin >> V;
    for (int i = 0; i<V; i++){
        int E;
        cin >> E;
        for (int j = 0; j<E; j++){
            int A;
            cin >> A;
            matriz[i][A] = 1;
        }
    }
    for (int i = 0; i<V; i++){
        for(int j = 1; j<=V; j++){
            cout << matriz[i][j];
            if (j != V){
                cout << ' ';
            }
        }
        cout << endl;
    }
}