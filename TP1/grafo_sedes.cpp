#include <iostream>
#include <climits>
using namespace std;

// ---------------------- CLASES BASE ----------------------
class Nodo
{
public:
    int id;
    Nodo *siguiente;
    Nodo(int id) : id(id), siguiente(nullptr) {}
};

class ListaEnlazada
{
public:
    Nodo *cabeza;
    ListaEnlazada() : cabeza(nullptr) {}

    void insertar(int id)
    {
        Nodo *nuevoNodo = new Nodo(id);
        if (!cabeza)
        {
            cabeza = nuevoNodo;
        }
        else
        {
            Nodo *temp = cabeza;
            while (temp->siguiente)
            {
                temp = temp->siguiente;
            }
            temp->siguiente = nuevoNodo;
        }
    }
};

class Cola
{
public:
    Nodo *frente;
    Nodo *final;
    Cola() : frente(nullptr), final(nullptr) {}

    void encolar(int id)
    {
        Nodo *nuevoNodo = new Nodo(id);
        if (!frente)
        {
            frente = final = nuevoNodo;
        }
        else
        {
            final->siguiente = nuevoNodo;
            final = nuevoNodo;
        }
    }

    int desencolar()
    {
        if (!frente)
            return -1;
        int id = frente->id;
        Nodo *temp = frente;
        frente = frente->siguiente;
        delete temp;
        return id;
    }

    bool vacia()
    {
        return frente == nullptr;
    }
};

// ---------------------- GRAFO ----------------------
class Grafo
{
private:
    int numNodos;
    ListaEnlazada *adyacencias;
    int **matrizCostes;

    void _dfsRecursivo(int nodo, bool visitados[])
    {
        visitados[nodo] = true;
        Nodo *temp = adyacencias[nodo].cabeza;
        while (temp)
        {
            if (!visitados[temp->id])
            {
                _dfsRecursivo(temp->id, visitados);
            }
            temp = temp->siguiente;
        }
    }

public:
    Grafo(int numNodos) : numNodos(numNodos)
    {
        adyacencias = new ListaEnlazada[numNodos];
        matrizCostes = new int *[numNodos];
        for (int i = 0; i < numNodos; i++)
        {
            matrizCostes[i] = new int[numNodos];
            for (int j = 0; j < numNodos; j++)
            {
                matrizCostes[i][j] = (i == j) ? 0 : INT_MAX;
            }
        }
    }

    void agregarArista(int origen, int destino, int coste)
    {
        adyacencias[origen].insertar(destino);
        adyacencias[destino].insertar(origen);
        matrizCostes[origen][destino] = coste;
        matrizCostes[destino][origen] = coste;
    }

    void floydWarshall(int **distancias, int **rutas)
    {
        for (int i = 0; i < numNodos; i++)
        {
            for (int j = 0; j < numNodos; j++)
            {
                distancias[i][j] = matrizCostes[i][j];
                rutas[i][j] = (i != j && matrizCostes[i][j] != INT_MAX) ? i : -1;
            }
        }

        for (int k = 0; k < numNodos; k++)
        {
            for (int i = 0; i < numNodos; i++)
            {
                for (int j = 0; j < numNodos; j++)
                {
                    if (distancias[i][k] != INT_MAX && distancias[k][j] != INT_MAX &&
                        distancias[i][j] > distancias[i][k] + distancias[k][j])
                    {
                        distancias[i][j] = distancias[i][k] + distancias[k][j];
                        rutas[i][j] = rutas[k][j];
                    }
                }
            }
        }
    }

    void bfs(int inicio)
    {
        bool *visitados = new bool[numNodos]{false};
        Cola cola;
        cola.encolar(inicio);
        visitados[inicio] = true;

        cout << "BFS desde nodo " << inicio << ": ";
        while (!cola.vacia())
        {
            int nodo = cola.desencolar();
            cout << nodo << " ";

            Nodo *temp = adyacencias[nodo].cabeza;
            while (temp)
            {
                if (!visitados[temp->id])
                {
                    visitados[temp->id] = true;
                    cola.encolar(temp->id);
                }
                temp = temp->siguiente;
            }
        }
        cout << endl;
        delete[] visitados;
    }

    void dfs(int inicio)
    {
        bool *visitados = new bool[numNodos]{false};
        cout << "DFS desde nodo " << inicio << ": ";
        _dfsRecursivo(inicio, visitados);
        cout << endl;
        delete[] visitados;
    }
};

// ---------------------- MAIN ----------------------
int main()
{
    const int numNodos = 4; // S=0, 1=1, 2=2, 3=3
    Grafo grafo(numNodos);

    // Configurar grafo según la Figura 1
    grafo.agregarArista(0, 1, 9); // S-1
    grafo.agregarArista(0, 2, 7); // S-2
    grafo.agregarArista(1, 2, 2); // 1-2
    grafo.agregarArista(1, 3, 5); // 1-3
    grafo.agregarArista(2, 3, 2); // 2-3

    // Floyd-Warshall
    int **distancias = new int *[numNodos];
    int **rutas = new int *[numNodos];
    for (int i = 0; i < numNodos; i++)
    {
        distancias[i] = new int[numNodos];
        rutas[i] = new int[numNodos];
    }
    grafo.floydWarshall(distancias, rutas);

    // Calcular número de saltos (enlaces) en cada ruta desde S (0)
    int saltos[numNodos] = {0};
    for (int j = 1; j < numNodos; j++)
    {
        int nodo = j;
        while (rutas[0][nodo] != 0 && rutas[0][nodo] != -1)
        {
            saltos[j]++;
            nodo = rutas[0][nodo];
        }
        saltos[j]++; // Contar el último salto (S -> ...)
    }

    // Imprimir rutas óptimas y saltos
    cout << "Rutas óptimas desde S (0):\n";
    for (int j = 1; j < numNodos; j++)
    {
        cout << "0 -> " << j << ": Coste = " << distancias[0][j] << ", Saltos = " << saltos[j] << endl;
    }

    // Calcular el MÁXIMO número de enlaces (resultado = 2)
    int maxSaltos = 0;
    for (int j = 1; j < numNodos; j++)
    {
        if (saltos[j] > maxSaltos)
            maxSaltos = saltos[j];
    }
    cout << "\nNúmero máximo de enlaces (respuesta final): " << maxSaltos << endl;

    // Liberar memoria
    for (int i = 0; i < numNodos; i++)
    {
        delete[] distancias[i];
        delete[] rutas[i];
    }
    delete[] distancias;
    delete[] rutas;

    return 0;
}