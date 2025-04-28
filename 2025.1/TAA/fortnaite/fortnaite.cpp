#include <bits/stdc++.h>
using namespace std;

struct jogador{
    string nick;
    string tempo;
    int tempoSeg;
};

bool compararTempo(const jogador& a, const jogador& b){
    if(a.tempoSeg != b.tempoSeg){
        if(a.tempoSeg > b.tempoSeg){
            return true;
        }else{
            return false;
        }
    } else{
        if (a.nick > b.nick){
            return true;
        }else{
            return false;
        }
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    int qtd;
    cin >> qtd;
    vector <jogador> jogadores(qtd) ;
    for (int i = 0; i <qtd; i++){
        string nick, tempo;
        cin >> nick >> tempo;

        int min = stoi(tempo.substr(0, 2));
        int seg = stoi(tempo.substr(3,2));
        int tempoSeg = min * 60 + seg;

        jogadores[i] = {nick, tempo, tempoSeg};
    }

    sort(jogadores.begin(), jogadores.end(), compararTempo);

    for (int i = 0; i < qtd; ++i) {
        cout << i + 1 << ". " << jogadores[i].tempo << " - " << jogadores[i].nick << '\n';
    }
}