#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Identitas {
    string nama;
    string nim;
};

struct Data {
    string namaItem;
    int jumlah;
    string tipe;
};

struct Node {
    Data data;
    Node* next;
};

Identitas identitas;
Node* head = nullptr;
int jumlahItem = 0;
const int JUMLAH_DEFAULT = 35;
const int POSISI_SISIP = 6;

void inputIdentitas();
void tampilkanMenu();
void tambahItemBaru();
void sisipkanItem();
void hapusItemTerakhir();
void gunakanItem();
void tampilkanInventory();
void clearInputBuffer();
int inputAngka();
Node* buatNode(const Data& data);
void insertDiAkhir(const Data& data);
void insertDiPosisi(const Data& data, int posisi);
bool hapusTerakhir();
bool cariDanGunakanItem(const string& namaItem);

int main() {
    inputIdentitas();
    
    int pilihan;
    bool running = true;
    
    while (running) {
        tampilkanMenu();
        pilihan = inputAngka();
        
        switch (pilihan) {
            case 1:
                tambahItemBaru();
                break;
            case 2:
                sisipkanItem();
                break;
            case 3:
                hapusItemTerakhir();
                break;
            case 4:
                gunakanItem();
                break;
            case 5:
                tampilkanInventory();
                break;
            case 0:
                cout << "\nTerima kasih telah menggunakan Game Inventory Management!\n";
                running = false;
                break;
            default:
                cout << "\nPilihan tidak valid! Silakan pilih 0-5.\n";
                break;
        }
        
        if (running) {
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
        }
    }
    
    return 0;
}

void inputIdentitas() {
    cout << "GAME INVENTORY MANAGEMENT\n";
    cout << "SETUP IDENTITAS\n\n";
    
    cout << "Masukkan Nama: ";
    getline(cin, identitas.nama);
    
    cout << "Masukkan NIM : ";
    getline(cin, identitas.nim);
    
    cout << "\nSelamat datang " << identitas.nama << " (" << identitas.nim << ")!\n";
    cout << "Jumlah item default: " << JUMLAH_DEFAULT << " (berdasarkan 2 digit terakhir NIM)\n";
    cout << "Posisi sisip: " << POSISI_SISIP << " (berdasarkan digit terakhir NIM + 1)\n\n";
}

void tampilkanMenu() {
    cout << "\nGAME INVENTORY MANAGEMENT\n";
    cout << "[ " << identitas.nama << " - " << identitas.nim << " ]\n\n";
    cout << "1. Tambah Item Baru\n";
    cout << "2. Sisipkan Item\n";
    cout << "3. Hapus Item Terakhir\n";
    cout << "4. Gunakan Item\n";
    cout << "5. Tampilkan Inventory\n";
    cout << "0. Keluar\n";
    cout << "Pilih menu (0-5): ";
}

void tambahItemBaru() {
    cout << "\nTAMBAH ITEM BARU\n";
    
    Data itemBaru;
    
    cout << "Nama Item: ";
    clearInputBuffer();
    getline(cin, itemBaru.namaItem);
    
    cout << "Tipe Item: ";
    getline(cin, itemBaru.tipe);
    
    itemBaru.jumlah = JUMLAH_DEFAULT;
    
    insertDiAkhir(itemBaru);
    
    cout << "\nItem '" << itemBaru.namaItem << "' berhasil ditambahkan!\n";
    cout << "Tipe: " << itemBaru.tipe << "\n";
    cout << "Jumlah: " << itemBaru.jumlah << " (otomatis berdasarkan NIM)\n";
}

void sisipkanItem() {
    cout << "\nSISIPKAN ITEM\n";
    cout << "Item akan disisipkan pada posisi ke-" << POSISI_SISIP << " (berdasarkan NIM)\n\n";
    
    Data itemBaru;
    
    cout << "Nama Item: ";
    clearInputBuffer();
    getline(cin, itemBaru.namaItem);
    
    cout << "Tipe Item: ";
    getline(cin, itemBaru.tipe);
    
    itemBaru.jumlah = JUMLAH_DEFAULT;
    
    insertDiPosisi(itemBaru, POSISI_SISIP);
    
    cout << "\nItem '" << itemBaru.namaItem << "' berhasil disisipkan!\n";
    cout << "Tipe: " << itemBaru.tipe << "\n";
    cout << "Jumlah: " << itemBaru.jumlah << " (otomatis berdasarkan NIM)\n";
    cout << "Posisi: " << POSISI_SISIP << "\n";
}

