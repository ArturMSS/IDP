#include <iostream>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    unsigned int a,b;
    cin >> a;
    b=0;
    for(int i =0; i <32; i++){
        b <<=1;
        b |= (a&1);
        a >>=1;
    }
    cout << b;
}