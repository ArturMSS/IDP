#include <bits/stdc++.h>
using namespace std;
int matriz[100][100];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int V, C;
    cin >> V >> C;
    for (int i = 0; i<C; i++){
        int A, B;
        cin >> A >> B;
        matriz[A][B] = 1;
        matriz[B][A] = 1;
    }
    for (int i = 1; i<=V; i++){
        for(int j = 1; j<=V; j++){
            cout << matriz[i][j];
            if (j != V){
                cout << ' ';
            }
        }
        cout << endl;
    }
}