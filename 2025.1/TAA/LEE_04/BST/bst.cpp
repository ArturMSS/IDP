#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

// Função para inserir um nó na BST
Node* insert(Node* root, int val) {
    if (!root)
        return new Node(val);
    if (val < root->val)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
    return root;
}

// Percurso in-order
void inOrder(Node* root, vector<int>& res) {
    if (!root) return;
    inOrder(root->left, res);
    res.push_back(root->val);
    inOrder(root->right, res);
}

// Percurso pre-order
void preOrder(Node* root, vector<int>& res) {
    if (!root) return;
    res.push_back(root->val);
    preOrder(root->left, res);
    preOrder(root->right, res);
}

// Percurso post-order
void postOrder(Node* root, vector<int>& res) {
    if (!root) return;
    postOrder(root->left, res);
    postOrder(root->right, res);
    res.push_back(root->val);
}

// Impressão dos vetores
void print(const string& label, const vector<int>& vec) {
    cout << label;
    for (int v : vec) cout << " " << v;
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    int N;
    cin >> N;
    vector<int> valores(N);
    for (int i = 0; i < N; ++i)
        cin >> valores[i];

    Node* root = nullptr;
    for (int v : valores)
        root = insert(root, v);

    vector<int> in, pre, post;
    inOrder(root, in);
    preOrder(root, pre);
    postOrder(root, post);

    print("In.:", in);
    print("Pre:", pre);
    print("Pos:", post);

    return 0;
}