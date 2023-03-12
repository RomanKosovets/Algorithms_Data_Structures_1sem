
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
static const int mod = 100000;                 // размер хеш-таблицы

struct HashStruct {
    string key, value;
    HashStruct *prev = nullptr;
    HashStruct *next = nullptr;
};
vector<vector<HashStruct>> table(mod);         // массив всех списков элементов

int hashFunction(string key) {
    int hash = 5381;
    for (int i = 0; i < key.length(); i++) {
        hash = (((hash << 5) + hash) + int(key[i])) % mod; // DJB Hash
    }
    return hash;
}

string get(string key) {
    int hashFun = hashFunction(key);        // берём хеш функцию
    int size = table[hashFun].size();
    for (int i = 0; i < size; i++) {            // цикл по списку элементов
        if (table[hashFun][i].key == key) {     // если ключ есть, то выводим соответствуещее значение
            return table[hashFun][i].value;
        }
    }
    return "none";
}

bool exists(string key) {
    string res = get(key);
    if (res != "none") {
        return true;
    }
    return false;
}

void put(string key, string value, HashStruct **previous) {
    int hashFun = hashFunction(key);                    // берём хеш функцию
    int size = table[hashFun].size();
    if (exists(key)) {
        for (int i = 0; i < size; i++) {                     // цикл по списку элементов
            if (table[hashFun][i].key == key) {                // если нашли key, то соотносим key с value
                table[hashFun][i].value = value;
                break;
            }
        }
    } else {
        if (size == 0){
            table[hashFun].reserve(10);
        }
        HashStruct newStruct;                                // если такого ключа нет,
        newStruct.key = key;                                 // добавляем в конец списка новую структуру
        newStruct.value = value;
        newStruct.prev = *previous;
        newStruct.next = nullptr;
        table[hashFun].emplace_back (newStruct);

        if (*previous != nullptr) {                                           // если есть prev, то меняем next у предыдущего значения на ссылку на добавляемое значение
            (*previous)->next = &table[hashFun][table[hashFun].size() - 1];
        }
        *previous = &table[hashFun][table[hashFun].size() - 1];             // текущее значение становится предыдущим
    }
    return;
}

void deleteKey(string key, HashStruct **previous) {
    int hashFun = hashFunction (key);
    int size = table[hashFun].size();
    for (int i = 0; i < size; i++) {                     // цикл по списку элементов
        if (table[hashFun][i].key == key) {
            if (table[hashFun][i].next == nullptr) {      // если удаляемое значение не имеет prev, то prev для следующего обнуляем
                *previous = table[hashFun][i].prev;
            } else {
                table[hashFun][i].next->prev = table[hashFun][i].prev;   // если есть prev, то меняем prev след. эл. на prev удаляемого
            }
            if (table[hashFun][i].prev != nullptr) {
                table[hashFun][i].prev->next = table[hashFun][i].next;   // если есть next, то меняем next пред. эл. на next удаляемого
            }
            table[hashFun][i].key = table[hashFun][i].value = "";        // удаляем ключ и значение из массива
            table[hashFun][i].prev = table[hashFun][i].next = nullptr;   // удаляем указатели prev и next
            break;
        }
    }
}

string prev(string key) {                       // предыдущий x
    int hash = hashFunction (key);
    int size = table[hash].size ();
    for (int i = 0; i < size; i++) {            // цикл по списку элементов
        if (table[hash][i].key == key && table[hash][i].prev != nullptr) {   // условие: если есть этот ключ
            return (table[hash][i].prev)->value;                             // и если элемент добавлен не первым
        }
    }
    return "none";
}

string next(string key) {                       // следующий x
    int hash = hashFunction (key);
    int size = table[hash].size ();
    for (int i = 0; i < size; i++) {            //цикл по списку элементов
        if (table[hash][i].key == key && table[hash][i].next != nullptr) {    // условие: если есть этот ключ
            return (table[hash][i].next)->value;                              // и если элемент добавлен не последним
        }
    }
    return "none";
}

int main() {
    ifstream fin("linkedmap.in");     //"C:\\Users\\roman\\CLionProjects\\Project C++\\123.txt"
    ofstream fout("linkedmap.out");

    string command, x, y;
    HashStruct *previous = nullptr;

    while (fin >> command >> x) {
        if (command == "put") {
            fin >> y;
            put(x, y, &previous);
        }
        if (command == "delete")
            deleteKey(x, &previous);
        if (command == "get")
            fout << get(x) << "\n";
        if (command == "prev")
            fout << prev(x) << "\n";
        if (command == "next")
            fout << next(x) << "\n";
    }
    return 0;
}