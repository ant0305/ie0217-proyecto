#include "banco.hpp"
#include "funciones.hpp"
#include <iostream>
#include <vector>
#include <limits>
#include <memory>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <chrono>
#include    <algorithm>

/**
 * @brief Verifica y convierte una cadena de texto en un valor numerico.
 * 
 * Esta funcion intenta convertir una cadena de texto en un valor numerico.
 * Si la conversion es exitosa devuelve ese valor.
 * 
 * @param entrada La cadena de texto que se intentara convertir en un valor numerico.
 * @return El valor numerico si es valido, -1 si hay un error.
 */
double verificarMonto(const std::string& entrada) {
    try {
        size_t procesado;
        double monto = std::stod(entrada, &procesado);
        if (monto > 0 && procesado == entrada.length()) {
            return monto; // Retorna el monto si es un numero valido y positivo
        }
    // No se pudo convertir a double
    } catch (const std::invalid_argument& e) {
    // El numero es demasiado grande para caber en un double
    } catch (const std::out_of_range& e) {
    }
    return -1; // Indica un error si la entrada no es valida
}


/**
 * @brief Verifica si una cadena de texto representa una opcion valida.
 * 
 * Esta función intenta convertir una cadena de texto en un numero entero y verifica si ese numero es 1 o 2.
 * Si la conversion es exitosa devuelve verdadero.
 * 
 * @param entrada La cadena de texto que se intentara convertir en un numero entero.
 * @param numero Variable de salida para almacenar el numero convertido.
 * @return true si la cadena representa una opcion valida, false de lo contrario.
 */

bool esOpcionValida(const std::string& entrada, int& numero) {
    try {
        size_t pos = 0;
        numero = std::stoi(entrada, &pos);
        // Verificar que toda la cadena se haya convertido y que el numero sea 1 o 2
        if (pos == entrada.length() && (numero == 1 || numero == 2)) {
            return true;
        }
    } catch (const std::invalid_argument& e) {
        // Caracteres invalidos
    } catch (const std::out_of_range& e) {
        // Numero demasiado grande
    }
    return false;
}


/**
 * @brief Deposita una cantidad en la cuenta bancaria.
 * 
 * @param cantidad Cantidad a depositar.
 */
void CuentaBancaria::depositar(const std::string& entrada) {
    // Se verifica que el monto sea valido 
    double cantidad = verificarMonto(entrada);
    if (cantidad > 0) {
        saldo += cantidad;
        std::cout << "Deposito realizado con exito. Saldo actual: " << saldo << std::endl;
    } else {
        // Si la cantidad no es valida, se muestra un mensaje de error
        std::cerr << "Entrada no valida. Por favor, introduzca un monto valido." << std::endl;
    }
}


/**
 * @brief Retira una cantidad de la cuenta bancaria.
 * 
 * @param cantidad Cantidad a retirar.
 * @return true si el retiro fue exitoso, false si hay fondos insuficientes.
 */
bool CuentaBancaria::retirar(const std::string& entrada) {
    // Se verifica que la entrada sea valida
    double cantidad = verificarMonto(entrada);

    if (cantidad < 0) {
        // Si cantidad no es valida lanza un mensaje de error
        std::cerr << "Entrada no valida. Por favor, introduzca un monto valido." << std::endl;
        return false;
    }
    // Se verifica si hay fondos suficientes en la cuenta para el retiro
    if (cantidad <= saldo) {
        saldo -= cantidad;
        std::cout << "Retiro realizado con éxito. Saldo actual: " << saldo << std::endl;
        return true;
    } else {
        // Si no hay fondos suficientes, se muestra un mensaje de error y se retorna false
        std::cerr << "Fondos insuficientes para el retiro." << std::endl;
        return false;
    }
}


/**
 * @brief Transfiere una cantidad de dólares a colones.
 * 
 * @param cantidad Cantidad de dolares a transferir.
 * @param tipoDeCambio Tipo de cambio actual.
 * @param cuentaColones Cuenta en colones donde se depositarán los colones.
 */
