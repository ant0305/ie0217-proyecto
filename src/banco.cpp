#include "banco.hpp"
#include <iostream>
#include <vector>
#include <limits>
#include <memory>
#include <ctime>
#include <iomanip>

/**
 * @brief Agrega un CDP a la lista de CDPs del cliente.
 * @param nuevoCDP Referencia al nuevo CDP a agregar.
 */

void Cliente::agregarCDP(const CDP &nuevoCDP) {
    cdps.push_back(nuevoCDP);
}

// Función para cargar clientes desde un archivo
std::vector<Cliente*> cargarClientesDesdeArchivo(const std::string& nombreArchivo) {
    std::vector<Cliente*> clientes;

    std::ifstream archivoEntrada(nombreArchivo);
    if (archivoEntrada.is_open()) {
        int id;
        std::string nombre;

        while (archivoEntrada >> id >> nombre) {
            clientes.push_back(new Cliente(id, nombre));
        }

        archivoEntrada.close();
    } else {
        std::cerr << "Error al abrir el archivo de clientes para leer.\n";
    }

    return clientes;
}

void imprimirClientesDesdeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivoEntrada(nombreArchivo);
    if (archivoEntrada.is_open()) {
        std::cout << "Clientes disponibles en el archivo:\n";
        std::string linea;
        while (std::getline(archivoEntrada, linea)) {
            std::cout << linea << "\n";
        }
        archivoEntrada.close();
    } else {
        std::cerr << "Error al abrir el archivo de clientes para leer.\n";
    }
}




/**
 * @brief Crea y agrega un CDP para un cliente.
 * @param clientes Vector de punteros a clientes.
 */

void CDP::crearYAgregarCDPParaCliente(std::vector<Cliente*>& clientes) {

    if (clientes.empty()) {
        std::cout << "No hay clientes registrados.\n";
        return;
    }
     // Muestra la lista de clientes
    std::cout << "Clientes registrados:\n";

    for (const auto& cliente : clientes) {
        std::cout << "ID: " << cliente->obtenerID() << ", Nombre: " << cliente->obtenerNombre() << "\n";
    }
    // Ingresa el ID del cliente para el CDP
    std::cout << "Ingrese el ID del cliente para el CDP: ";
    int clienteID;
    std::cin >> clienteID;

     // Busca al cliente seleccionado
    Cliente* clienteSeleccionado = nullptr;
    for (auto& cliente : clientes) {
        if (cliente->obtenerID() == clienteID) {
            clienteSeleccionado = cliente;
            break;
        }
    }

    // Verifica si el cliente existe
    if (!clienteSeleccionado) {
        std::cout << "Cliente no encontrado.\n";
        return;
    }
    // Ingresa la moneda y el monto del CDP
    std::cout << "Seleccione la moneda (1 para Colones, 2 para Dolares): ";
    int monedaOpcion;
    std::cin >> monedaOpcion;
    std::string moneda = (monedaOpcion == 1) ? "Colones" : "Dolares";

    std::cout << "Ingrese el monto del CDP: ";
    double monto;
    std::cin >> monto;

    // Muestra las opciones de CDP según la moneda
    int plazoDias;
    double tasaInteres;
    if (monedaOpcion == 1) {
        std::cout << "Opciones de CDP en Colones:\n"
                  << "1. 365 dias con 5.84%" << " de interes\n"
                  << "2. 730 dias con 6.29%" << " de interes\n"
                  << "3. 1460 dias con 6.63%" << " de interes\n";
    } else {
        std::cout << "Opciones de CDP en Dolares:\n"
                  << "1. 365 dias con 3.28%" << " de interes\n"
                  << "2. 730 dias con 4.06%" << " de interes\n"
                  << "3. 1460 dias con 4.81%" << " de interes\n";
    }
    // Ingresa la opción del CDP
    std::cout << "Seleccione una opcion: ";
    int cdpOpcion;
    std::cin >> cdpOpcion;
    // Asigna el plazo y la tasa de interés según la opción del CDP
    switch (cdpOpcion) {
        case 1:
            plazoDias = 365;
            tasaInteres = (monedaOpcion == 1) ? 5.84 : 3.28;
            break;
        case 2:
            plazoDias = 730;
            tasaInteres = (monedaOpcion == 1) ? 6.29 : 4.06;
            break;
        case 3:
            plazoDias = 1460;
            tasaInteres = (monedaOpcion == 1) ? 6.63 : 4.81;
            break;
        default:
            std::cerr << "Opcion no valida, seleccionando opcion predeterminada.\n";
            plazoDias = 365;
            tasaInteres = (monedaOpcion == 1) ? 5.84 : 3.28;
            break;
    }
            // Crea un nuevo CDP y lo agrega al cliente
            CDP nuevoCDP(clienteSeleccionado->obtenerNombre(), monto, tasaInteres, plazoDias, moneda);
            clienteSeleccionado->agregarCDP(nuevoCDP);

        // Informa que el CDP se creó y agregó con éxito
    std::cout << "CDP creado y agregado al cliente con exito.\n";

}

