#include <bits/stdc++.h>
using namespace std;
long long mdc (long long num1, long long num2){
    if (num1%num2 == 0) return num2;
    else return mdc(num2, num1%num2);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    long long X = 1,K,Y;
    cin >> Y >> K;
    for (int i =0; i<K; i++){
        X += mdc(Y, X);
    }
    cout << X;
}