#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    int n;
    string s, r , t;
    cin >> n;
    while(n--){
        cin >> s >> r;
        t.clear();
        for (int i =0; i< s.size(); ++i){
            if (s[i] == r[i]){
                t += toupper(r[i]);
            } else {
                t += tolower(r[i]);
            }
        }
        cout << t << endl;
    }
}