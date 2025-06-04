#include <iostream>
using namespace std;
long long nextCollatz(long long n){
    if (n % 2 == 0){
        return n/2; // se n for par
    } else{
        return (n*3) +1 ; // se n for impar
    }
}

void generateCollatzSequence(long long n){
    cout << n;
    while (n!=1){
        cout << " ";
        n = nextCollatz(n);
        cout << n;
    }
}

int main (){
    long long n;
    cin >> n;
    generateCollatzSequence(n);
}