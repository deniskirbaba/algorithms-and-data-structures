#### <div align="center"> [Задача 1207. Медиана на плоскости](https://acm.timus.ru/problem.aspx?space=1&num=1207) </div>

>Ограничение времени: 0.5 секунды
>Ограничение памяти: 64 МБ

###### Условие:

> На плоскости находятся *N* точек (*N* чётно). Никакие три точки не лежат на одной прямой. Ваша задача — выбрать две точки так, что прямая линия, проходящая через них, делит множество точек на две части одинакового размера.

###### Исходные данные:

> Первая строка содержит целое число *N* (4 ≤ *N* ≤ 10 000). Каждая из следующих *N* строк содержит пары целых чисел *xi*, *yi* (−10^6 ≤ *xi*, *yi* ≤ 10^6) — координаты *i*-й точки.

###### Результат:

> Выведите номера выбранных точек

| Исходные данные | Результат |
|-----------------|-----------|
| `4   `          | `1 4`     |
| `0 0 `          |           |
| `1 0  `         |           |
| `0 1 `          |           |
| `1 1 `          |           |

###### Описание алгоритма:

> Алгоритм решения задачи можно разбить на следующие части:
> 1. Запись входных данных в динамический массив, который хранит созданную структуру *Dot*, описывающая точку на плоскости (координаты, идентификатор, угол прямой проходящей через точку, а также метод для вычисления данного угла).
> 2. Поиск точки с минимальной координатой по оси oY и перемещение данного элемента в начало массива.
> 3. Проходя по всем элементам массива, вычисляем угол прямой проходящей через точку с минимальной координатой по оси oY (которая стоит в начале массива) и текущим элементом массива.
> 4. Затем отсортируем массив по возрастанию углов и игнорируя опорную выберем точку, расположенную в середине полученного массива.

В качестве алгоритма сортировки была выбрана "Быстрая сортировка". Метод основан на принципе "разделяй-и-властвуй".
Его общая схема такова:
1. из массива выбирается некоторый опорный элемент *a[i]*
2. запускается процедура разделения массива, которая перемещает все ключи, меньшие, либо равные *a[i]*, влево от него, а все ключи, большие, либо равные *a[i]* - вправо
3. теперь массив состоит из двух подмножеств, причем левое меньше, либо равно правого
![img.png](img.png)
4. для обоих подмассивов: если в подмассиве более двух элементов, рекурсивно запускаем для него ту же процедуру

###### Реализация:

```cpp
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define M_PI 3.14159265358979323846

// a structure for storing the coordinates of a point, its ordinal number,
// the angle of a straight line passing through this point, as well as the method for calculating the angle
struct Dot {
    // coordinates
    int x;
    int y;

    // ordinal number
    int id;

    // angle of a straight line
    double angle;

    // method for calculating the angle
    void calculateAngle(Dot minDot) {

        // if on one vertical line
        if (minDot.x == this->x) this->angle = M_PI/2;

        // if on one horizontal line
        else if (minDot.y == this->y) this->angle = 0;

        // calculation in other cases
        else this->angle = atan((double)(this->y - minDot.y)/(double)(this->x - minDot.x));

        // convert the angle to a range of positive numbers
        if (this->angle < 0) this->angle += 2 * M_PI;
    }
};

// just swapping dots function
void swap(Dot* first, Dot* second) {
    Dot buffer = *first;
    *first = *second;
    *second = buffer;
}

// my implementation of quick sort
void quickSort(vector<Dot> &dots, int left, int right) {

    int i = left, j = right;

    // pivot element
    double pivot = dots[(left + right) / 2].angle;

    // main loop
    while(i <= j) {
        while (dots[i].angle < pivot) i++;
        while (dots[j].angle > pivot) j--;
        if (i > j) break;
        swap(&dots[i], &dots[j]);
        i++;
        j--;
    }
    if (left < j) quickSort(dots, left, j);
    if (i < right) quickSort(dots, i, right);
}

int main() {

    // reading the number of points
    int n;
    cin >> n;

    // array containing points
    vector<Dot> dots(n);

    // minimum y dot
    Dot minDot = {1000001, 1000001, 0};

    // reading dots into array
    for (int i = 0; i < n; i++) {
        // saving coordinates
        cin >> dots[i].x >> dots[i].y;
        // saving id
        dots[i].id = i + 1;

        // choose the minimum y point
        if (dots[i].y < minDot.y or dots[i].y == minDot.y and dots[i].x < dots[minDot.id].x) {
            minDot.y = dots[i].y;
            minDot.id = i;
        }
    }

    // push min dot at the start of array
    swap(&dots[0], &dots[minDot.id]);

    // calculate angles relative to the min (first) dot
    for (int i = 1; i < n; i++) dots[i].calculateAngle(dots[0]);

    // sorting by ascending angle
    quickSort(dots, 1, n - 1);

    // result output - min dot and mean by angle dot
    cout << dots[0].id << " " << dots[n / 2].id << endl;

    return 0;
}
```

###### Подтверждение выполнения:
