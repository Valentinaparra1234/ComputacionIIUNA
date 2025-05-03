#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <cmath>
#include <cctype>

using namespace std;

// Constantes para el tamaño de la lista y los valores mínimo y máximo
const int TAMANIO_LISTA = 999;      // Número de elementos en la lista
const float VALOR_MINIMO = 0.0f;    // Valor mínimo para generar números
const float VALOR_MAXIMO = 2000.0f; // Valor máximo para generar números

// Clase Nodo que representa cada elemento de la lista enlazada
class Nodo
{
public:
    float valor;                                     // Valor del nodo
    Nodo *siguiente;                                 // Puntero al siguiente nodo en la lista
    Nodo(float val) : valor(val), siguiente(NULL) {} // Constructor del nodo
};

// Clase ListaEnlazada que maneja la lista de nodos
class ListaEnlazada
{
private:
    Nodo *cabeza; // Puntero al primer nodo de la lista
    int tamanio;  // Tamaño de la lista

    // Función auxiliar para obtener el último nodo de la lista
    Nodo *obtenerUltimo(Nodo *nodo)
    {
        // Recorre la lista hasta encontrar el último nodo
        while (nodo && nodo->siguiente)
        {
            nodo = nodo->siguiente;
        }
        return nodo; // Retorna el último nodo encontrado
    }

    // Función que realiza la partición para el algoritmo de QuickSort
    Nodo *particion(Nodo *primero, Nodo *ultimo, Nodo **nuevaPrimero, Nodo **nuevaUltimo)
    {
        Nodo *pivote = ultimo; // El pivote es el último nodo de la lista
        Nodo *anterior = NULL;
        Nodo *actual = primero;
        Nodo *cola = pivote; // Cola para manejar el último nodo

        // Reorganiza la lista de manera que los nodos menores que el pivote estén a su izquierda
        // y los mayores a su derecha
        while (actual != pivote)
        {
            if (actual->valor < pivote->valor) // Si el valor es menor que el pivote
            {
                if (*nuevaPrimero == NULL)
                {
                    *nuevaPrimero = actual; // Establece el primer nodo
                }
                anterior = actual;
                actual = actual->siguiente;
            }
            else // Si el valor es mayor o igual que el pivote
            {
                if (anterior)
                {
                    anterior->siguiente = actual->siguiente; // Elimina el nodo de la lista
                }
                Nodo *temp = actual->siguiente; // Mueve el nodo a la cola
                actual->siguiente = NULL;
                cola->siguiente = actual;
                cola = actual;
                actual = temp;
            }
        }

        // Ajuste del puntero para la lista particionada
        if (*nuevaPrimero == NULL)
        {
            *nuevaPrimero = pivote;
        }
        *nuevaUltimo = cola;
        return pivote; // Retorna el pivote
    }

    // Función recursiva que implementa el algoritmo QuickSort
    Nodo *quicksortRecursivo(Nodo *primero, Nodo *ultimo)
    {
        // Caso base: si la lista tiene un solo nodo o está vacía
        if (!primero || primero == ultimo)
        {
            return primero;
        }

        Nodo *nuevaPrimero = NULL;
        Nodo *nuevaUltimo = NULL;

        // Particiona la lista y obtiene el pivote
        Nodo *pivote = particion(primero, ultimo, &nuevaPrimero, &nuevaUltimo);

        // Ordena las partes izquierda y derecha de la lista recursivamente
        if (nuevaPrimero != pivote)
        {
            Nodo *temp = nuevaPrimero;
            while (temp->siguiente != pivote) // Busca el nodo anterior al pivote
            {
                temp = temp->siguiente;
            }
            temp->siguiente = NULL;                                // Finaliza la parte izquierda
            nuevaPrimero = quicksortRecursivo(nuevaPrimero, temp); // Ordena la parte izquierda
            temp = obtenerUltimo(nuevaPrimero);                    // Encuentra el último nodo de la parte izquierda
            temp->siguiente = pivote;                              // Conecta el pivote a la parte izquierda
        }

        pivote->siguiente = quicksortRecursivo(pivote->siguiente, nuevaUltimo); // Ordena la parte derecha
        return nuevaPrimero;                                                    // Retorna la lista ordenada
    }

public:
    // Constructor que inicializa la lista vacía
    ListaEnlazada() : cabeza(NULL), tamanio(0) {}

