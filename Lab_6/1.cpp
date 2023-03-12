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

Node *insert(Node *nodes, int i) {  // вставка элементов, постройка правильного бин дерева
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

int Tree_Height(Node *nodes) {  // считаем высоту дерева, разворачивая по очереди каждый элемент и возвращая их обратно
    if (nodes == nullptr)
        return 0;
    return max(Tree_Height(nodes->left), Tree_Height(nodes->right)) + 1;
}


int main() {

    ifstream fin ("C:\\Users\\roman\\CLionProjects\\Project C++\\5 laba\\123.txt");  //C:\Users\roman\CLionProjects\Project C++\5 laba\123.txt
    ofstream fout ("C:\\Users\\roman\\CLionProjects\\Project C++\\5 laba\\321.txt");

    int n;
    fin >> n;
    a.resize(n);

    for (int i = 0; i < n; i++) { // заносим в массив инфу о дереве (левого корня и правого)
        for (int j = 0; j < 3; j++) {
            fin >> a[i][j];
        }
    }

    Node *nodes = nullptr;
    for (int i = 0; i < n; i++) {
        nodes = insert(nodes, i);
    }

    fout << Tree_Height(nodes);
    return 0;
}