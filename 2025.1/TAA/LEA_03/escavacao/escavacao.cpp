#include <bits/stdc++.h>
using namespace std;

int predas(string predera){
    stack <char> pilha;
    int predinhas = 0;
    for (char c : predera){
        if(c == '<'){
            pilha.push('<');
        } else if (c == '>'){
            if (!pilha.empty()){
                pilha.pop();
                predinhas++;
            }
        }
    }
    return predinhas;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    cin.ignore();
    while (N--){
        string predera;
        cin >> predera;
        cout << predas(predera) << endl;
    }
}
