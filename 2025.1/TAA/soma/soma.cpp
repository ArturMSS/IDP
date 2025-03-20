#include <iostream>
using namespace std;

int main (){
    int a, b, c, soma;
    cin >> a;
    for (int i =0; i<a; i++){
        cin >> b >> c;
        soma = b + c;
        cout << soma << endl;
    }
    return 0;
}