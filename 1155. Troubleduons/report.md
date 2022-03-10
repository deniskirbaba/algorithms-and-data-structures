#### <div align="center"> [Задача 1155. Дуоны](https://acm.timus.ru/problem.aspx?space=1&num=1155) </div>

>Ограничение времени: 0.5 секунды
>Ограничение памяти: 64 МБ

###### Условие:

> *Архангел по науке докладывает:
> — Господи, эти физики там, внизу, — они открыли ещё одну элементарную частицу!
> — Хорошо, добавим параметр в Общее Уравнение Вселенной.*
>
> С развитием техники физики находят всё новые и новые элементарные частицы, с непонятными и даже загадочными свойствами. Многие слышали про мюоны, глюоны, странные кварки и прочую нечисть. Недавно были обнаружены элементарные частицы дуоны. Эти частицы названы так потому, что учёным удаётся создавать или аннигилировать их только парами. Кстати, от дуонов одни неприятности, поэтому от них стараются избавляться до начала экспериментов. Помогите физикам избавиться от дуонов в их установке.
>
> ![Problem illustration](https://acm.timus.ru/image/get.aspx/f3d327aa-1925-452e-be18-99973701b7a0)
>
> Экспериментальная установка состоит из восьми камер, которые расположены в вершинах куба. Камеры промаркированы латинскими буквами A, B, C, …, H. Технически возможно создать, или наоборот, аннигилировать, два дуона, находящихся в смежных камерах. Вам нужно автоматизировать процесс удаления дуонов из установки.

###### Исходные данные:

> В единственной строке даны восемь целых чисел в пределах от 0 до 100, описывающих количество дуонов в камерах установки (сначала в камере A, потом в B, и т.д.).

###### Результат:

> Выведите последовательность действий для удаления всех дуонов или слово «IMPOSSIBLE», если это невозможно. Каждое действие должно быть описано в отдельной строке, в следующем формате: маркер первой камеры, маркер второй (смежной с первой), далее плюс либо минус (создать или аннигилировать пару дуонов). Количество действий в последовательности не должно превосходить 1000.

| Исходные данные | Результат           |
| --------------- | ------------------- |
| 1 0 1 0 3 1 0 0 | EF- EA- AD+ AE- DC- |
| 0 1 0 1 2 3 2 2 | IMPOSSIBLE          |

###### Описание алгоритма:

>  Самым оптимальным способом найти пары смежных вершин для того, что бы свести суммарное колличество значений при каждой вершине (изначально от 0 до 800) к 0. Считываем значения вершин, проверяем на возможность аннигиляции дуонов. Если возможно - убираем пары простых вершин (занимает 1 операцию на две вершины), затем, когда не осталось простых смежны вершин, создаем дополнительную пару дуонов для аннигиляции двух несмежных вершин. Можно было бы реализовать алгоритм в массиве, однако это более сложно с точки зрения алгоритма. Реализация разделена на два цикла для того, что бы минимизировать количество операций (уменьшить количество созданий дуонов)

###### Реализация:

```cpp
#include <iostream>

int main() {

    // data input
    int a, b, c, d, e, f, g, h;
    std::cin >> a >> b >> c >> d >> e >> f >> g >> h;

    // annihilation impossibility condition - sum of the groups of adjacent duons aren't equal
    if ((a + h + f + c) != (e + d + g + b)) std::cout << "IMPOSSIBLE";
    else {

        // annihilation adjacent duons while it's possible
        bool annih_condition = true;
        while (annih_condition) {

            // vertex A
            if (a > 0 && b > 0) {
                a -= 1;
                b -= 1;
                std::cout << "AB-" << std::endl;
            }
            else if (a > 0 && d > 0) {
                a -= 1;
                d -= 1;
                std::cout << "AD-" << std::endl;
            }
            else if (a > 0 && e > 0) {
                a -= 1;
                e -= 1;
                std::cout << "AE-" << std::endl;
            }

            // vertex B
            else if (b > 0 && f > 0) {
                b -= 1;
                f -= 1;
                std::cout << "BF-" << std::endl;
            }
            else if (b > 0 && c > 0) {
                b -= 1;
                c -= 1;
                std::cout << "BC-" << std::endl;
            }

            // vertex C
            else if (c > 0 && g > 0) {
                c -= 1;
                g -= 1;
                std::cout << "CG-" << std::endl;
            }
            else if (c > 0 && d > 0) {
                c -= 1;
                d -= 1;
                std::cout << "CD-" << std::endl;
            }

            // vertex D
            else if (d > 0 && h > 0) {
                d -= 1;
                h -= 1;
                std::cout << "DH-" << std::endl;
            }

            // vertex E
            else if (e > 0 && f > 0) {
                e -= 1;
                f -= 1;
                std::cout << "EF-" << std::endl;
            }
            else if (e > 0 && h > 0) {
                e -= 1;
                h -= 1;
                std::cout << "EH-" << std::endl;
            }

            // vertex F
            else if (f > 0 && g > 0) {
                f -= 1;
                g -= 1;
                std::cout << "FG-" << std::endl;
            }

            // vertex G
            else if (g > 0 && h > 0) {
                g -= 1;
                h -= 1;
                std::cout << "GH-" << std::endl;
            }

            // if annihilation adjacent duons is not possible
            else annih_condition = false;
        }

        annih_condition = true;
        // annihilate the opposite vertices of the cube, for this we add duons between them
        while (annih_condition) {

            // vertices A and G
            if (a > 0 && g > 0) {
                std::cout << "EF+" << std::endl;
                e += 1;
                f += 1;
                std::cout << "AE-" << std::endl;
                a -= 1;
                e -= 1;
                std::cout << "FG-" << std::endl;
                f -= 1;
                g -= 1;
            }

            // vertices C and E
            else if (c > 0 && e > 0) {
                std::cout << "BF+" << std::endl;
                b += 1;
                f += 1;
                std::cout << "BC-" << std::endl;
                b -= 1;
                c -= 1;
                std::cout << "EF-" << std::endl;
                b -= 1;
                f -= 1;
            }

            // vertices B and H
            else if (b > 0 && h > 0) {
                std::cout << "EF+" << std::endl;
                e += 1;
                f += 1;
                std::cout << "BF-" << std::endl;
                b -= 1;
                f -= 1;
                std::cout << "EH-" << std::endl;
                e -= 1;
                h -= 1;
            }

            // vertices D and F
            else if (d > 0 && f > 0) {
                std::cout << "EH+" << std::endl;
                e += 1;
                h += 1;
                std::cout << "DH-" << std::endl;
                d -= 1;
                h -= 1;
                std::cout << "EF-" << std::endl;
                e -= 1;
                f -= 1;
            }

            // if annihilation the opposite vertices is not possible
            else annih_condition = false;
        }
    }

    return 0;
}

```

###### Подтверждение выполнения:
