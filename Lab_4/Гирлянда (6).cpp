#include <iostream>
#include <fstream>


int main() {

    std::ifstream fin("garland.in");
    FILE* fp = fopen("garland.out", "w+");

    int n;
    double high;
    fin >> n;
    fin >> high;

    double left = 0;
    double right = high;
    double last = -1;

    while (true) {
        double mid = (left + right) / 2;
        if (mid == left or mid == right) {
            break;
        }
        double prev = high; // предыдущее значение
        double cur = mid;   // текущее значение
        bool UP = cur > 0;  // true когда мид больше нуля
        for(int i = 3; i <= n; i++){
            double next = 2 * cur - prev + 2; // получаем по формуле высоту лампочки
            UP &= next > 0; // требуется чтобы все до были выше и следующий тоже был выше
            prev = cur;     // переприсваиваем текущее значение
            cur = next;     // переприсваиваем следующее значение
        }
        if (UP){            // если выше
            right = mid;    // оставляем только левую часть, чтоб найти минимальную высоту В
            last = cur;     // последний элемент
        }
        else {
            left = mid;     // иначе, если ниже, то берем правую часть
        }
    }
    fprintf(fp, "%.2f", last);
    return 0;
}
                            // в процессе такого поиска right обязательно понизится