#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


vector <string> commands;
vector <int> registers(26, 0);
vector <pair<string, int>> labels;


int newIndex(string label) {
    for (int j = 0; j < labels.size(); j++) {
        if (labels[j].first == label) {
            return labels[j].second;
        }
    }
}


struct Node {
    int data;
    Node* next;
};


void put(Node** head, int value) {
    Node *temp = new Node();
    Node *last = *head;

    temp->data = value;
    temp->next = nullptr;

    if (*head == nullptr) {
        *head = temp;
        return;
    }

    while (last->next != nullptr) {
        last = last->next;
    }

    last->next = temp;
}


int get(Node** head) {
    Node *temp = *head;
    *head = temp->next;
    return temp->data;
}


int main() {
    ifstream fin("quack.in");
    ofstream fout("quack.out");

    string command, label;
    char reg;
    uint16_t x, y;
    bool run = true;

    Node *head = nullptr;

    int n = 0;
    while (fin >> command) {
        commands.emplace_back(command); // создает объект внутри вектора
        n++;
    }

    for (int i = 0; i < n; i++) {
        if (commands[i][0] == ':')
            labels.emplace_back(make_pair(commands[i].substr(1), i)); //возвращает подстроку данной строки начиная с символа с индексом pos
    }

    int i = 0;
    while (i < n) {
        command = commands[i];

        switch (command[0]) {
            case '+': {
                x = get(&head);
                y = get(&head);
                uint16_t sum = (x + y) % 65536;
                put(&head, sum);
                break;
            }

            case '-': {
                x = get(&head);
                y = get(&head);
                uint16_t diff = (x - y) % 65536;
                put(&head, diff);
                break;
            }

            case '*': {
                x = get(&head);
                y = get(&head);
                uint16_t ymnoj = (x * y) % 65536;
                put(&head, ymnoj);
                break;
            }

            case '/': {
                x = get(&head);
                y = get(&head);
                uint16_t del;
                if (y == 0)
                    del = 0;
                else
                    del = (x / y) % 65536;
                put(&head, del);
                break;
            }

            case '%': {
                x = get(&head);
                y = get(&head);
                uint16_t ostat;
                if (y == 0)
                    ostat = 0;
                else
                    ostat = (x % y) % 65536;
                put(&head, ostat);
                break;
            }

            case '>': {
                reg = command[1];
                x = get(&head);
                registers[reg % 97] = x;
                break;
            }

            case '<': {
                reg = command[1];
                x = registers[reg % 97];
                put(&head, x);
                break;
            }

            case 'P': {
                if (command.length() == 1) {
                    x = get(&head);
                } else {
                    reg = command[1];
                    x = registers[reg % 97];
                }
                fout << x << '\n';
                break;
            }

            case 'C': {
                if (command.length() == 1) {
                    x = get(&head);
                } else {
                    reg = command[1];
                    x = registers[reg % 97];
                }
                fout << char(x % 256);
                break;
            }

            case ':': {
                labels.emplace_back(make_pair(commands[i].substr(1), i));
                break;
            }

            case 'J': {
                label = commands[i].substr(1);
                i = newIndex(label);
                break;
            }

            case 'Z': {
                label = commands[i].substr(2);
                if (registers[command[1] % 97] == 0)
                    i = newIndex(label);
                break;
            }

            case 'E': {
                label = commands[i].substr(3);
                if (registers[command[1] % 97] == registers[command[2] % 97]) {
                    i = newIndex(label);
                }
                break;
            }

            case 'G': {
                label = commands[i].substr(3);
                if (registers[command[1] % 97] > registers[command[2] % 97]) {
                    i = newIndex(label);
                }
                break;
            }

            case 'Q': {
                run = false;
                break;
            }

            default: {
                uint16_t num = atoi(command.c_str()); //конвертирует строку, на которую указывает параметр str, в величину типа int
                put(&head, num);
                break;
            }
        }
        i++;
        if (!run)
            break;
    }
    return 0;
}




