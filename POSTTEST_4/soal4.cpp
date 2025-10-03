#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

void sortedInsert(Node *&head_ref, int data) {
    Node* newNode = new Node{data, nullptr, nullptr};

    if (head_ref == nullptr) {
        newNode->next = newNode;
        newNode->prev = newNode;
        head_ref = newNode;
        return;
    }

    // --- LENGKAPI DI SINI ---
    Node* current = head_ref;

    // Kasus 2: Data baru lebih kecil dari atau sama dengan head (sisipkan di awal)
    if (data <= head_ref->data) {
        Node* tail = head_ref->prev;
        newNode->next = head_ref;
        head_ref->prev = newNode;
        newNode->prev = tail;
        tail->next = newNode;
        head_ref = newNode; // Update head
        return;
    }

    // Kasus 3: Cari posisi yang tepat (tengah/akhir)
    // Loop untuk menemukan node sebelum posisi penyisipan
    while (current->next != head_ref && current->next->data < data) {
        current = current->next;
    }

    // Sisipkan newNode setelah current
    newNode->next = current->next;
    current->next->prev = newNode;
    current->next = newNode;
    newNode->prev = current;
    // --- LENGKAPI DI SINI ---
}

void printList(Node *head_ref) {
    if (head_ref == nullptr)
    {
        cout << "List kosong" << endl;
        return;
    }

    Node *current = head_ref;
    do
    {
        cout << current->data << " ";
        current = current->next;
    } while (current != head_ref);
    cout << endl;
}

int main() {
    Node *head = nullptr;

    sortedInsert(head, 30);
    sortedInsert(head, 10);
    sortedInsert(head, 40);
    sortedInsert(head, 20);

    cout << "Circular Doubly Linked List (sorted): ";
    printList(head); // Expected output: 10 20 30 40

    return 0;
}
