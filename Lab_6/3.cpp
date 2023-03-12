#include <iostream>
#include <fstream>

using namespace std;

struct Node {
    int value;
    Node *left;
    Node *right;
};

Node *getNewNode(int value) {
    Node *newNode = new Node();
    newNode->value = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

Node *insert(Node *root, int value) {  // добавляем в дерево,  при обнаружении у элемента отсутствие ребенка нужно подвесить на него вставляемый элемент.
    if (root == nullptr)
        root = getNewNode(value);
    else if (value < root->value)
        root->left = insert(root->left, value);
    else if (value > root->value)
        root->right = insert(root->right, value);

    return root;
}

bool exists(Node **root, int value) { //нахождение ключа
    Node *temp = *root;

    if (temp == nullptr)
        return false;
    if (temp->value == value)
        return true;

    else if (value < temp->value)
        return exists(&temp->left, value);
    else
        return exists(&temp->right, value);
}

Node *prev(Node *&root, int value) {
    Node *current = root; // текущий
    Node *res = nullptr;  // следующий

    while (current != nullptr) {
        if (value > current->value) {
            res = current;
            current = current->right;
        } else {
            current = current->left;
        }
    }
    return res;
}

Node *next(Node *&root, int value) {
    Node *current = root;  // текущий
    Node *res = nullptr;   // следующий

    while (current != nullptr) {
        if (value < current->value) {
            res = current;
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return res;
}

Node *min_in_right_subtree(Node *root) {  // ищем минимальный эл в правом поддереве
    Node *successor = root->right;

    while (successor != nullptr && successor->left != nullptr) {
        successor = successor->left;
    }

    return successor;
}

Node *delete_value(Node *root, int value) { // три случая
    if (root == nullptr)
        return root;

    if (value < root->value)   // удаляемый эл находится лево
        root->left = delete_value(root->left, value);
    else if (value > root->value)    // удаляемый эл находится справа
        root->right = delete_value(root->right, value);
    else {
        if (root->left == nullptr && root->right == nullptr)   // эл находится в корне
            return nullptr;
        else if (root->left == nullptr) {  // находим следующий за удаляемымм эл и удаляем его, после вставляем найденный эл вместо удаляемого
            Node *temp_l = root->right;
            free(root);
            return temp_l;
        } else if (root->right == nullptr) {
            Node *temp_r = root->left;
            free(root);
            return temp_r;
        }

        Node *temp = min_in_right_subtree(root);
        root->value = temp->value;
        root->right = delete_value(root->right, temp->value);
    }
    return root;
}

int main() {
    ifstream fin ("bstsimple.in"); //C:\Users\roman\CLionProjects\Project C++\5 laba\123.txt
    ofstream fout ("bstsimple.out");

    string command;
    Node* root = nullptr;

    while (fin >> command) {
        int value;
        fin >> value;

        if (command == "insert")
            root = insert(root, value);

        if (command == "delete")
            root = delete_value(root, value);

        if (command == "exists") {
            if (exists(&root, value))
                fout << "true" << "\n";
            else
                fout << "false" << "\n";
        }
        if (command == "next") {
            Node *temp = next(root, value);
            if (temp == nullptr)
                fout << "none" << "\n";
            else
                fout << temp->value << "\n";

        }
        if (command == "prev") {
            Node *temp = prev(root, value);
            if (temp == nullptr)
                fout << "none" << "\n";
            else
                fout << temp->value << "\n";
        }
    }
    return 0;
}