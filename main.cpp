#include "banco.hpp"
#include <limits>
#include <vector>

int main() {
    std::vector<Cliente*> clientes;
    std::string entradaID, nombre;
    int id, opcion = 0;

    std::cout << "Sistema de Gestion Bancaria\n";

    while (opcion != 5) {
        std::cout << "\nMenu:\n"
                  << "1. Crear Cliente\n"
                  << "2. Crear CDP para Cliente\n"
                  << "3. Mostrar Detalles del Cliente\n"
                  << "4. Agregar cuenta para Cliente\n"
                  << "5. Salir\n"
                  << "Seleccione una opcion: ";
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcion) {
            case 1: {
                std::cout << "Ingrese el ID del cliente: ";
                std::getline(std::cin, entradaID);

                int id;
                if (Cliente::esNumeroValido(entradaID, id)) {
                    std::cout << "Ingrese el nombre del cliente: ";
                    std::getline(std::cin, nombre);

                    Cliente* nuevoCliente = new Cliente(id, nombre);
                    clientes.push_back(nuevoCliente);
                    std::cout << "\nCliente creado con exito.\n";
                } else {
                    std::cout << "ID invalido. Por favor, introduzca un numero de ID valido.\n";
                }
                break;
            }
            case 2: {
                CDP::crearYAgregarCDPParaCliente(clientes);
                break;
            }
            case 3: {
                for (auto& cliente : clientes) {
                    std::cout << "\nID: " << cliente->obtenerID() << ", Nombre: " << cliente->obtenerNombre() << "\n";

                }
                if (clientes.empty()) {
                    std::cout << "No hay clientes para mostrar.\n";
                }
                break;
            }
            case 4: {
                Cliente::agregarCuentaABanco(clientes);
                break;
            }
            case 5:
                std::cout << "Saliendo del sistema.\n";
                break;
            default:
                std::cout << "Opcion no valida.\n";
                break;
        }
    }
    for (auto cliente : clientes) {
        delete cliente;
    }
    clientes.clear();

    return 0;
}
