#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

void exchangeHeadAndTail(Node *&head_ref) {
    // Hanya berjalan jika ada 2 node atau lebih
    if (head_ref == nullptr || head_ref->next == head_ref) {
        return;
    }

    Node* head = head_ref;
    Node* tail = head_ref->prev;

    // Kasus khusus: hanya ada 2 node
    if (head->next == tail) {
        head_ref = tail;
        return;
    }

    // Simpan neighbor (node setelah head dan sebelum tail)
    Node* head_next = head->next;
    Node* tail_prev = tail->prev;

    // 1. Update pointer neighbor
    tail_prev->next = head; // Node sebelum tail sekarang menunjuk ke head
    head_next->prev = tail; // Node setelah head sekarang menunjuk ke tail

    // 2. Update pointer head dan tail
    head->prev = tail_prev;
    head->next = tail; // Ini akan menjadi link sirkular dari tail baru ke head baru

    tail->prev = head; // Ini akan menjadi link sirkular dari head baru ke tail baru
    tail->next = head_next;

    // 3. Update head_ref untuk menunjuk ke head yang baru (yaitu tail lama)
    head_ref = tail;
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

void insertEnd(Node *&head_ref, int data) {
    Node *newNode = new Node{data, nullptr, nullptr};

    if (head_ref == nullptr)
    {
        newNode->next = newNode;
        newNode->prev = newNode;
        head_ref = newNode;
        return;
    }

    Node *tail = head_ref->prev;
    newNode->next = head_ref;
    newNode->prev = tail;
    head_ref->prev = newNode;
    tail->next = newNode;
}

int main() {
    Node *head = nullptr;

    // Buat list: 1 <-> 2 <-> 3 <-> 4 <-> 5
    insertEnd(head, 1);
    insertEnd(head, 2);
    insertEnd(head, 3);
    insertEnd(head, 4);
    insertEnd(head, 5);

    cout << "List sebelum exchange: ";
    printList(head);

    exchangeHeadAndTail(head);

    cout << "List setelah exchange head dan tail: ";
    // Expected output: 5 2 3 4 1
    printList(head);

    // Test dengan 2 node
    Node *head2 = nullptr;
    insertEnd(head2, 10);
    insertEnd(head2, 20);
    cout << "\nList 2 node sebelum exchange: ";
    printList(head2);
    exchangeHeadAndTail(head2);
    cout << "List 2 node setelah exchange: ";
    printList(head2); // Expected output: 20 10

    return 0;
}
