#include <iostream>
#include <fstream>
#include <cstddef>

using namespace std;

struct Node {
    Node* next; // указатель на след. элемент
    int data;  // информационное поле
};

void push(Node** head, int value) {  // создание очереди
    Node* temp = new Node(); // временно новый указатель на начало
    Node* last = *head; // объявляем первый элемент
    temp->data = value; // добавление элемента в конец
    temp->next = NULL; // обнуление указателя на след. элемент
    if (*head == NULL) {
        *head = temp;
        return;
    }
    while (last->next != NULL) { // пока след элемент не равен нулю
        last = last->next; // последний равен следующему
    }
    last->next = temp;
}


int pop(Node** head) {
    Node* temp = (*head);
    (*head) = temp->next;
    return temp->data;
}


int main() {
    ifstream fin("C:\\Users\\roman\\CLionProjects\\Project C++\\stack.txt");
    ofstream fout("C:\\Users\\roman\\CLionProjects\\Project C++\\stack.out.txt");
    int m;
    fin >> m;
    char s;
    int value;
    Node* head = NULL;
    for (int i = 0; i < m; i++) {
        fin >> s;
        if (s == '+') {
            fin >> value;
            push(&head, value);
        } else {
            fout << pop(&head) << "\n";
        }
    }

    return 0;
}


