#include <iostream>
#include <cstdlib> // Para atoi
#define NULL 0

using namespace std;

// ============================================
// Estructura nodo para lista enlazada simple
// ============================================
struct Nodo
{
    int dato;
    Nodo *siguiente;
};

// Clase Lista Enlazada para almacenar datos del cuadrado
class ListaEnlazada
{
private:
    Nodo *cabeza;

public:
    ListaEnlazada()
    {
        cabeza = NULL;
    }

    void insertarFinal(int valor)
    {
        Nodo *nuevo = new Nodo;
        nuevo->dato = valor;
        nuevo->siguiente = NULL;

        if (cabeza == NULL)
        {
            cabeza = nuevo;
        }
        else
        {
            Nodo *actual = cabeza;
            while (actual->siguiente != NULL)
            {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
    }

    void mostrarLista()
    {
        Nodo *actual = cabeza;
        cout << "\nElementos en la lista enlazada: ";
        while (actual != NULL)
        {
            cout << actual->dato << " ";
            actual = actual->siguiente;
        }
        cout << endl;
    }

    ~ListaEnlazada()
    {
        Nodo *actual = cabeza;
        while (actual != NULL)
        {
            Nodo *temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }
};

// ============================================
// Clase CuboMagico con encapsulamiento
// ============================================
class CuboMagico
{
private:
    int matriz[9][9];    // Matriz fija de 9x9
    ListaEnlazada lista; // Lista enlazada para almacenar los valores

public:
    // Método para llenar el cuadrado mágico
    void llenarCuboMagico(int n)
    {
        // Inicializar la matriz con ceros
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                matriz[i][j] = 0;
            }
        }

        int fila = 0;
        int columna = n / 2;

        for (int num = 1; num <= n * n; num++)
        {
            matriz[fila][columna] = num;
            lista.insertarFinal(num); // Guardar en lista enlazada

            int nuevaFila = (fila - 1 + n) % n;
            int nuevaColumna = (columna - 1 + n) % n;

            if (matriz[nuevaFila][nuevaColumna] != 0)
            {
                fila = (fila + 1) % n;
            }
            else
            {
                fila = nuevaFila;
                columna = nuevaColumna;
            }
        }
    }

    // Método para visualizar el cuadrado mágico
    void visualizarCuboMagico(int n)
    {
        cout << "\nCuadrado magico de tamano " << n << "x" << n << ":\n";
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << matriz[i][j] << "\t";
            }
            cout << "\n";
        }

        int sumaMagica = n * (n * n + 1) / 2;
        cout << "\nLa suma magica es: " << sumaMagica << "\n";

        lista.mostrarLista(); // Mostrar los elementos también en la lista
    }
};

// ============================================
// Función para verificar si la entrada es válida
// ============================================
bool esNumeroValido(char entrada[])
{
    int i = 0;
    if (entrada[0] == '\0')
        return false;
    while (entrada[i] != '\0')
    {
        if (entrada[i] < '0' || entrada[i] > '9')
            return false;
        i++;
    }
    return true;
}

// ============================================
// Función principal del programa
// ============================================
int main()
{
    char entrada[10];
    int n;

    // Encabezado del programa
    cout << "=============================================\n";
    cout << "       Generador de Cuadrados Magicos\n";
    cout << "=============================================\n";
    cout << "Este programa genera un cuadrado magico de tamano n x n,\n";
    cout << "donde n es un numero impar entre 1 y 9.\n";
    cout << "Un cuadrado magico es una matriz en la que la suma de los\n";
    cout << "numeros en cada fila, columna y diagonal es la misma.\n";
    cout << "=============================================\n";

    // Entrada del usuario
    cout << "\nIngrese el tamano del cuadrado magico (n): ";
    cin.getline(entrada, 10);

    // Validación
    if (!esNumeroValido(entrada))
    {
        cout << "Error: Debe ingresar un numero entero valido.\n";
        return 1;
    }

    n = atoi(entrada);

    if (n < 1 || n > 9 || n % 2 == 0)
    {
        cout << "Error: El tamano debe ser un numero impar entre 1 y 9.\n";
        return 1;
    }

    // Crear objeto y ejecutar métodos
    CuboMagico cubo;
    cubo.llenarCuboMagico(n);
    cubo.visualizarCuboMagico(n);

    cout << "\n=============================================\n";
    cout << "Gracias por usar el Generador de Cuadrados Magicos\n";
    cout << "=============================================\n";

    return 0;
}