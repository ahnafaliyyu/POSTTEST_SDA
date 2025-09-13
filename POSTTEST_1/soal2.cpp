#include <iostream>
using namespace std;

int matriks[3][3];
int main() {
    cout << "Masukkan elemen matriks 3x3:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "Elemen [" << i + 1 << "][" << j + 1 << "]: ";
            cin >> matriks[i][j];
        }
    }
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            cout << matriks[i][j] << " ";
        }
        cout << "\n";
    }

    int diagonalutama=0;
    for (int i=0; i<3; i++){
        diagonalutama += matriks[i][i];
    }

    cout << "Jumlah diagonal utama: " << diagonalutama << endl;

    int diagonalsekunder=0;
    for (int i=0; i<3; i++){
        diagonalsekunder += matriks[i][2-i];
    }   
    cout << "Jumlah diagonal sekunder: " << diagonalsekunder << endl;
    return 0;
}
