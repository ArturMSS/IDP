#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        string cartas1, cartas2;
        cin >> cartas1 >> cartas2;

        unordered_set<char> set1(cartas1.begin(), cartas1.end());
        set<char> intersecao;

        for (char c : cartas2) {
            if (set1.count(c)) {
                intersecao.insert(c);  
            }
        }

        if (intersecao.empty()) {
            cout << "Baralhos prontos para o duelo";
            cout << endl;
        } else {
            for (char c : intersecao) {
                cout << c ;
            }
            cout << endl;
        }

        set1.clear();
        intersecao.clear();
    }
    
}