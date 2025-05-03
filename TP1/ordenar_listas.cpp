#include <iostream>
#include <limits>
#include <string>

// Constantes para mensajes
const std::string MENSAJE_ERROR_ENTRADA = "Por favor ingrese solo números enteros.\n";
const std::string MENSAJE_CONTINUAR = "\n¿Desea realizar otra operación? (1: Sí / 0: No): ";

// Clase que representa un nodo de la lista enlazada
class NodoLista
{
public:
    int valor;            // Valor almacenado en el nodo
    NodoLista *siguiente; // Puntero al siguiente nodo

    NodoLista(int valorAlmacenar) : valor(valorAlmacenar), siguiente(NULL) {}
};

// Clase que representa una lista enlazada de enteros
class ListaEnlazada
{
private:
    NodoLista *cabeza; // Puntero al primer nodo de la lista

    // Método recursivo para liberar memoria de los nodos
    void liberarMemoria(NodoLista *nodoActual)
    {
        if (nodoActual != NULL)
        {
            liberarMemoria(nodoActual->siguiente);
            delete nodoActual;
        }
    }

public:
    ListaEnlazada() : cabeza(NULL) {}

    ~ListaEnlazada()
    {
        liberarMemoria(cabeza);
    }

    // Inserta un nuevo nodo al final de la lista
    void insertarElemento(int valorInsertar)
    {
        NodoLista *nuevoNodo = new NodoLista(valorInsertar);

        if (cabeza == NULL)
        {
            cabeza = nuevoNodo;
        }
        else
        {
            NodoLista *nodoActual = cabeza;
            while (nodoActual->siguiente != NULL)
            {
                nodoActual = nodoActual->siguiente;
            }
            nodoActual->siguiente = nuevoNodo;
        }
    }

    // Muestra todos los elementos de la lista con un mensaje
    void mostrarLista(const std::string &mensajeMostrar) const
    {
        std::cout << mensajeMostrar;
        NodoLista *nodoActual = cabeza;
        while (nodoActual != NULL)
        {
            std::cout << nodoActual->valor << " ";
            nodoActual = nodoActual->siguiente;
        }
        std::cout << std::endl;
    }

    // Devuelve el puntero al primer nodo de la lista
    NodoLista *obtenerCabeza() const
    {
        return cabeza;
    }
};

// Clase que implementa un algoritmo de ordenación recursivo tipo selección
// Nota: Este algoritmo no es el más eficiente, pero es válido con pocos elementos.
class OrdenadorRecursivo
{
public:
    // Ordena la lista desde el nodo dado usando recursión
    static void ordenarLista(NodoLista *nodoInicio)
    {
        if (nodoInicio == NULL || nodoInicio->siguiente == NULL)
        {
            return;
        }

        NodoLista *nodoMinimo = encontrarMinimo(nodoInicio);
        intercambiarValores(nodoInicio, nodoMinimo);
        ordenarLista(nodoInicio->siguiente);
    }

private:
    // Encuentra el nodo con el valor mínimo a partir del nodo actual
    static NodoLista *encontrarMinimo(NodoLista *nodoActual)
    {
        NodoLista *nodoMinimo = nodoActual;

        while (nodoActual != NULL)
        {
            if (nodoActual->valor < nodoMinimo->valor)
            {
                nodoMinimo = nodoActual;
            }
            nodoActual = nodoActual->siguiente;
        }

        return nodoMinimo;
    }

    // Intercambia los valores de dos nodos
    static void intercambiarValores(NodoLista *nodoA, NodoLista *nodoB)
    {
        int valorTemporal = nodoA->valor;
        nodoA->valor = nodoB->valor;
        nodoB->valor = valorTemporal;
    }
};

// Módulo para validación de entrada del usuario
namespace ValidacionEntrada
{
    // Solicita al usuario un número entero, validando errores
    int obtenerEntero(const std::string &mensaje)
    {
        int valor;

        while (true)
        {
            std::cout << mensaje;

            if (std::cin >> valor)
            {
                break;
            }
            else
            {
                std::cerr << MENSAJE_ERROR_ENTRADA;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        return valor;
    }

    // Pregunta al usuario si desea continuar, validando entrada
    bool deseaContinuar()
    {
        int opcion;

        while (true)
        {
            opcion = obtenerEntero(MENSAJE_CONTINUAR);

            if (opcion == 0 || opcion == 1)
            {
                break;
            }
            else
            {
                std::cerr << "Error: Ingrese 1 para Sí o 0 para No.\n";
            }
        }

        return opcion == 1;
    }
}

// Módulo que gestiona la interacción con el usuario
namespace InterfazUsuario
{
    // Solicita al usuario los elementos de la lista
    void solicitarElementosLista(ListaEnlazada &lista)
    {
        int cantidadElementos = ValidacionEntrada::obtenerEntero(
            "Por favor, indique cuántos elementos desea ordenar: ");

        std::cout << "Ingrese los elementos (uno por uno):\n";
        for (int indice = 0; indice < cantidadElementos; ++indice)
        {
            std::string mensaje = "Elemento " + std::to_string(indice + 1) + ": ";
            int valorElemento = ValidacionEntrada::obtenerEntero(mensaje);
            lista.insertarElemento(valorElemento);
        }
    }

    // Ejecuta el proceso completo de ordenamiento
    void ejecutarProcesoOrdenamiento()
    {
        ListaEnlazada lista;

        solicitarElementosLista(lista);
        lista.mostrarLista("\nLista original: ");

        OrdenadorRecursivo::ordenarLista(lista.obtenerCabeza());
        lista.mostrarLista("Lista ordenada: ");
    }
}

// Función principal del programa
int main()
{
    std::cout << "=== ORDENADOR DE LISTAS ===" << std::endl;

    do
    {
        InterfazUsuario::ejecutarProcesoOrdenamiento();
    } while (ValidacionEntrada::deseaContinuar());

    std::cout << "Programa finalizado. ¡Gracias por usar nuestro servicio!\n";
    return 0;
}
