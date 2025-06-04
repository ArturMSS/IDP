#include <iostream>
using namespace std;

string verificarPrimo(long long n){
    bool primo = true;
    if (n == 1){
        primo = false;
    } else {
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                primo = false;
                break;
            }
        }
    }

    if (!primo) {
        return "o numero " + to_string(n) + " nao eh primo";
    } else {
        return "o numero " + to_string(n) + " eh primo";
    }
}    
int main(){
    int num;
    cin >> num;

    long long primo;
    for (int i = 0; i < num; i++){
        cin >> primo;
        cout << verificarPrimo(primo) << endl;
    }
    return 0;
}