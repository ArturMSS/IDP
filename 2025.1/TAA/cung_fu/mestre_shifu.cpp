#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    while(N--){
        string palavras;
        int cont = 0;
        cin >> palavras;
        unordered_set<char> letras;
        for (char c : palavras){
            if(letras.count(c)){
                cont++;
            }
            else{
                letras.insert(c);
            }
        }
        if(cont>0){
            cout << "WEAKORD" << endl;
        } else{
            cout << "STRONGRAMA" << endl;
        }

    }

}