void CuentaBancaria::transferirDolaresAColones(double cantidad, double tipoDeCambio, CuentaBancaria& cuentaColones) {

    if(this->obtenerSaldo() >= cantidad) { // Verifica si hay suficientes dolares
        double montoEnColones = cantidad * tipoDeCambio;
        this->actualizarSaldo(this->obtenerSaldo() - cantidad); // Retira dolares
        cuentaColones.actualizarSaldo(cuentaColones.obtenerSaldo() + montoEnColones); // Deposita en colones
        // Se imprimen mensajes de seguimiento
        std::cout << "Transferencia completada: $" << cantidad << " convertidos a CRC" << montoEnColones << std::endl;
        std::cout << "Nuevo saldo en dolares: $" << this->obtenerSaldo() << std::endl;
        std::cout << "Nuevo saldo en colones: CRC" << cuentaColones.obtenerSaldo() << std::endl;
    } else {
        // Mensaje si no hay fondos suficientes
        std::cerr << "Fondos insuficientes en la cuenta de dolares." << std::endl;
    }
}


/**
 * @brief Transfiere una cantidad de colones a dólares.
 * 
 * @param cantidad Cantidad de colones a transferir.
 * @param tipoDeCambio Tipo de cambio actual.
 * @param cuentaDolares Cuenta en dólares donde se depositarán los dólares.
 */
void CuentaBancaria::transferirColonesADolares(double cantidad, double tipoDeCambio, CuentaBancaria& cuentaDolares) {
    if(this->obtenerSaldo() >= cantidad) { // Verifica si hay suficientes colones
        double montoEnDolares = cantidad / tipoDeCambio;
        this->actualizarSaldo(this->obtenerSaldo() - cantidad); // Retira colones
        cuentaDolares.actualizarSaldo(cuentaDolares.obtenerSaldo() + montoEnDolares); // Deposita en dolares
        // Se imprimen mensajes de seguimiento
        std::cout << "Transferencia completada: CRC" << cantidad << " convertidos a $" << montoEnDolares << std::endl;
        std::cout << "Nuevo saldo en colones: CRC" << this->obtenerSaldo() << std::endl;
        std::cout << "Nuevo saldo en dolares: $" << cuentaDolares.obtenerSaldo() << std::endl;
    } else {
        // Mensaje si no hay fondos suficientes
        std::cerr << "Fondos insuficientes en la cuenta de colones." << std::endl;
    }
}


/**
 * @brief Transfiere una cantidad entre cuentas con posible conversion de moneda.
 * 
 * @param cuentaOrigen Cuenta de origen.
 * @param cuentaDestino Cuenta de destino.
 * @param cantidad Cantidad de dinero a transferir.
 * @param tipoDeCambio Tipo de cambio actual.
 * @param conversionNecesaria Indica si se necesita realizar una conversion de moneda.
 */
void CuentaBancaria::transferirAotraPersonaConConversion(CuentaBancaria& cuentaOrigen, CuentaBancaria& cuentaDestino, double cantidad, double tipoDeCambio, bool conversionNecesaria) {
    // Se convierte el monto a string para usarlo como argumento.
    std::string montoStr = std::to_string(cantidad);
    std::string montoConvertidoStr;

    if (!conversionNecesaria) {
        // Si no es necesaria la conversion se tranfiere el monto de forma comun
        if (cuentaOrigen.retirar(montoStr)) {
            cuentaDestino.depositar(montoStr);
            std::cout << "Transferencia completada sin necesidad de conversion." << std::endl;
        } else {
            std::cerr << "Fondos insuficientes en la cuenta de origen." << std::endl;
        }
    } else {
        // Calculamos el monto convertido segun la moneda de origen y destino y el tipo de cambio
        double montoConvertido = (cuentaOrigen.moneda == "USD" && cuentaDestino.moneda == "CRC") ? cantidad * tipoDeCambio : cantidad / tipoDeCambio;
        montoConvertidoStr = std::to_string(montoConvertido);  // Se convierte el monto a str para usarse en las funciones

        if (cuentaOrigen.retirar(montoStr)) {
            cuentaDestino.depositar(montoConvertidoStr);
            // Se muestra un mensaje si la tranferencia se hizo correctamente
            std::cout << "Transferencia y conversion completadas: " << cantidad << " de " << cuentaOrigen.moneda << " a " << montoConvertido << " en " << cuentaDestino.moneda << std::endl;
        } else {
            // Mensaje si  los fondos no son suficientes
            std::cerr << "Fondos insuficientes para completar la transferencia y conversion." << std::endl;
        }
    }
}


