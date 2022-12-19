// laba7.2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

struct node
{
    int inf;
    struct node* next; // ссылка на следующий элемент 
};

int** createMatrix(int** g, int n);
void printMatrix(int** g, int n);
void freeMatrix(int** g, int n);
void dfs(int** g, int n, int v, int* visited);

node* push(int num, node* vertex);
node* pop(node* vertex);

int main()
{
    setlocale(LC_ALL, "");
    srand(time(NULL));
    int** g = NULL, n, * visited = NULL, v;
    node* vertex = NULL;

    cout << "Введите количество вершин для графа: ";
    cin >> n;

    g = createMatrix(g, n);
    printMatrix(g, n);

    cout << "Введите вершину для поиска: ";
    cin >> v;

    visited = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    dfs(g, n, v, visited);
    cout << endl;

    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    do {
        while (visited[v]) {
            v = vertex->inf;
            vertex = pop(vertex);
            if (!vertex) break;
        }
        if (!vertex && visited[v]) break;
        cout << v << " ";
        visited[v] = true;
        for (int i = n - 1; i >= 0; i--) {
            if (g[v][i] == 1) vertex = push(i, vertex);
        }
    } while (vertex);

    freeMatrix(g, n);
    free(visited);
}

void dfs(int** g, int n, int v, int* visited) {
    visited[v] = true;
    cout << v << " ";
    for (int i = 0; i < n; i++) {
        if (g[v][i] == 1 && !visited[i]) {
            dfs(g, n, i, visited);
        }
    }
}

int** createMatrix(int** g, int n) {
    g = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        *(g + i) = (int*)malloc(n * sizeof(int)); //выделяем память под значения столбцов
    }
    for (int i = 0; i < n; i++)  // цикл по строкам
    {
        for (int j = i; j < n; j++)  // цикл по столбцам строки
        {
            if (i == j) {
                *(*(g + i) + j) = 0;
            }
            else {
                *(*(g + i) + j) = rand() % 2;
                *(*(g + j) + i) = *(*(g + i) + j);
            }
        }
    }
    return g;
}

void printMatrix(int** g, int n) {
    cout << "  ";
    for (int i = 0; i < n; i++) {
        cout.width(3);
        cout << i;
    }
    cout << endl << endl;
    for (int i = 0; i < n; i++) {
        cout << i << " ";
        for (int j = 0; j < n; j++)
        {
            cout.width(3);
            cout << *(*(g + i) + j);
        }
        cout << endl;
    }
    cout << endl << endl;
}

void freeMatrix(int** g, int n) {
    for (int i = 0; i < n; i++) {
        free(*(g + i)); //освобождаем память
    }
    free(g); //освобождаем память
}

node* push(int num, node* vertex) {
    node* tmp = (node*)malloc(sizeof(node));
    if (vertex == NULL) {
        vertex = tmp;
        vertex->inf = num;
        vertex->next = NULL;
    }
    else {
        tmp->next = vertex;
        tmp->inf = num;
        vertex = tmp;
    }
    return vertex;
}

node* pop(node* vertex) {
    node* tmp = vertex;
    vertex = vertex->next;
    free(tmp);
    return vertex;
}