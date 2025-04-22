#include <iostream>
#include <vector>
#include <limits> // Para limpiar el buffer de entrada
using namespace std;

/*
 * Función para mostrar una lista.
 *
 * Parámetros:
 *   - lista: Vector que contiene los elementos de la lista.
 *   - nombre: Nombre de la lista (para identificarla al mostrarla).
 */
void mostrarLista(const vector<int> &lista, const string &nombre)
{
    cout << nombre << ": ";
    for (int elemento : lista)
    {
        cout << elemento << " ";
    }
    cout << endl;
}

/*
 * Función para intercalar dos listas en una tercera lista.
 *
 * Parámetros:
 *   - lista1: Inventario de la Sucursal A.
 *   - lista2: Inventario de la Sucursal B.
 *   - resultado: Inventario combinado (intercalado) de ambas sucursales.
 */
void intercalarListas(const vector<int> &lista1, const vector<int> &lista2, vector<int> &resultado)
{
    int tamano1 = lista1.size();
    int tamano2 = lista2.size();
    int maxSize = max(tamano1, tamano2);

    for (int i = 0; i < maxSize; i++)
    {
        if (i < tamano1)
        {
            resultado.push_back(lista1[i]);
        }
        if (i < tamano2)
        {
            resultado.push_back(lista2[i]);
        }
    }
}

/*
 * Función para calcular la resta de dos listas.
 *
 * Parámetros:
 *   - lista1: Inventario de la Sucursal A.
 *   - lista2: Inventario de la Sucursal B.
 *   - resultado: Diferencia de inventario (Sucursal A - Sucursal B).
 */
void restarListas(const vector<int> &lista1, const vector<int> &lista2, vector<int> &resultado)
{
    int tamano1 = lista1.size();
    int tamano2 = lista2.size();
    int maxSize = max(tamano1, tamano2);

    for (int i = 0; i < maxSize; i++)
    {
        int valor1 = (i < tamano1) ? lista1[i] : 0;
        int valor2 = (i < tamano2) ? lista2[i] : 0;
        resultado.push_back(valor1 - valor2);
    }
}

/*
 * Función para leer un valor entero con validación.
 * Muestra un mensaje de error si la entrada no es un número entero.
 */
int leerEntero()
{
    int valor;
    while (true)
    {
        cin >> valor;
        if (cin.fail()) // Si la entrada falla (no es un número)
        {
            cin.clear();                                         // Limpiar el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar la entrada incorrecta
            cout << "Error: Por favor ingrese solo numeros enteros. Intente nuevamente: ";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer
            return valor;
        }
    }
}

/*
 * Función principal del programa.
 */
int main()
{
    vector<int> inventarioSucursalA, inventarioSucursalB, inventarioCombinado, diferenciaInventario;
    int n, valor;

    // Ingresar el inventario de la Sucursal A
    cout << "Ingrese el numero de productos en la Sucursal A: ";
    n = leerEntero();
    cout << "Ingrese las cantidades de cada producto en la Sucursal A:" << endl;
    for (int i = 0; i < n; i++)
    {
        valor = leerEntero();
        inventarioSucursalA.push_back(valor);
    }

    // Ingresar el inventario de la Sucursal B
    cout << "Ingrese el numero de productos en la Sucursal B: ";
    n = leerEntero();
    cout << "Ingrese las cantidades de cada producto en la Sucursal B:" << endl;
    for (int i = 0; i < n; i++)
    {
        valor = leerEntero();
        inventarioSucursalB.push_back(valor);
    }

    // Mostrar los inventarios de ambas sucursales
    mostrarLista(inventarioSucursalA, "Inventario Sucursal A");
    mostrarLista(inventarioSucursalB, "Inventario Sucursal B");

    // Intercalar los inventarios de ambas sucursales
    intercalarListas(inventarioSucursalA, inventarioSucursalB, inventarioCombinado);
    mostrarLista(inventarioCombinado, "Inventario Combinado (Intercalado)");

    // Calcular la diferencia de inventario entre la Sucursal A y la Sucursal B
    restarListas(inventarioSucursalA, inventarioSucursalB, diferenciaInventario);
    mostrarLista(diferenciaInventario, "Diferencia de Inventario (Sucursal A - Sucursal B)");

    return 0;
}