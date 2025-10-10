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
 * @brief Fungsi untuk melakukan post-order traversal pada tree.
 * @param root Pointer ke node root dari tree.
 * @logic
 * 1. Jika node saat ini adalah nullptr, kembalikan (base case).
 * 2. Rekursif ke subtree kiri.
 * 3. Rekursif ke subtree kanan.
 * 4. Cetak data node saat ini.
 */
void postOrderTraversal(Node* root) {
    // --- LENGKAPI KODE DI SINI ---
    // Base case: if the current node is null, do nothing.
    if (root == nullptr) {
        return;
    }
    // First, recursively traverse the left subtree.
    postOrderTraversal(root->left);
    // Then, recursively traverse the right subtree.
    postOrderTraversal(root->right);
    // Finally, process the current node (print its data).
    cout << root->data << " ";
    // -----------------------------
}

int main() {
    Node* root = nullptr;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 60);
    insert(root, 80);

    cout << "Post-order traversal dari tree adalah: ";
    postOrderTraversal(root); // Harusnya output: 20 40 30 60 80 70 50
    cout << endl;
    return 0;
}
