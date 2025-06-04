#include <bits/stdc++.h>
using namespace std;

bool ehCardial(string s){
    return s == "N" || s == "S" || s == "L" || s == "O";
}

int main(){
    ios_base::sync_with_stdio(false);
    queue <string> norte, sul, leste, oeste;
    string input;
    char direcao;
    cin >> direcao;
    while (true){
        cin >> input;
        if (input == "0"){
            break;
        }
        if (input.size() == 1 && ehCardial(input)){
            direcao = input[0];
        } else {
            switch(direcao){
                case 'N' : norte.push(input); break;
                case 'S' : sul.push(input); break;
                case 'L' : leste.push(input); break;
                case 'O' : oeste.push(input); break;
            }
        }
    }
    //ok todas as direcoes feitas agora fazer a ordem resultante
    vector <string> ordem;
    while (!norte.empty() || !sul.empty() || !oeste.empty() || !leste.empty()){
        if (!norte.empty()){
            ordem.push_back(norte.front());
            norte.pop();
        }
        if (!sul.empty()){
            ordem.push_back(sul.front());
            sul.pop();
        }
        if (!leste.empty()){
            ordem.push_back(leste.front());
            leste.pop();
        }
        if (!oeste.empty()){
            ordem.push_back(oeste.front());
            oeste.pop();
        }
    }
    for (int i = 0; i < ordem.size(); i++) {
        cout << ordem[i];
        if (i < ordem.size() - 1) cout << " ";
    }
    
}