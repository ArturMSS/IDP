#include <iostream>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    int a;
    while(true){
        cin>>a;
        int esquecido=0;
        long long b[a];
        if (a==-1){
            break;
        }
        for(int i =0; i < a ; i++){
            cin >> b[i];
            esquecido ^= b[i];
        }
        cout << esquecido << endl;
    }
    
}