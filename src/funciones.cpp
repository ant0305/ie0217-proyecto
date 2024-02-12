#include "funciones.hpp"
#include "info.hpp"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <cmath>

void MostrarMenu() {
    std::cout << "\n ---BIENVENIDO AL BANCO---\n";
    std::cout << "\n 1. Seleccione esta opcion si quiere consultar informacion\n";
    std::cout << "\n 2. Seleccione esta opcion si desea realizar operaciones en su cuenta.\n";
    std::cout << "\n 3. Salir\n";
}

void procesarOpcion(Cliente& cliente) {
    int opcion;
    do {
        try {
            std::cout << "Ingrese una opcion: ";
            std::cin >> opcion;

            if (std::cin.fail()) {
                throw std::runtime_error("Entrada no valida. Por favor, ingrese un numero.");
            }

            switch (opcion) {
                case 1: {
                    while (true) {
                        MostrarMenuSecundario();
                        int opcion_secundario;
                        std::cout << "Ingrese una opcion para ver otra informacion disponible, o bien, presione 4 para volver al menu principal: ";
                        std::cin >> opcion_secundario;

                        if (std::cin.fail()) {
                            throw std::runtime_error("Opcion no valida. Por favor, ingrese un numero valido.");
                        }

                        switch (opcion_secundario) {
                            case 1:
                                InfoPrestamoPersonal();
                                break;
                            case 2:
                                InfoPrestamoPrendario();
                                break;
                            case 3:
                                InfoPrestamoHipotecario();
                                break;
                            case 4:
                                std::cout << "Volviendo al menu principal... ";
                                // Salir del bucle del menú secundario y volver al menú principal
                                break;
                            default:
                                std::cout << "Opcion no valida. Intente de nuevo.\n";
                                break;
                        }

                        // Si la opción no es 4, salir del bucle del menú secundario y volver al menú principal
                        if (opcion_secundario == 4) {
                            break;
                        }
                    }
                    break;
                }
                case 2:
                    // Implementa la lógica para Modo_Atencion(cliente);
                    std::cout << "Implementa la logica para Modo_Atencion(cliente);\n";
                    break;
                case 3:
                    std::cout << "\nSaliendo del programa. Gracias por utilizar nuestros servicios.\n";
                    exit(0);
                default:
                    std::cout << "Opcion no valida. Intente de Nuevo...\n";
                    break;
            }
            if (opcion != 3) {
                MostrarMenu();
            }
        } catch (std::exception const& e) {
            std::cerr << e.what() << std::endl;
            std::cin.clear();  // Limpiar el indicador de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Descartar la entrada no válida
        }
    } while (opcion != 3);
}