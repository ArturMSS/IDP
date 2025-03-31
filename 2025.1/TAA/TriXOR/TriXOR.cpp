#include <iostream>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    int T;
    long long A, B , C, Y;
    cin >> T;

    while (T--){
        cin >> A >> B;
        cin >> Y;
        C= A^B^Y;
        if ( (A^B^C) == Y){
            cout << C << endl;
        } else {
            cout << "-1" << endl;
        }
    }
}