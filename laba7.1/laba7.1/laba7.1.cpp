// laba7.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

struct node
{
    int vertex;         //номер вершины
    struct node* next;  //ссылка на след. вершину
};
struct node* createNode(int);

struct Graph
{
    int numVertices;        //кол-во вершин
    int* visited;           //массив посещёных вершин
    struct node** adjLists; //массив на указатели, которые хранят адрес вершин
};
struct Graph* createGraph(int vertices);

void addEdge(struct Graph* graph, int src, int dest);
void printGraph(struct Graph* graph);
void fillGraph(struct Graph* graph, int** g, int n);
void freeMatrix(struct Graph* graph);
void dfs(struct Graph* graph, int vertex);

int** createMatrix(int** g, int n);
void printMatrix(int** g, int n);
void freeMatrix(int** g, int n);
void dfs(int** g, int n, int v, int* visited);

int main()
{
    setlocale(LC_ALL, "");
    srand(time(NULL));
    int** g = NULL, n, * visited = NULL, v;
    struct Graph* graph;

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

    graph = createGraph(n);
    fillGraph(graph, g, graph->numVertices);
    printGraph(graph);
    dfs(graph, v);
    cout << endl;

    freeMatrix(g, n);
    freeMatrix(graph);
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

// Алгоритм
void dfs(struct Graph* graph, int vertex) {
    struct node* adjList = graph->adjLists[vertex];
    struct node* temp = adjList;

    graph->visited[vertex] = 1;
    cout << vertex << " ";

    while (temp != NULL) {
        int connectedVertex = temp->vertex;

        if (graph->visited[connectedVertex] == 0) {
            dfs(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

// Создание вершины
struct node* createNode(int v) {
    struct node* newNode = (node*)malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Создание пустого графа
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = (node**)malloc(vertices * sizeof(struct node*));

    graph->visited = (int*)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

// Добавление ребра
void addEdge(struct Graph* graph, int src, int dest) {
    // Проводим ребро от начальной вершины ребра графа к конечной вершине ребра графа
    struct node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Проводим ребро из конечной вершины ребра графа в начальную вершину ребра графа
    //newNode = createNode(src);
    //newNode->next = graph->adjLists[dest];
    //graph->adjLists[dest] = newNode;
}

// Выводим граф
void printGraph(struct Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        struct node* temp = graph->adjLists[v];
        cout << endl << "Список смежности вершин " << v << endl;
        while (temp) {
            if (temp->next == NULL) {
                cout << temp->vertex;
            }
            else {
                cout << temp->vertex << ", ";
            }
            temp = temp->next;
        }
        cout << endl;
    }
    cout << endl;
}

//Заполнение графа
void fillGraph(struct Graph* graph, int** g, int n) {
    for (int i = 0; i < n; i++)  // цикл по строкам
    {
        for (int j = n - 1; j >= 0; j--)  // цикл по столбцам строки
        {
            if (*(*(g + i) + j) == 1) {
                addEdge(graph, i, j);
            }
        }
    }
}

//Освобождение памяти
void freeMatrix(struct Graph* graph) {
    struct node* temp1, * temp2;
    for (int i = 0; i < graph->numVertices; i++) {
        temp1 = graph->adjLists[i];
        temp2 = graph->adjLists[i];
        while (temp2)
        {
            temp1 = temp1->next;
            free(temp2);
            temp2 = temp1;
        }
    }
    free(graph); //освобождаем память
}