#include <iostream>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    int T;
    long long a, b , c, d;
    cin >> T;

    while (T--){
        cin >> a >> b;
        cin >> c;
        d = c - (a|b);
        if ( (a|b|d) == c){
            cout << d << endl;
        } else {
            cout << "-1" << endl;
        }
    }
}