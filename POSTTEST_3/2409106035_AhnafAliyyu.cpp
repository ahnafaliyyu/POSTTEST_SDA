#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

struct Identitas {
    string nama;
    string nim;
};

struct Data {
    string namaItem;
    int jumlah;
    string tipe;
    int no_item;
};

struct Node {
    Data data;
    Node* next;
    Node* prev;
};

struct DoublyLinkedList {
    Node* head = nullptr;
    Node* tail = nullptr;
    int jumlahItem = 0;
};

enum Halaman {
    UTAMA,
    TAMBAH_ITEM,
    SISIP_ITEM,
    HAPUS_ITEM,
    GUNAKAN_ITEM,
    LIHAT_INVENTORY
};

struct AppState {
    Halaman halamanAktif = UTAMA;
    DoublyLinkedList inventory;
    string pesanInfo = "";
    Identitas identitas;
};

namespace View {
    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    void renderHeader(const AppState& state) {
        cout << "+----------------------------------------------------------------------+\n";
        cout << "|                    GAME INVENTORY MANAGEMENT                         |\n";
        cout << "|                   [ " << state.identitas.nama << " - " << state.identitas.nim << " ]                              |\n";
        cout << "+----------------------------------------------------------------------+\n";
    }

    void renderInfoMessage(const AppState& state) {
        if (!state.pesanInfo.empty()) {
            cout << "[INFO] " << state.pesanInfo << "\n\n";
        }
    }

    void renderMenuUtama() {
        cout << "| 1. Tambah Item Baru                                                  |\n";
        cout << "| 2. Sisipkan Item                                                     |\n";
        cout << "| 3. Hapus Item Terakhir                                               |\n";
        cout << "| 4. Gunakan Item                                                      |\n";
        cout << "| 5. Tampilkan Inventory                                               |\n";
        cout << "| 0. Keluar                                                            |\n";
        cout << "+----------------------------------------------------------------------+\n";
        cout << "Pilih menu (0-5): ";
    }

    void renderInventory(const AppState& state) {
        cout << "INVENTORY GAME\n";
        
        if (state.inventory.head == nullptr) {
            cout << "Inventory kosong! Belum ada item yang tersimpan.\n";
            return;
        }
        
        cout << "Total item: " << state.inventory.jumlahItem << "\n\n";
        
        Node* current = state.inventory.head;
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

    void render(const AppState& state) {
        clearScreen();
        renderHeader(state);
        renderInfoMessage(state);

        switch (state.halamanAktif) {
            case UTAMA:
                renderMenuUtama();
                break;
            case TAMBAH_ITEM:
                cout << "TAMBAH ITEM BARU\n";
                break;
            case SISIP_ITEM:
                cout << "SISIPKAN ITEM\n";
                cout << "Item akan disisipkan pada posisi ke-6\n";
                break;
            case HAPUS_ITEM:
                cout << "HAPUS ITEM TERAKHIR\n";
                break;
            case GUNAKAN_ITEM:
                cout << "GUNAKAN ITEM\n";
                break;
            case LIHAT_INVENTORY:
                renderInventory(state);
                break;
        }
    }
}

namespace UseCase {
    const int JUMLAH_DEFAULT = 35;
    const int POSISI_SISIP = 6;

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
        nodeBaru->prev = nullptr;
        return nodeBaru;
    }

    void insertDiAkhir(AppState& state, const Data& data) {
        Node* nodeBaru = buatNode(data);
        nodeBaru->data.no_item = state.inventory.jumlahItem + 1;
        
        if (state.inventory.head == nullptr) {
            state.inventory.head = nodeBaru;
            state.inventory.tail = nodeBaru;
        } else {
            nodeBaru->prev = state.inventory.tail;
            state.inventory.tail->next = nodeBaru;
            state.inventory.tail = nodeBaru;
        }
        
        state.inventory.jumlahItem++;
    }

