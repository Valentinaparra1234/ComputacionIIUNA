#include <iostream>
#include <climits> // Para usar INT_MAX
using namespace std;

// ---------------------- CLASE NODO ----------------------
// Representa un nodo individual con un ID y un puntero al siguiente (para listas o colas)
class Nodo
{
private:
    int id;
    Nodo *siguiente;

public:
    // Constructor
    Nodo(int id) : id(id), siguiente(NULL) {}

    // Getter del ID
    int getId() const { return id; }

    // Getter del puntero siguiente
    Nodo *getSiguiente() const { return siguiente; }

    // Setter del puntero siguiente
    void setSiguiente(Nodo *sig) { siguiente = sig; }
};

// ---------------------- CLASE LISTA ENLAZADA ----------------------
// Lista enlazada simple para almacenar adyacencias en el grafo
class ListaEnlazada
{
private:
    Nodo *cabeza; // Primer nodo de la lista

public:
    // Constructor
    ListaEnlazada() : cabeza(NULL) {}

    // Inserta un nuevo nodo al final de la lista
    void insertar(int id)
    {
        Nodo *nuevoNodo = new Nodo(id);
        if (cabeza == NULL)
        {
            cabeza = nuevoNodo;
        }
        else
        {
            Nodo *temp = cabeza;
            while (temp->getSiguiente())
            {
                temp = temp->getSiguiente();
            }
            temp->setSiguiente(nuevoNodo);
        }
    }

    // Devuelve el puntero al primer nodo
    Nodo *getCabeza() const
    {
        return cabeza;
    }
};

// ---------------------- CLASE COLA ----------------------
// Implementación de una cola FIFO usando nodos
class Cola
{
private:
    Nodo *frente; // Inicio de la cola
    Nodo *final;  // Final de la cola

public:
    Cola() : frente(NULL), final(NULL) {}

    // Agrega un elemento al final de la cola
    void encolar(int id)
    {
        Nodo *nuevoNodo = new Nodo(id);
        if (frente == NULL)
        {
            frente = final = nuevoNodo;
        }
        else
        {
            final->setSiguiente(nuevoNodo);
            final = nuevoNodo;
        }
    }

    // Remueve y devuelve el elemento del frente
    int desencolar()
    {
        if (frente == NULL)
            return -1;
        int id = frente->getId();
        Nodo *temp = frente;
        frente = frente->getSiguiente();
        delete temp;
        return id;
    }

    // Verifica si la cola está vacía
    bool vacia()
    {
        return frente == NULL;
    }
};

// ---------------------- CLASE GRAFO ----------------------
// Clase principal que representa un grafo no dirigido y ponderado
class Grafo
{
private:
    int numNodos;               // Número total de nodos
    ListaEnlazada *adyacencias; // Lista de adyacencias para cada nodo
    int **matrizCostes;         // Matriz de pesos (costes) entre nodos

    // Función recursiva auxiliar para el recorrido DFS
    void _dfsRecursivo(int nodo, bool visitados[])
    {
        visitados[nodo] = true;
        cout << nodo << " ";
        Nodo *temp = adyacencias[nodo].getCabeza();
        while (temp)
        {
            if (!visitados[temp->getId()])
            {
                _dfsRecursivo(temp->getId(), visitados);
            }
            temp = temp->getSiguiente();
        }
    }

public:
    // Constructor: inicializa matrices y listas
    Grafo(int numNodos) : numNodos(numNodos)
    {
        adyacencias = new ListaEnlazada[numNodos];
        matrizCostes = new int *[numNodos];
        for (int i = 0; i < numNodos; i++)
        {
            matrizCostes[i] = new int[numNodos];
            for (int j = 0; j < numNodos; j++)
            {
                matrizCostes[i][j] = (i == j) ? 0 : INT_MAX; // 0 en diagonal, infinito en el resto
            }
        }
    }

