//Archivos de encabezado
#include "funciones.hpp"
#include "banco.hpp"
#include "info.hpp"
#include <iostream> // Incluye las funciones estándar de entrada/salida
#include <limits> // Incluye definiciones para valores límite
#include <cstdlib> // Incluye funciones estándar para manipulación de memoria y otras operaciones
#include <cmath>  // Incluye funciones matemáticas


/**
 * @brief Muestra el menú principal del programa.
 */
void MostrarMenu() {
    std::cout << "\n ---BIENVENIDO AL BANCO---\n";
    std::cout << "\n 1. Seleccione esta opcion si quiere consultar informacion\n";
    std::cout << "\n 2. Seleccione esta opcion si desea realizar operaciones en su cuenta.\n";
    std::cout << "\n 3. Salir\n";
}

/**
 * @brief Procesa la opción seleccionada por el usuario.
 * @param cliente Referencia a un objeto de tipo Base, que representa al cliente.
 */


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
                case 1: {//Si se selecciona la opcion 1, se corre todo este proceso.
                    while (true) {
                        /*Llamada a la funcion que levanta el menu Secundario,
                        que corresponde a la funcion de MODO INFORMACION*/
                        MostrarMenuSecundario();
                        int opcion_secundario; //Almacena la opcion escogida por el usuario
                        std::cout << "Ingrese una opcion para ver otra informacion disponible, o bien, presione 4 para volver al menu principal: ";
                        std::cin >> opcion_secundario;
                        //Se selecciona la opcion

                        if (std::cin.fail()) {
                            throw std::runtime_error("Opcion no valida. Por favor, ingrese un numero valido.");
                        }

                        switch (opcion_secundario) {
                            case 1:
                            /*Llamada a la funcion que muestra la informacion sobre los
                            prestamos personales, al presionar la opcion 1.*/
                                InfoPrestamoPersonal();
                            // Llamada a una función estática de la clase InfoPrestamo para calcular un préstamo genérico
                                InfoPrestamo::calcularPrestamo();
                                break;
                            case 2:
                            /*Llamada a la funcion que muestra la informacion sobre los
                            prestamos prendarios, al presionar la opcion 2.*/
                                InfoPrestamoPrendario();
                            // Llamada a la función estática de la clase InfoPrestamo para calcular otro préstamo genérico
                                InfoPrestamo::calcularPrestamo();
                                break;
                            case 3:
                            /*Llamada a la funcion que muestra la informacion sobre los
                            prestamos hipotecarios, al presionar la opcion 3.*/
                                InfoPrestamoHipotecario();
                                InfoPrestamo::calcularPrestamo();
                                break;
                            // Salir del bucle del menú secundario y volver al menú PRINCIPAL    
                            case 4:
                                std::cout << "Volviendo al menu principal... ";
                                break;
                            default:
                            //Por si se ingresa un valor incorrecto.
                                std::cout << "Opcion no valida. Intente de nuevo.\n";
                                break;
                        }

                        // Si la opción es 4, salir del bucle del menú secundario y volver al menú PRINCIPAL
                        if (opcion_secundario == 4) {
                            break;
                        }
                    }
                    break;
                }
                case 2: { //Si se selecciona la opcion 2, se corre todo este otro proceso.
                    while (true) {
                        mostrarMenuAtencion();
                        /*Llamada a la funcion que se encarga de mostrar el menu
                        del modo ATENCION.*/
                    
                    if (std::cin.fail()) {
                            throw std::runtime_error("Opcion no valida. Por favor, ingrese un numero valido.");
                        }
                    // Si la opción es 5, salir del bucle del menú secundario y volver al menú PRINCIPAL
                    if (opcion != 5) {
                            break;
                        }
                    }
                    break;
                }
                case 3:{//Si se selecciona la opcion 3, se finaliza la aplicacion bancaria.
                    std::cout << "\nSaliendo del programa. Gracias por utilizar nuestros servicios.\n";
                    exit(0);
                }
                default:
                    std::cout << "Opcion no valida. Intente de Nuevo...\n";
                    break;
            }
            if (opcion != 3) {//Para que el menu se siga mostrando cuando se selccione una opcion distinta de 3.
                MostrarMenu();
            }
        } catch (std::exception const& e) {
            std::cerr << e.what() << std::endl;
            std::cin.clear();  // Limpiar el indicador de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Descartar la entrada no válida
        }
    } while (opcion != 3); /*Con este while, se va a seguir ejecutando el menu PRINCIPAl cuando se 
                            cuando se selecciona una opcion diferente a las que hay.*/
}