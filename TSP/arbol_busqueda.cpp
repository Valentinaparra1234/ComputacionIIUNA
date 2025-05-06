#include <iostream>
using namespace std;

// Estructura que representa un nodo de un Árbol Binario de Búsqueda
struct Nodo
{
    int valor;
    Nodo *izquierdo;
    Nodo *derecho;

    Nodo(int v)
    {
        valor = v;
        izquierdo = NULL;
        derecho = NULL;
    }
};

// Clase que encapsula la lógica del Árbol Binario
class ArbolBinario
{
private:
    Nodo *raiz;

    // Método recursivo para insertar
    Nodo *insertar(Nodo *nodo, int valor)
    {
        if (nodo == NULL)
        {
            return new Nodo(valor);
        }
        if (valor < nodo->valor)
        {
            nodo->izquierdo = insertar(nodo->izquierdo, valor);
        }
        else if (valor > nodo->valor)
        {
            nodo->derecho = insertar(nodo->derecho, valor);
        }
        return nodo;
    }

    // Método recursivo para buscar el grado de un nodo
    int grado(Nodo *nodo, int valor)
    {
        if (nodo == NULL)
        {
            cout << "El valor " << valor << " no se encuentra en el arbol." << endl;
            return -1;
        }
        if (nodo->valor == valor)
        {
            int g = 0;
            if (nodo->izquierdo != NULL)
                g++;
            if (nodo->derecho != NULL)
                g++;
            return g;
        }
        else if (valor < nodo->valor)
        {
            return grado(nodo->izquierdo, valor);
        }
        else
        {
            return grado(nodo->derecho, valor);
        }
    }

    // Recorrido en orden
    void inOrden(Nodo *nodo)
    {
        if (nodo != NULL)
        {
            inOrden(nodo->izquierdo);
            cout << nodo->valor << " ";
            inOrden(nodo->derecho);
        }
    }

public:
    ArbolBinario()
    {
        raiz = NULL;
    }

    void insertar(int valor)
    {
        raiz = insertar(raiz, valor);
    }

    int obtenerGrado(int valor)
    {
        return grado(raiz, valor);
    }

    void visualizar()
    {
        cout << "Valores del arbol (ordenados): ";
        inOrden(raiz);
        cout << endl;
    }
};

// Función para validar si una cadena es un número entero positivo
bool esNumeroValido(string entrada)
{
    if (entrada.length() == 0)
        return false;
    for (int i = 0; i < entrada.length(); i++)
    {
        if (entrada[i] < '0' || entrada[i] > '9')
        {
            return false;
        }
    }
    return true;
}

// Función principal
int main()
{
    ArbolBinario arbol;

    // Insertar valores en el árbol
    arbol.insertar(18);
    arbol.insertar(11);
    arbol.insertar(23);
    arbol.insertar(7);
    arbol.insertar(15);
    arbol.insertar(20);
    arbol.insertar(25);
    arbol.insertar(13);

    // Mostrar los valores del árbol
    arbol.visualizar();

    string entrada;
    string opcion;
    int numero;

    do
    {
        cout << "Ingrese un numero entero para calcular su grado en el arbol: ";
        cin >> entrada;

        // Validar entrada
        while (!esNumeroValido(entrada))
        {
            cout << "Entrada invalida. Ingrese un numero entero positivo: ";
            cin >> entrada;
        }

        // Convertir a entero
        numero = atoi(entrada.c_str());

        // Calcular y mostrar grado
        int g = arbol.obtenerGrado(numero);
        if (g != -1)
        {
            cout << "El grado del nodo con valor " << numero << " es: " << g << endl;
        }

        // Preguntar si desea continuar
        cout << "¿Desea buscar otro numero? (S/N): ";
        cin >> opcion;

        // Validar respuesta
        while (opcion != "S" && opcion != "s" && opcion != "N" && opcion != "n")
        {
            cout << "Opcion invalida. Ingrese 'S' para continuar o 'N' para salir: ";
            cin >> opcion;
        }

    } while (opcion == "S" || opcion == "s");

    cout << "Programa finalizado. Gracias por usar el sistema." << endl;

    return 0;
}
