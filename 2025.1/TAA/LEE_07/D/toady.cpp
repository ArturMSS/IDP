#include <bits/stdc++.h>
using namespace std;

static const int oo = 0x3f3f3f3f;
int main(){
    ios::sync_with_stdio(false);
    int N;
    cin >> N;
    vector<int> h(N+1);

    for(int i = 1; i <= N; i++){
        cin >> h[i];
    }

    vector <int> stam (N+1 , oo);
    stam[1] = 0;

    for(int i = 2; i <= N; i++){
        int cost1 = stam[i-1] + abs(h[i] - h[i-1]);
        int cost2 = oo;

        if (i >= 3){
            cost2 = stam[i-2] + abs(h[i] - h[i-2]);
        }
        stam[i] = min(cost1, cost2);
    }
    cout << stam[N] << endl;
}