void hapusItemTerakhir() {
    cout << "\nHAPUS ITEM TERAKHIR\n";
    
    if (hapusTerakhir()) {
        cout << "Item terakhir berhasil dihapus dari inventory!\n";
    } else {
        cout << "Inventory kosong! Tidak ada item yang dapat dihapus.\n";
    }
}

void gunakanItem() {
    cout << "\nGUNAKAN ITEM\n";
    
    if (head == nullptr) {
        cout << "Inventory kosong! Tidak ada item yang dapat digunakan.\n";
        return;
    }
    
    string namaItem;
    cout << "Masukkan nama item yang ingin digunakan: ";
    clearInputBuffer();
    getline(cin, namaItem);
    
    if (cariDanGunakanItem(namaItem)) {
        cout << "Item '" << namaItem << "' berhasil digunakan!\n";
    } else {
        cout << "Item '" << namaItem << "' tidak ditemukan dalam inventory!\n";
    }
}

void tampilkanInventory() {
    cout << "\nINVENTORY GAME\n";
    
    if (head == nullptr) {
        cout << "Inventory kosong! Belum ada item yang tersimpan.\n";
        return;
    }
    
    cout << "Total item: " << jumlahItem << "\n\n";
    
    Node* current = head;
    int nomor = 1;
    
    while (current != nullptr) {
        cout << nomor << ". Nama   : " << current->data.namaItem << "\n";
        cout << "   Tipe   : " << current->data.tipe << "\n";
        cout << "   Jumlah : " << current->data.jumlah << "\n";
        cout << "   ------------------------\n";
        
        current = current->next;
        nomor++;
    }
}

void clearInputBuffer() {
    if (cin.peek() == '\n') {
        cin.ignore();
    }
}

int inputAngka() {
    int angka;
    while (true) {
        if (cin >> angka) {
            return angka;
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input harus berupa angka! Coba lagi: ";
        }
    }
}

Node* buatNode(const Data& data) {
    Node* nodeBaru = new Node;
    nodeBaru->data = data;
    nodeBaru->next = nullptr;
    return nodeBaru;
}

void insertDiAkhir(const Data& data) {
    Node* nodeBaru = buatNode(data);
    
    if (head == nullptr) {
        head = nodeBaru;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = nodeBaru;
    }
    
    jumlahItem++;
}

void insertDiPosisi(const Data& data, int posisi) {
    if (posisi <= 1) {
        Node* nodeBaru = buatNode(data);
        nodeBaru->next = head;
        head = nodeBaru;
        jumlahItem++;
        return;
    }
    
    if (posisi >= jumlahItem + 1) {
        insertDiAkhir(data);
        return;
    }
    
    Node* nodeBaru = buatNode(data);
    Node* current = head;
    
    for (int i = 1; i < posisi - 1 && current != nullptr; i++) {
        current = current->next;
    }
    
    if (current != nullptr) {
        nodeBaru->next = current->next;
        current->next = nodeBaru;
        jumlahItem++;
    }
}

bool hapusTerakhir() {
    if (head == nullptr) {
        return false;
    }
    
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        jumlahItem--;
        return true;
    }
    
    Node* current = head;
    while (current->next->next != nullptr) {
        current = current->next;
    }
    
    delete current->next;
    current->next = nullptr;
    jumlahItem--;
    return true;
}

bool cariDanGunakanItem(const string& namaItem) {
    if (head == nullptr) {
        return false;
    }
    
    Node* current = head;
    Node* previous = nullptr;
    
    while (current != nullptr) {
        if (current->data.namaItem == namaItem) {
            current->data.jumlah--;
            
            cout << "Jumlah " << namaItem << " berkurang menjadi: " << current->data.jumlah << "\n";
            
            if (current->data.jumlah == 0) {
                cout << "Item " << namaItem << " habis dan dihapus dari inventory!\n";
                
                if (previous == nullptr) {
                    head = current->next;
                } else {
                    previous->next = current->next;
                }
                
                delete current;
                jumlahItem--;
            }
            
            return true;
        }
        
        previous = current;
        current = current->next;
    }
    
    return false;
}