#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    int cartaAtual = 0;
    queue<int> cartas;
    cin >> N;
    for (int i = N; i>0;i--){
        cartas.push(i);
    }
    cout << "Descarte: ";
    while(cartas.size() > 1){
        cout << cartas.front();
        cartas.pop();
        if(cartas.size() >1) cout << ", ";
        cartas.push(cartas.front());
        cartas.pop();
    }
    cout << endl << "Ultima carta: " << cartas.front();
}