/**
 * @brief Se almacenan los IDs asignados a clientes.
 */
std::set<int> Cliente::idsAsignados;


/**
 * @brief Constructor de la clase Cliente.
 * @param id Identificador único del cliente.
 * @param nombre Nombre del cliente.
 * @throw std::runtime_error Si el ID es inválido o ya está en uso.
 */
Cliente::Cliente(int id, std::string nombre) : id(id), nombre(nombre), cuentaColones(nullptr), cuentaDolares(nullptr) {
    if (!asignarID(id)) {
        throw std::runtime_error("ID invalido o ya utilizado.");
    }
}
/**
 * @brief Destructor de la clase Cliente.
 * Elimina el ID del conjunto de IDs asignados cuando se destruye un cliente.
 */
Cliente::~Cliente() {
    idsAsignados.erase(id);
}

/**
 * @brief Asigna un ID al cliente.
 * @param id ID a asignar.
 * @return true si el ID se asigna correctamente, false si el ID ya está en uso.
 */
bool Cliente::asignarID(int id) {
    auto resultado = idsAsignados.insert(id);
    return resultado.second;
}

/**
 * @brief Verifica si una cadena es un número válido y lo convierte.
 * @param str Cadena que se intenta convertir a número.
 * @param numero Variable donde se almacenará el número convertido.
 * @return true si la cadena es un número válido y se convierte correctamente, false en caso contrario.
 */
bool Cliente::esNumeroValido(const std::string& str, int& numero) {
    try {
        size_t pos;
        long num = std::stoi(str, &pos); //stoi convierte la cadena recibida a un entero, pero no acepta caracteres numericos
        if (pos != str.length() || num < 0 || num > 999999999) {
            return false;
        }
        numero = static_cast<int>(num);
        return true;
    } catch (const std::invalid_argument& e) {
        return false;
    } catch (const std::out_of_range& e) {
        return false;
    }
}

/**
 * @brief Obtiene el identificador único del cliente.
 * @return El identificador único del cliente.
 */
int Cliente::obtenerID() const {
    return id;
}

double CDP::obtenerMonto() const {
    return monto;
}

/**
 * @brief Obtiene el nombre del cliente.
 * @return El nombre del cliente.
 */
std::string Cliente::obtenerNombre() const {
    return nombre;
}


/**
 * @brief Agrega una cuenta bancaria al cliente.
 * 
 * @param clientes Vector de clientes registrados.
 */
void Cliente::agregarCuentaABanco(std::vector<Cliente*>& clientes) {
    // Verificar si hay clientes registrados
    if (clientes.empty()) {
        std::cout << "No hay clientes registrados.\n";
        return;
    }
    
    // Solicitar al usuario el ID del cliente al que se le desea agregar una cuenta
    std::cout << "Ingrese el ID del cliente a quien desea agregar una cuenta: ";
    int clienteID;
    std::cin >> clienteID;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // Buscar al cliente seleccionado por su ID
    Cliente* clienteSeleccionado = nullptr;
    for (auto& cliente : clientes) {
        if (cliente->obtenerID() == clienteID) {
            clienteSeleccionado = cliente;
            break;
        }
    }
    // Verificar si se encontró al cliente
    if (!clienteSeleccionado) {
        std::cout << "Cliente no encontrado.\n";
        return;
    }
    
    // Solicitar al usuario información para la nueva cuenta
    std::string numeroCuenta, moneda;
    double saldoInicial;
    std::cout << "Ingrese el numero de cuenta: ";
    std::getline(std::cin, numeroCuenta);

    int opcionMoneda;
    std::cout << "Seleccione la moneda:\n";
    std::cout << "1. CRC (Colones)\n";
    std::cout << "2. USD (Dolares)\n";
    std::cout << "Opcion: ";
    std::cin >> opcionMoneda;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // Asignar la moneda según la opción ingresada por el usuario
    if (opcionMoneda == 1) {
        moneda = "CRC";
    } else if (opcionMoneda == 2) {
        moneda = "USD";
    } else {
        std::cerr << "Opcion no valida. La cuenta no fue agregada." << std::endl;
        return;
    }
    // Solicitar al usuario el saldo inicial de la cuenta
    std::cout << "Ingrese el saldo inicial de la cuenta: ";
    std::cin >> saldoInicial;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // Crear una nueva instancia de CuentaBancaria
    CuentaBancaria* nuevaCuenta = new CuentaBancaria(clienteSeleccionado->obtenerNombre(), numeroCuenta, moneda, saldoInicial);
     // Agregar la cuenta al cliente correspondiente según la moneda
    if (moneda == "CRC") {
        clienteSeleccionado->agregarCuentaColones(nuevaCuenta);
    } else if (moneda == "USD") {
        clienteSeleccionado->agregarCuentaDolares(nuevaCuenta);
    } else {
        std::cerr << "Moneda no reconocida. La cuenta no fue agregada." << std::endl;
        delete nuevaCuenta; // Liberar memoria en caso de moneda no reconocida
    }
}


/**
 * @brief Intenta agregar una cuenta en colones al cliente.
 * 
 * @param cuenta Puntero a la cuenta en colones a agregar.
 */