/**
 * @brief Realiza una transferencia entre cuentas de diferentes clientes
 * 
 * @param clientes Vector de punteros a los clientes del banco.
 * @param clienteSeleccionado Cliente que realiza la transferencia.
 * @return true si la transferencia fue exitosa, false si fallo por alguna razon.
 */
bool CuentaBancaria::realizarTransferenciaEntreCuentas(std::vector<Cliente*>& clientes, Cliente* clienteSeleccionado) {
    std::string entradaIdClienteDestino;
    std::cout << "Ingrese el ID del cliente destino: ";
    // Se captura el ID como texto para su posterior verificacion
    std::getline(std::cin, entradaIdClienteDestino);

    int idClienteDestino = 0;
    // Verifica si el input es valido utilizando el metodo esNumeroValido
    if (!Cliente::esNumeroValido(entradaIdClienteDestino, idClienteDestino)) {
        std::cout << "ID no valido. Por favor, ingrese un numero.\n";
        return false;
    }
    // Busca al cliente destino en el vector de clientes del banco
    Cliente* clienteDestino = nullptr;
    for (auto& cliente : clientes) {
        if (cliente->obtenerID() == idClienteDestino) { // Compara el ID del cliente con el ID proporcionado
            clienteDestino = cliente;
            break;
        }
    }
    // Se devuelve un mensaje de error si no se encontro el cliente
    if (!clienteDestino) {
        std::cout << "Cliente destino no encontrado.\n";
        return false;
    }

    int cuentaOrigenTipo = 0, cuentaDestinoTipo = 0;
    std::string entrada;

    // Se solicita y valida la cuenta de origen
    while (true) {
        std::cout << "Seleccione la cuenta de origen (1 para Dolares, 2 para Colones): ";
        std::getline(std::cin, entrada);
        if (esOpcionValida(entrada, cuentaOrigenTipo)) break;
        else std::cout << "Opcion no valida. Intente de nuevo.\n";
    }

    // Se solicita y valida la cuenta destino
    while (true) {
        std::cout << "Seleccione la cuenta destino (1 para Dolares, 2 para Colones): ";
        std::getline(std::cin, entrada);
        if (esOpcionValida(entrada, cuentaDestinoTipo)) break;
        else std::cout << "Opcion no valida. Intente de nuevo.\n";
    }

    std::string entradaMonto;
    std::cout << "Ingrese el monto a transferir: ";
    std::getline(std::cin, entradaMonto); // Captura el monto como texto
    // Se verifica si el monto es valido con la funcion verificarMonto
    double cantidad = verificarMonto(entradaMonto);
    if (cantidad <= 0) {
        std::cerr << "Entrada no valida. Por favor, introduzca un monto valido." << std::endl;
        return false;
    }

    // Determinar la cuenta de origen y la cuenta de destino
    CuentaBancaria* cuentaOrigen = (cuentaOrigenTipo == 1) ? clienteSeleccionado->cuentaDolares : clienteSeleccionado->cuentaColones;
    CuentaBancaria* cuentaDestino = (cuentaDestinoTipo == 1) ? clienteDestino->cuentaDolares : clienteDestino->cuentaColones;

    if (!cuentaOrigen || !cuentaDestino) {
        std::cout << "Una de las cuentas no existe.\n";
        return false;
    }

    if (cuentaOrigen->obtenerSaldo() < cantidad) {
        std::cout << "Fondos insuficientes en la cuenta de origen.\n";
        return false;
    }
    // Determinar si es necesaria una conversion de moneda
    bool conversionNecesaria = cuentaOrigenTipo != cuentaDestinoTipo;
    double tipoDeCambio = 1.0; // Si la conversion no es necesaria se hace una relacion de 1.
    if (conversionNecesaria) {
        std::cout << "Ingrese el tipo de cambio actual: ";
        std::cin >> tipoDeCambio;
    }

    // Guardar los saldos antes de la transferencia
    double saldoOrigenAntes = cuentaOrigen->obtenerSaldo();
    double saldoDestinoAntes = cuentaDestino->obtenerSaldo();

    transferirAotraPersonaConConversion(*cuentaOrigen, *cuentaDestino, cantidad, tipoDeCambio, conversionNecesaria);

    // Guardar los saldos despues de la transferencia
    double saldoOrigenDespues = cuentaOrigen->obtenerSaldo();
    double saldoDestinoDespues = cuentaDestino->obtenerSaldo();

    // Verificar si la transferencia fue exitosa basandose en el cambio de los saldos
    bool transferenciaExitosa = (saldoOrigenAntes > saldoOrigenDespues) && (saldoDestinoDespues > saldoDestinoAntes);
    return transferenciaExitosa;
}


