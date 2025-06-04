#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int P, R;
    cin >> P >> R;
    multiset<int> cliente;
    for(int i =0; i<P ; i++){
        int cadeira;
        cin >> cadeira;
        cliente.insert(cadeira);
        if(cliente.size() < R){
            cout << *cliente.rbegin() << endl;
        }else {
            cout << *next(cliente.begin(), R - 1) << endl;
        }
    }
}