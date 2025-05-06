#include <iostream>

using namespace std;

// ------------------------------
// TAD Pedido
// ------------------------------
struct Pedido
{
    string nombre;
    string cedula;
    string hamburguesa;
};

// ------------------------------
// Nodo para cola dinámica
// ------------------------------
struct Nodo
{
    Pedido dato;
    Nodo *siguiente;
};

// ------------------------------
// Cola dinámica (lista enlazada)
// ------------------------------
class ColaPedidos
{
private:
    Nodo *frente;
    Nodo *fin;

public:
    ColaPedidos()
    {
        frente = NULL;
        fin = NULL;
    }

    void encolar(Pedido p)
    {
        Nodo *nuevo = new Nodo();
        nuevo->dato = p;
        nuevo->siguiente = NULL;
        if (fin != NULL)
        {
            fin->siguiente = nuevo;
        }
        fin = nuevo;
        if (frente == NULL)
        {
            frente = nuevo;
        }
    }

    bool estaVacia()
    {
        return frente == NULL;
    }

    void mostrar()
    {
        if (estaVacia())
        {
            cout << "No hay pedidos en la cola." << endl;
            return;
        }

        Nodo *aux = frente;
        while (aux != NULL)
        {
            cout << "- Hamburguesa: " << aux->dato.hamburguesa
                 << ", Cliente: " << aux->dato.nombre
                 << " (Cedula: " << aux->dato.cedula << ")" << endl;
            aux = aux->siguiente;
        }
    }

    ~ColaPedidos()
    {
        while (frente != NULL)
        {
            Nodo *temp = frente;
            frente = frente->siguiente;
            delete temp;
        }
        fin = NULL;
    }
};

// ------------------------------
// Clase Hamburgueseria
// ------------------------------
class Hamburgueseria
{
private:
    ColaPedidos cola;

    // Validar si nombre tiene solo letras
    bool esNombreValido(const string &nombre)
    {
        for (char c : nombre)
        {
            if (!isalpha(c) && c != ' ')
            {
                return false;
            }
        }
        return true;
    }

    // Validar si cédula tiene solo números
    bool esCedulaValida(const string &cedula)
    {
        for (char c : cedula)
        {
            if (!isdigit(c))
            {
                return false;
            }
        }
        return true;
    }

public:
    void mostrarMenuHamburguesas()
    {
        cout << "\n--- Menu de Hamburguesas ---" << endl;
        cout << "A. Hamburguesa Clasica" << endl;
        cout << "B. Hamburguesa con Queso" << endl;
        cout << "C. Hamburguesa Doble Carne" << endl;
        cout << "D. Hamburguesa Vegetariana" << endl;
        cout << "E. Hamburguesa Especial" << endl;
        cout << "Ingrese la letra de la hamburguesa que desea pedir: ";
    }

    string obtenerHamburguesa(char opcion)
    {
        opcion = toupper(opcion);
        if (opcion == 'A')
            return "Hamburguesa Clasica";
        if (opcion == 'B')
            return "Hamburguesa con Queso";
        if (opcion == 'C')
            return "Hamburguesa Doble Carne";
        if (opcion == 'D')
            return "Hamburguesa Vegetariana";
        if (opcion == 'E')
            return "Hamburguesa Especial";
        return "";
    }

    void llenar()
    {
        Pedido p;
        char letra;

        // Validar nombre
        do
        {
            cout << "\nIngrese su nombre: ";
            cin.ignore();
            getline(cin, p.nombre);
            if (!esNombreValido(p.nombre))
            {
                cout << "Nombre invalido. Intente de nuevo.\n";
            }
        } while (!esNombreValido(p.nombre));

        // Validar cédula
        do
        {
            cout << "Ingrese su cedula: ";
            getline(cin, p.cedula);
            if (!esCedulaValida(p.cedula))
            {
                cout << "Cedula invalida. Intente de nuevo.\n";
            }
        } while (!esCedulaValida(p.cedula));

        // Validar hamburguesa
        do
        {
            mostrarMenuHamburguesas();
            cin >> letra;
            p.hamburguesa = obtenerHamburguesa(letra);
            if (p.hamburguesa == "")
            {
                cout << "Letra invalida. Por favor elija una opcion existente del menu." << endl;
            }
        } while (p.hamburguesa == "");

        // Encolar pedido
        cola.encolar(p);
        cout << "Pedido agregado: " << p.hamburguesa << " para " << p.nombre << endl;
    }

    void mostrarCola()
    {
        cout << "\n--- Pedidos en Cola ---" << endl;
        cola.mostrar();
    }
};

// ------------------------------
// Función Principal
// ------------------------------
int main()
{
    Hamburgueseria sistema;
    int opcion;

    do
    {
        cout << "\n===== SISTEMA DE PEDIDOS =====" << endl;
        cout << "1. Agregar pedido" << endl;
        cout << "2. Mostrar pedidos en cola" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            sistema.llenar();
            break;
        case 2:
            sistema.mostrarCola();
            break;
        case 3:
            cout << "Gracias por usar el sistema. Hasta luego!" << endl;
            break;
        default:
            cout << "Opcion invalida. Intente nuevamente." << endl;
        }
    } while (opcion != 3);

    return 0;
}
