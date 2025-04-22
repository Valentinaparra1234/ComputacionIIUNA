#include <iostream>
using namespace std;
// Estructura para representar un nodo del árbol
struct Nodo
{
    int valor;
    Nodo *izquierdo;
    Nodo *derecho;
    // Constructor
    Nodo(int v) : valor(v), izquierdo(nullptr), derecho(nullptr) {}
};
// Función para insertar un valor en el árbol binario de búsqueda
Nodo *insertar(Nodo *raiz, int valor)
{
    if (raiz == nullptr)
    {
        return new Nodo(valor);
    }
    if (valor < raiz->valor)
    {
        raiz->izquierdo = insertar(raiz->izquierdo, valor);
    }
    else if (valor > raiz->valor)
    {
        raiz->derecho = insertar(raiz->derecho, valor);
    }
    return raiz;
}
// Función recursiva para buscar un nodo y determinar su grado
int Grado(Nodo *raiz, int valor)
{
    if (raiz == nullptr)
    {
        cout << "El valor " << valor << " no se encuentra en el arbol." << endl;
        return -1; // Valor no encontrado
    }
    if (raiz->valor == valor)
    {
        int grado = 0;
        if (raiz->izquierdo != nullptr)
            grado++;
        if (raiz->derecho != nullptr)
            grado++;
        return grado;
    }
    if (valor < raiz->valor)
    {
        return Grado(raiz->izquierdo, valor);
    }
    else
    {
        return Grado(raiz->derecho, valor);
    }
}
// Función principal
int main()
{
    Nodo *raiz = nullptr;
    // Insertar valores en el árbol
    raiz = insertar(raiz, 18);
    raiz = insertar(raiz, 11);
    raiz = insertar(raiz, 23);
    raiz = insertar(raiz, 7);
    raiz = insertar(raiz, 15);
    raiz = insertar(raiz, 20);
    raiz = insertar(raiz, 25);
    raiz = insertar(raiz, 13);
    // Número a buscar
    int numero;
    cout << "Ingrese el numero a buscar en el arbol: ";
    cin >> numero;
    // Buscar el número y determinar su grado
    int grado = Grado(raiz, numero);
    if (grado != -1)
    {
        cout << "El grado del nodo con valor " << numero << " es: " << grado << endl;
    }
    return 0;
}
