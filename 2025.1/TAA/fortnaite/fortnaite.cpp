#include <bits/stdc++.h>
using namespace std;

struct jogador{
    string nick;
    string tempo;
    int tempoSeg;
    jogador(string n, string t){
        nick = n;
        tempo = t;
        int min = (t[0] - '0') * 10 + (t[1] - '0');
        int seg = (t[3] - '0') * 10 + (t[4] - '0');
        tempoSeg = min * 60 + seg;        
    }
};
bool compararTempo(const jogador &a, const jogador &b) {
    return a.tempo > b.tempo;
}

int main(){
    ios_base::sync_with_stdio(false);
    int qtd;
    cin >> qtd;
    vector <jogador> jogadores ;
    vector <int> tempoINT;
    for (int i = 0; i <qtd; i++){
        string nick, tempo;
        cin >> nick >> tempo;
        jogadores.emplace_back(nick, tempo);
    }
    sort(jogadores.begin(), jogadores.end(), compararTempo);

    for (int i = 0; i < qtd; ++i) {
        cout << i + 1 << ". " << jogadores[i].tempo << " - " << jogadores[i].nick << '\n';
    }
}