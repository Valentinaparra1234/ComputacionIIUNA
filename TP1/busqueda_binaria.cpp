#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <cmath>
#include <cctype>

using namespace std;

const int TAMANIO_LISTA = 999;
const float VALOR_MINIMO = 0.0f;
const float VALOR_MAXIMO = 2000.0f;

// Clase Nodo para la lista enlazada
class Nodo
{
public:
    float valor;
    Nodo *siguiente;
    Nodo(float val) : valor(val), siguiente(nullptr) {}
};

// Clase ListaEnlazada
class ListaEnlazada
{
private:
    Nodo *cabeza;
    int tamanio;

    Nodo *obtenerUltimo(Nodo *nodo)
    {
        while (nodo && nodo->siguiente)
        {
            nodo = nodo->siguiente;
        }
        return nodo;
    }

    Nodo *particion(Nodo *primero, Nodo *ultimo, Nodo **nuevaPrimero, Nodo **nuevaUltimo)
    {
        Nodo *pivote = ultimo;
        Nodo *anterior = nullptr;
        Nodo *actual = primero;
        Nodo *cola = pivote;

        while (actual != pivote)
        {
            if (actual->valor < pivote->valor)
            {
                if (*nuevaPrimero == nullptr)
                {
                    *nuevaPrimero = actual;
                }
                anterior = actual;
                actual = actual->siguiente;
            }
            else
            {
                if (anterior)
                {
                    anterior->siguiente = actual->siguiente;
                }
                Nodo *temp = actual->siguiente;
                actual->siguiente = nullptr;
                cola->siguiente = actual;
                cola = actual;
                actual = temp;
            }
        }

        if (*nuevaPrimero == nullptr)
        {
            *nuevaPrimero = pivote;
        }
        *nuevaUltimo = cola;
        return pivote;
    }

    Nodo *quicksortRecursivo(Nodo *primero, Nodo *ultimo)
    {
        if (!primero || primero == ultimo)
        {
            return primero;
        }

        Nodo *nuevaPrimero = nullptr;
        Nodo *nuevaUltimo = nullptr;
        Nodo *pivote = particion(primero, ultimo, &nuevaPrimero, &nuevaUltimo);

        if (nuevaPrimero != pivote)
        {
            Nodo *temp = nuevaPrimero;
            while (temp->siguiente != pivote)
            {
                temp = temp->siguiente;
            }
            temp->siguiente = nullptr;
            nuevaPrimero = quicksortRecursivo(nuevaPrimero, temp);
            temp = obtenerUltimo(nuevaPrimero);
            temp->siguiente = pivote;
        }

        pivote->siguiente = quicksortRecursivo(pivote->siguiente, nuevaUltimo);
        return nuevaPrimero;
    }

public:
    ListaEnlazada() : cabeza(nullptr), tamanio(0) {}

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

    void insertar(float valor)
    {
        Nodo *nuevoNodo = new Nodo(valor);
        if (!cabeza)
        {
            cabeza = nuevoNodo;
        }
        else
        {
            Nodo *temp = cabeza;
            while (temp->siguiente)
            {
                temp = temp->siguiente;
            }
            temp->siguiente = nuevoNodo;
        }
        tamanio++;
    }

