#### <div align="center"> [Задача 1067. Структура папок](https://acm.timus.ru/problem.aspx?space=1&num=1067) </div>

>Ограничение времени: 2.0 секунды
>Ограничение памяти: 64 МБ

###### Условие:

> Хакер Билл случайно потерял всю информацию с жесткого диска своего компьютера, и у него нет резервных копий его содержимого. Но он сожалеет не о потере самих файлов, а о потере очень понятной и удобной структуры папок, которую он создавал и сохранял в течение многих лет работы.
>
> К счастью, у Билла есть несколько копий списков папок с его жесткого диска. С помощью этих списков он смог восстановить полные пути к некоторым папкам (например, «WINNT\SYSTEM32\CERTSRV\CERTCO~1\X86»). Он поместил их все в файл, записав каждый найденный путь в отдельную строку.
>
> Напишите программу, которая восстановит структуру папок Билла и выведет ее в виде отформатированного дерева.

###### Исходные данные:

> Первая строка содержит целое число *N* – количество различных путей к папкам (1 ≤ *N* ≤ 500). Далее следуют *N* строк с путями к папкам. Каждый путь занимает одну строку и не содержит пробелов, в том числе, начальных и конечных. Длина каждого пути не превышает 80 символов. Каждый путь встречается в списке один раз и состоит из нескольких имен папок, разделенных обратной косой чертой («\»).
>
> Имя каждой папки состоит из 1-8 заглавных букв, цифр или специальных символов из следующего списка: восклицательный знак, решетка, знак доллара, знак процента, амперсанд, апостроф, открывающаяся и закрывающаяся скобки, знак дефиса, собаки, циркумфлекс, подчеркивание, гравис, открывающаяся и закрывающаяся фигурная скобка и тильда («**`!#$%&'()-@^_`{}~`**»).

###### Результат:

> Выведите отформатированное дерево папок. Каждое имя папки должно быть выведено в отдельной строке, перед ним должно стоять несколько пробелов, указывающих на глубину этой папки в иерархии. Подпапки должны быть перечислены в лексикографическом порядке непосредственно после их родительской папки; перед их именем должно стоять на один пробел больше, чем перед именем их родительской папки. Папки верхнего уровня выводятся без пробелов и также должны быть перечислены в лексикографическом порядке.

| Исходные данные                       | Результат     |
|---------------------------------------|---------------|
| `7`                                   | `GAMES`       |
| `WINNT\SYSTEM32\CONFIG`               | ` DRIVERS`    |
| `GAMES`                               | `HOME`        |
| `WINNT\DRIVERS`                       | `WIN`         |
| `HOME`                                | ` SOFT`       |
| `WIN\SOFT`                            | `WINNT`       |
| `GAMES\DRIVERS`                       | ` DRIVERS`    |
| `WINNT\SYSTEM32\CERTSRV\CERTCO~1\X86` | ` SYSTEM32`   |
| ``                                    | `  CERTSRV`   |
| ``                                    | `   CERTCO~1` |
| ``                                    | `    X86`     |
| ``                                    | `  CONFIG`    | 

###### Описание алгоритма:

> Создадим класс *Directory*. Он будет инкапсулировать методы создания, получения, вывода директорий.  
> У класса *Directory* единственное поле - *map<string, Directory*> directories* - это ассоциативный контейнер с автоматической сортировкой при добавлении. Ключом выступает имя каталога, а значением - ссылка на вложенные каталоги.  
> Получим из исходной строки fullPath строку name, представляющую полный путь к каталогу и часть имени, до первого вхождения.  
> Проверим, существует ли в текущем каталоге директория с именем name. Если нет - создадим, если есть - делаем её текущим каталогом и получим следующую часть fullPath.  
> Когда дерево для fullPath будет полностью заполнено, мы снова вернёмся в корень и повторим алгоритм.  
> В конце рекурсивно выведем папки пути наращивая на каждом уровне количество пробельных отступов.

###### Реализация:

```cpp
#include <iostream>
#include <string>
#include <sstream>
#include <map>

using std::cin, std::cout, std::map, std::string, std::stringstream;

class Directory {
private: map<string, Directory*> directories;
public:
    Directory() {}

    Directory* create(string name) {
        directories[name] = new Directory();
        return directories[name];
    }

    Directory* get(string name) { // check if there is a directory named *name* in the current directory
        if (directories.find(name) == directories.end()) return create(name); // if not, create
        else return directories[name]; // if there is, return part of the next level directory
    }

    void print(string separator = "") { // recursive output of the resulting structure
        string tabs = " ";
        tabs += separator; // incrementing the indent for the next iteration
        map<string, Directory*> contents(directories.begin(), directories.end()); // get current branch of the directory
        for (auto dir = contents.begin(); dir != contents.end(); dir++) { // go through tree
            cout << separator << dir->first << '\n'; // print margin and local root folder
            dir->second->print(tabs); // go next
        }
    }
};

int main() {
    uint16_t n;
    cin >> n;

    Directory* root = new Directory(); // create root directory
    for (uint16_t i = 0; i < n; i++) {
        Directory* currentDir = root; // За локальную дефолтную деректорию берем root
        string fullPath, name;
        cin >> fullPath;
        stringstream ss(fullPath); // extract data from the input stream
        while (getline(ss, name, '\\'))  // while there is a continuation of the path, we go further in the catalog
            currentDir = currentDir->get(name); // if it already exists, go to the next level, if not, create a new one
    }
    root->print(); // recursively print directory tree

    return 0;
}
```

###### Подтверждение выполнения:
<p align="center">
  <img width="1000" src="https://github.com/pivp/algorithms-and-data-structures/blob/c1b47d724ac8c2fa3ddb3ebf16ac7394164d5b25/1067.%20Disk%20Tree/timus.png">
</p>
