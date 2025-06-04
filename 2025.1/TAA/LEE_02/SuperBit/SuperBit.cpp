#include <iostream>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    long long bit, qtd, nums;
    cin >> qtd >> bit;
    while (qtd--){
        cin >> nums;
        cout << (nums | (1 << bit)) << endl;
    }
}