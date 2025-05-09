#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    int A;
    scanf("%d", &A);

    vector<int> notas(A);
    for (int i = 0; i < A; ++i) {
        scanf("%d", &notas[i]);
    }

    sort(notas.begin(), notas.end());

    for (int i = 0; i < A; ++i) {
        printf("%d\n", notas[i]);
    }

    return 0;
}
