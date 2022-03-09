#### <div align="center"> [Задача 1005. Куча камней](https://acm.timus.ru/problem.aspx?space=1&num=1005) </div>

>Ограничение времени: 1.0 секунды
>Ограничение памяти: 64 МБ

###### Условие:

> У вас есть несколько камней известного веса w1, …, wn. Напишите программу, которая распределит камни в две кучи так, что разность весов этих двух куч будет минимальной.

###### Исходные данные:

> Ввод содержит количество камней n (1 ≤ n ≤ 20) и веса камней w1, …, wn (1 ≤ wi ≤ 100 000) — целые, разделённые пробельными символами.

###### Результат:

> Ваша программа должна вывести одно число — минимальную разность весов двух куч. 

| Исходные данные   | Результат |
| ----------------- | :-------- |
| `5 5 8 13 27 14 ` | `3`       |

###### Описание алгоритма:

> Так как количество камней невелико, то мы можем провести полный перебор всех комбинаций (при 20-ти камнях получается *2^20 - 1 = 1048574* итераций). Так как количество куч равно двум, то при формировании комбинаций испольлзуем двоичное представление числа *2^n - 1* и будем пробегать все значения, начиная с 0 до *2^n - 2*. Для хранения весов камней использовалась структура *std::vector* - динамический массив (необходим динамический, так как мы не знали количество камней во время компиляции программы), элементы которого хранятся непрерывно, что означает, что доступ к элементам возможен не только через итераторы, но и с использованием смещений к обычным указателям на элементы.

###### Реализация:

```cpp
#include <iostream>
#include <vector>
#include <cmath>

int main() {

    /* input of initial data */

    int n;
    std::cin >> n;

    std::vector<int> w(n); // need dynamic array (don't know length during program compilation)
    for (int i = 0; i < n; i++) {
        std::cin >> w[i];
    }

    int result = n * 100000; // upper limit on the difference in the weights of two heaps

    /* realization */

    for (int combination = 0; combination < std::pow(2, n) - 1; combination++) { // enumeration of all possible combinations in two heaps

        int first_heap = 0;
        int second_heap = 0;

        for (int i = 0; i < n; i++) { // make heaps of stones by combination
            if (((combination >> i) & 1) == 0) first_heap += w[i];
            else second_heap += w[i];
        }

        int cur_difference = abs(first_heap - second_heap);

        if (cur_difference == 0) {
            result = 0;
            break;
        }
        if (cur_difference < result) result = cur_difference;
    }

    /* output of the answer */

    std::cout << result;

    return 0;
}

```

###### Подтверждение выполнения:

![timus_screen](https://user-images.githubusercontent.com/75897943/157456013-d5eadabb-66ee-447f-a4ba-bdfbe6045c95.png)
