#include <iostream>
using namespace std;

long long calcularMC(long long a){
    if(a > 100){
        return a - 10;
    }
    else{
        return calcularMC(calcularMC(a + 11));
    }
}

int main (){
    long long a, b;
    cin >> a;
    for (int i = 0; i < a; i++){
        cin >> b;
        cout << calcularMC(b) << endl;
    }
}
