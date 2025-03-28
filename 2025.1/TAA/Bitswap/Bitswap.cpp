#include <iostream>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    unsigned long long qtd, bit1, bit2, num, val1, val2;
    cin >> qtd;
    while (qtd --){
        cin >> num >> bit1 >> bit2;
        val1 = 1ULL << bit1;
        val2 = 1ULL << bit2;
        if(((num & val1) != 0) && ((num & val2)==0)){
            cout << (num + val2 - val1)<< endl;
        }else if (((num & val1) == 0) && ((num & val2)!=0)){
            cout << (num + val1 - val2)<< endl;
        } else cout << num << endl;
    }
}