/**
 * @brief Agrega un CDP a la lista de CDPs del cliente.
 * @param nuevoCDP Referencia al nuevo CDP a agregar.
 */

void Cliente::agregarCDP(const CDP &nuevoCDP) {
    cdps.push_back(nuevoCDP);
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
    std::cout<<"Usted selecciono: "<< monedaOpcion<<"\n";

    std::cout << "Ingrese el monto del CDP: ";
    double monto;
    std::cin >> monto;
    std::cout<<"Su monto es de: "<< monto<<"\n";

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
    // Incrementa el contador de prestamos del cliente
    clienteSeleccionado->incrementarContadorCDPs();
        // Informa que el CDP se creó y agregó con éxito
        // Abrir el archivo en modo de escritura
    std::ofstream archivo("registro.txt", std::ios_base::app);
    if (archivo.is_open()) {
        std::string nombreMoneda = (monedaOpcion == 1) ? "colones" : "dólares";
        std::time_t tiempo_actual = std::time(nullptr);
        std::tm* tiempo_info = std::localtime(&tiempo_actual);

        archivo << "-----------------------------------------------------------------------------" << "\n";
        archivo << "Fecha y hora: " << std::put_time(tiempo_info, "%Y-%m-%d %H:%M:%S") << "\n";
        archivo << "El cliente de ID: " << clienteSeleccionado->obtenerID() << ", abrió un CDP con un monto de "
                << std::fixed << std::setprecision(2) << monto << " " << nombreMoneda << "\n"
                << "a un plazo de " << plazoDias << " días y con " << tasaInteres << "% de interés." << "\n";
        archivo << "-----------------------------------------------------------------------------" << "\n";

        archivo.close();  // Cerrar el archivo después de escribir
        std::cout << "Informacion de clientes guardada en 'registro.txt'.\n";
    } else {
        std::cout << "Error al abrir el archivo para escribir.\n";
    }
    std::cout << "CDP creado y agregado al cliente con exito.\n";
}

/**
 * @brief Agrega un Prestamo a la lista de Prestamos del cliente.
 * @param nuevoPrestamo Referencia al nuevo Prestamo a agregar.
 */
void Cliente::agregarPrestamo(const Prestamo &nuevoPrestamo) {
    prestamos.push_back(nuevoPrestamo);
}


/**
 * @brief Funcion crea y agrega prestamos para un cliente
 * 
 * @param clientes Vector de punteros a clientes
 */
