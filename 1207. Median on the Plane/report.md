#### <div align="center"> [Задача 1207. Медиана на плоскости](https://acm.timus.ru/problem.aspx?space=1&num=1207) </div>

>Ограничение времени: 0.5 секунды
>Ограничение памяти: 64 МБ

###### Условие:

> На плоскости находятся *N* точек (*N* чётно). Никакие три точки не лежат на одной прямой. Ваша задача — выбрать две точки так, что прямая линия, проходящая через них, делит множество точек на две части одинакового размера.

###### Исходные данные:

> Первая строка содержит целое число *N* (4 ≤ *N* ≤ 10 000). Каждая из следующих *N* строк содержит пары целых чисел *xi*, *yi* (−10^6 ≤ *xi*, *yi* ≤ 10^6) — координаты *i*-й точки.

###### Результат:

> Выведите номера выбранных точек

| Исходные данные      | Результат |
| -------------------- | --------- |
| `4 0 0 1 0 0 1 1 1 ` | `1 4`     |

###### Интерпретация задачи:

>  Выбрать две точки так, что прямая линия, проходящая через них, делит множество точек на две части одинакового размера.

###### Описание алгоритма:

>  Создаем структуру для хранения информации о точке и расчета угла прямой проходящей черз эту точку. Чтобы прямая линия прошла через две точки и поделила множество оставшихся точек на две равные полуплоскости, нам для начала нужно выбрать опорную точку, которую примем за начало координат. Возьмём минимальную по OX или OY точку и примем за опорную, и рассчитаем углы всех векторов, проведенных из опорной точки к каждой остальной. Затем отсортируем массив по возрастанию углов и игнорируя опорную выберем точку, расположенную в середине полученного массива.

###### Реализация:

```cpp
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
#define PI 3.141592653589793238462643383279502884197169399375105820974

struct Point {
    int x, y;
    short number;
    double angle;
    void calcAngle(Point zero) {
        if (zero.x == this->x) this->angle = PI/2; // Если dY == 0;
        else if (zero.y == this->y) this->angle = 0; // Если dX == 0;
        else this->angle = atan((double)(this->y - zero.y)/(double)(this->x - zero.x)); // ПРосто рассчет угла
        if (this->angle < 0) this->angle += 2 * PI; // Если угол отрицательный - вносим в диапазон положительных чисел
    }
};

void swap(Point* a, Point* b) {
	Point t = *a;
	*a = *b;
	*b = t;
}

void quickSort(vector<Point> &vec, int left, int right) {
    int i = left, j = right;
    double pivot = vec[(left + right) / 2].angle;
    while(i <= j) {
        while (vec[i].angle < pivot) i++;
        while (vec[j].angle > pivot) j--;
        if (i > j) break;
        swap(&vec[i], &vec[j]);
        i++;
        j--;
    }
    if (left < j) quickSort(vec, left, j);
    if (i < right) quickSort(vec, i, right);
}

int main() {
    short n; cin >> n; // Считывание количества точек
    vector<Point> points(n); // Массив точек
    pair<int, int> minPoint = make_pair(2000000, 0); // Минимальная точка по X или Y
    
    for (short i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y; // Заполняем массив точек
        points[i].number = i + 1; // Задаем номер каждой точке в соответствии с порядком считывания
        if (points[i].y < minPoint.first or points[i].y == minPoint.first and points[i].x < points[minPoint.second].x) {
            minPoint.first = points[i].y;
            minPoint.second = i;
        } // Выбираем минимальную по x или y точку
    }
    
    swap(&points[0], &points[minPoint.second]); // Ставим минимальную точку в начало
    for (int i = 1; i < n; i++) points[i].calcAngle(points[0]); // Рассчитываем угол относительно начальной точки
    quickSort(points, 1, n - 1); // Сортируем по возрастанию угла
    cout << points[0].number << " " << points[n / 2].number << endl; // Искомые точки - минимальная и средняя по углу
    return 0;
}
```

###### Подтверждение выполнения:

![image-20220214040150940](C:\Users\User\AppData\Roaming\Typora\typora-user-images\image-20220214040150940.png)