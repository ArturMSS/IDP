#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    priority_queue<pair<int, string>> detentos;
    cin >> N;
    for(int i =0; i<N;i++){
        string nome;
        int tempo;
        cin >> nome >> tempo;
        detentos.push({tempo,nome});
    }
    while(!detentos.empty()){
        auto detento = detentos.top();
        cout << detento.second << " " <<detento.first << endl;
        detentos.pop();
        if(detento.first>1){
            detento.first = detento.first/2;
            detentos.push(detento);
        }

    }
}