#include <iostream>
#include <limits>
#include <string>

// Constantes
const std::string MENSAJE_ERROR_ENTRADA = "Error: Por favor ingrese solo numeros enteros.\n";
const std::string MENSAJE_CONTINUAR = "\nDesea realizar otra operacion? (1: Si / 0: No): ";

// Clase Nodo para la lista enlazada
class NodoLista
{
public:
    int valor;
    NodoLista *siguiente;

    NodoLista(int valorAlmacenar) : valor(valorAlmacenar), siguiente(nullptr) {}
};

// Clase ListaEnlazada
class ListaEnlazada
{
private:
    NodoLista *cabeza;

    void liberarMemoria(NodoLista *nodoActual)
    {
        if (nodoActual != nullptr)
        {
            liberarMemoria(nodoActual->siguiente);
            delete nodoActual;
        }
    }

public:
    ListaEnlazada() : cabeza(nullptr) {}

    ~ListaEnlazada()
    {
        liberarMemoria(cabeza);
    }

    void insertarElemento(int valorInsertar)
    {
        NodoLista *nuevoNodo = new NodoLista(valorInsertar);

        if (cabeza == nullptr)
        {
            cabeza = nuevoNodo;
        }
        else
        {
            NodoLista *nodoActual = cabeza;
            while (nodoActual->siguiente != nullptr)
            {
                nodoActual = nodoActual->siguiente;
            }
            nodoActual->siguiente = nuevoNodo;
        }
    }

    void mostrarLista(const std::string &mensajeMostrar) const
    {
        std::cout << mensajeMostrar;
        NodoLista *nodoActual = cabeza;
        while (nodoActual != nullptr)
        {
            std::cout << nodoActual->valor << " ";
            nodoActual = nodoActual->siguiente;
        }
        std::cout << std::endl;
    }

    NodoLista *obtenerCabeza() const
    {
        return cabeza;
    }
};

// Clase OrdenadorRecursivo
class OrdenadorRecursivo
{
public:
    static void ordenarLista(NodoLista *nodoInicio)
    {
        if (nodoInicio == nullptr || nodoInicio->siguiente == nullptr)
        {
            return;
        }

        NodoLista *nodoMinimo = encontrarMinimo(nodoInicio);
        intercambiarValores(nodoInicio, nodoMinimo);
        ordenarLista(nodoInicio->siguiente);
    }

private:
    static NodoLista *encontrarMinimo(NodoLista *nodoActual)
    {
        NodoLista *nodoMinimo = nodoActual;

        while (nodoActual != nullptr)
        {
            if (nodoActual->valor < nodoMinimo->valor)
            {
                nodoMinimo = nodoActual;
            }
            nodoActual = nodoActual->siguiente;
        }

        return nodoMinimo;
    }

    static void intercambiarValores(NodoLista *nodoA, NodoLista *nodoB)
    {
        int valorTemporal = nodoA->valor;
        nodoA->valor = nodoB->valor;
        nodoB->valor = valorTemporal;
    }
};

// Módulo de validación de entrada
namespace ValidacionEntrada
{
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
                std::cerr << "Error: Ingrese 1 para Si o 0 para No.\n";
            }
        }

        return opcion == 1;
    }
}

// Módulo de interacción con el usuario
namespace InterfazUsuario
{
    void solicitarElementosLista(ListaEnlazada &lista)
    {
        int cantidadElementos = ValidacionEntrada::obtenerEntero(
            "Ingrese la cantidad de elementos a ordenar: ");

        std::cout << "Ingrese los elementos (uno por uno):\n";
        for (int indice = 0; indice < cantidadElementos; ++indice)
        {
            std::string mensaje = "Elemento " + std::to_string(indice + 1) + ": ";
            int valorElemento = ValidacionEntrada::obtenerEntero(mensaje);
            lista.insertarElemento(valorElemento);
        }
    }

    void ejecutarProcesoOrdenamiento()
    {
        ListaEnlazada lista;

        solicitarElementosLista(lista);
        lista.mostrarLista("\nLista original: ");

        OrdenadorRecursivo::ordenarLista(lista.obtenerCabeza());
        lista.mostrarLista("Lista ordenada: ");
    }
}

// Función principal
int main()
{
    std::cout << "=== ORDENADOR DE LISTAS ===" << std::endl;

    do
    {
        InterfazUsuario::ejecutarProcesoOrdenamiento();
    } while (ValidacionEntrada::deseaContinuar());

    std::cout << "Programa finalizado. Gracias por usar nuestro servicio!\n";
    return 0;
}