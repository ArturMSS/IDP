#include <bits/stdc++.h>
using namespace std;

struct Digimon {
    string nome;
    int fome;
    int tempo_chegada;

    Digimon(string n, int h, int t) : nome(n), fome(h), tempo_chegada(t) {}

    bool operator<(const Digimon& outro) const {
        if (fome == outro.fome)
            return tempo_chegada > outro.tempo_chegada; // menor tempo_chegada tem prioridade
        return fome < outro.fome; // maior fome tem prioridade
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int A; cin >> A;
    priority_queue<Digimon> pq; // priority queue
    unordered_map<string, pair<int,int>> dados; //para armazenar os dados que serão usados
    vector<string> servidos;

    int tempo_chegada = 0;
    for(int i = 0; i< A; i++){
        string acao; 
        cin >> acao;
        if (acao == "CHEGA"){
            string nome; 
            int fome;
            cin >> nome >> fome;
            dados[nome] = {fome, tempo_chegada++};
            pq.push(Digimon(nome, dados[nome].first, dados[nome].second ));
        } else if ( acao == "FOME"){
            string nome;
            int incremento;
            cin >> nome >> incremento;
            dados[nome].first += incremento;
            pq.push(Digimon(nome, dados[nome].first, dados[nome].second));
        } else if (acao == "SAI"){
            string nome; 
            cin >> nome;
            dados.erase(nome);
        } else if (acao == "SERVE"){
            while(!pq.empty()){
                auto d = pq.top(); pq.pop();
                if(dados.count(d.nome)){
                    servidos.push_back(d.nome);
                    dados.erase(d.nome);
                    break;
                }
            }
        }
    }

    for(string nome : servidos){
        cout << nome << endl;
    }
    return 0;
}