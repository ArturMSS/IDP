#include <iostream>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    long long N,B,V,Troca, Res;
    cin >> N >> B ;
    Troca = 1<<(B);

    while (N--){
        cin >> V;
        Res = V^(V&Troca);
        cout << (Res) <<endl;
    }
}