void Cliente::agregarCuentaColones(CuentaBancaria* cuenta) {
     // Imprimir el estado actual de la cuenta en colones del cliente
    std::cout << "Intentando agregar cuenta en colones. Estado actual: " << (cuentaColones ? "Ya tiene cuenta" : "Sin cuenta") << std::endl;
    // Verificar si el cliente ya tiene una cuenta en colones
    if (!cuentaColones) {
        cuentaColones = cuenta; // Asignar la nueva cuenta en colones
        std::cout << "Cuenta en colones agregada con exito." << std::endl;
    } else {
        std::cerr << "El cliente ya tiene una cuenta en colones." << std::endl;
    }
}


/**
 * @brief Intenta agregar una cuenta en dólares al cliente.
 * 
 * @param cuenta Puntero a la cuenta en dólares a agregar.
 */
void Cliente::agregarCuentaDolares(CuentaBancaria* cuenta) {
    // Imprimir el estado actual de la cuenta en dólares del cliente
    std::cout << "Intentando agregar cuenta en dolares. Estado actual: " << (cuentaDolares ? "Ya tiene cuenta" : "Sin cuenta") << std::endl;
    // Verificar si el cliente ya tiene una cuenta en dólares
    if (!cuentaDolares) {
        cuentaDolares = cuenta;// Asignar la nueva cuenta en dólares
        std::cout << "Cuenta en dolares agregada con exito." << std::endl;
    } else {
        std::cerr << "El cliente ya tiene una cuenta en dolares." << std::endl;
    }
}

bool contieneDigitos(const std::string& str) {
    for (char c : str) {
        if (std::isdigit(c)) {
            return true;  // Devuelve true si encuentra al menos un dígito
        }
    }
    return false;  // Devuelve false si no se encontraron dígitos
}


/**
 * @brief Muestra el menú de atención al cliente y realiza operaciones según la opción seleccionada.
 * @note Para agregar cuentas o clientes, se solicita información interactivamente al usuario.
 */
std::ofstream Cliente::archivoClientes("clientes.txt", std::ios::app);
void mostrarMenuAtencion(){
std::vector<Cliente*> clientes;
    std::string entradaID, nombre;
    int id, opcion = 0;
    while (opcion != 5) {
        std::cout << "\n---BIENVENIDO AL MODO ATENCION---\n"
                  << "1. Crear Cliente\n"
                  << "2. Crear CDP para Cliente\n"
                  << "3. Mostrar Detalles del Cliente en un archivo aparte\n"
                  << "4. Agregar cuenta para Cliente\n"
                  << "5. Salir\n"
                  << "Ingrese una opcion para realizar operaciones en su cuenta, o bien, presione 5 para volver al menu principal: ";
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

                    if (contieneDigitos(nombre)) {
                        std::cout << "Error: El nombre no debe contener numeros.\n";
                    }else{
                        Cliente* nuevoCliente = new Cliente(id, nombre);
                        clientes.push_back(nuevoCliente);
                        std::cout << "\nCliente creado con exito.\n";
                    }
                } else {
                    std::cout << "ID invalido. Por favor, introduzca un numero de ID valido.\n";
                }
                break;
            }

            case 2: {
                CDP::crearYAgregarCDPParaCliente(clientes);
                clientes[clientes.size() - 1]->incrementarContadorCDPs();
                break;
                clientes[0]->incrementarContadorCDPs();
                
            }
            case 3: {
                // Abrir el archivo en modo de escritura
                std::ofstream archivo("clientes.txt",std::ios_base::app);
                if (archivo.is_open()) {
                   
                    for (auto& cliente : clientes) {
                        std::time_t tiempo_actual = std::time(nullptr);
                        std::tm* tiempo_info = std::localtime(&tiempo_actual);
                        archivo << "-----------------------------------------------------------------" << "\n";
                        archivo << "Fecha y hora: " << std::put_time(tiempo_info, "%Y-%m-%d %H:%M:%S") << "\n";
                        // Escribir la información del cliente en el archivo en lugar de imprimir en la terminal
                        archivo << "ID:" << cliente -> obtenerID() << ", Nombre:" << cliente->obtenerNombre() <<", CDPs activos:"<< cliente->obtenerContadorCDPs() <<
                        "\n";

                        archivo << "-----------------------------------------------------------------" << "\n";
                    }
                    archivo.close();  // Cerrar el archivo después de escribir
                    std::cout << "Informacion de clientes guardada en 'clientes.txt'.\n";
                } else {
                    std::cout << "Error al abrir el archivo para escribir.\n";
                }

                    break;
            }
            case 4: {
                Cliente::agregarCuentaABanco(clientes);
                break;
            }
            case 5:
                std::cout << "Volviendo al menu principal...\n";

            Cliente::archivoClientes.close();  // Cierra el archivo después de escribir
                
            default:
                std::cout << "Opcion no valida.\n";
                break;
        }
    }
    for (auto cliente : clientes) {
        delete cliente;
    }
    clientes.clear();
}
