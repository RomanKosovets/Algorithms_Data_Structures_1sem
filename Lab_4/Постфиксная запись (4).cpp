#include <iostream>
#include <fstream>

using namespace std;


struct Node {
    int data;
    Node* next;
};

void push(Node** head, int value) {
    Node* temp = new Node();
    temp->data = value;
    temp->next = *head;
    *head = temp;
}

int pop(Node** head) {
    Node* temp = *head;
    *head = temp->next;
    return temp->data;
}

int main() {
    ifstream fin("postfix.in");
    ofstream fout("postfix.out");

    Node* head = NULL;
    string s;
    getline(fin, s);

    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == ' ') {
            continue;
        }
        if (s[i] == '+' or s[i] == '-' or s[i] == '*') {
            int n1 = pop(&head);
            int n2 = pop(&head);
            if (s[i] == '+') {
                push(&head, n1 + n2);
            } else if (s[i] == '-') {
                push(&head, n2 - n1);
            } else {
                push(&head, n1 * n2);
            }
        } else {
            int ch = s[i] - '0'; // преобразуем символ в число
            push(&head, ch);
        }
    }
    fout << pop(&head);
    return 0;
}


