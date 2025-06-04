#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    stack<char> pilha;
    string S;
    cin >> S;

    const char aberturas[] = {'(', '[', '{'};
    const char fechamentos[] = {')', ']', '}'};

    auto corresponde = [&](char abertura, char fechamento) -> bool {
        for (int i = 0; i < 3; ++i) {
            if (abertura == aberturas[i])
                return fechamento == fechamentos[i];
        }
        return false;
    };

    for (char c : S) {
        if (c == '(' || c == '[' || c == '{') {
            pilha.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (pilha.empty() || !corresponde(pilha.top(), c)) {
                cout << "SyntaxError";
                return 0;
            }
            pilha.pop();
        }
    }

    if (pilha.empty()) {
        cout << "OK";
    } else {
        cout << "SyntaxError";
    }

    return 0;
}
