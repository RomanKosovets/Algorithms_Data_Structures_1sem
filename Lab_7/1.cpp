#include <fstream>
#include <vector>

struct Node {
    int key;
    int height;
    int children[2];

    Node(int key, int left, int right) {
        children[0] = left;
        children[1] = right;
    }
};

struct AVL_Tree {

    std::vector<Node *> tree;

    int balance(int v) {
        return (tree[v]->children[1] != -1 ? tree[tree[v]->children[1]]->height : 0) -
        (tree[v]->children[0] != -1 ? tree[tree[v]->children[0]]->height : 0);    // Считаем балансировку путём
    }                                                                             // вычитания из левого дерева правое

    void count_height() {
        if (tree.empty())
            return ;
        dfs(tree[0]);
    }

    int height_left(Node *v){                                            // Считаем высоту левого ключа
        return v->children[0] != -1 ? tree[v->children[0]] -> height : 0;
    }
    int height_right(Node *v) {                                          // Считаем высоту правого ключа
        return v->children[1] != -1 ? tree[v->children[1]] -> height : 0;
    }

    void dfs(Node *v) {                // делаем обход в глубину и считаем высоту каждой вершины
        for (int child : v->children) {
            if (child != -1)
                dfs(tree[child]);
        }
        v->height = std::max(height_left(v), height_right(v)) + 1;
    }
};

int main() {

    std::ifstream fin("C:\\Users\\roman\\CLionProjects\\Project C++\\123.txt");
    std::ofstream fout("C:\\Users\\roman\\CLionProjects\\Project C++\\321.txt");

    size_t n;
    fin >> n;
    auto avl = new AVL_Tree();           // Создаём АВЛ-дерево

    for (int i = 0; i < n; i++) {        // Считываем данные
        int key;
        int left, right;
        fin >> key >> left >> right;
        avl->tree.push_back(new Node(key, left-1, right-1));  // Создаём новую ноду
    }

    avl->count_height();
    for (int i = 0; i < avl->tree.size(); i++) {
        fout << avl->balance(i) << "\n";
    }
}