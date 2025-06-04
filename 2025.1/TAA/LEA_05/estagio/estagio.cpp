#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    set<char> palavra;
    string embaralhada;
    cin >> embaralhada;
    for (char c : embaralhada){
        palavra.insert(c);
    }
    for (char c: palavra){
        cout << c;
    }
}