    // Destructor que elimina todos los nodos de la lista
    ~ListaEnlazada()
    {
        Nodo *actual = cabeza;
        while (actual)
        {
            Nodo *siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }

    // Función para insertar un valor en la lista
    void insertar(float valor)
    {
        Nodo *nuevoNodo = new Nodo(valor); // Crea un nuevo nodo
        if (!cabeza)
        {
            cabeza = nuevoNodo; // Si la lista está vacía, el nuevo nodo es la cabeza
        }
        else
        {
            Nodo *temp = cabeza;
            // Recorre hasta el final de la lista
            while (temp->siguiente)
            {
                temp = temp->siguiente;
            }
            temp->siguiente = nuevoNodo; // Inserta el nuevo nodo al final
        }
        tamanio++; // Incrementa el tamaño de la lista
    }

    // Función para generar números aleatorios dentro del rango definido
    void generarNumeros()
    {
        srand(time(NULL)); // Inicializa la semilla para la generación de números aleatorios
        for (int i = 0; i < TAMANIO_LISTA; ++i)
        {
            // Genera un número aleatorio dentro del rango
            float num = VALOR_MINIMO + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (VALOR_MAXIMO - VALOR_MINIMO)));
            insertar(num); // Inserta el número en la lista
        }
    }

    // Función para ordenar la lista usando QuickSort
    void ordenar()
    {
        cabeza = quicksortRecursivo(cabeza, obtenerUltimo(cabeza)); // Ordena la lista usando QuickSort
    }

    // Función para realizar la búsqueda binaria en la lista
    bool busquedaBinaria(float valor)
    {
        return busquedaBinariaAux(cabeza, obtenerUltimo(cabeza), valor); // Llama a la búsqueda binaria recursiva
    }

    // Función auxiliar recursiva que implementa la búsqueda binaria
    bool busquedaBinariaAux(Nodo *inicio, Nodo *fin, float valor)
    {
        if (!inicio || !fin) // Si los nodos no son válidos
            return false;

        if (inicio == fin)                                // Caso base: si solo hay un nodo
            return fabs(inicio->valor - valor) < 0.0001f; // Compara el valor con el nodo

        Nodo *lento = inicio;
        Nodo *rapido = inicio->siguiente;

        // Avanza los nodos "lento" y "rápido" para encontrar el punto medio
        while (rapido != fin && rapido->siguiente != fin)
        {
            lento = lento->siguiente;
            rapido = rapido->siguiente->siguiente;
        }

        // Si encontramos el valor, lo retornamos como encontrado
        if (fabs(lento->valor - valor) < 0.0001f)
            return true;

        // Recursión para la búsqueda binaria en la mitad correspondiente
        if (lento->valor < valor)
            return busquedaBinariaAux(lento->siguiente, fin, valor);
        return busquedaBinariaAux(inicio, lento, valor);
    }

    // Función para mostrar los primeros N elementos de la lista
    void mostrarMuestra(int n = 20)
    {
        cout << "Muestra de la lista (" << n << " elementos):\n";
        Nodo *temp = cabeza;
        for (int i = 0; i < n && temp; ++i)
        {
            cout << temp->valor << " "; // Muestra el valor del nodo
            temp = temp->siguiente;     // Avanza al siguiente nodo
        }
        cout << "\n";
    }
};

// Clase ColaResultados para almacenar los resultados de búsqueda
class ColaResultados
{
private:
    struct NodoCola
    {
        string mensaje;                                                // Mensaje que describe el resultado
        NodoCola *siguiente;                                           // Puntero al siguiente nodo en la cola
        NodoCola(const string &msg) : mensaje(msg), siguiente(NULL) {} // Constructor
    };
    NodoCola *frente; // Puntero al primer nodo de la cola
    NodoCola *final;  // Puntero al último nodo de la cola

public:
    ColaResultados() : frente(NULL), final(NULL) {}

