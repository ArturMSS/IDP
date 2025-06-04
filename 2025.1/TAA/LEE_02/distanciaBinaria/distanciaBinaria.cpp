#include <iostream>
using namespace std;
void calculo(long long a, long long b){
    cin >> a >> b;
    cout << __builtin_popcountll(a^b) << endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    int num;
    cin >> num;
    long long a;
    long long b;

    while (num--){
        calculo(a,b);
    }

}