    #include <bits/stdc++.h>
    using namespace std;
     
    int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector <int> peso(N);
    vector <int> val(N);

    for(int i = 0 ; i < N ; i++){
        cin >> val[i];
    }

    for(int i = 0; i < N; i++){
        cin >> peso[i];
    }

    int pMax;
    cin >> pMax;

    vector<long long> valMax(pMax + 1, 0);
    
    for(int i = 0; i < N; i++){
        int p = peso[i];
        int v = val[i];
        if (p > pMax) continue;
        for(int cap = pMax; cap >= p; --cap){
            int temp1 = valMax[cap];
            int temp2 = valMax[cap - p] + v;
            valMax[cap] = max(temp1, temp2);
        }
    }

    cout << valMax[pMax] << endl;
}