    // Destructor que elimina todos los nodos de la cola
    ~ColaResultados()
    {
        while (frente)
        {
            NodoCola *temp = frente;
            frente = frente->siguiente;
            delete temp;
        }
    }

    // Función para agregar un mensaje a la cola
    void encolar(const string &mensaje)
    {
        NodoCola *nuevo = new NodoCola(mensaje); // Crea un nuevo nodo
        if (!frente)
        {
            frente = final = nuevo; // Si la cola está vacía, el nuevo nodo es el primero y el último
        }
        else
        {
            final->siguiente = nuevo; // Conecta el nuevo nodo al final de la cola
            final = nuevo;            // Actualiza el puntero al último nodo
        }
    }

    // Función para imprimir todos los mensajes de la cola
    void imprimir()
    {
        NodoCola *temp = frente;
        while (temp)
        {
            cout << temp->mensaje << "\n"; // Muestra el mensaje de cada nodo
            temp = temp->siguiente;        // Avanza al siguiente nodo
        }
    }

    // Función para limpiar la cola
    void limpiar()
    {
        while (frente)
        {
            NodoCola *temp = frente;
            frente = frente->siguiente;
            delete temp; // Elimina cada nodo de la cola
        }
        final = NULL; // Reinicia el puntero al último nodo
    }
};

// Función para solicitar un número válido del usuario dentro de un rango
float solicitarNumero()
{
    float numero;
    while (true)
    {
        cout << "Ingrese un numero entre " << VALOR_MINIMO << " y " << VALOR_MAXIMO << ": ";
        cin >> numero;
        if (cin.fail() || numero < VALOR_MINIMO || numero > VALOR_MAXIMO)
        {
            // Si la entrada no es válida, mostramos un mensaje de error
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Entrada invalida. Intente de nuevo.\n";
        }
        else
        {
            break; // Si la entrada es válida, salimos del bucle
        }
    }
    return numero; // Retorna el número ingresado
}

// Función para preguntar al usuario si desea continuar con otra búsqueda
char preguntarContinuar()
{
    char respuesta;
    do
    {
        cout << "\n¿Desea realizar otra busqueda? (S/N): ";
        cin >> respuesta;
        respuesta = toupper(respuesta); // Convierte la respuesta a mayúscula para estandarizar
        if (respuesta != 'S' && respuesta != 'N')
        {
            cout << "Error: Ingrese 'S' para continuar o 'N' para salir.\n"; // Validamos la entrada
        }
    } while (respuesta != 'S' && respuesta != 'N');
    return respuesta; // Retorna la respuesta
}

// Función principal que ejecuta el programa
int main()
{
    // Creamos una lista enlazada
    ListaEnlazada lista;
    lista.generarNumeros(); // Generamos números aleatorios en la lista
    cout << "=== LISTA GENERADA ===\n";
    lista.mostrarMuestra(); // Mostramos una muestra de la lista generada

    lista.ordenar(); // Ordenamos la lista
    cout << "\n=== LISTA ORDENADA ===\n";
    lista.mostrarMuestra(); // Mostramos la lista ordenada

    ColaResultados resultados; // Creamos una cola para almacenar los resultados
    char continuar;

    do
    {
        resultados.limpiar(); // Limpiamos los resultados anteriores

        // Solicitamos un número del usuario
        float numero = solicitarNumero();

        // Verificamos si el número existe en la lista usando búsqueda binaria
        if (lista.busquedaBinaria(numero))
        {
            resultados.encolar("El numero " + to_string(numero) + " SI existe en la lista.");
        }
        else
        {
            resultados.encolar("El numero " + to_string(numero) + " NO existe en la lista.");
        }

        // Mostramos los resultados de la búsqueda
        cout << "\n=== RESULTADOS ===\n";
        resultados.imprimir();

        // Preguntamos si el usuario desea realizar otra búsqueda
        continuar = preguntarContinuar();
    } while (continuar == 'S'); // Si la respuesta es 'S', repetimos el proceso

    cout << "\nPrograma finalizado. Gracias por usar el sistema!\n"; // Mensaje final
    return 0;                                                        // Finaliza el programa
}
