#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

/*
 * Función para generar un cuadrado mágico de tamaño n x n.
 * Un cuadrado mágico es una matriz en la que la suma de los números
 * en cada fila, columna y diagonal es la misma.
 *
 * Parámetros:
 *   - n: Tamaño del cuadrado mágico (debe ser un número impar entre 1 y 9).
 */
void generarCuadradoMagico(int n)
{
    // Verificar que n sea un número impar entre 1 y 9
    if (n < 1 || n > 9 || n % 2 == 0)
    {
        cout << "Error: El tamano del cuadrado magico debe ser un numero impar entre 1 y 9." << endl;
        return;
    }

    // Crear una matriz de tamaño n x n inicializada con 0
    vector<vector<int>> cuadrado(n, vector<int>(n, 0));

    // Inicializar la posición del primer número
    int fila = 0;
    int columna = n / 2;

    // Llenar el cuadrado mágico con los números del 1 al n^2
    for (int numero = 1; numero <= n * n; numero++)
    {
        // Asignar el número actual a la posición actual
        cuadrado[fila][columna] = numero;

        // Calcular la nueva posición (moverse una fila arriba y una columna a la izquierda)
        int nuevaFila = (fila - 1 + n) % n;
        int nuevaColumna = (columna - 1 + n) % n;

        // Si la nueva posición ya está ocupada, moverse una fila hacia abajo
        if (cuadrado[nuevaFila][nuevaColumna] != 0)
        {
            fila = (fila + 1) % n;
        }
        else
        {
            fila = nuevaFila;
            columna = nuevaColumna;
        }
    }

    // Mostrar el cuadrado mágico
    cout << "\nCuadrado magico de tamano " << n << "x" << n << ":" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << cuadrado[i][j] << "\t";
        }
        cout << endl;
    }

    // Calcular y mostrar la suma mágica
    int sumaMagica = n * (n * n + 1) / 2;
    cout << "\nLa suma magica es: " << sumaMagica << endl;
}

/*
 * Función para verificar si una cadena es un número válido
 */
bool esNumeroValido(const string &s)
{
    return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}

/*
 * Función principal del programa.
 * Solicita al usuario el tamaño del cuadrado mágico y lo genera.
 */
int main()
{
    string entrada;
    int n;

    // Encabezado del programa
    cout << "=============================================" << endl;
    cout << "       Generador de Cuadrados Magicos" << endl;
    cout << "=============================================" << endl;
    cout << "Este programa genera un cuadrado magico de tamano n x n," << endl;
    cout << "donde n es un numero impar entre 1 y 9." << endl;
    cout << "Un cuadrado magico es una matriz en la que la suma de los" << endl;
    cout << "numeros en cada fila, columna y diagonal es la misma." << endl;
    cout << "=============================================" << endl;

    // Solicitar al usuario el tamaño del cuadrado mágico
    cout << "\nIngrese el tamano del cuadrado magico (n): ";
    getline(cin, entrada);

    // Eliminar espacios de la entrada
    entrada.erase(remove_if(entrada.begin(), entrada.end(), ::isspace), entrada.end());

    // Verificar que la entrada sea un número válido
    if (!esNumeroValido(entrada))
    {
        cout << "Error: Debe ingresar un numero entero valido." << endl;
        return 1;
    }

    // Convertir a entero
    n = stoi(entrada);

    // Generar y mostrar el cuadrado mágico
    generarCuadradoMagico(n);

    // Mensaje final
    cout << "\n=============================================" << endl;
    cout << "Gracias por usar el Generador de Cuadrados Magicos" << endl;
    cout << "=============================================" << endl;

    return 0;
}