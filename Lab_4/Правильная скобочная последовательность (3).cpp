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
    ifstream fin("brackets.in");
    ofstream fout("brackets.out");

    Node* head = NULL;
    string s;

    while (getline(fin, s)) {
        bool F = true;
        for (char i : s) {
            if (i == '(' or i == '[') {
                push(&head, i);
            } else if (i == ')' or i == ']') {
                if (head == NULL) {
                    F = false;
                    break;
                }
                int open_bracket = pop(&head);
                if (open_bracket == '(' and i != ')' or open_bracket == '[' and i != ']') {
                    F = false;
                    break;
                }
            }
        }
        if (head == NULL and F) {
            fout << "YES" << "\n";
        } else {
            fout << "NO" << "\n";
        }
        head = NULL;
    }

    return 0;
}
