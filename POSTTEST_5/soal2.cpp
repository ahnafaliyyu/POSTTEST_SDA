#include <iostream>
using namespace std;
// Struktur Node untuk Binary Tree
struct Node {
    int data;
    Node* left;
    Node* right;

    // Constructor
    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

// Fungsi insert untuk membangun tree
Node* insert(Node* root, int val) {
    if (root == nullptr) {
        return new Node(val);
    }
    if (val < root->data) {
        root->left = insert(root->left, val);
    } else if (val > root->data) {
        root->right = insert(root->right, val);
    }
    return root;
}
/**
 * @brief Fungsi untuk mencari nilai terkecil dalam sebuah BST.
 * @param root Pointer ke node root dari tree.
 * @return Nilai integer terkecil. Mengembalikan -1 jika tree kosong.
 * @logic
 * 1. Cek jika tree kosong.
 * 2. Selama masih ada anak kiri (left child), terus telusuri ke kiri.
 * 3. Node paling kiri adalah node dengan nilai terkecil.
 */
int findMinValue(Node* root) {
    // --- LENGKAPI KODE DI SINI ---
    // If the tree is empty, return -1 as specified.
    if (root == nullptr) {
        return -1;
    }
    // The minimum value is the leftmost node.
    Node* current = root;
    while (current->left != nullptr) {
        current = current->left;
    }
    // Return the data of the leftmost node.
    return current->data;
    // -----------------------------
}

int main() {
    Node* root = nullptr;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);

    cout << "Nilai terkecil dalam tree adalah: " << findMinValue(root) << endl; // Harusnya output: 20
    return 0;
}
