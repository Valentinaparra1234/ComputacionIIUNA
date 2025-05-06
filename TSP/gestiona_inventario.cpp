#include <iostream>
#include <limits>
#include <string>

// Mensaje para entrada no válida
const std::string MENSAJE_ERROR_ENTRADA = "Error: Ingrese solo numeros enteros.\n";

// ---------------------- VALIDACIÓN DE ENTRADAS ----------------------
// Encapsulamos la lógica de validación para evitar duplicación y mejorar la robustez
namespace ValidacionEntrada
{
    // Solicita un numero entero y valida que la entrada sea correcta
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
                std::cin.clear();                                                   // Limpia el estado de error del stream
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descarta entrada inválida
            }
        }
        return valor;
    }
}

// ---------------------- DEFINICIÓN DE NODO ----------------------
// Nodo representa cada elemento de una lista enlazada
class Nodo
{
public:
    int valor;       // Valor almacenado
    Nodo *siguiente; // Puntero al siguiente nodo

    // Constructor
    Nodo(int valorDato) : valor(valorDato), siguiente(NULL) {}
};

// ---------------------- LISTA ENLAZADA ----------------------
// Estructura de datos dinámica lineal
class ListaEnlazada
{
private:
    Nodo *cabeza;

    // Método recursivo para liberar memoria
    void liberarMemoria(Nodo *nodo)
    {
        if (nodo != NULL)
        {
            liberarMemoria(nodo->siguiente);
            delete nodo;
        }
    }

public:
    // Constructor
    ListaEnlazada() : cabeza(NULL) {}

    // Destructor para evitar fugas de memoria
    ~ListaEnlazada()
    {
        liberarMemoria(cabeza);
    }

    // Inserta un nodo al final de la lista
    void insertarAlFinal(int valor)
    {
        Nodo *nuevo = new Nodo(valor);
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

    // Muestra todos los elementos de la lista
    void mostrarLista(const std::string &mensaje) const
    {
        std::cout << mensaje;
        Nodo *actual = cabeza;
        while (actual != NULL)
        {
            std::cout << actual->valor << " ";
            actual = actual->siguiente;
        }
        std::cout << std::endl;
    }

    // Devuelve el nodo cabeza
    Nodo *obtenerCabeza() const
    {
        return cabeza;
    }

    // Devuelve el tamaño de la lista
    int obtenerTamano() const
    {
        int contador = 0;
        Nodo *actual = cabeza;
        while (actual != NULL)
        {
            contador++;
            actual = actual->siguiente;
        }
        return contador;
    }

    // Devuelve el valor en un índice específico
    int obtenerValorEn(int indice) const
    {
        int contador = 0;
        Nodo *actual = cabeza;
        while (actual != NULL)
        {
            if (contador == indice)
            {
                return actual->valor;
            }
            contador++;
            actual = actual->siguiente;
        }
        return 0; // Devuelve 0 si el índice es inválido
    }
};

// ---------------------- INVENTARIO SUCURSAL ----------------------
// Representa una lista de inventario para una sucursal específica
class InventarioSucursal
{
private:
    ListaEnlazada inventario;

public:
    // Llenar el inventario con entradas del usuario
    void llenar(int cantidad)
    {
        for (int i = 0; i < cantidad; i++)
        {
            int valor = ValidacionEntrada::obtenerEntero("Cantidad producto [" + std::to_string(i + 1) + "]: ");
            inventario.insertarAlFinal(valor);
        }
    }

    // Muestra el inventario
    void mostrar(const std::string &nombre)
    {
        inventario.mostrarLista(nombre);
    }

    // Devuelve la lista enlazada del inventario
    ListaEnlazada &obtenerInventario()
    {
        return inventario;
    }
};

// ---------------------- PROCESADOR DE INVENTARIOS ----------------------
// Contiene operaciones para combinar o modificar inventarios entre sucursales
class ProcesadorInventario
{
public:
    // Intercala elementos de dos listas (uno de A, luego uno de B, etc.)
    static ListaEnlazada intercalar(const ListaEnlazada &a, const ListaEnlazada &b)
    {
        ListaEnlazada resultado;
        int maxLen = (a.obtenerTamano() > b.obtenerTamano()) ? a.obtenerTamano() : b.obtenerTamano();

        for (int i = 0; i < maxLen; ++i)
        {
            if (i < a.obtenerTamano())
            {
                resultado.insertarAlFinal(a.obtenerValorEn(i));
            }
            if (i < b.obtenerTamano())
            {
                resultado.insertarAlFinal(b.obtenerValorEn(i));
            }
        }

        return resultado;
    }

    // Resta elemento a elemento los inventarios de A y B
    static ListaEnlazada restar(const ListaEnlazada &a, const ListaEnlazada &b)
    {
        ListaEnlazada resultado;
        int maxLen = (a.obtenerTamano() > b.obtenerTamano()) ? a.obtenerTamano() : b.obtenerTamano();

        for (int i = 0; i < maxLen; ++i)
        {
            int valorA = (i < a.obtenerTamano()) ? a.obtenerValorEn(i) : 0;
            int valorB = (i < b.obtenerTamano()) ? b.obtenerValorEn(i) : 0;
            resultado.insertarAlFinal(valorA - valorB);
        }

        return resultado;
    }
};

// ---------------------- FUNCIÓN PRINCIPAL ----------------------
int main()
{
    std::cout << "=== SISTEMA DE INVENTARIO (SUCURSALES) ===\n";

    // Crear objetos para dos sucursales
    InventarioSucursal sucursalA, sucursalB;

    // Llenar inventario sucursal A
    int cantidadA = ValidacionEntrada::obtenerEntero("\nIngrese numero de productos para Sucursal A: ");
    sucursalA.llenar(cantidadA);

    // Llenar inventario sucursal B
    int cantidadB = ValidacionEntrada::obtenerEntero("\nIngrese numero de productos para Sucursal B: ");
    sucursalB.llenar(cantidadB);

    // Mostrar inventarios originales
    std::cout << "\n-- INVENTARIOS --\n";
    sucursalA.mostrar("Sucursal A: ");
    sucursalB.mostrar("Sucursal B: ");

    // Mostrar inventario intercalado
    std::cout << "\n-- INVENTARIO INTERCALADO --\n";
    ListaEnlazada intercalado = ProcesadorInventario::intercalar(
        sucursalA.obtenerInventario(), sucursalB.obtenerInventario());
    intercalado.mostrarLista("Intercalado: ");

    // Mostrar diferencia entre inventarios
    std::cout << "\n-- DIFERENCIA DE INVENTARIO (A - B) --\n";
    ListaEnlazada diferencia = ProcesadorInventario::restar(
        sucursalA.obtenerInventario(), sucursalB.obtenerInventario());
    diferencia.mostrarLista("Diferencia: ");

    // Final del programa
    std::cout << "\nPrograma finalizado correctamente.\n";
    return 0;
}
