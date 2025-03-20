#include <iostream>
using namespace std;

bool verificarPrimo(long long n){
    if (n <= 1) return false;
    if (n == 2) return true;  
    if (n % 2 == 0) return false; 

    for (long long i = 3; i * i <= n; i += 2) { 
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}  

string verificarPrimoGemeo(long long n) {
    if (verificarPrimo(n) && (verificarPrimo(n - 2) || verificarPrimo(n + 2))) {
        return "O numero " + to_string(n) + " eh um primo gemeo";
    } else {
        return "O numero " + to_string(n) + " nao eh um primo gemeo";
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    int num;
    cin >> num;

    long long primo;
    for (int i = 0; i < num; i++){
        cin >> primo;
        cout << verificarPrimoGemeo(primo) << endl;
    }
    return 0;
}