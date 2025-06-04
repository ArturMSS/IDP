#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T;
    cin >> T;
    while (T--){
        string palavra1, palavra2;
        cin >> palavra1 >> palavra2;
        // só dar sort e comparar, sort deixa string automaticamente em ordem alfabetica
        sort(palavra1.begin(), palavra1.end());
        sort(palavra2.begin(), palavra2.end());
        if(palavra1 == palavra2){
            cout << "ANAGRAMAS" << endl;
        }else cout << "DIFERENTES" << endl;
    }
}