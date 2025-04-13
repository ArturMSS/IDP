#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    long long atual, dias, previsao, media, novo, soma;
    soma = 0;
    cin >> atual >> dias;
    queue<int> ultimos30;
    for (int i = 0; i<30; i++){
        cin >> novo;
        ultimos30.push(novo);
        soma += novo;
    }
    previsao = atual;
    for (int i=0; i< dias ;i++){
        media = (soma+29)/30;
        previsao += media;
        soma -= ultimos30.front();
        soma += media;
        ultimos30.pop();
        ultimos30.push(media);
    }
    cout << previsao << endl;
    return 0;

}