    void insertDiPosisi(AppState& state, const Data& data, int posisi) {
        if (posisi <= 1) {
            Node* nodeBaru = buatNode(data);
            nodeBaru->data.no_item = 1;
            
            if (state.inventory.head == nullptr) {
                state.inventory.head = nodeBaru;
                state.inventory.tail = nodeBaru;
            } else {
                nodeBaru->next = state.inventory.head;
                state.inventory.head->prev = nodeBaru;
                state.inventory.head = nodeBaru;
                
                // Update nomor item
                Node* current = nodeBaru->next;
                while (current != nullptr) {
                    current->data.no_item++;
                    current = current->next;
                }
            }
            
            state.inventory.jumlahItem++;
            return;
        }
        
        if (posisi > state.inventory.jumlahItem) {
            insertDiAkhir(state, data);
            return;
        }
        
        Node* current = state.inventory.head;
        for (int i = 1; i < posisi && current != nullptr; i++) {
            current = current->next;
        }
        
        if (current != nullptr) {
            Node* nodeBaru = buatNode(data);
            nodeBaru->data.no_item = posisi;
            
            nodeBaru->next = current;
            nodeBaru->prev = current->prev;
            
            if (current->prev != nullptr) {
                current->prev->next = nodeBaru;
            } else {
                state.inventory.head = nodeBaru;
            }
            current->prev = nodeBaru;
            
            // Update nomor item setelah posisi sisip
            Node* temp = current;
            while (temp != nullptr) {
                temp->data.no_item++;
                temp = temp->next;
            }
            
            state.inventory.jumlahItem++;
        }
    }

    bool hapusTerakhir(AppState& state) {
        if (state.inventory.tail == nullptr) {
            return false;
        }
        
        Node* nodeHapus = state.inventory.tail;
        
        if (state.inventory.head == state.inventory.tail) {
            state.inventory.head = nullptr;
            state.inventory.tail = nullptr;
        } else {
            state.inventory.tail = nodeHapus->prev;
            state.inventory.tail->next = nullptr;
        }
        
        delete nodeHapus;
        state.inventory.jumlahItem--;
        return true;
    }

    bool cariDanGunakanItem(AppState& state, const string& namaItem) {
        if (state.inventory.head == nullptr) {
            return false;
        }
        
        Node* current = state.inventory.head;
        
        while (current != nullptr) {
            if (current->data.namaItem == namaItem) {
                current->data.jumlah--;
                
                cout << "Jumlah " << namaItem << " berkurang menjadi: " << current->data.jumlah << "\n";
                
                if (current->data.jumlah == 0) {
                    cout << "Item " << namaItem << " habis dan dihapus dari inventory!\n";
                    
                    // Hapus node dari double linked list
                    if (current->prev != nullptr) {
                        current->prev->next = current->next;
                    } else {
                        state.inventory.head = current->next;
                    }
                    
                    if (current->next != nullptr) {
                        current->next->prev = current->prev;
                    } else {
                        state.inventory.tail = current->prev;
                    }
                    
                    // Update nomor item setelah node yang dihapus
                    Node* temp = current->next;
                    while (temp != nullptr) {
                        temp->data.no_item--;
                        temp = temp->next;
                    }
                    
                    delete current;
                    state.inventory.jumlahItem--;
                }
                
                return true;
            }
            
            current = current->next;
        }
        
        return false;
    }

    void inputIdentitas(AppState& state) {
        cout << "GAME INVENTORY MANAGEMENT\n";
        cout << "SETUP IDENTITAS\n";
        
        cout << "Masukkan Nama: ";
        getline(cin, state.identitas.nama);
        
        cout << "Masukkan NIM : ";
        getline(cin, state.identitas.nim);
        
        cout << "Selamat datang " << state.identitas.nama << " (" << state.identitas.nim << ")!\n";
        cout << "Jumlah item default: " << JUMLAH_DEFAULT << " (berdasarkan 2 digit terakhir NIM)\n";
        cout << "Posisi sisip: " << POSISI_SISIP << " (berdasarkan digit terakhir NIM + 1)\n\n";
        
        cout << "\nTekan Enter untuk melanjutkan...";
        cin.get();
    }

    void tambahItem(AppState& state) {
        Data itemBaru;
        
        cout << "Nama Item: ";
        clearInputBuffer();
        getline(cin, itemBaru.namaItem);
        
        cout << "Tipe Item: ";
        getline(cin, itemBaru.tipe);
        
        itemBaru.jumlah = JUMLAH_DEFAULT;
        
        insertDiAkhir(state, itemBaru);
        
        state.pesanInfo = "Item '" + itemBaru.namaItem + "' berhasil ditambahkan! Tipe: " + itemBaru.tipe + ", Jumlah: " + to_string(itemBaru.jumlah);
        state.halamanAktif = UTAMA;
    }

    void sisipkanItem(AppState& state) {
        Data itemBaru;
        
        cout << "Nama Item: ";
        clearInputBuffer();
        getline(cin, itemBaru.namaItem);
        
        cout << "Tipe Item: ";
        getline(cin, itemBaru.tipe);
        
        itemBaru.jumlah = JUMLAH_DEFAULT;
        
        insertDiPosisi(state, itemBaru, POSISI_SISIP);
        
        state.pesanInfo = "Item '" + itemBaru.namaItem + "' berhasil disisipkan pada posisi " + to_string(POSISI_SISIP);
        state.halamanAktif = UTAMA;
    }

    void hapusItemTerakhir(AppState& state) {
        if (hapusTerakhir(state)) {
            state.pesanInfo = "Item terakhir berhasil dihapus dari inventory!";
        } else {
            state.pesanInfo = "Inventory kosong! Tidak ada item yang dapat dihapus.";
        }
        state.halamanAktif = UTAMA;
        
        cout << "\nTekan Enter untuk melanjutkan...";
        cin.ignore();
        cin.get();
    }

    void gunakanItem(AppState& state) {
        if (state.inventory.head == nullptr) {
            state.pesanInfo = "Inventory kosong! Tidak ada item yang dapat digunakan.";
            state.halamanAktif = UTAMA;
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
            return;
        }
        
        string namaItem;
        cout << "Masukkan nama item yang ingin digunakan: ";
        clearInputBuffer();
        getline(cin, namaItem);
        
        if (cariDanGunakanItem(state, namaItem)) {
            state.pesanInfo = "Item '" + namaItem + "' berhasil digunakan!";
        } else {
            state.pesanInfo = "Item '" + namaItem + "' tidak ditemukan dalam inventory!";
        }
        
        state.halamanAktif = UTAMA;
        cout << "\nTekan Enter untuk melanjutkan...";
        cin.get();
    }

    void lihatInventory(AppState& state) {
        state.halamanAktif = LIHAT_INVENTORY;
        cout << "\nTekan Enter untuk kembali ke menu utama...";
        cin.ignore();
        cin.get();
        state.halamanAktif = UTAMA;
    }

    void prosesInput(AppState& state, const string& input) {
        if (input == "1") {
            state.halamanAktif = TAMBAH_ITEM;
        } else if (input == "2") {
            state.halamanAktif = SISIP_ITEM;
        } else if (input == "3") {
            state.halamanAktif = HAPUS_ITEM;
        } else if (input == "4") {
            state.halamanAktif = GUNAKAN_ITEM;
        } else if (input == "5") {
            state.halamanAktif = LIHAT_INVENTORY;
        } else {
            state.pesanInfo = "Pilihan tidak valid! Silakan pilih 0-5.";
        }
    }
}

int main() {
    AppState state;
    string input;
    
    UseCase::inputIdentitas(state);
    
    while (true) {
        View::render(state);
        
        if (state.halamanAktif == UTAMA) {
            cin >> input;
            if (input == "0") {
                cout << "Terima kasih telah menggunakan Game Inventory Management!\n";
                break;
            }
            UseCase::prosesInput(state, input);
        } else if (state.halamanAktif == TAMBAH_ITEM) {
            UseCase::tambahItem(state);
        } else if (state.halamanAktif == SISIP_ITEM) {
            UseCase::sisipkanItem(state);
        } else if (state.halamanAktif == HAPUS_ITEM) {
            UseCase::hapusItemTerakhir(state);
        } else if (state.halamanAktif == GUNAKAN_ITEM) {
            UseCase::gunakanItem(state);
        } else if (state.halamanAktif == LIHAT_INVENTORY) {
            UseCase::lihatInventory(state);
        }
        
        // Reset pesan info setelah ditampilkan
        if (state.halamanAktif == UTAMA && !state.pesanInfo.empty()) {
            state.pesanInfo = "";
        }
    }
    
    return 0;
}
