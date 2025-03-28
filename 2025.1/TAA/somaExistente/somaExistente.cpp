#include <bits/stdc++.h>
using namespace std;
void calcularSoma(){
    int qtd;
    cin >> qtd;
    vector<int> num(qtd);
    for (int i = 0; i < qtd; i++) {
        cin >> num[i];
    }
    int soma;
    cin >> soma;
    int left =0;
    int right = qtd -1;
    int resultado;
    while (left < right) {
        resultado = num[left] + num[right];
        if (resultado == soma) {
            cout << "SIM" << endl;
            return;
        }
        if (resultado < soma)
            left++;
        else
            right--;
    }
    
    cout << "NAO" << endl;    

}
int main(){
    ios_base::sync_with_stdio(false);
    int testes;

    cin >> testes;
    while (testes--){
        calcularSoma();
    }        
}