#### <div align="center"> [Задача 1162. Currency Exchange](https://acm.timus.ru/problem.aspx?space=1&num=1162) </div>

>Ограничение времени: 1.0 секунды
>Ограничение памяти: 64 МБ

###### Условие:

> В нашем городе работает несколько пунктов обмена валюты. Предположим, что каждая точка специализируется на двух конкретных валютах и осуществляет обменные операции только с этими валютами. Может быть несколько точек, специализирующихся на одной и той же паре валют. Каждая точка имеет свои собственные обменные курсы, обменный курс A к B - это количество B, которое вы получаете за 1A. Также каждый обменный пункт имеет определенную комиссию, сумму, которую вы должны заплатить за свою обменную операцию. Комиссия всегда взимается в валюте источника.
>
> Например, если вы хотите обменять 100 долларов США на российские рубли в пункте обмена, где обменный курс составляет 29,75, а комиссия составляет 0,39, вы получите (100 - 0,39) * 29,75 = 2963,3975руб.
>
> Вы наверняка знаете, что в нашем городе существует N различных валют, с которыми вы можете иметь дело. Давайте присвоим каждой валюте уникальное целое число от 1 до N. Затем каждый пункт обмена может быть описан 6 числами: целыми A и B - номерами валют, которые он обменивает, и реальными RAB, CAB, RBA и CBA - обменными курсами и комиссиями при обмене A на B и B на A соответственно.
>
> У Ника есть немного денег в валюте S, и он задается вопросом, может ли он каким-то образом, после некоторых обменных операций, увеличить свой капитал. Конечно, в конце концов он хочет получить свои деньги в валюте S. Помогите ему ответить на этот трудный вопрос. Ник всегда должен иметь неотрицательную сумму денег при совершении своих операций.

###### Исходные данные:

> Первая строка содержит четыре числа: N - количество валют, M - количество обменных пунктов, S - количество валют, которыми располагает Ник, и V - количество единиц валюты, которыми он располагает. Следующие M строк содержат по 6 номеров каждая - описание соответствующего пункта обмена - в указанном выше порядке. Числа разделяются одним или несколькими пробелами. 1 ≤ S ≤ N ≤ 100, 1 ≤ M ≤ 100, V - действительное число, 0 ≤ V ≤ 10^3.
>
> Для каждого пункта обменные курсы и комиссии являются реальными, указаны не более чем с двумя цифрами после запятой, 10^-2 ≤ курс ≤ 10^2, 0 ≤ комиссия ≤ 10^ 2.
>
> Назовем некоторую последовательность операций обмена простой, если в этой последовательности ни одна точка обмена не используется более одного раза. Вы можете предположить, что соотношение числовых значений сумм в конце и в начале любой простой последовательности операций обмена будет меньше 10^4.

###### Результат:

> Если Ник может увеличить свое богатство, выведите "ДА", в другом случае выведите "НЕТ".

| Исходные данные        | Результат |
|------------------------|-----------|
| `3 2 1 10.0`           | `NO`      |
| `1 2 1.0 1.0 1.0 1.0`  | ``        |
| `2 3 1.1 1.0 1.1 1.0`  | ``        |
| `3 2 1 20.0`           | `YES`     |
| `1 2 1.0 1.0 1.0 1.0`  | ``        |
| `2 3 1.1 1.0 1.1 1.0 ` | ``        |

###### Описание алгоритма:

> Сохраняем информацию о каждом обменном пункте в массив структур в виде двух элементов - прямой и обратной конвертации.  
> Каждая структура содержит номера изначальной, целевой валют, а также курс обмена и комиссию.  
> В дополнительный массив сохраняется максимум, который можно получить обменом первоначальной валюты в i-ой валюте.  

###### Реализация:

```cpp
#include <iostream>
#include <vector>

using std::cin, std::vector, std::cout, std::max;

struct exchangePoint
{
    uint8_t a, b;
    double r, c;
};

int main()
{
    uint8_t n, m, s;
    double v;
    cin >> n >> m >> s >> v;

    vector<exchangePoint> exchangePoints;

    vector<double> profit(n + 1, 0.000);
    profit[s] = v;

    uint8_t a, b;
    double rab, cab, rba, cba;

    for (uint8_t i = 0; i < m; i++) {
        cin >> a >> b >> rab >> cab >> rba >> cba;
        exchangePoints.push_back({a, b, rab, cab}); // direct convert
        exchangePoints.push_back({b, a, rba, cba}); // inverse convert
    }

    for (uint8_t i = 0; i < n - 1; i++) for (auto & exPoint : exchangePoints) {
            profit[exPoint.b] = max((profit[exPoint.a] - exPoint.c) * exPoint.r, profit[exPoint.b]);
        } // choosing the most profitable point of currency exchange for the i-th and the result of the exchange

    for (auto & exPoint : exchangePoints) if ((profit[exPoint.a] - exPoint.c) * exPoint.r > profit[exPoint.b]) {
            cout << "YES" << '\n'; // if we can get profit
            return 0;
        }

    cout << "NO" << '\n';

    return 0;
}
```

###### Подтверждение выполнения:
