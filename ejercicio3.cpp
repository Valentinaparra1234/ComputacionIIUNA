#include <iostream>
#include <queue>
#include <map>
using namespace std;
// Estructura para almacenar la información de un pedido.
struct Pedido
{
    string nombre;
    string cedula;
    string hamburguesa;
};
// Función para mostrar el menú de hamburguesas
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
// Función para mostrar el menú principal
void mostrarMenuPrincipal()
{
    cout << "\n--- Menu de la Hamburgueseria ---" << endl;
    cout << "1. Agregar un pedido a la cola" << endl;
    cout << "2. Mostrar todos los pedidos en la cola" << endl;
    cout << "3. Salir" << endl;
    cout << "Ingrese su opcion: ";
}
// Función principal del programa
int main()
{
    queue<Pedido> colaPedidos; // Cola para almacenar los pedidos
    map<char, string> menu = {
        {'A', "Hamburguesa Clasica"},
        {'B', "Hamburguesa con Queso"},
        {'C', "Hamburguesa Doble Carne"},
        {'D', "Hamburguesa Vegetariana"},
        {'E', "Hamburguesa Especial"}};
    int opcion;
    char letraHamburguesa;
    string nombre, cedula;
    do
    {
        mostrarMenuPrincipal();
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            // Opción 1: Agregar un pedido a la cola
            cout << "\nIngrese su nombre: ";
            cin.ignore(); // Limpiar el buffer de entrada
            getline(cin, nombre);
            cout << "Ingrese su cedula: ";
            getline(cin, cedula);
            mostrarMenuHamburguesas();
            cin >> letraHamburguesa;
            // Convertir la letra a mayúscula para evitar problemas con minúsculas
            letraHamburguesa = toupper(letraHamburguesa);
            if (menu.find(letraHamburguesa) != menu.end())
            {
                Pedido nuevoPedido = {nombre, cedula, menu[letraHamburguesa]};
                colaPedidos.push(nuevoPedido);
                cout << "Pedido agregado: " << menu[letraHamburguesa] << " para " << nombre << " (Cedula: " << cedula << ")" << endl;
            }
            else
            {
                cout << "Letra de hamburguesa no valida. Intente de nuevo." << endl;
            }
            break;
        case 2:
            // Opción 2: Mostrar todos los pedidos en la cola
            if (colaPedidos.empty())
            {
                cout << "No hay pedidos en la cola." << endl;
            }
            else
            {
                cout << "\nPedidos en la cola:" << endl;
                queue<Pedido> copiaCola = colaPedidos; // Copia de la cola para mostrar sin modificar la original
                while (!copiaCola.empty())
                {
                    Pedido pedido = copiaCola.front();
                    cout << "- Hamburguesa: " << pedido.hamburguesa << ", Cliente: " << pedido.nombre << " (Cedula: " << pedido.cedula << ")" << endl;
                    copiaCola.pop();
                }
            }
            break;
        case 3:
            // Opción 3: Salir del programa
            cout << "Gracias por usar el sistema de pedidos. ¡Hasta luego!" << endl;
            break;
        default:
            // Opción no válida
            cout << "Opción no valida. Intente de nuevo." << endl;
            break;
        }
    } while (opcion != 3);
    return 0;
}