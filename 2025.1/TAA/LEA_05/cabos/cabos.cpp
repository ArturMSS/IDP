#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;

    priority_queue<int, vector<int>, greater<int>> cabos;
    while (N--){
        int a;
        cin >> a;
        cabos.push(a);
    }
    int custo = 0;
    while(cabos.size() > 1){
        int cabo1 = cabos.top(); cabos.pop();
        int cabo2 = cabos.top(); cabos.pop();
        custo += cabo2;
        int cabo_novo = cabo1 + cabo2;
        cabos.push(cabo_novo);
    }
    cout << custo;
}