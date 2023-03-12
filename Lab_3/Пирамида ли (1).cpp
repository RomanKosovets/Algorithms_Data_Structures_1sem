#include <fstream>


int main() {

    std::ifstream fin("isheap.in");
    std::ofstream fout("isheap.out");

    int n;
    fin >> n;
    int *array = new int [n + 1];
    for (int i = 1; i < n + 1; i++)
        fin >> array[i];

    for (int i = 1; i < n + 1; i++) {
        if (2 * i <= n && array[i] > array[2 * i]) {
            fout << "NO\n";
            return 0;
        }
        else if (2 * i + 1 <= n && array[i] > array[2 * i + 1]) {
            fout << "NO\n";
            return 0;
        }
    }

    fout << "YES\n";
    return 0;
}