void Prestamo::crearYAgregarPrestamos(std::vector<Cliente*>& clientes) {
    // Verifica si hay clientes registrados
    if (clientes.empty()) {
        std::cout << "No hay clientes registrados.\n";
        return;
    }
    // Muestra la lista de clientes
    std::cout << "Clientes registrados:\n";
    for (const auto& cliente : clientes) {
        std::cout << "ID: " << cliente->obtenerID() << ", Nombre: " << cliente->obtenerNombre() << "\n";
    }

    // Ingresa el ID del cliente para el Prestamo
    std::cout << "Ingrese el ID del cliente para el Prestamo: ";
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

    // Muestra los tipos de Prestamos
    std::cout << "Tipos de Prestamos\n"
              << "1. Prestamo Personal\n"
              << "2. Prestamo Prendario\n"
              << "3. Prestamo Hipotecario\n"
              <<"\nSeleccione el tipo de Prestamo que desea adquirir: ";
    int tipoPrestamo;
    std::cin >> tipoPrestamo;

    // Ingresa la moneda y el monto del Prestamo
    std::cout << "Seleccione la moneda (1 para Colones, 2 para Dolares): ";
    int monedaOpcion;
    std::cin >> monedaOpcion;
    std::string moneda = (monedaOpcion == 1) ? "Colones" : "Dolares";

    // Verifica si ya tiene un prestamo en esa moneda
    for (const auto& prestamo : clienteSeleccionado->obtenerPrestamos()) {
        if (prestamo.obtenerMoneda() == moneda) {
            std::cout << "Cliente ya posee un prestamo en " << moneda;
            return;
        }
    }

    // Solicita el monto del Prestamo
    std::cout << "Ingrese el monto del Prestamo: ";
    double monto;
    std::cin >> monto;

    // Muestra las opciones de Prestamo según la moneda
    int plazoMeses;
    double tasaInteres;
    switch (tipoPrestamo){
        case 1:
            std::cout << "\nOpciones de prestamo en " <<moneda << ":\n";
            if (monedaOpcion == 1) {
                    std::cout << "\nOpciones de prestamo en Colones:\n"
                            << "1. 96 meses con 12.72% de interes\n"
                            << "2. 120 meses con 25.44% de interes\n"
                            << "3. 180 meses con 38.16% de interes\n";
            } else {
                std::cout << "\nOpciones de prestamo en Dolares:\n"
                        << "1. 96 meses con 10.09% de interes\n"
                        << "2. 120 meses con 20.18% de interes\n"
                        << "3. 180 meses con 30.27% de interes\n";
                }
            break;
        case 2:
            std::cout << "\nOpciones de prestamo en " <<moneda << ":\n";
            if (monedaOpcion == 1) {
                    std::cout << "\nOpciones de prestamo en Colones:\n"
                            << "1. 96 meses con 12.72% de interes\n"
                            << "2. 120 meses con 25.44% de interes\n"
                            << "3. 180 meses con 38.16% de interes\n";
            } else {
                std::cout << "\nOpciones de prestamo en Dolares:\n"
                          << "1. 96 meses con 10.09% de interes\n"
                          << "2. 120 meses con 20.18% de interes\n"
                          << "3. 180 meses con 30.27% de interes\n";
                }
            break;
        case 3:
            std::cout << "\nOpciones de prestamo en " <<moneda << ":\n";
            if (monedaOpcion == 1) {
                    std::cout << "\nOpciones de prestamo en Colones:\n"
                            << "1. 96 meses con 12.72% de interes\n"
                            << "2. 120 meses con 25.44% de interes\n"
                            << "3. 180 meses con 38.16% de interes\n";
            } else {
                std::cout << "\nOpciones de prestamo en Dolares:\n"
                        << "1. 96 meses con 10.09% de interes\n"
                        << "2. 120 meses con 20.18% de interes\n"
                        << "3. 180 meses con 30.27% de interes\n";
                }
            break;
        default:
            std::cerr << "\nTipo de prestamo no valido, selecione una opcion valida";
            return;
    }

    // Solicita la opción del Prestamo
    std::cout << "Seleccione una opcion: ";
    int prestamoOpcion;
    std::cin >> prestamoOpcion;
    // Asigna el plazo y la tasa de interés según la opción del CDP
    switch (prestamoOpcion) {
        case 1:
            plazoMeses = 96;
            tasaInteres = (monedaOpcion == 1) ? 12.72 : 10.09;
            break;
        case 2:
            plazoMeses = 120;
            tasaInteres = (monedaOpcion == 1) ? 25.44 : 20.18;
            break;
        case 3:
            plazoMeses = 180;
            tasaInteres = (monedaOpcion == 1) ? 38.16 : 30.27;
            break;
        case 4:
            return;
        default:
            std::cerr << "\nOpcion no valida, seleccionando opcion predeterminada.\n";
            plazoMeses = 84;
            tasaInteres = (monedaOpcion == 1) ? 12.72 : 10.09;
            break;
    }
    // Crea un nuevo Prestamo y lo agrega al cliente
    Prestamo nuevoPrestamo(clienteSeleccionado->obtenerNombre(), monto, tasaInteres, plazoMeses, moneda);
    clienteSeleccionado->agregarPrestamo(nuevoPrestamo);
    
    // Incrementa el contador de prestamos del cliente
    clienteSeleccionado-> incrementarContadorPrestamos();

    // Informa que el Prestamo se creó y agregó con éxito
    std::cout << "Prestamo creado y agregado al cliente con exito.\n";
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


/**
 * @brief obtiene el monto del CDP
 * 
 * @return monto del CDP
 */
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
    // Muestra la lista de clientes
    std::cout << "Clientes registrados:\n";

    for (const auto& cliente : clientes) {
        std::cout << "ID: " << cliente->obtenerID() << ", Nombre: " << cliente->obtenerNombre() << "\n";
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
    // Abrir el archivo en modo de escritura
        std::ofstream archivo("registro.txt",std::ios_base::app);
        if (archivo.is_open()) {
            
            for (auto& cliente : clientes) {
                std::string nombreMoneda = (opcionMoneda == 1) ? "colones" : "dólares";
                std::ostringstream ss;
                std::time_t tiempo_actual = std::time(nullptr);
                std::tm* tiempo_info = std::localtime(&tiempo_actual);
                archivo << "-----------------------------------------------------------------------------" << "\n";
                archivo << "Fecha y hora: " << std::put_time(tiempo_info, "%Y-%m-%d %H:%M:%S") << "\n";
                // Escribir la información del cliente en el archivo en lugar de imprimir en la terminal
                archivo << "El cliente de ID: " << cliente -> obtenerID() << ",abrió una cuenta, de numero: "<< numeroCuenta 
                <<" con un monto de " <<std::fixed << std::setprecision(2) <<saldoInicial <<" "<<nombreMoneda<<"\n";
                archivo << "-----------------------------------------------------------------------------" << "\n";
            }
            archivo.close();  // Cerrar el archivo después de escribir
            std::cout << "Informacion de clientes guardada en 'clientes.txt'.\n";
        } else {
            std::cout << "Error al abrir el archivo para escribir.\n";
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


/**
 * @brief Funcion que analiza si contiene digitos el string
 * 
 * @param str
 * @return true Devuelve true si se encuentra al menos un digito
 * @return false devuelve false si no se encontraron digitos
 */
bool contieneDigitos(const std::string& str) {
    for (char c : str) {
        if (std::isdigit(c)) {
            return true;
        }
    }
    return false;
}


/**
 * @brief Muestra el menú de atención al cliente y realiza operaciones según la opción seleccionada.
 * @note Para agregar cuentas o clientes, se solicita información interactivamente al usuario.
 */

std::ofstream Cliente::archivoClientes("clientes.txt", std::ios::app);
void mostrarMenuAtencion(){
std::vector<Cliente*> clientes;
    std::string entradaID, nombre;
    int opcion = 0;
    while (opcion != 7) {
        std::cout << "\n---BIENVENIDO AL MODO ATENCION---\n"
                  << "1. Crear Cliente\n"
                  << "2. Crear CDP para Cliente\n"
                  << "3. Agregar cuenta para Cliente\n"
                  << "4. Mostrar Detalles del Cliente en un archivo aparte\n"
                  << "5. Realizar Transacciones\n"
                  << "6. Agregar Prestamo\n"
                  << "7. Salir\n"
                  << "Ingrese una opcion para realizar operaciones en su cuenta, o bien, presione 7 para volver al menu principal: ";
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
                std::ofstream archivo("registro.txt", std::ios_base::app);
                if (archivo.is_open()) {
                    using namespace std::chrono;
                    // Obtener el tiempo actual para la marca de tiempo del nuevo cliente
                    auto ahora = system_clock::to_time_t(system_clock::now());
                    std::tm* tiempo_info = std::localtime(&ahora);

                    archivo << "-----------------------------------------------------------------" << "\n";
                    archivo << "                Fecha y hora: " << std::put_time(tiempo_info, "%Y-%m-%d %H:%M:%S") << "\n";
                    // Agregar solo la información del nuevo cliente sin iterar sobre todos los clientes
                    auto& nuevoCliente = clientes.back();
                    archivo << "Cliente registrado con ID: " << nuevoCliente->obtenerID() << ", y nombre: " << nuevoCliente->obtenerNombre() << ".\n";
                    archivo << "-----------------------------------------------------------------" << "\n";
                    archivo.close();  // Cerrar el archivo después de escribir el nuevo registro
                    std::cout << "Informacion del nuevo cliente guardada en 'registro.txt'.\n";
                } else {
                    std::cout << "Error al abrir el archivo para escribir.\n";
                }
                break;
            }

            case 2: {
                CDP::crearYAgregarCDPParaCliente(clientes);
                break;
            }
            case 3: {
                Cliente::agregarCuentaABanco(clientes);
                clientes[clientes.size() - 1]->incrementarContadorCuentas();
                break;
            }
            case 4: {
                // Abrir el archivo en modo de escritura
                std::ofstream archivo("clientes.txt",std::ios_base::app);
                if (archivo.is_open()) {
                   
                    for (auto& cliente : clientes) {
                        std::time_t tiempo_actual = std::time(nullptr);
                        std::tm* tiempo_info = std::localtime(&tiempo_actual);
                        archivo << "-----------------------------------------------------------------" << "\n";
                        archivo << "Fecha y hora: " << std::put_time(tiempo_info, "%Y-%m-%d %H:%M:%S") << "\n";
                        // Escribir la información del cliente en el archivo en lugar de imprimir en la terminal
                        archivo << "ID: " << cliente -> obtenerID() << ", Nombre: " << cliente->obtenerNombre() <<", CDPs activos: "<< cliente->obtenerContadorCDPs() <<
                        ", Cuentas activas:" << cliente ->obtenerContadorCuentas() <<", Prestamos Activos:"<<cliente ->obtenerContadorPrestamos()<<"\n";

                        archivo << "-----------------------------------------------------------------" << "\n";
                    }
                    archivo.close();  // Cerrar el archivo después de escribir
                    std::cout << "Informacion de clientes guardada en 'clientes.txt'.\n";
                } else {
                    std::cout << "Error al abrir el archivo para escribir.\n";
                }
                break;
            }
            case 5: {
                int transaccionOpcion;
                std::cout << "Seleccione la operacion a realizar:\n"
                        << "1. Transferir entre cuentas de diferentes clientes\n"
                        << "2. Transferir dinero entre cuentas del mismo cliente\n"
                        << "3. Depositar dinero en una cuenta\n"
                        << "4. Retirar dinero de una cuenta\n"
                        << "5. Salir\n"
                        << "Ingrese su opcion: ";
                std::cin >> transaccionOpcion;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                // Si el usuario elige salir, regresa al menú principal
                if (transaccionOpcion == 5) {
                    std::cout << "\nVolviendo al menu principal.\n";
                    break;
                }

                std::string inputID;
                std::cout << "Ingrese el ID del cliente que realizara la transaccion: ";
                std::getline(std::cin, inputID);

                int clienteID;
                if (Cliente::esNumeroValido(inputID, clienteID)) {
                    Cliente* clienteSeleccionado = nullptr;
                    for (auto& cliente : clientes) {
                        if (cliente->obtenerID() == clienteID) {
                            clienteSeleccionado = cliente;
                            break;
                        }
                    }
                    if (!clienteSeleccionado) {
                        std::cout << "Cliente no encontrado.\n";
                        break;
                    }

                    switch (transaccionOpcion) {
                        case 1: {
                            if (CuentaBancaria::realizarTransferenciaEntreCuentas(clientes, clienteSeleccionado)) {
                                std::cout << "Transferencia realizada con exito.\n";
                            } else {
                                std::cout << "La transferencia fallo.\n";
                            }
                            break;
                        }
                        case 2: {
                            // Opcion para transferencias entre cuentas del mismo cliente
                            std::string entradaEleccion;
                            std::cout << "Seleccione la operacion a realizar:\n"
                                    << "1. De la cuenta de dolares a la de colones\n"
                                    << "2. De la cuenta de colones a la de dolares\n"
                                    << "3. Salir\n"
                                    << "Ingrese su opcion: ";
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::getline(std::cin, entradaEleccion); // Captura la elección como string

                            int eleccionTransferencia = 0;
                            // Intenta convertir la entrada a un numero y verifica si es valida
                            if (!Cliente::esNumeroValido(entradaEleccion, eleccionTransferencia) || eleccionTransferencia < 1 || eleccionTransferencia > 3) {
                                std::cout << "Opcion no valida. Por favor, ingrese un numero valido.\n";
                                break;
                            }

                            if (eleccionTransferencia == 3) {
                                std::cout << "\nVolviendo al menu principal.\n";
                                break;
                            }
                            // Se solicita el monto a transferir
                            std::string entradaMonto, entradaTipoDeCambio;
                            std::cout << "Ingrese el monto a transferir: ";
                            std::getline(std::cin, entradaMonto);
                            // Se verifica que el monto sea valido
                            double monto = verificarMonto(entradaMonto);
                            if (monto <= 0) {
                                std::cerr << "Entrada no valida. Por favor, introduzca un monto positivo." << std::endl;
                                break;
                            }
                            // Se solicita el tipo de cambio
                            std::cout << "Ingrese el tipo de cambio actual: ";
                            std::getline(std::cin, entradaTipoDeCambio);
                            // Se verifica que el tipo de cambio sea valido
                            double tipoDeCambio = verificarMonto(entradaTipoDeCambio);
                            if (tipoDeCambio <= 0) {
                                std::cerr << "Entrada no valida. Por favor, introduzca un valor positivo para el tipo de cambio." << std::endl;
                                break;
                            }


                            switch (eleccionTransferencia) {
                                case 1: // De dólares a colones
                                    if (clienteSeleccionado->cuentaDolares && clienteSeleccionado->cuentaColones) {
                                        clienteSeleccionado->cuentaDolares->transferirDolaresAColones(monto, tipoDeCambio, *clienteSeleccionado->cuentaColones);
                                    } else {
                                        std::cerr << "El cliente no tiene configuradas las cuentas necesarias para realizar esta operacion." << std::endl;
                                    }
                                    break;
                                case 2: // De colones a dólares
                                    if (clienteSeleccionado->cuentaColones && clienteSeleccionado->cuentaDolares) {
                                        clienteSeleccionado->cuentaColones->transferirColonesADolares(monto, tipoDeCambio, *clienteSeleccionado->cuentaDolares);
                                    } else {
                                        std::cerr << "El cliente no tiene configuradas las cuentas necesarias para realizar esta operacion." << std::endl;
                                    }
                                    break;
                                default:
                                    std::cout << "Opcion no valida." << std::endl;
                                    break;
                            }
                            break;
                        }
                        case 3: {
                            // Depositar dinero en una cuenta
                            std::string entradaMonto;
                            std::cout << "Ingrese el monto a depositar: ";
                            // La entrada se toma como string
                            std::cin >> entradaMonto;

                            // Seleccionar la cuenta (Colones o Dolares)
                            int tipoCuenta;
                            std::cout << "Seleccione el tipo de cuenta para el deposito (1: Colones, 2: Dolares): ";
                            std::cin >> tipoCuenta;
                            if (tipoCuenta == 1 && clienteSeleccionado->cuentaColones) {
                                clienteSeleccionado->cuentaColones->depositar(entradaMonto);
                            } else if (tipoCuenta == 2 && clienteSeleccionado->cuentaDolares) {
                                clienteSeleccionado->cuentaDolares->depositar(entradaMonto);
                            } else {
                                std::cerr << "Cuenta no disponible o monto no valido." << std::endl;
                            }
                            break;
                        }
                        case 4: {
                            // Retirar dinero de una cuenta
                            std::string entradaMonto;
                            std::cout << "Ingrese el monto a retirar: ";
                            // La entrada se toma como string para su uso
                            std::cin >> entradaMonto;

                            // Se selecciona la cuenta (Colones o Dolares)
                            int tipoCuenta;
                            std::cout << "Seleccione el tipo de cuenta para el retiro (1: Colones, 2: Dolares): ";
                            std::cin >> tipoCuenta;
                            if (tipoCuenta == 1 && clienteSeleccionado->cuentaColones) {
                                clienteSeleccionado->cuentaColones->retirar(entradaMonto);
                            } else if (tipoCuenta == 2 && clienteSeleccionado->cuentaDolares) {
                                clienteSeleccionado->cuentaDolares->retirar(entradaMonto);
                            } else {
                                std::cerr << "Cuenta no disponible o monto no valido." << std::endl;
                            }
                            break;
                        }
                        default:
                            std::cout << "Opcion no valida." << std::endl;
                            break;
                    }
                } else {
                    std::cout << "ID de cliente no valido.\n";
                }
                break;
            }
            
            case 6: {
                Prestamo::crearYAgregarPrestamos(clientes);
                break;
            }
            case 7: {
                std::cout << "Volviendo al menu principal...\n";
                break;
            }
        }
        }
            Cliente::archivoClientes.close();  // Cierra el archivo después de escribir
}
