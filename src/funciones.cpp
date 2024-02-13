#include "funciones.hpp"
#include "banco.hpp"
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

void procesarOpcion(Base& cliente) {
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
                                InfoPrestamo::calcularPrestamo();
                                break;
                            case 2:
                                InfoPrestamoPrendario();
                                InfoPrestamo::calcularPrestamo();
                                break;
                            case 3:
                                InfoPrestamoHipotecario();
                                InfoPrestamo::calcularPrestamo();
                                break;
                            case 4:
                                std::cout << "Volviendo al menu principal... ";
                                // Salir del bucle del menú secundario y volver al menú principal
                                break;
                            default:
                                std::cout << "Opcion no valida. Intente de nuevo.\n";
                                break;
                        }

                        // Si la opción es 4, salir del bucle del menú secundario y volver al menú principal
                        if (opcion_secundario == 4) {
                            break;
                        }
                    }
                    break;
                }
                case 2: {
                    while (true) {
                        mostrarMenuAtencion();
                    
                    if (std::cin.fail()) {
                            throw std::runtime_error("Opcion no valida. Por favor, ingrese un numero valido.");
                        }
                    // Si la opción es 5, salir del bucle del menú secundario y volver al menú principal
                    if (opcion != 5) {
                            break;
                        }
                    }
                    break;
                }
                case 3:{
                    std::cout << "\nSaliendo del programa. Gracias por utilizar nuestros servicios.\n";
                    exit(0);
                }
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