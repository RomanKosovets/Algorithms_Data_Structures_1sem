#include <iostream>
#include <fstream>
#include <list>

using namespace std;

class hashTable {
private:
    static const int mod = 100000;             // размер хеш-таблицы
    list<pair<string, string >> table[mod];    // создаём массив пар

public:
    static int hashFunction(string key) {
        int hash = 5381;
        for (int i = 0; i < key.length(); i++) {
            hash = (((hash << 5) + hash) + int(key[i])) % mod; // DJB Hash
        }
        return hash;
    }

    string get(string key) {
        int hashFun = hashFunction (key);          // берём хеш функцию
        auto &address = table[hashFun];                // берём ссылку на ячейку с хешом
        for (auto i = address.begin (); i != address.end (); i++) {      // цикл по списку элементов в ячейке
            if (i->first == key)                                         // если нашли такой ключ в таблице, то возвращаем значение
                return i->second;
        }
        return "none";
    }

    void HashDelete(string key) {
        int hashFun = hashFunction(key);           // берём хеш функцию
        auto &address = table[hashFun];                // берём ссылку на ячейку с хешом
        for (auto i = address.begin(); i != address.end(); i++) {        // цикл по списку элементов в ячейке
            if (i->first == key) {                                       // если нашли такой ключ, то удаляем
                address.erase(i);
                break;
            }
        }
    }

    bool exists(string key) {
        string res = get(key);
        if (res != "none")
            return true;
        return false;
    }

    void put(string key, string value) {
        int hashFun = hashFunction (key);        // берём хеш функцию
        auto &address = table[hashFun];              // берём ссылку на ячейку с хешом
        if (exists(key)) {
            for (auto i = address.begin (); i != address.end (); i++) {    // цикл по списку элементов в ячейке
                if (i->first == key) {                                     // ставим в соответствие ключу x ключ y
                    i->second = value;
                    break;
                }
            }
        } else {
            address.emplace_back(key, value); // если такого ключа нет, добавляем новую пару в конец
        }
        return;
    }
};

int main() {
    ifstream fin("map.in");   // "C:\\Users\\roman\\CLionProjects\\Project C++\\6 lab\\123.txt"
    ofstream fout("map.out");

    string command, x, y;
    hashTable Hashtable;

    while (fin >> command >> x) {
        if (command == "put") {
            fin >> y;
            Hashtable.put(x, y);
        }
        if (command == "delete")
            Hashtable.HashDelete(x);
        if (command == "get")
            fout << Hashtable.get(x) << "\n";
    }
    return 0;
}

