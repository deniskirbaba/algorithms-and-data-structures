#### <div align="center"> [Задача 1650. Миллиардеры](https://acm.timus.ru/problem.aspx?space=1&num=1650) </div>

>Ограничение времени: 3.0 секунды
>Ограничение памяти: 64 МБ

###### Условие:

> Возможно, вы знаете, что из всех городов мира больше всего миллиардеров живёт в Москве. Но, поскольку работа миллиардера подразумевает частые перемещения по всему свету, в определённые дни какой-то другой город может занимать первую строчку в таком рейтинге. Ваши приятели из ФСБ, ФБР, MI5 и Шин Бет скинули вам списки перемещений всех миллиардеров за последнее время. Ваш работодатель просит посчитать, сколько дней в течение этого периода каждый из городов мира был первым по общей сумме денег миллиардеров, находящихся в нём.

###### Исходные данные:

> В первой строке записано число *n* — количество миллиардеров (1 ≤ *n* ≤ 10000). Каждая из следующих *n* строк содержит данные на определённого человека: его имя, название города, где он находился в первый день данного периода, и размер состояния. В следующей строке записаны два числа: *m* — количество дней, о которых есть данные (1 ≤ *m* ≤ 50000), *k* — количество зарегистрированных перемещений миллиардеров (0 ≤ *k* ≤ 50000). Следующие *k* строк содержат список перемещений в формате: номер дня (от 1 до *m* − 1), имя человека, название города назначения. Вы можете считать, что миллиардеры путешествуют не чаще одного раза в день, и что они отбывают поздно вечером и прибывают в город назначения рано утром следующего дня. Список упорядочен по возрастанию номера дня. Все имена и названия городов состоят не более чем из 20 латинских букв, регистр букв имеет значение. Состояния миллиардеров лежат в пределах от 1 до 100 миллиардов.

###### Результат:

> В каждой строке должно содержаться название города и, через пробел, количество дней, в течение которых этот город лидировал по общему состоянию миллиардеров, находящихся в нём. Если таких дней не было, пропустите этот город. Города должны быть отсортированы по алфавиту (используйте обычный порядок символов: ABC...Zabc...z).



###### Описание алгоритма:

> Разделим алгоритм на 2 части:  
1. Формирование всех необходимых структур и массивов данных  
2. Заполнение структур и массивов теми данными, которые получены в первой части программы  
> Суть заполнения - последовательное считывание дорожной карты миллиардеров и их перебрасывание из одного города в другой, с соответствующим обновлением рейтинга городов по капиталу в силу его изменения из-за перемещения миллиардера.  
> В конце достаточно просто пройтись по всем городам из топа, отсортировать их в алфавитном порядке и вывести результат.  

###### Реализация:

```cpp
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <iostream>
#include <functional> // Для сортировки в set

using std::cin, std::cout, std::pair, std::string, std::unordered_map, std::map, std::greater, std::set;

struct City {
    string name;
    uint64_t money{};
    int days{}; // days in top
};

struct Person {
    City* city;
    uint64_t money;
};

int main()
{
    City cities[60000];
    Person persons[10000];
    unordered_map<string, Person*> namePerson;
    map<string, City*> nameCity;
    set<pair<uint64_t , City*>, greater<>> topCity; // sorting cities by money

    uint16_t n, m, k, count; cin >> n;
    m, k, count = 0;

    uint64_t money;

    string curPersonName, curCityName;

    for(uint16_t i = 0; i < n; i++) { // cycle reading the names of billionaires, cities and states on day 0
        cin >> curPersonName >> curCityName >> money;
        namePerson[curPersonName] = &persons[i]; // add person
        if(!nameCity[curCityName]) nameCity[curCityName] = &cities[count++]; // if there is no such city yet, add
        persons[i] = (Person){nameCity[curCityName], money}; // fill out the person info
        nameCity[curCityName]->name = curCityName; // add city name
        nameCity[curCityName]->money += money; // sum the money
    }
    for(const auto& city : nameCity) // add cities to the toCity array
        topCity.insert({city.second->money, city.second });

    uint16_t prevDay = 0, day;
    string name, place;
    cin >> m >> k;

    while(true) {
        bool finished = (!(cin >> day >> curPersonName >> place)); // while we can read go ahead
        if(finished) day = m; // to prevent premature exit from the loop

        if(day != prevDay) { // if day continue
            auto top1 = topCity.begin(); // first city at the top now
            auto top2 = top1++; // second city at the top now (if sums are equals)
            if(top1 == topCity.end() or top2->first > top1->first) // if only one day or the first day is superior to the second
                top2->second->days += day - prevDay; // increase the number of days of the top city by the time difference
        }
        if(finished) break; // leave if there are no more cities
        if(!nameCity[place]) { // if there was no such city
            nameCity[place] = &cities[count++]; // add this city
            nameCity[place]->name = place;
        }

        { // updating
            auto nextPlace = nameCity[place]; // city name
            auto person = namePerson[curPersonName]; // person name
            auto prevPlace = person->city;
            auto prevMoney = prevPlace->money;
            { // transferring a person from one city to another
                topCity.erase({prevMoney, prevPlace}); // delete from old
                prevPlace->money -= person->money; // decrease the money
                topCity.insert({prevPlace->money, prevPlace}); // add to the new city
                topCity.erase({nextPlace->money, nextPlace}); // remove the old top city
                nextPlace->money += person->money; // recalculate the money
                topCity.insert({nextPlace->money, nextPlace}); // correct the money of the new city
                person->city = nextPlace; // change the location
                prevDay = day;
            }
        }
    }

    map<string, int> result; // output with sorting

    for (auto& r : topCity) if (r.second->days) // if was at top at least once
        result.insert(make_pair(r.second->name, r.second->days)); // add to the result
    for (auto& o : result) cout << o.first << " " << o.second << "\n"; // output

    return 0;
}
```

###### Подтверждение выполнения:
