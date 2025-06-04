#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    string S, T;
    float counter1=0.00, counter2=0.00;
    cin >> S >> T;
    for (char c:S){
        if ( c == '*') counter1++;
    }
    for (char c : T){
        if (c == '*') counter2++;
    }
    int quo = counter1  - counter2;
    cout << fixed << setprecision(2)<< quo/counter1;
}