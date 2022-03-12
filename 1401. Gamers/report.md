#### <div align="center"> [Задача 1401. Игроки](https://acm.timus.ru/problem.aspx?space=1&num=1401) </div>

>Ограничение времени: 2.0 секунды
>Ограничение памяти: 64 МБ

###### Условие:

> Известно, что господин Чичиков зарабатывал свой капитал и таким способом: он спорил со всякими недотёпами, что сможет доказать, что квадратную доску размера 512 × 512 нельзя замостить следующими фигурами:
>
> ```
> X      XX       X       XX 
> XX      X      XX        X
> ```
>
> и всегда выигрывал. Однако один из недотёп оказался не так уж глуп, и сказал, что сможет замостить такими фигурами доску размера 512 × 512 без правой верхней клетки. Чичиков, не подумав, ляпнул, что он вообще может любую доску размера 2^n × 2^n без одной произвольной клетки замостить такими фигурами. Слово за слово, они поспорили. Чичиков чувствует, что сам он не докажет свою правоту. Помогите же ему!

###### Исходные данные:

> В первой строке записано целое число *n* (1 ≤ *n* ≤ 9). Во второй строке через пробел даны два целых числа *x*, *y*: координаты «выколотой» клетки доски (1 ≤ *x*, *y* ≤ 2^n), *x* — номер строки, *y* — номер столбца. Левый верхний угол доски имеет координаты (1, 1).

###### Результат:

> Ваша программа должна выдать 2^n строчек по 2^n чисел в каждой строке. На месте выбитой клетки должно стоять число 0. На месте остальных клеток должны стоять числа от 1 до (2^2*n* − 1) / 3 — номер фигуры, закрывающей данную клетку. Разумеется, одинаковые номера должны образовывать фигуры. Если же такую доску нельзя покрыть фигурами, выведите «−1».

| Исходные данные | Результат |
|-----------------|-----------|
| `2`             | `0 1 3 3` |
| `1 1`           | `1 1 4 3` |
|                 | `2 4 4 5` |
|                 | `2 2 5 5` |

###### Описание алгоритма:

> Используемый алгоритм состоит из следующих частей:
> 1. Представляем поле в виде двумерного динамического массива структуры *vector<vector<int>>*. В данный массив записываются числа, которые обозначают различные фигуры. Для удобства будем использовать координаты левой верхней точки не (1; 1) как в условии, а (0; 0).
> 2. Далее будем выполнять рекурсивную функцию, которая делит поле на 4 равных, но размера 2^(n-1) и на стыке полей в том секторы где нет пустоты размещается угловая фигура, это выполняется пока размер секторов не станет 2х2.
> 3. В конце программы выводится результат размещения

###### Реализация:

