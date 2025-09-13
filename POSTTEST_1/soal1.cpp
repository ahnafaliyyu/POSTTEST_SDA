#include <iostream>
using namespace std; 

int angka[5];
int masuk;

int main(){
    for(int i=0; i<5; i++){
        cout << "Masukkan angka ke-" << i+1 << ": ";
        cin >> masuk;
        angka[i] = masuk * 3;
    }

    cout << "\nAngka yang dimasukkan adalah: ";
    for(int i=0; i<5; i++){
        cout << angka[i] << " ";
    }
    
    return 0;
}