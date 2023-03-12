#include <iostream>
#include <fstream>
#include <list>

using namespace std;

class hashTable {
private:
    static const int mod = 1000000;    // максимальный размер хеш-таблицы по усл.
    list<int> table[mod];              // создаём массив массив для хеш функций

public:
    int hashFunction(int key) {
        int hashFun = abs(key) % mod;
        return hashFun;
    }

    void insert(int key) {
        int hashFun = hashFunction(key);
        if (!exists(key))                   // если нет такого элемента, то добавляем, иначе скипаем
            table[hashFun].push_back(key);
    }

    bool exists(int key) {                  // нахождение ключа
        int hashFun = hashFunction(key);    // берём хеш функцию
        auto &address = table[hashFun];     // берём ссылку на ячейку с нашим хешем
        for (auto i = address.begin(); i != address.end(); i++) {     // цикл по списку элементов в ячейке
            if (*i == key) {                                          // если нашли, то true
                return true;
            }
        }
        return false;
    }

    void deleteKey(int key) {
        int hash = hashFunction (key);      // берём хеш функцию
        auto &address = table[hash];        // берём ссылку на ячейку с нашим хешем
        for (auto i = address.begin (); i != address.end (); i++) {   // цикл по списку элементов в ячейке
            if (*i == key) {                                          // если нашли, то true
                address.erase(i);           // удаляем хеш с индексом i из таблицы и выходим
                break;
            }
        }
    }
};

int main() {
    ifstream fin("set.in");  //"C:\\Users\\roman\\CLionProjects\\Project C++\\123.txt"
    ofstream fout ("set.out");

    string command;
    int x;
    hashTable table;

    while (fin >> command >> x) {
        if (command == "insert")
            table.insert(x);
        if (command == "delete")
            table.deleteKey(x);
        if (command == "exists") {
            if (table.exists(x))
                fout << "true" << "\n";
            else
                fout << "false" << "\n";
        }
    }
}