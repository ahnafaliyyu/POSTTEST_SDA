#include <iostream>
#include <string>
using namespace std;

struct Node {
    char data;
    Node* next;
};

// Fungsi Push dan Pop
void push(Node*& top, char data) {
    Node* newNode = new Node{data, top};
    top = newNode;
}

char pop(Node*& top) {
    if (top == nullptr) return '\0';
    Node* temp = top;
    char poppedValue = temp->data;
    top = top->next;
    delete temp;
    return poppedValue;
}

bool areBracketsBalanced(string expr) {
    Node* stackTop = nullptr;

    
    // 1. Loop setiap karakter dalam `expr`.
    for (char c : expr) {
        // 2. Jika karakter adalah kurung buka '(', '{', '[', push ke stack.
        if (c == '(' || c == '{' || c == '[') {
            push(stackTop, c);
        } 
        // 3. Jika karakter adalah kurung tutup ')', '}', ']'
        else if (c == ')' || c == '}' || c == ']') {
            // a. Apakah stack kosong? Jika ya, return false.
            if (stackTop == nullptr) {
                return false;
            }
            // b. Pop stack, lalu cek apakah kurung tutup cocok dengan kurung buka.
            char topChar = pop(stackTop);
            if ((c == ')' && topChar != '(') ||
                (c == '}' && topChar != '{') ||
                (c == ']' && topChar != '[')) {
                return false; // Pasangan tidak cocok
            }
        }
    }
    
    // 4. Setelah loop selesai, jika stack kosong, return true. Jika tidak, return false.
    return stackTop == nullptr;
    
}

int main() {
    string expr1 = "{[()]}";
    cout << expr1 << " -> " << (areBracketsBalanced(expr1) ? "Seimbang" : "Tidak Seimbang") << endl;
    // Expected output: Seimbang
    string expr2 = "{[(])}";
    cout << expr2 << " -> " << (areBracketsBalanced(expr2) ? "Seimbang" : "Tidak Seimbang") << endl;
     // Expected output: Tidak Seimbang
    return 0;
}