```cpp
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void play(vector<vector<int>> &gameBoard, int xEmptyDot, int yEmptyDot, int xLeftUpperDot, int yLeftUpperDot, int n) {

    // figure id
    static int c; c++;

    // calculate the position of the empty point in the coordinates of a smaller square
    int xEmptyRel = xEmptyDot - yLeftUpperDot;
    int yEmptyRel = yEmptyDot - xLeftUpperDot;

    // dimensionality reduction
    n = n / 2;

    // calculation of coordinates of the separated sectors closest to the center
    int xRightLowerCenter = xLeftUpperDot + n,      yRightLowerCenter = yLeftUpperDot + n;
    int xLeftLowerCenter = xLeftUpperDot + n - 1,   yLeftLowerCenter = yLeftUpperDot + n;
    int xRightUpperCenter = xLeftUpperDot + n,      yRightUpperCenter = yLeftUpperDot + n - 1;
    int xLeftUpperCenter = xLeftUpperDot + n - 1,   yLeftUpperCenter  = yLeftUpperDot + n - 1;

    // if an empty dot at right lower sector
    if (xEmptyRel >= n and yEmptyRel >= n) {

        // build a corner figure in the central part, except for the right lower sector
        gameBoard[xLeftLowerCenter][yLeftLowerCenter] = c;
        gameBoard[xRightUpperCenter][yRightUpperCenter] = c;
        gameBoard[xLeftUpperCenter][yLeftUpperCenter] = c;

        // dimensionality limit 2x2
        if (n > 1) {
            // using recursion
            play(gameBoard, xEmptyDot, yEmptyDot, xRightLowerCenter, yRightLowerCenter, n);
            play(gameBoard, yLeftLowerCenter, xLeftLowerCenter, xLeftUpperDot,  yLeftLowerCenter, n);
            play(gameBoard, yRightUpperCenter, xRightUpperCenter, xRightUpperCenter, yLeftUpperDot,  n);
            play(gameBoard, yLeftUpperCenter, xLeftUpperCenter, xLeftUpperDot,  yLeftUpperDot,  n);
        }
    }
        // if an empty dot at left lower sector
    else if (xEmptyRel >= n and yEmptyRel < n) {

        // build a corner figure in the central part, except for the left lower sector
        gameBoard[xRightLowerCenter][yRightLowerCenter] = c;
        gameBoard[xRightUpperCenter][yRightUpperCenter] = c;
        gameBoard[xLeftUpperCenter][yLeftUpperCenter] = c;

        // dimensionality limit 2x2
        if (n > 1) {
            // using recursion
            play(gameBoard, yRightLowerCenter, xRightLowerCenter, xRightLowerCenter, yRightLowerCenter, n);
            play(gameBoard, xEmptyDot,  yEmptyDot,  xLeftUpperDot,  yLeftLowerCenter, n);
            play(gameBoard, yRightUpperCenter, xRightUpperCenter, xRightUpperCenter, yLeftUpperDot,  n);
            play(gameBoard, yLeftUpperCenter, xLeftUpperCenter, xLeftUpperDot,  yLeftUpperDot,  n);
        }
    }
        // if an empty dot at right upper sector
    else if (xEmptyRel < n and yEmptyRel >= n) {

        // build a corner figure in the central part, except for the right upper sector
        gameBoard[xRightLowerCenter][yRightLowerCenter] = c;
        gameBoard[xLeftLowerCenter][yLeftLowerCenter] = c;
        gameBoard[xLeftUpperCenter][yLeftUpperCenter] = c;

        // dimensionality limit 2x2
        if (n > 1) {
            // using recursion
            play(gameBoard, yRightLowerCenter, xRightLowerCenter, xRightLowerCenter, yRightLowerCenter, n);
            play(gameBoard, yLeftLowerCenter, xLeftLowerCenter, xLeftUpperDot,  yLeftLowerCenter, n);
            play(gameBoard, xEmptyDot,  yEmptyDot,  xRightUpperCenter, yLeftUpperDot,  n);
            play(gameBoard, yLeftUpperCenter, xLeftUpperCenter, xLeftUpperDot,  yLeftUpperDot,  n);
        }
    }
        // if an empty dot at left upper sector
    else  if (xEmptyRel < n and yEmptyRel < n) {

        // build a corner figure in the central part, except for the left upper sector
        gameBoard[xRightLowerCenter][yRightLowerCenter] = c;
        gameBoard[xLeftLowerCenter][yLeftLowerCenter] = c;
        gameBoard[xRightUpperCenter][yRightUpperCenter] = c;

        // dimensionality limit 2x2
        if (n > 1) {
            // using recursion
            play(gameBoard, yRightLowerCenter, xRightLowerCenter, xRightLowerCenter, yRightLowerCenter, n);
            play(gameBoard, yLeftLowerCenter, xLeftLowerCenter, xLeftUpperDot,  yLeftLowerCenter, n);
            play(gameBoard, yRightUpperCenter, xRightUpperCenter, xRightUpperCenter, yLeftUpperDot,  n);
            play(gameBoard,  xEmptyDot,  yEmptyDot, xLeftUpperDot,  yLeftUpperDot,  n);
        }
    }
    return;
}

int main() {

    // data input
    int n, xEmptyDot, yEmptyDot;
    cin >> n >> yEmptyDot >> xEmptyDot;

    // calculate n
    n = pow(2, n);

    // left upper coords (1; 1) -> (0; 0)
    int xLeftUpperDot, yLeftUpperDot;
    xLeftUpperDot = 0; yLeftUpperDot = 0;
    xEmptyDot--; yEmptyDot--;

    // creating game board
    vector<vector<int>> gameBoard(n, (vector<int>(n)));

    // recursive function that arranges the pieces by dividing the board into 4 equal squares until we get the size 4x4
    play(gameBoard, xEmptyDot, yEmptyDot, xLeftUpperDot, yLeftUpperDot, n);

    // result table output
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << gameBoard[i][j] << " ";
        cout << endl;
    }

    return 0;
}
```

###### Подтверждение выполнения:
