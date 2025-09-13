#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

struct Mahasiswa {
    string nama;
    string nim;    // gunakan string agar NIM dengan leading zero tetap aman
    double ipk;
};

int main() {
    Mahasiswa mhs[5];
    for (int i = 0; i < 5; i++) {
        cout << "Masukkan data mahasiswa ke-" << (i + 1) << ":\n";
        cout << "Nama: ";
        cin>>mhs[i].nama;
        cout << "NIM: ";
        cin>> mhs[i].nim;
        cout << "IPK: ";
        cin >> mhs[i].ipk;
    }
    int ipktinggi = 0;
    for (int i = 1; i < 5; i++) {
        if (mhs[i].ipk > mhs[ipktinggi].ipk) {
            ipktinggi = i;
        }
    }
    cout << "\nMahasiswa dengan IPK tertinggi:\n";
    cout << "Nama: " << mhs[ipktinggi].nama << "\n";
    cout << "NIM: " << mhs[ipktinggi].nim << "\n";
    cout << "IPK: " << mhs[ipktinggi].ipk << "\n";
    

    return 0;
}
