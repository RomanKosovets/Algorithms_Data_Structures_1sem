#include <fstream>
#include <vector>
#include <queue>
#include <iostream>

enum Side {right=0, left=1};

struct First_Node {                                      // Создаём структуру для первого дерева
    int key;            // ключ
    int children[2];    // дети

    First_Node(int key, int left, int right) : key(key) {
        children[0] = left;
        children[1] = right;
    }
};

struct Node {                                            // Создаём структуру для создания нашего дерева

    int key;            // ключ
    int height;         // высота
    int inp_num;        // индекс
    Node* children[2];  // дети

    Node(int key, Node * left, Node * right, int num) : key(key), height(0), inp_num(num) {
        children[0] = left;
        children[1] = right;
    }
    Node(First_Node *node, int num) : height(0), key(node->key), inp_num(num) {
        children[0] = children[1] = nullptr;
    }
};

struct AVL_Tree {

    std::vector<First_Node *> first_tree;               // Исходное дерево
    std::vector<First_Node *> second_tree;              // Дерево после поворота
    Node * root = nullptr;

    void make_tree() {                                  // Создаём наше дерево, занося в "детей" наши значения,
        root = new Node(first_tree[0], 0);    // учитывая условия АВЛ дерева
        dfs_make(root);
    }
    void dfs_make(Node *v) {
        for (int i = 0; i < 2; i++) {
            if (first_tree[v->inp_num]->children[i] == -1)
                v->children[i] = nullptr;
            else {
                v->children[i] = new Node(first_tree[first_tree[v->inp_num]->children[i]], first_tree[v->inp_num]->children[i]);
                dfs_make(v->children[i]);
            }
        }
    }

    void count_height() {
        if (first_tree.empty())
            return ;
        dfs(root);
    }
    void fix_height(Node * v) {                             // Считаем высоту
        v->height = std::max(height_left(v), height_right(v)) + 1;
    }
    int height_right(Node * v) {                            // Возвращаем высоту правого ребёнка
        return v->children[1] == nullptr ? 0 : v->children[1]->height;
    }
    int height_left(Node * v) {                             // Возвращаем высоту левого ребёнка
        return v->children[0] == nullptr ? 0 : v->children[0]->height;
    }

    void dfs(Node * v) {                                    // Делаем обход в глубину (Depth-First Search) и считаем высоту
        for (auto child : v->children) {
            if (child != nullptr)
                dfs(child);
        }
        fix_height(v);
    }

    int count_balance(Node * v) {   // Считаем баланс
        return (v->children[1] != nullptr ? v->children[1]->height : 0) -
               (v->children[0] != nullptr ? v->children[0]->height : 0);
    }

    Node * rotate(Node *v, int side) {      // Производим малое левое вращение
        Node *u = v->children[side == Side::left ? 1 : 0];                                  // создаём указатель на правый дочерний узел
        v->children[side == Side::left ? 1 : 0] = u->children[side == Side::left ? 0 : 1];  // к главной вершине присваиваем левого ребёнка нового корня, который присвоили выше
        u->children[side == Side::left ? 0 : 1] = v;                                        // меняем указатель левого ребёнка нового корня на старый корень v
        fix_height(v); // корректировка высоты v
        fix_height(u); // корректировка высоты u
        return u;
    }

    Node * balance(Node * v) {
        if (count_balance(v->children[1]) < 0)
            v->children[1] = rotate(v->children[1], Side::right);
        return rotate(v, Side::left);
    }

    void make_second_tree() {
        std::queue<Node *> queue; // создаём очередь
        queue.push(root);
        int num = 1;
        while (!queue.empty()) {
            Node *v = queue.front();    // ссылка на  верхней элемент
            queue.pop();                // удаляем верхний
            int children_num[2] = {0, 0};
            for (int i = 0; i < 2; i++) {
                if (v->children[i] != nullptr) {
                    queue.push(v->children[i]);
                    children_num[i] = ++num;
                }
            }
            second_tree.push_back(new First_Node(v->key, children_num[0], children_num[1])); // заносим в массив наши значения в правильном порядке
        }
    }
};

int main() {

    std::ifstream fin("C:\\Users\\roman\\CLionProjects\\Project C++\\123.txt");
    std::ofstream fout("C:\\Users\\roman\\CLionProjects\\Project C++\\321.txt");

    size_t n;
    fin >> n;
    auto avl = new AVL_Tree();

    for (int i = 0; i < n; i++) {
        int key;
        int left, right;
        fin >> key >> left >> right;
        avl->first_tree.push_back(new First_Node(key, left-1, right-1));
    }

    avl->make_tree();

    avl->count_height();
    avl->root = avl->balance(avl->root);

    avl->make_second_tree();

    fout << n << "\n";
    for (auto v : avl->second_tree) {
        fout << v->key << " " << v->children[0] << " " << v->children[1] << "\n";
    }
}
