#include <iostream>
#include <vector>

using namespace std;

int main() {

    // data input

    // number of different road signs
    int k;
    cin >> k;

    // dynamic array, containing signs
    vector<short> roadSigns(k);

    // total number of road signs
    int total = 0;

    // reading sings restrictions number in array
    for (int i = 0; i < k; i++) {
        cin >> roadSigns[i];
        total += roadSigns[i];
    }

    short max_index = 0, last_index = 0;
    // main loop
    while (total) {
        max_index = 0;
        if (last_index == 0) max_index = 1; // Костыль

        for (int j = 0; j < k; j++)
            if (last_index != j && roadSigns[j] >= roadSigns[max_index])
                max_index = j; // Находим новый индекс с максимальным значением

        if (roadSigns[max_index] == 0) max_index = last_index; // Если тут пусто, идем по новой
        roadSigns[max_index] -= 1; // Убираем использованный знак
        last_index = max_index; // Исключаем повторения

        // result output
        cout << max_index + 1 << ' ';

        total--;
    }
    return 0;
}