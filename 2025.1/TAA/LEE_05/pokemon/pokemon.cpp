#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int P;
    cin >> P;
    priority_queue<pair<int, string>> pk;

    for (int i = 0; i < P; i++) {
        string name;
        int power;
        cin >> name >> power;
        pk.push({power, name});
    }
    
    while (pk.size() > 1) {
        auto first = pk.top(); pk.pop();
        auto second = pk.top(); pk.pop();

        int power1 = first.first;
        string name1 = first.second;
        int power2 = second.first;
        string name2 = second.second;

        if (power1 > power2) {
            cout << name1 << " (" << power1 << ") x (" << power2 << ") " << name2 << " : " << name1 << " venceu\n";
            power1 -= power2;
            pk.push({power1, name1});
        } else {
            cout << name1 << " (" << power1 << ") x (" << power2 << ") " << name2 << " : empate\n";
        }
    }

    if (pk.empty()) {
        cout << "nenhum vencedor\n";
    } else {
        auto winner = pk.top();
        cout << winner.second << " venceu com " << winner.first << "\n";
    }

    return 0;
}