    // Agrega una arista entre dos nodos con un coste
    void agregarArista(int origen, int destino, int coste)
    {
        adyacencias[origen].insertar(destino);
        adyacencias[destino].insertar(origen); // grafo no dirigido
        matrizCostes[origen][destino] = coste;
        matrizCostes[destino][origen] = coste;
    }

    // Algoritmo de Floyd-Warshall para encontrar rutas más cortas entre todos los pares de nodos
    void floydWarshall(int **distancias, int **rutas)
    {
        // Inicializa distancias y rutas
        for (int i = 0; i < numNodos; i++)
        {
            for (int j = 0; j < numNodos; j++)
            {
                distancias[i][j] = matrizCostes[i][j];
                rutas[i][j] = (i != j && matrizCostes[i][j] != INT_MAX) ? i : -1;
            }
        }

        // Triple bucle para considerar todos los nodos intermedios
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

    // Imprime la ruta completa desde un nodo origen hasta un destino usando la matriz de rutas
    void imprimirRuta(int origen, int destino, int **rutas)
    {
        if (origen == destino)
        {
            cout << origen;
        }
        else if (rutas[origen][destino] == -1)
        {
            cout << "No hay ruta";
        }
        else
        {
            imprimirRuta(origen, rutas[origen][destino], rutas);
            cout << " -> " << destino;
        }
    }

    // Recorrido BFS desde un nodo de inicio
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

            Nodo *temp = adyacencias[nodo].getCabeza();
            while (temp)
            {
                if (!visitados[temp->getId()])
                {
                    visitados[temp->getId()] = true;
                    cola.encolar(temp->getId());
                }
                temp = temp->getSiguiente();
            }
        }
        cout << endl;
        delete[] visitados;
    }

    // Recorrido DFS desde un nodo de inicio
    void dfs(int inicio)
    {
        bool *visitados = new bool[numNodos]{false};
        cout << "DFS desde nodo " << inicio << ": ";
        _dfsRecursivo(inicio, visitados);
        cout << endl;
        delete[] visitados;
    }

    // Destructor: libera memoria
    ~Grafo()
    {
        for (int i = 0; i < numNodos; i++)
        {
            delete[] matrizCostes[i];
        }
        delete[] matrizCostes;
        delete[] adyacencias;
    }
};

// ---------------------- FUNCIÓN PRINCIPAL ----------------------
int main()
{
    const int numNodos = 4; // Nodos: S=0, 1=1, 2=2, 3=3
    Grafo grafo(numNodos);

    // Agregar aristas con sus respectivos costes
    grafo.agregarArista(0, 1, 9); // S-1
    grafo.agregarArista(0, 2, 7); // S-2
    grafo.agregarArista(1, 2, 2); // 1-2
    grafo.agregarArista(1, 3, 5); // 1-3
    grafo.agregarArista(2, 3, 2); // 2-3

    // Reservar memoria para matrices de distancias y rutas
    int **distancias = new int *[numNodos];
    int **rutas = new int *[numNodos];
    for (int i = 0; i < numNodos; i++)
    {
        distancias[i] = new int[numNodos];
        rutas[i] = new int[numNodos];
    }

    // Ejecutar Floyd-Warshall
    grafo.floydWarshall(distancias, rutas);

    // Calcular número de saltos desde S a cada nodo
    int saltos[numNodos] = {0};
    for (int j = 1; j < numNodos; j++)
    {
        int nodo = j;
        while (rutas[0][nodo] != 0 && rutas[0][nodo] != -1)
        {
            saltos[j]++;
            nodo = rutas[0][nodo];
        }
        saltos[j]++;
    }

    // Mostrar rutas desde nodo 0 a todos los demás
    cout << "Rutas óptimas desde S (0):\n";
    for (int j = 1; j < numNodos; j++)
    {
        cout << "0 -> " << j << ": Coste = " << distancias[0][j]
             << ", Saltos = " << saltos[j] << ", Ruta: ";
        grafo.imprimirRuta(0, j, rutas);
        cout << endl;
    }

    // Determinar y mostrar el máximo número de enlaces
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