    void generarNumeros()
    {
        srand(time(nullptr));
        for (int i = 0; i < TAMANIO_LISTA; ++i)
        {
            float num = VALOR_MINIMO + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (VALOR_MAXIMO - VALOR_MINIMO)));
            insertar(num);
        }
    }

    void ordenar()
    {
        cabeza = quicksortRecursivo(cabeza, obtenerUltimo(cabeza));
    }

    bool busquedaBinaria(float valor)
    {
        return busquedaBinariaAux(cabeza, obtenerUltimo(cabeza), valor);
    }

    bool busquedaBinariaAux(Nodo *inicio, Nodo *fin, float valor)
    {
        if (!inicio || !fin)
            return false;
        if (inicio == fin)
            return fabs(inicio->valor - valor) < 0.0001f;

        Nodo *lento = inicio;
        Nodo *rapido = inicio->siguiente;

        while (rapido != fin && rapido->siguiente != fin)
        {
            lento = lento->siguiente;
            rapido = rapido->siguiente->siguiente;
        }

        if (fabs(lento->valor - valor) < 0.0001f)
            return true;
        if (lento->valor < valor)
            return busquedaBinariaAux(lento->siguiente, fin, valor);
        return busquedaBinariaAux(inicio, lento, valor);
    }

    void mostrarMuestra(int n = 20)
    {
        cout << "Muestra de la lista (" << n << " elementos):\n";
        Nodo *temp = cabeza;
        for (int i = 0; i < n && temp; ++i)
        {
            cout << temp->valor << " ";
            temp = temp->siguiente;
        }
        cout << "\n";
    }
};

class ColaResultados
{
private:
    struct NodoCola
    {
        string mensaje;
        NodoCola *siguiente;
        NodoCola(const string &msg) : mensaje(msg), siguiente(nullptr) {}
    };
    NodoCola *frente;
    NodoCola *final;

public:
    ColaResultados() : frente(nullptr), final(nullptr) {}

    ~ColaResultados()
    {
        while (frente)
        {
            NodoCola *temp = frente;
            frente = frente->siguiente;
            delete temp;
        }
    }

    void encolar(const string &mensaje)
    {
        NodoCola *nuevo = new NodoCola(mensaje);
        if (!frente)
        {
            frente = final = nuevo;
        }
        else
        {
            final->siguiente = nuevo;
            final = nuevo;
        }
    }

    void imprimir()
    {
        NodoCola *temp = frente;
        while (temp)
        {
            cout << temp->mensaje << "\n";
            temp = temp->siguiente;
        }
    }

    void limpiar()
    {
        while (frente)
        {
            NodoCola *temp = frente;
            frente = frente->siguiente;
            delete temp;
        }
        final = nullptr;
    }
};

float solicitarNumero()
{
    float numero;
    while (true)
    {
        cout << "Ingrese un numero entre " << VALOR_MINIMO << " y " << VALOR_MAXIMO << ": ";
        cin >> numero;
        if (cin.fail() || numero < VALOR_MINIMO || numero > VALOR_MAXIMO)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Entrada invalida. Intente de nuevo.\n";
        }
        else
        {
            break;
        }
    }
    return numero;
}

char preguntarContinuar()
{
    char respuesta;
    do
    {
        cout << "\n¿Desea realizar otra busqueda? (S/N): ";
        cin >> respuesta;
        respuesta = toupper(respuesta);
        if (respuesta != 'S' && respuesta != 'N')
        {
            cout << "Error: Ingrese 'S' para continuar o 'N' para salir.\n";
        }
    } while (respuesta != 'S' && respuesta != 'N');
    return respuesta;
}

int main()
{
    ListaEnlazada lista;
    lista.generarNumeros();
    cout << "=== LISTA GENERADA ===\n";
    lista.mostrarMuestra();

    lista.ordenar();
    cout << "\n=== LISTA ORDENADA ===\n";
    lista.mostrarMuestra();

    ColaResultados resultados;
    char continuar;

    do
    {
        resultados.limpiar();
        float numero = solicitarNumero();

        if (lista.busquedaBinaria(numero))
        {
            resultados.encolar("El numero " + to_string(numero) + " SI existe en la lista.");
        }
        else
        {
            resultados.encolar("El numero " + to_string(numero) + " NO existe en la lista.");
        }

        cout << "\n=== RESULTADOS ===\n";
        resultados.imprimir();

        continuar = preguntarContinuar();
    } while (continuar == 'S');

    cout << "\nPrograma finalizado. Gracias por usar el sistema!\n";
    return 0;
}