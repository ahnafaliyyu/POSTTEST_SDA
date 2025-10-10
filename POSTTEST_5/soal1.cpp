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
 * @brief Fungsi untuk menghitung jumlah total node dalam tree.
 * @param root Pointer ke node root dari tree.
 * @return Jumlah total node.
 * @logic
 * 1. Base case: Jika root adalah nullptr, tree kosong, kembalikan 0.
 * 2. Recursive step: Jumlah node adalah 1 (untuk node saat ini) +
 * jumlah node di subtree kiri + jumlah node di subtree kanan.
 */
int countNodes(Node* root) {
    // --- LENGKAPI KODE DI SINI ---
    // Base case: if the tree is empty, it has 0 nodes.
    if (root == nullptr) {
        return 0;
    }
    // Recursive step: count the current node (1) + nodes in the left subtree + nodes in the right subtree.
    return 1 + countNodes(root->left) + countNodes(root->right);
    // -----------------------------
}

int main() {
    Node* root = nullptr;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);

    cout << "Jumlah total node dalam tree adalah: " << countNodes(root) << endl; // Harusnya output: 4
    return 0;
}
