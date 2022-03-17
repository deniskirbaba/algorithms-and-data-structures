#### <div align="center"> [Задача 1322. Шпион](https://acm.timus.ru/problem.aspx?space=1&num=1322) </div>

>Ограничение времени: 0.25 секунды
>Ограничение памяти: 64 МБ

###### Условие:

> Спецслужбы обнаружили действующего иностранного агента. Шпиона то есть. Установили наблюдение и выяснили, что каждую неделю он через Интернет посылает кому-то странные нечитаемые тексты. Чтобы выяснить, к какой информации получил доступ шпион, требуется расшифровать информацию. Сотрудники спецслужб проникли в квартиру разведчика, изучили шифрующее устройство и выяснили принцип его работы.
>
> На вход устройства подается строка текста S1 = s1s2...sN. Получив ее, устройство строит все циклические перестановки этой строки, то есть S2 = s2s3...sNs1, ..., SN = sNs1s2...sN-1. Затем множество строк S1, S2, ..., SN сортируется лексикографически по возрастанию. И в этом порядке строчки выписываются в столбец, одна под другой. Получается таблица размером N × N. В какой-то строке K этой таблицы находится исходное слово. Номер этой строки вместе с последним столбцом устройство и выдает на выход.
>
> Например, если исходное слово S1 = abracadabra, то таблица имеет такой вид:
>
> 1. aabracadabr = S11
> 2. abraabracad = S8
> 3. abracadabra = S1
> 4. acadabraabr = S4
> 5. adabraabrac = S6
> 6. braabracada = S9
> 7. bracadabraa = S2
> 8. cadabraabra = S5
> 9. dabraabraca = S7
> 10. raabracadab = S10
> 11. racadabraab = S3
>
> И результатом работы устройства является число 3 и строка rdarcaaaabb.
>
> Это все, что известно про шифрующее устройство. А вот дешифрующего устройства не нашли. Но поскольку заведомо известно, что декодировать информацию можно (а иначе зачем же ее передавать?), Вам предложили помочь в борьбе с хищениями секретов и придумать алгоритм для дешифровки сообщений. А заодно и реализовать дешифратор.

###### Исходные данные:

> В первой и второй строках находятся соответственно целое число и строка, возвращаемые шифратором. Длина строки и число не превосходят 100000. Строка содержит лишь следующие символы: a-z, A-Z, символ подчеркивания. Других символов в строке нет. Лексикографический порядок на множестве слов задается таким порядком символов:
>
> ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz
>
> Символы здесь выписаны в порядке возрастания.

###### Результат:

> Выведите декодированное сообщение в единственной строке
>

| Исходные данные | Результат     |
|-----------------|---------------|
| `3 `            | `abracadabra` |
| ` rdarcaaaabb`  |               |

###### Описание алгоритма:

> Реализованный алгоритм состоит из следующих частей:
1. Считываем строку в динамический массив *<vector>*, который хранит созданную структура *sequenceChar* (хранит *char symbol* и *int id*).  
2. Сортируем массив по алфавиту в порядке возрастания с сохранением порядка повторяющихся символов, используя функцию stale_sort.
3. Полученная строка совпадает со строкой, полученной перестановками и сортировкой исходной строки, а ряд индексов указывает на последовательность расстановки букв и место индекса следующей буквы
4. Выводим дешифрованную строку в цикле *for*

###### Реализация:

```cpp
#include <iostream>
#include <vector>

using namespace std;

// a structure for storing a symbol and its ordinal in a sequence
struct sequenceChar {
    char symbol;
    int id;
};

// comparator for lexical sorting
bool SequenceCharSort(const sequenceChar first, const sequenceChar second) {
    return first.symbol < second.symbol;
}

int main() {

    // word id input
    int n;
    cin >> n;
    n--;

    // array for storing elements (chars) of sequence
    vector<sequenceChar> sequence;

    int len = 0;
    char c;
    // loop reading element to end of line
    while (cin.get(c)) {

        // character input end condition
        if (len > 0 && (c == '\n' or c == '\r')) break;

        // if an " " meets
        else if (isspace(c)) continue;

        // creating and adding element in an array
        sequenceChar newChar = {c, len};
        sequence.push_back(newChar);

        len++;
    }

    // ascending sorting using self-made comparator
    stable_sort(sequence.begin(), sequence.end(), SequenceCharSort);

    int j = n; // starting element of the initial sequence

    // result output
    for (int i = 0; i < len; i++, j = sequence[j].id) cout << sequence[j].symbol;

    return 0;
}
```

###### Подтверждение выполнения:
