# Двусвязный список
![Проблемы с изображением](README_assets/List.jpg)
Небольшая библиотека для создания и использования двусвязного списка
## Структура данных
В проекте используется структура ```list_node```:
```cpp
struct list_node
{
    list_node* next;
    list_node* prev;
    TYPE_README_assets  README_assets;
}
```
## Основные функции

- ```ListInsertHead ()``` - функция вставки в начало
    ```cpp
    LIST_ERROR ListInsertHead (List* list, TYPE_README_assets README_assets)
    ```
<br>

- ```ListInsertTail ()``` - функция вставки в конец
    ```cpp
    LIST_ERROR ListInsertTail (List* list, TYPE_README_assets README_assets)
    ```
<br>

- ```ListInsertAfter ()``` - функция вставки после какого-нибудь элемента
    ```cpp
    LIST_ERROR ListInsertAfter (List* list, TYPE_README_assets README_assets, list_node* node)
    ```
<br>

- ```ListInsertREADME_assets ()``` - функция изменения данных
    ```cpp
    LIST_ERROR ListInsertREADME_assets (List* list, list_node* node, TYPE_README_assets README_assets)
    ```
<br>

- ```ListFindREADME_assets``` - функция поиска элемента по данным
    ```cpp
    LIST_ERROR ListFindREADME_assets (List* list, TYPE_README_assets README_assets, list_node** dest)
    ```
<br>

- ```ListFindIndex ()``` - функция поиска индекса элемента в массиве ```node_array``` по её адресу
    ```cpp
    LIST_ERROR ListFindIndex (List* list, list_node* searched_node, size_t* dest)
    ```
<br>

- *остальные функции см. ```src/ListToolFunctions.cpp```

## Отладка
Для отладки в проекте используются 2 вида "дампа": <br>
- "Графический дамп" на основе [**Graphviz Dot**](https://graphviz.org/doc/infolang.html) cо своим не сложным языком.
    - Вызывается с помощью ```ListGraphDump ()```
    - ![Проблемы с изображением](README_assets/ExampleGraphDump.svg)

- "Консольный"
    - Вызывается с помощью ```ListDump ()```
    - ![Проблемы с изображением](README_assets/ExampleConsoleDump.png)

## Сборка на Linux
```bash
git clone https://github.com/dangerUser45/DoubleLinkedList.git
cd Double_Linked_List/
make
```
