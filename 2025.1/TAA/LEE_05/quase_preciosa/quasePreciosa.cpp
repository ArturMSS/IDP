#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--){
    string encontradas, aceitasStr;
    cin >> encontradas >> aceitasStr;
    unordered_set<char> aceitas(aceitasStr.begin(), aceitasStr.end()); 

    int pedras = 0;
    for (char a : encontradas) {
        if (aceitas.count(a)) { 
            pedras++;
        }
    }
    cout << "Contem " << pedras << " pedras negociaveis"<< endl;
    }
}