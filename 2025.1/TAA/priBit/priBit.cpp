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

int main(){
    ios_base::sync_with_stdio(false);
    int qtd;
    long long num, popcount;
    cin >> qtd;

    while (qtd --){
        cin >> num;
        popcount = __builtin_popcountll(num);
        if (verificarPrimo(popcount)){
            cout << num << " eh um pribit" << endl;
        } else {
            cout << num << " nao eh um pribit" << endl;
        }
    }
}
