#include <iostream>
using namespace std;

void tukar(int **nilai1, int **nilai2) {
    int temp = **nilai1;
    **nilai1 = **nilai2;
    **nilai2 = temp;
}

int main() {
    int nilai1 = 10, nilai2 = 20;
    int *pnilai1 = &nilai1;
    int *pnilai2 = &nilai2;
    int **ppnilai1 = &pnilai1;
    int **ppnilai2 = &pnilai2;

    cout << "Sebelum menukar: nilai1 = " << nilai1 << " dan nilai2 = " << nilai2 << endl;

    tukar(ppnilai1, ppnilai2);

    cout << "Sesudah menukar: nilai1 = " << nilai1 << " dan nilai2 = " << nilai2 << endl;

    return 0;
}
