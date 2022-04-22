#### <div align="center"> [Задача 1628. Белые полосы](https://acm.timus.ru/problem.aspx?space=1&num=1628) </div>

>Ограничение времени: 1.0 секунды
>Ограничение памяти: 64 МБ

###### Условие:

> У каждого неудачника в жизни бывают не только чёрные, но и белые полосы. Марсианин Вась-Вась отмечает в календаре, представляющем собой таблицу *m* × *n*, те дни, когда ему ужасно не повезло. Если Вась-Васю не повезло в *j*-й день *i*-й недели, то он закрашивает ячейку таблицы (*i*, *j*) в чёрный цвет. Все незакрашенные ячейки в таблице имеют белый цвет.
>
> Будем называть отрезками жизни прямоугольники размером 1 × *l* либо *l* × 1. Белыми полосами Вась-Вась считает все максимальные по включению белые отрезки таблицы. А сможете ли Вы определить, сколько всего белых полос было в жизни Вась-Вася?

###### Исходные данные:

> Первая строка содержит целые числа *m*, *n*, *k* — размеры календаря и количество неудачных дней в жизни Вась-Вася (1 ≤ *m*, *n* ≤ 30000; 0 ≤ *k* ≤ 60000). В следующих *k* строках перечислены неудачные дни в виде пар (*xi*, *yi*), где *xi* — номер недели, к которой относится неудачный день, а *yi* — номер дня в этой неделе (1 ≤ *xi* ≤ *m*; 1 ≤ *yi* ≤ *n*). Описание каждого неудачного дня встречается только один раз.

###### Результат:

> Выведите число белых полос в жизни Вась-Вася.

| Исходные данные | Результат |
|-----------------|-----------|
| `3 5 4`         | `8`       |
| `1 1 `          | ``        |
| `1 5`           | ` `       | 
| `2 2`           | ``        |
| `3 3`           | ``        |
| ``              | ``        |
| `5 1 2`         | `2`       |
| `2 1`           | ``        |
| `3 1`           | ``        |

###### Описание алгоритма:

> Создадим 2 динамических массива set-ов: *x[m]* - отсортированные координаты Y_cordinat соответствующие x[X_cordinat]  (ассоциация Y c X), и аналогичный *y[n]* (ассоциация X c Y).  
> *std::set* — ассоциативный контейнер, содержащий отсортированный набор уникальных объектов типа Key.  
> Затем каждую строку обоих массивов проверяем на наличие белых полос, если их длинна больше 1 - сразу выводим результат, если равна 1, то заменяем проверенную строчку на список координат одиночек.  
> Затем проверяем список одиночек в обоих обновленных массивах, и если одиночка является таковой в обоих массивах, то увеличиваем количество белых полос на 1, в противном случае игнорируем.  

###### Реализация:

```cpp
#include <iostream>
#include <set>
#include <vector>

using std::cin, std::cout, std::vector, std::set;

int res = 0;

set<uint16_t> count(const set<uint16_t>& collection, uint16_t maxSize) {
    uint16_t prev = 0;
    set<uint16_t> singleElements;
    for(uint16_t cur : collection){
        if (cur - prev > 2) res++; // if at least two whites in a row: res++
        else if (cur - prev == 2) singleElements.insert(cur - 1); // Otherwise, add to the cells-singles array
        prev = cur;
    }
    if (maxSize - prev > 1) res++; // if the last one is bad worth not extreme: res++
    else if (maxSize - prev == 1) singleElements.insert(maxSize); // If penultimate, then add to the cells-singles array
    return singleElements; // Now the output is an array of singles in a specific line / row
}

int main() {
    uint16_t m, n, k, x, y;
    cin >> m >> n >> k;

    // dynamic arrays with sorting
    vector<set<uint16_t>> blackX(m);
    vector<set<uint16_t>> blackY(n);

    while(k--){
        cin >> x >> y;
        blackX[x - 1].insert(y); // array х -> у
        blackY[y - 1].insert(x); // array y -> x
    }

    for(set<uint16_t>& setX : blackX) setX = count(setX, n); // counting stripes on x
    for(set<uint16_t>& setY : blackY) setY = count(setY, m); // counting stripes on y
    for (uint16_t i = 0; i < m; i++) for (uint16_t j : blackX[i]) // counting the cells-singles
            if (blackY[j - 1].find(i + 1) != blackY[j - 1].end()) res++;

    cout << res << '\n';

    return 0;
}
```

###### Подтверждение выполнения:
