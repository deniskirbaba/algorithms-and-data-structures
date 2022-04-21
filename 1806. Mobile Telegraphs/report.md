#### <div align="center"> [Задача 1806. Мобильные телеграфы](https://acm.timus.ru/problem.aspx?space=1&num=1806) </div>

>Ограничение времени: 3.0 секунды
>Ограничение памяти: 64 МБ

###### Условие:

> Каждому бойцу 25-й стрелковой дивизии выдали новейшее средство связи — мобильный телеграф. С его помощью можно отправлять телеграммы командованию и боевым товарищам прямо на поле битвы. К сожалению, конструкция телеграфов ещё далека от совершенства — передавать сообщения можно только между некоторыми парами телеграфов.
>
> Каждому устройству присвоен уникальный номер — строка из десяти десятичных цифр. С телеграфа *a* можно отправить сообщение на телеграф *b* только в том случае, если из номера *a* можно получить номер *b*, изменив в нём ровно одну цифру либо поменяв в нём две цифры местами. Время передачи сообщения с телеграфа *a* на телеграф *b* зависит от длины наибольшего общего префикса их номеров — чем больше его длина, тем быстрее передаётся сообщение.
>
> Во время очередного сражения Анка из своей хорошо замаскированной позиции увидела небольшую группу белых, пытающуюся обойти обороняющихся красноармейцев с тыла. Какое минимальное время понадобится на доставку этой информации от Анки до Чапаева по телеграфу, возможно, с помощью других красноармейцев?

###### Исходные данные:

> В первой строке записано целое число *n* (2 ≤ *n* ≤ 50000) — количество бойцов в дивизии. Во второй строке через пробел в порядке невозрастания записаны десять целых чисел в пределах от 1 до 10000 — время передачи сообщения с одного телеграфа на другой при длине общего префикса их номеров, равной нулю, единице, двум, …, девяти. Далее идут *n* строк, содержащие номера телеграфов, выданных бойцам дивизии. Номер телеграфа Анки указан первым, а номер телеграфа Чапаева — последним. Все номера телеграфов попарно различны.

###### Результат:

> Если передать Чапаеву сообщение нельзя, выведите в единственной строке «-1». В противном случае в первой строке выведите минимальное время, за которое можно доставить сообщение. Во второй строке выведите количество бойцов, которые поучаствуют в его доставке, а в третьей строке выведите через пробел их номера в порядке от Анки к Чапаеву. Бойцы 25-й дивизии занумерованы числами от 1 до *n* в том порядке, в котором описаны номера их мобильных телеграфов на входе. Если существует несколько способов передать сообщение за минимальное время, выведите любой из них.

| Исходные данные             | Результат   |
|-----------------------------|-------------|
| `5`                         | `211`       |
| `100 10 10 10 1 1 1 1 1 1`  | `5`         |
| `9123493342`                | `1 2 4 3 5` |
| `3123493942`                |             |
| `9223433942`                |             |
| `3223493942`                |             |
| `9223433945`                |             |

| Исходные данные         | Результат |
|-------------------------|-----------|
| `2`                     | `-1`      |
| `1 1 1 1 1 1 1 1 1 1`   |           |
| `0123493342`            |           |
| `0223433945`            |           |

###### Описание алгоритма:

> Для представления телеграфа отдельного бойца используется структура *telegraphNUmber*, в которой содержатся идентификатор, номер телеграфа, массив с идентификаторами контактов и временем пересылки сообщения.  
> В начале происходит считывание информации и заполнение исходной информацией массива *soldierBook*.  
> Для поиска минимального пути от первого до последнего бойца используется алгоритм Дейкстры.  
> 

###### Реализация:

