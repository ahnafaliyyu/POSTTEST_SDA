#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

// -- 1. MODEL DATA & STRUKTUR DATA --

struct Penghuni {
  string nama = "Kosong";
  string no_hp = "-";
};

struct Kamar {
  int no_kamar;
  bool terisi = false;
  Penghuni penghuni;
  double harga_sewa;
};

struct Node {
  Kamar data;
  Node *next;
  Node *prev;
};

struct KamarList {
  Node *head = nullptr;
  Node *tail = nullptr;
};

enum Halaman { UTAMA, TAMBAH_KAMAR, CHECK_IN, LIHAT_DETAIL, HAPUS_KAMAR };

// -- 2. STATE APLIKASI
struct AppState {
  Halaman halamanAktif = UTAMA;
  KamarList daftarKamar;
  string pesanInfo = "";
  int kamarDipilih = -1;
};

// -- 3. KOMPONEN VIEW --
namespace View {
void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void renderHeader() {
  cout << "========================================\n";
  cout << "   Sistem Manajemen Kamar Kos 'KamarKita' \n";
  cout << "========================================\n\n";
}

void renderInfoMessage(const AppState &state) {
  if (!state.pesanInfo.empty()) {
    cout << "[INFO] " << state.pesanInfo << "\n\n";
  }
}

void renderTabelHeader() {
  cout << "--- Daftar Kamar ---\n";
  cout << left;
  cout << setw(8) << "No." << setw(12) << "Status"
            << setw(20) << "Penghuni" << "\n";
  cout << "----------------------------------------\n";
}

void renderTabelBody(const AppState &state) {
  if (state.daftarKamar.head == nullptr) {
    cout << "Belum ada kamar yang terdaftar.\n";
  } else {
    Node *current = state.daftarKamar.head;
    while (current != nullptr) {
      cout << setw(8) << current->data.no_kamar << setw(12)
           << (current->data.terisi ? "Terisi" : "Kosong") << setw(20)
           << current->data.penghuni.nama << "\n";
      current = current->next;
    }
  }
}

void renderMenuUtama() {
  cout << "\n--- Menu Utama ---\n";
  cout << "[1] Tambah Kamar Baru\n";
  cout << "[2] Check-in Penghuni\n";
  cout << "[3] Lihat Detail / Check-out\n";
  cout << "[4] Hapus Kamar\n";
  cout << "[0] Keluar\n";
  cout << "Pilihan: ";
}

void renderDashboard(const AppState &state) {
  renderTabelHeader();
  renderTabelBody(state);
  renderMenuUtama();
}

void renderFormTambahKamar() {
  cout << "--- Form Tambah Kamar Baru ---\n";
  cout << "Masukkan Nomor Kamar: ";
}

void renderFormCheckIn(const AppState &state) {

  renderTabelHeader();
  renderTabelBody(state);
  cout << "--- Form Check-in Penghuni ---\n";
  cout << "Masukkan Nomor Kamar yang akan diisi: ";
}

void renderFormHapusKamar() {
  cout << "--- Form Hapus Kamar ---\n";
  cout << "Masukkan Nomor Kamar yang akan dihapus: ";
}

void renderDetailKamar(const AppState &state) {
  Node *current = state.daftarKamar.head;
  while (current != nullptr && current->data.no_kamar != state.kamarDipilih) {
    current = current->next;
  }

  if (current == nullptr) {
    cout << "Kamar tidak ditemukan.\n";
  } else {
    Kamar &k = current->data;
    cout << "--- Detail Kamar No. " << k.no_kamar << " ---\n";
    cout << "Harga Sewa : Rp" << k.harga_sewa << "\n";
    cout << "Status     : " << (k.terisi ? "Terisi" : "Kosong") << "\n";
    cout << "Penghuni   : " << k.penghuni.nama << "\n";
    cout << "No. HP     : " << k.penghuni.no_hp << "\n";
    cout << "\n--- Menu Detail ---\n";
    if (k.terisi) {
      cout << "[1] Lakukan Check-out\n";
    }
    cout << "[0] Kembali ke Menu Utama\n";
    cout << "Pilihan: ";
  }
}

void render(const AppState &state) {
  clearScreen();
  renderHeader();
  renderInfoMessage(state);

  switch (state.halamanAktif) {
  case UTAMA:
    renderDashboard(state);
    break;
  case TAMBAH_KAMAR:
    renderFormTambahKamar();
    break;
  case CHECK_IN:
    renderFormCheckIn(state);
    break;
  case LIHAT_DETAIL:
    renderDetailKamar(state);
    break;
  case HAPUS_KAMAR:
    renderFormHapusKamar();
    break;
  }
}
} // namespace View

// -- 4. KOMPONEN USE CASE --
namespace UseCase {

Node *cariKamar(KamarList &list, int no_kamar) {
  Node *current = list.head;
  while (current != nullptr) {
    if (current->data.no_kamar == no_kamar)
      return current;
    current = current->next;
  }
  return nullptr;
}

void tambahKamar(AppState &state) {
  int no_kamar;
  double harga;

  cin >> no_kamar;

  if (cin.fail() || cariKamar(state.daftarKamar, no_kamar) != nullptr) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    state.pesanInfo = "Gagal! Nomor kamar tidak valid atau sudah ada.";
  } else {
    cout << "Masukkan Harga Sewa: ";
    cin >> harga;

    Kamar kamarBaru;
    kamarBaru.no_kamar = no_kamar;
    kamarBaru.harga_sewa = harga;

    Node *newNode = new Node{kamarBaru, nullptr, state.daftarKamar.tail};
    if (state.daftarKamar.head == nullptr) {
      state.daftarKamar.head = state.daftarKamar.tail = newNode;
    } else {
      state.daftarKamar.tail->next = newNode;
      state.daftarKamar.tail = newNode;
    }
    state.pesanInfo =
        "Kamar No. " + to_string(no_kamar) + " berhasil ditambahkan.";
  }
  state.halamanAktif = UTAMA;
}

void checkInPenghuni(AppState &state) {
  int no_kamar;
  cin >> no_kamar;

  Node *kamarNode = cariKamar(state.daftarKamar, no_kamar);

  if (cin.fail() || kamarNode == nullptr || kamarNode->data.terisi) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    state.pesanInfo = "Gagal! Kamar tidak ditemukan atau sudah terisi.";
  } else {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Masukkan Nama Penghuni: ";
    getline(cin, kamarNode->data.penghuni.nama);
    cout << "Masukkan No. HP: ";
    getline(cin, kamarNode->data.penghuni.no_hp);
    kamarNode->data.terisi = true;
    state.pesanInfo =
        "Penghuni berhasil check-in ke kamar No. " + to_string(no_kamar) + ".";
  }
  state.halamanAktif = UTAMA;
}

void checkOutPenghuni(AppState &state) {
  Node *kamarNode = cariKamar(state.daftarKamar, state.kamarDipilih);
  if (kamarNode != nullptr) {
    kamarNode->data.terisi = false;
    kamarNode->data.penghuni = {"Kosong", "-"};
    state.pesanInfo = "Penghuni dari kamar No. " +
                      to_string(state.kamarDipilih) + " berhasil check-out.";
  }
  state.kamarDipilih = -1;
  state.halamanAktif = UTAMA;
}

void hapusKamar(AppState &state) {
  int no_kamar;
  cin >> no_kamar;

  Node *target = cariKamar(state.daftarKamar, no_kamar);

  if (cin.fail() || target == nullptr) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    state.pesanInfo =
        "Gagal! Kamar No. " + to_string(no_kamar) + " tidak ditemukan.";
  } else if (target->data.terisi) {
    state.pesanInfo = "Gagal! Kamar No. " + to_string(no_kamar) +
                      " masih terisi. Check-out dulu.";
  } else {
    if (target == state.daftarKamar.head)
      state.daftarKamar.head = target->next;
    if (target == state.daftarKamar.tail)
      state.daftarKamar.tail = target->prev;
    if (target->prev != nullptr)
      target->prev->next = target->next;
    if (target->next != nullptr)
      target->next->prev = target->prev;

    delete target;
    state.pesanInfo = "Kamar No. " + to_string(no_kamar) + " berhasil dihapus.";
  }
  state.halamanAktif = UTAMA;
}

void prosesInput(AppState &state, const string &input) {
  state.pesanInfo = "";

  try {
    int pilihan = stoi(input);
    if (state.halamanAktif == UTAMA) {
      switch (pilihan) {
      case 1:
        state.halamanAktif = TAMBAH_KAMAR;
        break;
      case 2:
        state.halamanAktif = CHECK_IN;
        break;
      case 3:
        cout << "Masukkan nomor kamar yang ingin dilihat: ";
        cin >> state.kamarDipilih;
        if (cariKamar(state.daftarKamar, state.kamarDipilih) != nullptr) {
          state.halamanAktif = LIHAT_DETAIL;
        } else {
          state.pesanInfo = "Kamar tidak ditemukan!";
          state.kamarDipilih = -1;
        }
        break;
      case 4:
        state.halamanAktif = HAPUS_KAMAR;
        break; // MODIFIKASI: Menambahkan case untuk hapus
      case 0:
        break;
      default:
        state.pesanInfo = "Pilihan tidak valid!";
        break;
      }
    } else if (state.halamanAktif == LIHAT_DETAIL) {
      switch (pilihan) {
      case 1:
        checkOutPenghuni(state);
        break;
      case 0:
        state.halamanAktif = UTAMA;
        state.kamarDipilih = -1;
        break;
      default:
        state.pesanInfo = "Pilihan tidak valid!";
        break;
      }
    }
  } catch (const invalid_argument &e) {
    state.pesanInfo = "Input harus berupa angka!";
  }
}
} // namespace UseCase

// -- 5. MAIN APPLICATION LOOP --
int main() {
  AppState state;
  string input;

  while (true) {
    View::render(state);

    if (state.halamanAktif == UTAMA || state.halamanAktif == LIHAT_DETAIL) {
      cin >> input;
    }

    if (state.halamanAktif == UTAMA) {
      if (input == "0")
        break;
      UseCase::prosesInput(state, input);
    } else if (state.halamanAktif == TAMBAH_KAMAR) {
      UseCase::tambahKamar(state);
    } else if (state.halamanAktif == CHECK_IN) {
      UseCase::checkInPenghuni(state);
    } else if (state.halamanAktif == LIHAT_DETAIL) {
      UseCase::prosesInput(state, input);
    } else if (state.halamanAktif == HAPUS_KAMAR) {
      UseCase::hapusKamar(state);
    }
  }

  cout << "Program selesai. Terima kasih!\n";
  return 0;
}