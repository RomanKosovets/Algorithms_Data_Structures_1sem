#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector <int> > a(200000, vector<int>(3, 0));

struct Node {
    int value;
    Node *left;
    Node *right;
};

Node *NewNode(int value) {
    Node *newNode = new Node();
    newNode->value = value;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

Node *insert(Node *nodes, int i) {
    if (i != -1) {
        if (nodes == nullptr) {
            nodes = NewNode(a[i][0]);
            nodes->left = insert(nodes->left, a[i][1] - 1);
            nodes->right = insert(nodes->right, a[i][2] - 1);
        }
        return nodes;
    }
    return nullptr;
}

bool BST(Node* nodes, int l_min, int r_max) {  // делаем обход в глубину, проверяя каждый элемент на  мин и макс
    if (nodes == nullptr)
        return true;
    if (nodes->value <= l_min || nodes->value >= r_max)
        return false;
    return BST(nodes->left, l_min, nodes->value) && BST (nodes->right, nodes->value, r_max);
}

int main() {

    ifstream fin ("check.in");  //C:\Users\roman\CLionProjects\Project C++\5 laba\123.txt
    ofstream fout ("check.out");

    int n;
    fin >> n;
    a.resize(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            fin >> a[i][j];
        }
    }

    Node *nodes = nullptr;
    for (int i = 0; i < n; i++) {
        nodes = insert(nodes, i);
    }

    if (BST(nodes, -1000000000, 1000000000) || n == 0)
        fout << "YES";
    else
        fout << "NO";

    return 0;
}