```cpp
#include <iostream>
#include <vector>

using namespace std;

// struct that represents the soldier's telegraph
// it contains id, telegraph number and array of the available contacts with transmission time
struct telegraphNumber {
    int id;
    int number[10];
    vector<vector<int>> contacts; // contacts[0] - contact id, contacts[1] - transmission time
};

// a function that returns the time of transmission of a message from one fighter to another,
// if the transmission is not possible, return 0
int getTransmissionTime(const vector <vector<int>>& contacts, int id) {
    for (vector<int> contact : contacts) {
        if (contact[0] == id) return contact[1];
    }
    return 0;
}

int main() {

    // input number of soldiers
    int n;
    cin >> n;

    // input times of transmission of a message from one telegraph to another
    // with the length of the common prefix of their numbers equal to zero, one, two, ..., nine
    int time[10];
    for (int & i : time) cin >> i;

    // dynamic array that contains telegraphs numbers
    vector<telegraphNumber> soldierBook(n);

    // fill the soldiers telegraphs numbers array
    uint64_t buffer;
    for (int i = 0; i < n; i++) {
        cin >> buffer;

        // write to array number by one digit
        for (int j = 9; j > -1; j--) {
            soldierBook[i].number[j] = buffer % 10;
            buffer /= 10;
        }
        soldierBook[i].id = i;

        if (soldierBook.size() == 1) continue;

        // fill the contacts
        int mismatchCounter;
        vector<int> mismatchPositions;
        int transmissionSpeed;
        for (int j = 0; j < soldierBook.size(); j++) {
            // counting the mismatches and calculation of message transmission time depending on number prefix
            mismatchCounter = 0;
            mismatchPositions.clear();
            bool firstMismatch = true;
            for (int k = 0; k < 10; k++) {
                if (soldierBook[i].number[k] != soldierBook[j].number[k]) {
                    if (firstMismatch) {
                        transmissionSpeed = time[k];
                        firstMismatch = false;
                    }
                    mismatchCounter += 1;
                    mismatchPositions.push_back(k);
                }
            }
            // condition for sending a message
            if (mismatchCounter == 1 || ((mismatchCounter == 2) &&
                                         (soldierBook[i].number[mismatchPositions[0]] == soldierBook[j].number[mismatchPositions[1]]) &&
                                         (soldierBook[i].number[mismatchPositions[1]] == soldierBook[j].number[mismatchPositions[0]]))) {
                soldierBook[j].contacts.push_back({i, transmissionSpeed});
                soldierBook[i].contacts.push_back({j, transmissionSpeed});
            }
        }
    }

    // Dijkstra's algorithm

    vector <int> minDistances(n);
    vector <int> visitedVertices(n);
    int minIndex;
    int minWeight;
    int temp;

    // initialize vertices and distances
    for (int i = 0; i < n; i++)
    {
        minDistances[i] = 10000;
        visitedVertices[i] = 1;
    }
    minDistances[0] = 0; // initial vertex

    do {
        minIndex = 10000;
        minWeight = 10000;
        for (int i = 0; i < n; i++)
        { // if vertex isn't visited and its weight less than minWeight
            if ((visitedVertices[i] == 1) && (minDistances[i] < minWeight))
            { // rewrite values
                minWeight = minDistances[i];
                minIndex = i;
            }
        }
        // add found minWeight to the current vertex weight and compare with current minWeight of vertex
        if (minIndex != 10000)
        {
            for (int i = 0; i < n; i++)
            {
                if (getTransmissionTime(soldierBook[minIndex].contacts, i) > 0)
                {
                    temp = minWeight + getTransmissionTime(soldierBook[minIndex].contacts, i);
                    if (temp < minDistances[i])
                    {
                        minDistances[i] = temp;
                    }
                }
            }
            visitedVertices[minIndex] = 0;
        }
    } while (minIndex < 10000);

    /*
    // output soldier book info
    cout << '\n' << '\n';
    for (int i = 0; i < n; i++) {
        cout << "id: " << soldierBook[i].id << '\n';

        cout << "number: ";
        for (int j : soldierBook[i].number) {
            cout << j;
        }
        cout << '\n';

        cout << "contacts: ";
        for (vector<int> contact : soldierBook[i].contacts) {
            cout << "{id: " << contact[0] << ", time: " << contact[1] << "} ";
        }

        cout << '\n' << '\n';
    }
    */

    // finding the transmission path
    if (minDistances[n-1] != 10000) {
        vector <int> ver(n); // array of visited vertices
        int end = n - 1; // index of the final vertex
        ver[0] = end + 1; // starting element - final vertex
        int k = 1; // index of the prev vertex
        int weight = minDistances[end]; // weight of the final vertex

        while (end != 0) // until reach the final vertex
        {
            for (int i = 0; i < n; i++) // looking through all vertices
                if (getTransmissionTime(soldierBook[i].contacts, end) != 0) // if connection is exists
                {
                    int temp = weight - getTransmissionTime(soldierBook[i].contacts, end); // define the weight from prev vertex
                    if (temp == minDistances[i]) // if weight is equal with calculated, it means that from this peak there was a transition
                    {
                        weight = temp; // save new weight
                        end = i;       // save prev vertex
                        ver[k] = i + 1;
                        k++;
                    }
                }
        }

        // output result
        cout << minDistances[n-1] << '\n'; // min transmission time
        cout << ver.size() << '\n'; // the number of fighters who will participate in its delivery
        // path output (starting vertex is at the end of an array of k elements)
        for (int i = k - 1; i >= 0; i--) cout << ver[i] << ' ';
    }
    else cout << -1;

    return 0;
}
```

###### Подтверждение выполнения:

