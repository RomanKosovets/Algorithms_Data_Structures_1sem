#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void count_sort(vector<string> & a, int k){
    vector<int> count((int) 'z');

    for (auto & s : a){                         // Выведет все элементы из списка a. Он поочередно возьмет каждый элемент и выведет его
        count[s[k]]++;                          // Берем вертикально ряды с конца
    }

    int pos = 0;
    for (char i = 'a'; i <= 'z'; i++)
    {
        int add_pos = count[i];                 // считаем кол-во наших букв i
        count[i] = pos;
        pos = pos + add_pos;
    }

    vector<string> b(a.size());

    for (auto &s : a){                         //Выводит все элементы из списка a. Он поочередно возьмет каждый элемент и выведет его
        char d = s[k];
        b[count[d]++] = s;                     //сохраняем правильный порядок вывода
    }
    a = b;
}

void radix_sort(vector<string> & a, int m, int k){
    for (int i = 1; i <= k; i++)
    {
        count_sort(a, m - i);             // m-i так как индекс с нуля
    }
}

using namespace std;

int main()
{
    std::ifstream fin("radixsort.in");
    std::ofstream fout("radixsort.out");

    int n = 0, m =0, k = 0;
    fin >> n >> m >> k;

    vector<string> a(n);

    for (int i = 0; i < n; i++){
        fin >> a[i];
    }

    radix_sort(a, m, k);

    for (auto &s : a){                         // Выведет все элементы из списка a. Он поочередно возьмет каждый элемент и выведет его
        fout << s << '\n';
    }

    return 0;
}
