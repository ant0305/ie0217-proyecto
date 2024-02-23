#include "banco.hpp"
#include <iostream>
#include <vector>
#include <limits>
#include <memory>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <string>
#include <cmath>


/**
 * @brief Verifica si un ID ya existe en un archivo .csv
 * Busca el ID, si existe entonces muestra el mensaje error
 * @param nombreArchivo Nombre del archivo .csv
 * @param nuevoID El ID que se verifica
 * @return true Si ya existe
 */
bool verificarIDExistente(const std::string& nombreArchivo, int nuevoID) {
    std::ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo " << nombreArchivo << std::endl;
        return true; // Suponemos que hay un error, por precaución
    }

    std::string linea;

    while (std::getline(archivo, linea)) {
        std::istringstream ss(linea);
        std::string fechaHora, idStr, nombre;

        // Leer Fecha y hora, ID y nombre desde el formato CSV
        if (std::getline(ss, fechaHora, ',') &&
            std::getline(ss, idStr, ',') &&
            std::getline(ss, nombre, ',')) {
            
            // Si la columna "ID" está presente, intentamos extraer el ID.
            if (idStr.find("ID:") != std::string::npos) {
                idStr.erase(0, 4); // Eliminamos "ID: " del inicio de la cadena
            }

            int id;
            if (Cliente::esNumeroValido(idStr, id)) {
                if (id == nuevoID) {
                    std::cout << "ID ya existente en el archivo. Ingrese otro ID.\n";
                    archivo.close();
                    return true;
                } 
            } else {
                std::cerr << "Error: El formato del ID en el archivo no es válido.\n";
                archivo.close();
                return true;
            }
        }
    }

    archivo.close();

    // No se encontró el ID en el archivo
    return false;
}




/**
 * @brief Funcion que imprime los depositos en el archivo
 * Cuando el cliente realice depositos, lo imprime en registros.txt
 * @param cantidad el monto que se deposita
 * @param saldo el monto que tiene en la cuenta luego del deposito
 */
void imprimirDepositoenregistro(double cantidad,double saldo) {
    std::ofstream archivo("registro.txt", std::ios_base::app);
    if (archivo.is_open()) {
        std::ostringstream ss;
        std::time_t tiempo_actual = std::time(nullptr);
        std::tm* tiempo_info = std::localtime(&tiempo_actual);
        archivo << "-----------------------------------------------------------------------------" << "\n";
        archivo << "Fecha y hora: " << std::put_time(tiempo_info, "%Y-%m-%d %H:%M:%S") << "\n";
        // Escribir la información del cliente en el archivo en lugar de imprimir en la terminal
        archivo << "Deposito exitoso por un valor de: "<< cantidad <<" y su saldo actual es:" <<saldo<<"\n";
        archivo << "-----------------------------------------------------------------------------" << "\n";
        archivo.close();  // Cerrar el archivo después de escribir
        std::cout << "\nInformacion de clientes guardada en 'registro.txt'.\n";
    } else {
        std::cout << "\nError al abrir el archivo para escribir.\n";
    }
}



/**
 * @brief Funcion que imprime los retiros de dinero en un registro
 * Cuando el cliente retire dinero, se imprime en el archivo de texto
 * @param cantidad Monto de dinero que se retira
 * @param saldo Monto de la cuenta luego del retiro
 */
void imprimirRetiroenregistro(double cantidad, double saldo) {
    std::ofstream archivo("registro.txt", std::ios_base::app);
    if (archivo.is_open()) {
        std::ostringstream ss;
        auto tiempo_actual = std::time(nullptr);
        auto tiempo_info = std::localtime(&tiempo_actual);
        ss << std::put_time(tiempo_info, "%Y-%m-%d %H:%M:%S");
        archivo << "-----------------------------------------------------------------------------\n";
        archivo << "Fecha y hora: " << ss.str() << "\n";
        archivo << "Retiro exitoso por un valor de: " << cantidad << " y su saldo actual es: " << saldo << "\n";
        archivo << "-----------------------------------------------------------------------------\n";
        archivo.close();
        std::cout << "\nInformacion del retiro guardada en 'registro.txt'.\n";
    } else {
        std::cerr << "\nError al abrir el archivo para escribir.\n";
    }
}

/**
 * @brief Funcion que imprime en el registro las conversiones de dinero
 * Cuando se realicen conversiones de dinero, se imprimen en el archivo de texto
 * Se cambia de colones a dolares
 * @param cantidad El monto que se va a convertir a otra moneda
 * @param tipoDeCambio El valor que tiene la moneda
 * @param cuentaDolares Cuenta que posee la moneda final
 */
void imprimirConversionCaDenregistro(double cantidad, double tipoDeCambio, CuentaBancaria& cuentaDolares) {
    std::ofstream archivo("registro.txt", std::ios_base::app);
    if (archivo.is_open()) {
        std::ostringstream ss;
        std::time_t tiempo_actual = std::time(nullptr);
        std::tm* tiempo_info = std::localtime(&tiempo_actual);
        archivo << "-----------------------------------------------------------------------------" << "\n";
        archivo << "Fecha y hora: " << std::put_time(tiempo_info, "%Y-%m-%d %H:%M:%S") << "\n";
        double montoEnDolares = cantidad /tipoDeCambio;
        // Escribir la información del cliente en el archivo en lugar de imprimir en la terminal
        archivo << "Conversion exitosa de CRC"<<cantidad<<" a $ "<< montoEnDolares <<"\n";
        archivo << "-----------------------------------------------------------------------------" << "\n";
        archivo.close();  // Cerrar el archivo después de escribir
        std::cout << "\nInformacion de clientes guardada en 'registro.txt'.\n";
    } else {
        std::cout << "\nError al abrir el archivo para escribir.\n";
    }
}


/**
 * @brief Funcion que imprime en el registro las conversiones de dinero
 * Cuando se realicen conversiones de dinero, se imprimen en el archivo de texto
 * Se cambia de dolares a colones
 * @param cantidad El monto que se va a convertir a otra moneda
 * @param tipoDeCambio El valor que tiene esa moneda
 * @param cuentaColones Cuenta que posee la moneda final
 */
void imprimirConversionDaCenregistro(double cantidad, double tipoDeCambio, CuentaBancaria& cuentaColones) {
    std::ofstream archivo("registro.txt", std::ios_base::app);
    if (archivo.is_open()) {
        std::ostringstream ss;
        std::time_t tiempo_actual = std::time(nullptr);
        std::tm* tiempo_info = std::localtime(&tiempo_actual);
        archivo << "-----------------------------------------------------------------------------" << "\n";
        archivo << "Fecha y hora: " << std::put_time(tiempo_info, "%Y-%m-%d %H:%M:%S") << "\n";
        double montoEnColones = cantidad * tipoDeCambio;
        // Escribir la información del cliente en el archivo en lugar de imprimir en la terminal
        archivo << "Conversion exitosa de $"<<cantidad<<" a CRC "<< montoEnColones <<"\n";
        archivo << "-----------------------------------------------------------------------------" << "\n";
        archivo.close();  // Cerrar el archivo después de escribir
        std::cout << "\nInformacion de clientes guardada en 'registro.txt'.\n";
    } else {
        std::cout << "\nError al abrir el archivo para escribir.\n";
    }
}


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
        std::cout << "\nDeposito realizado con exito. Saldo actual: " << saldo << std::endl;
        imprimirDepositoenregistro(cantidad,saldo);
    } else {
        // Si la cantidad no es valida, se muestra un mensaje de error
        std::cerr << "\nEntrada no valida. Por favor, introduzca un monto valido.\n" << std::endl;
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
        std::cerr << "\nEntrada no valida. Por favor, introduzca un monto valido.\n" << std::endl;
        return false;
    }
    // Se verifica si hay fondos suficientes en la cuenta para el retiro
    if (cantidad <= saldo) {
        saldo -= cantidad;
        std::cout << "\nRetiro realizado con exito. Saldo actual: " << saldo << std::endl;
        imprimirRetiroenregistro(cantidad,saldo);
        return true;
    } else {
        // Si no hay fondos suficientes, se muestra un mensaje de error y se retorna false
        std::cerr << "\nFondos insuficientes para el retiro." << std::endl;
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
        std::cout << "\nTransferencia completada: $" << cantidad << " convertidos a CRC" << montoEnColones << std::endl;
        std::cout << "Nuevo saldo en dolares: $" << this->obtenerSaldo() << std::endl;
        std::cout << "Nuevo saldo en colones: CRC" << cuentaColones.obtenerSaldo() << std::endl;
        imprimirConversionDaCenregistro(cantidad,tipoDeCambio,cuentaColones);
    } else {
        // Mensaje si no hay fondos suficientes
        std::cerr << "\nFondos insuficientes en la cuenta de dolares." << std::endl;
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
        imprimirConversionCaDenregistro(cantidad,tipoDeCambio,cuentaDolares);
    } else {
        // Mensaje si no hay fondos suficientes
        std::cerr << "\nFondos insuficientes en la cuenta de colones." << std::endl;
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
            std::cout << "\nTransferencia completada sin necesidad de conversion." << std::endl;
        } else {
            std::cerr << "\nFondos insuficientes en la cuenta de origen." << std::endl;
        }
    } else {
        // Calculamos el monto convertido segun la moneda de origen y destino y el tipo de cambio
        double montoConvertido = (cuentaOrigen.moneda == "USD" && cuentaDestino.moneda == "CRC") ? cantidad * tipoDeCambio : cantidad / tipoDeCambio;
        montoConvertidoStr = std::to_string(montoConvertido);  // Se convierte el monto a str para usarse en las funciones

        if (cuentaOrigen.retirar(montoStr)) {
            cuentaDestino.depositar(montoConvertidoStr);
            // Se muestra un mensaje si la tranferencia se hizo correctamente
            std::cout << "\nTransferencia y conversion completadas: " << cantidad << " de " << cuentaOrigen.moneda << " a " << montoConvertido << " en " << cuentaDestino.moneda << std::endl;
        } else {
            // Mensaje si  los fondos no son suficientes
            std::cerr << "\nFondos insuficientes para completar la transferencia y conversion." << std::endl;
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
    std::cout << "\nIngrese el ID del cliente destino: ";
    // Se captura el ID como texto para su posterior verificacion
    std::getline(std::cin, entradaIdClienteDestino);

    int idClienteDestino = 0;
    // Verifica si el input es valido utilizando el metodo esNumeroValido
    if (!Cliente::esNumeroValido(entradaIdClienteDestino, idClienteDestino)) {
        std::cout << "\nID no valido. Por favor, ingrese un numero.\n";
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
        std::cout << "\nCliente destino no encontrado.\n";
        return false;
    }

    int cuentaOrigenTipo = 0, cuentaDestinoTipo = 0;
    std::string entrada;

    // Se solicita y valida la cuenta de origen
    while (true) {
        std::cout << "\nSeleccione la cuenta de origen (1 para Dolares, 2 para Colones): ";
        std::getline(std::cin, entrada);
        if (esOpcionValida(entrada, cuentaOrigenTipo)) break;
        else std::cout << "\nOpcion no valida. Intente de nuevo.\n";
    }

    // Se solicita y valida la cuenta destino
    while (true) {
        std::cout << "\nSeleccione la cuenta destino (1 para Dolares, 2 para Colones): ";
        std::getline(std::cin, entrada);
        if (esOpcionValida(entrada, cuentaDestinoTipo)) break;
        else std::cout << "\nOpcion no valida. Intente de nuevo.\n";
    }

    std::string entradaMonto;
    std::cout << "\nIngrese el monto a transferir: ";
    std::getline(std::cin, entradaMonto); // Captura el monto como texto
    // Se verifica si el monto es valido con la funcion verificarMonto
    double cantidad = verificarMonto(entradaMonto);
    if (cantidad <= 0) {
        std::cerr << "\nEntrada no valida. Por favor, introduzca un monto valido." << std::endl;
        return false;
    }
    
    // Determinar la cuenta de origen y la cuenta de destino
    CuentaBancaria* cuentaOrigen = (cuentaOrigenTipo == 1) ? clienteSeleccionado->cuentaDolares : clienteSeleccionado->cuentaColones;
    CuentaBancaria* cuentaDestino = (cuentaDestinoTipo == 1) ? clienteDestino->cuentaDolares : clienteDestino->cuentaColones;

    if (!cuentaOrigen || !cuentaDestino) {
        std::cout << "\nUna de las cuentas no existe.\n";
        return false;
    }

    if (cuentaOrigen->obtenerSaldo() < cantidad) {
        std::cout << "\nFondos insuficientes en la cuenta de origen.\n";
        return false;
    }
    // Determinar si es necesaria una conversion de moneda
    bool conversionNecesaria = cuentaOrigenTipo != cuentaDestinoTipo;
    double tipoDeCambio = 1.0; // Si la conversion no es necesaria se hace una relacion de 1.
    if (conversionNecesaria) {
        std::cout << "\nIngrese el tipo de cambio actual: ";
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
 * @brief Funcion que imprime los CDP en un registro
 * Cuando se creen y agreguen CDP se agregaran en un archivo de texto
 * @param monedaOpcion Tipo de moneda
 * @param monto El monto del CDP
 * @param plazoDias El plazo del CDP en dias
 * @param tasaInteres La tasa de interes del CDP
 * @param clienteSeleccionado El cliente al que se le agrega el CDP
 */
void imprimirCDPenregistro(int monedaOpcion, double monto, int plazoDias, double tasaInteres, Cliente* clienteSeleccionado) {
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
        std::cout << "\nInformacion de clientes guardada en 'registro.txt'.\n";
    } else {
        std::cout << "\nError al abrir el archivo para escribir.\n";
    }
}

/**
 * @brief Crea y agrega un CDP para un cliente.
 * @param clientes Vector de punteros a clientes.
 */

void CDP::crearYAgregarCDPParaCliente(std::vector<Cliente*>& clientes) {
   
    if (clientes.empty()) {
        std::cout << "\nNo hay clientes registrados el dia de hoy.\n";
        return;
    }
     // Muestra la lista de clientes
    std::cout << "Clientes registrados:\n";
    
    for (const auto& cliente : clientes) {
        std::cout << "ID: " << cliente->obtenerID() << ", Nombre: " << cliente->obtenerNombre() << "\n";
    }
    // Ingresa el ID del cliente para el CDP
    std::cout << "\nIngrese el ID del cliente para el CDP: ";
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
        std::cout << "\nCliente no encontrado.\n";
        return;
    }
    // Ingresa la moneda y el monto del CDP
    std::cout << "\nSeleccione la moneda (1 para Colones, 2 para Dolares): ";
    int monedaOpcion;
    std::cin >> monedaOpcion;
    std::string moneda = (monedaOpcion == 1) ? "Colones" : "Dolares";
    std::cout<<"\nUsted selecciono: "<< monedaOpcion<<"\n";

    std::cout << "\nIngrese el monto del CDP: ";
    double monto;
    do {
    std::cin >> monto;
    if (monto <= 0) {
        std::cout << "\nIngrese un monto valido mayor que 0. Intente de nuevo: ";
    }
    } while (monto <= 0);
    std::cout<<"\nSu monto es de: "<< monto<<"\n";

    // Muestra las opciones de CDP según la moneda
    int plazoDias;
    double tasaInteres;
    if (monedaOpcion == 1) {
        std::cout << "\nOpciones de CDP en Colones:\n"
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
            std::cerr << "\nOpcion no valida, seleccionando opcion predeterminada.\n";
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
    imprimirCDPenregistro(monedaOpcion,monto,plazoDias,tasaInteres,clienteSeleccionado);
    std::cout << "\nCDP creado y agregado al cliente con exito.\n";
}




/**
 * @brief Agrega un Prestamo a la lista de Prestamos del cliente.
 * @param nuevoPrestamo Referencia al nuevo Prestamo a agregar.
 */
void Cliente::agregarPrestamo(const Prestamo &nuevoPrestamo) {
    prestamos.push_back(nuevoPrestamo);
}

/**
 * @brief Obtiene el tipo de prestamo
 * Devuelve una cadena con el tipo de prestamo
 * @param tipoPrestamo El numero que representa cada prestamo
 * @return cadena del tipo de prestamo
 */
std::string obtenerTipoPrestamo(int tipoPrestamo) {
    switch (tipoPrestamo) {
        case 1:
            return "Prestamo Personal";
        case 2:
            return "Prestamo Prendario";
        case 3:
            return "Prestamo Hipotecario";
        default:
            return "No se conoce el tipo de prestamo";
    }
}


bool encabezado = false; ///< Varaible global que verifica si ya existe encabezado

/**
 * @brief funcion para escribir la primera fila del archivo prestamo
 * 
 * @param archivo_prestamos El archivo donde se imprimen los prestamos
 */
void escribirfila(std::ofstream& archivo_prestamos) {
    // Escribir la tabla en el archivo
    archivo_prestamos << std::setw(15) << std::left << "ID"
                        << std::setw(20) << std::left << "Cliente"
                        << std::setw(25) << std::left << "Tipo de Prestamo"
                        << std::setw(15) << std::left << "Moneda"
                        << std::setw(20) << std::left << "Plazo en meses"
                        << std::setw(20) << std::left << "Monto inicial"
                        << std::setw(20) << std::left << "Cuota mensual"
                        << std::setw(20) << std::left << "Tasa de intereses" << "\n";
}


/**
 * @brief Funcion que imprime los prestamos en el registro
 * 
 * @param monedaOpcion Se escoge la moneda
 * @param monto El monto del prestamo
 * @param plazoMeses El plazo en meses del prestamo
 * @param tasaInteres La tasa de interes del prestamo
 * @param clienteSeleccionado El cliente al que se le agrega el prestamo
 * @param tipoPrestamo El tipo del prestamo
 */
void escribirPrestamoenRegistro(int monedaOpcion, double monto, int plazoMeses, double tasaInteres, Cliente* clienteSeleccionado, int tipoPrestamo){
    std::ofstream archivo("registro.txt", std::ios_base::app);
    if (archivo.is_open()) {
        std::string nombreMoneda = (monedaOpcion == 1) ? "colones" : "dólares";
        std::time_t tiempo_actual = std::time(nullptr);
        std::tm* tiempo_info = std::localtime(&tiempo_actual);
        // llama a la funcion para conocer el tipo de prestamo
        std::string tipoPrestamoNombre = obtenerTipoPrestamo(tipoPrestamo);

        archivo << "-----------------------------------------------------------------------------" << "\n";
        archivo << "Fecha y hora: " << std::put_time(tiempo_info, "%Y-%m-%d %H:%M:%S") << "\n";
        archivo << "El cliente de ID: " << clienteSeleccionado->obtenerID() << ", abrió un Prestamo del tipo "
                << std::fixed << std::setprecision(2)<< obtenerTipoPrestamo(tipoPrestamo) << " con un\n"
                << std::fixed << std:: setprecision(2)<< "monto de "<< monto << " " << nombreMoneda << " a un plazo de " << plazoMeses 
                << " meses y con " << tasaInteres << "% de interés." << "\n";
        archivo << "-----------------------------------------------------------------------------" << "\n";

        archivo.close();  // Cerrar el archivo después de escribir
    } else {
        std::cout << "\nError al abrir el archivo registro.txt para escribir.\n";
    }
}
    


/**
 * @brief Funcion crea y agrega prestamos para un cliente
 * 
 * @param clientes Vector de punteros a clientes
 */
void Prestamo::crearYAgregarPrestamos(std::vector<Cliente*>& clientes) {
    // Verifica si hay clientes registrados
    if (clientes.empty()) {
        std::cout << "No hay clientes registradosel dia de hoy.\n";
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
    std::cout << "\nSeleccione la moneda (1 para Colones, 2 para Dolares): ";
    int monedaOpcion;
    std::cin >> monedaOpcion;
    std::string moneda = (monedaOpcion == 1) ? "Colones" : "Dolares";

    // Verifica si ya tiene un prestamo en esa moneda
    for (const auto& prestamo : clienteSeleccionado->obtenerPrestamos()) {
        if (prestamo.obtenerMoneda() == moneda) {
            std::cout << "\nCliente ya posee un prestamo en " << moneda;
            return;
        }
    }

    // Solicita el monto del Prestamo
    std::cout << "\nIngrese el monto del Prestamo: ";
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
    std::cout << "\nSeleccione una opcion: ";
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

   


    // Abrir el archivo 
    std::ofstream archivo_prestamos("prestamo.txt", std::ios_base::app);
    if (archivo_prestamos.is_open()) {
        if (!encabezado) {
            escribirfila(archivo_prestamos);
            encabezado = true;
        }

        std::string nombreMoneda = (monedaOpcion == 1) ? "colones" : "dólares";
        double tasaInteresMensual = tasaInteres / 100 / 12;
        double cuotaMensual = monto * tasaInteresMensual / (1 - std::pow(1 + tasaInteresMensual, -plazoMeses));

        archivo_prestamos << std::fixed << std::setprecision(2);
        archivo_prestamos << std::setw(15) << std::left << clienteSeleccionado->obtenerID()
                            << std::setw(20) << std::left << clienteSeleccionado->obtenerNombre()
                            << std::setw(25) << std::left << obtenerTipoPrestamo(tipoPrestamo)
                            << std::setw(16) << std::left << nombreMoneda
                            << std::setw(20) << std::left << plazoMeses
                            << std::setw(20) << std::left << monto
                            << std::setw(20) << std::left << cuotaMensual
                            << std::setw(20) << std::left << tasaInteres << "\n";

        archivo_prestamos.close();  // Cerrar el archivo después de escribir
    } else {
        std::cout << "\nError al abrir el archivo prestamo.txt para escribir.\n";
    }
    escribirPrestamoenRegistro(monedaOpcion,monto,plazoMeses, tasaInteres,  clienteSeleccionado, tipoPrestamo);

    // Informa que el Prestamo se creó y agregó con éxito
    std::cout << "\nPrestamo creado y agregado al cliente con exito.\n";
}


/**
 * @brief Realiza el pago de una cuota mensual del prestamo y calcula la cuota mensual del prestamo
 */
void Prestamo::pagarCuota() {
    double cuotaMensual = calcularCuotaMensual();
    if (saldoRestante >= cuotaMensual) {
        saldoRestante -= cuotaMensual;
        pagos.push_back(cuotaMensual);
        std::cout << "\nCuota de " << cuotaMensual << " " << moneda << " pagada exitosamente. Saldo restante: " << saldoRestante << std::endl;
    } else {
        std::cout << "\nEl saldo restante es menor que la cuota mensual. Realizando pago final de " << saldoRestante << std::endl;
        pagos.push_back(saldoRestante);
        saldoRestante = 0;
    }
}


/**
 * @brief Calcula la cuota mensual del prestamo
 * 
 * @return Devuelve el resultado de la cuota
 */
double Prestamo::calcularCuotaMensual() const {
    double tasaInteresMensual = tasaInteres / 12 / 100;
    double cuota = (monto * tasaInteresMensual) / (1 - pow(1 + tasaInteresMensual, -plazoMeses));
    return cuota;
}


/**
 * @brief Genera reporte del prestamo
 * Recibe el vector de prestamos y genera el reporte con los datos
 * @param prestamos El vector de prestamos
 */
void Prestamo::generarReporteDePrestamos(const std::vector<Prestamo>& prestamos) {
    std::ofstream reporte("reporte_prestamos.txt");
    if (reporte.is_open()) {
        for (const auto& prestamo : prestamos) {
            reporte << "Titular: " << prestamo.titular << "\n";
            reporte << "Monto inicial: " << prestamo.monto << " " << prestamo.moneda << "\n";
            reporte << "Tasa de interes: " << prestamo.tasaInteres << "%\n";
            reporte << "Plazo: " << prestamo.plazoMeses << " meses\n";
            reporte << "Saldo restante: " << prestamo.saldoRestante << "\n";
            reporte << "Pagos realizados:\n";
            for (const auto& pago : prestamo.pagos) {
                reporte << "- " << pago << " " << prestamo.moneda << "\n";
            }
            reporte << "-----------------------------\n";
        }
        reporte.close();
        std::cout << "\nReporte de prestamos generado exitosamente y guardado en 'reporte_prestamos.txt'.\n";
    } else {
        std::cout << "\nNo se pudo abrir el archivo para escribir el reporte.\n";
    }
}


/**
 * @brief Actualiza el registro de prestamos
 */
void Cliente::actualizarRegistroDePrestamos() {
   
    std::ofstream archivo("registro_prestamos.txt", std::ios::out | std::ios::trunc);
    if (archivo.is_open()) {
        for (const auto& prestamo : prestamos) {
            archivo << "Titular: " << nombre
                    << ", Monto: " << prestamo.obtenerMonto()
                    << ", Tasa de Interes: " << prestamo.obtenerTasaInteres()
                    << ", Plazo: " << prestamo.obtenerPlazoMeses() << " meses"
                    << ", Saldo Restante: " << prestamo.obtenerSaldoRestante() << "\n";
        }
        archivo.close();
    } else {
        std::cout << "\nNo se pudo abrir el archivo para actualizar el registro de prestamos.\n";
    }
}


/**
 * @brief Realiza el pago de la cuota mensual del prestamo
 * Verifica que tenga prestamos
 * Muestra los prestamos del cliente y se selecciona el prestamo a pagar
 */
void Cliente::pagarCuotaDePrestamo() {
    if (prestamos.empty()) {
        std::cout << "\nNo tienes prestamos activos.\n";
        return;
    }

    std::cout << "\nTiene los siguientes prestamos activos:\n";
    for (size_t i = 0; i < prestamos.size(); ++i) {
        std::cout << i + 1 << ". Monto: " << prestamos[i].obtenerMonto()
                  << ", Tasa de Interes: " << prestamos[i].obtenerTasaInteres()
                  << "%, Plazo: " << prestamos[i].obtenerPlazoMeses()
                  << " meses, Saldo Restante: " << prestamos[i].obtenerSaldoRestante() << "\n";
    }

    std::cout << "\nSelecciona el prestamo para pagar la cuota (1-" << prestamos.size() << "): ";
    size_t seleccion;
    std::cin >> seleccion;
    if (seleccion > 0 && seleccion <= prestamos.size()) {
        prestamos[seleccion - 1].pagarCuota();

        actualizarRegistroDePrestamos();

        std::cout << "\nCuota pagada exitosamente para el prestamo seleccionado.\n";
    } else {
        std::cout << "\nSeleccion no valida.\n";
    }
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
        throw std::runtime_error("\nID invalido o ya utilizado.\n");
    }
}


/**
 * @brief Destructor de la clase Cliente.
 * Libera la memoria de los punteros
 * Elimina el ID del conjunto de IDs asignados cuando se destruye un cliente.
 */
Cliente::~Cliente() {
    if (cuentaColones != nullptr) {
        delete cuentaColones;
        cuentaColones = nullptr;
    }
    if (cuentaDolares != nullptr) {
        delete cuentaDolares;
        cuentaDolares = nullptr;
    }
    if (cdp != nullptr) {
        delete cdp;
        cdp = nullptr;
    }
    if (prestamo != nullptr) {
        delete prestamo;
        prestamo = nullptr;
    }
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
 * @brief Funcion imprime la creacion de cuentas en el registro
 * Cuando se creen cuentas, se imprimen en el registro
 * @param cliente Cliente que crea la cuenta
 * @param numeroCuenta El numero de cuenta
 * @param opcionMoneda Se selecciona la moneda
 * @param saldoInicial El saldo inicial de la cuenta
 */
void imprimirCuentaenregistro(const Cliente* cliente, const std::string& numeroCuenta, int opcionMoneda, double saldoInicial) {
    std::ofstream archivo("registro.txt", std::ios_base::app);

    if (archivo.is_open()) {
        std::string nombreMoneda = (opcionMoneda == 1) ? "colones" : "dólares";
        std::ostringstream ss;
        std::time_t tiempo_actual = std::time(nullptr);
        std::tm* tiempo_info = std::localtime(&tiempo_actual);

        archivo << "-----------------------------------------------------------------------------" << "\n";
        archivo << "Fecha y hora: " << std::put_time(tiempo_info, "%Y-%m-%d %H:%M:%S") << "\n";
        // Escribir la información del cliente en el archivo en lugar de imprimir en la terminal
        archivo << "El cliente de ID: " << cliente->obtenerID() << ", abrió una cuenta, de numero: " << numeroCuenta
                << " con un monto de " << std::fixed << std::setprecision(2) << saldoInicial << " " << nombreMoneda << "\n";
        archivo << "-----------------------------------------------------------------------------" << "\n";

        archivo.close();  // Cerrar el archivo después de escribir
        std::cout << "\nInformacion de clientes guardada en 'clientes.txt'.\n";
    } else {
        std::cout << "\nError al abrir el archivo para escribir.\n";
    }
}

/**
 * @brief Agrega una cuenta bancaria al cliente.
 * 
 * @param clientes Vector de clientes registrados.
 */
void Cliente::agregarCuentaABanco(std::vector<Cliente*>& clientes) {
    // Verificar si hay clientes registrados
    if (clientes.empty()) {
        std::cout << "\nNo hay clientes registrados el dia de hoy.\n";
        return;
    }
    // Muestra la lista de clientes
    std::cout << "\nClientes registrados:\n";

    for (const auto& cliente : clientes) {
        std::cout << "ID: " << cliente->obtenerID() << ", Nombre: " << cliente->obtenerNombre() << "\n";
    }
    
    // Solicitar al usuario el ID del cliente al que se le desea agregar una cuenta
    std::cout << "\nIngrese el ID del cliente a quien desea agregar una cuenta: ";
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
        std::cout << "\nCliente no encontrado.\n";
        return;
    }
    
    // Solicitar al usuario información para la nueva cuenta
    std::string numeroCuenta, moneda;
    double saldoInicial;
    std::cout << "\nIngrese el numero de cuenta: ";
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
        std::cerr << "\nOpcion no valida. La cuenta no fue agregada." << std::endl;
        return;
    }
    // Solicitar al usuario el saldo inicial de la cuenta
    std::cout << "\nIngrese el saldo inicial de la cuenta: ";
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
        std::cerr << "\nMoneda no reconocida. La cuenta no fue agregada." << std::endl;
        delete nuevaCuenta; // Liberar memoria en caso de moneda no reconocida
    }
    clienteSeleccionado->incrementarContadorCuentas();
    imprimirCuentaenregistro(clienteSeleccionado, numeroCuenta, opcionMoneda, saldoInicial);
}


/**
 * @brief Funcion que borra las ultimas lineas en el registro
 */
void borrarUltimasLineasRegistro() {
    const int lineasABorrar = 4;
    // Leer todo el contenido del archivo
    std::ifstream archivoEntrada("registro.txt");
    std::vector<std::string> lineas;
    std::string linea;
    while (std::getline(archivoEntrada, linea)) {
        lineas.push_back(linea);
    }
    archivoEntrada.close();
    // Verificar si hay suficientes líneas para borrar
    if (lineas.size() >= lineasABorrar) {
        // Eliminar las últimas 4 líneas
        lineas.erase(lineas.end() - lineasABorrar, lineas.end());
    } else {
        std::cerr << "\nNo hay suficientes líneas para borrar.\n";
        return;
    }
    // Escribir el contenido actualizado en el archivo
    std::ofstream archivoSalida("registro.txt");
    for (const auto& l : lineas) {
        archivoSalida << l << "\n";
    }
    archivoSalida.close();
}




/**
 * @brief Intenta agregar una cuenta en colones al cliente.
 * 
 * @param cuenta Puntero a la cuenta en colones a agregar.
 */

void Cliente::agregarCuentaColones(CuentaBancaria* cuenta) {
     // Imprimir el estado actual de la cuenta en colones del cliente
    std::cout << "\nIntentando agregar cuenta en colones. Estado actual: " << (cuentaColones ? "Ya tiene cuenta" : "Sin cuenta") << std::endl;
    // Verificar si el cliente ya tiene una cuenta en colones
    if (!cuentaColones) {
        cuentaColones = cuenta; // Asignar la nueva cuenta en colones
        std::cout << "\nCuenta en colones agregada con exito." << std::endl;
    } else {
        std::cerr << "\nEl cliente ya tiene una cuenta en colones." << std::endl;
        borrarUltimasLineasRegistro();
        decrementarContadorCuentas();
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
        borrarUltimasLineasRegistro();
        decrementarContadorCuentas();
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
 * @brief Funcion que realiza transferencias
 * 
 * @param clientes Vector de punteros a los clientes del banco.
 */
void CuentaBancaria::realizarTransferencias(std::vector<Cliente*>& clientes) {
    int transaccionOpcion;
    std::cout << "\nSeleccione la operacion a realizar\n"
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
        return;
    }

    std::string inputID;
    std::cout << "\nIngrese el ID del cliente que realizara la transaccion: ";
    std::getline(std::cin, inputID);

    int clienteID;
    if (!Cliente::esNumeroValido(inputID, clienteID)) {
        std::cout << "\nID de cliente no valido.\n";
        return;
    }

    Cliente* clienteSeleccionado = nullptr;
    for (auto& cliente : clientes) {
        if (cliente->obtenerID() == clienteID) {
            clienteSeleccionado = cliente;
            break;
        }
    }

    if (!clienteSeleccionado) {
        std::cout << "\nCliente no encontrado.\n";
        return;
    }

    switch (transaccionOpcion) {
        case 1:
            if (CuentaBancaria::realizarTransferenciaEntreCuentas(clientes, clienteSeleccionado)) {
                                std::cout << "\nTransferencia realizada con exito.\n";
                            } else {
                                std::cout << "\nLa transferencia fallo.\n";
                            }
                            break;
            break;
        case 2:{
             // Opcion para transferencias entre cuentas del mismo cliente
            std::string entradaEleccion;
            std::cout << "\nSeleccione la operacion a realizar:\n"
                    << "1. De la cuenta de dolares a la de colones\n"
                    << "2. De la cuenta de colones a la de dolares\n"
                    << "3. Salir\n"
                    << "Ingrese su opcion: ";
                std::cin >> entradaEleccion; // Cambiado a std::cin para capturar la opción como string directamente.
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');// Captura la elección como string

            int eleccionTransferencia = stoi(entradaEleccion);
            // Intenta convertir la entrada a un numero y verifica si es valida
            if (!Cliente::esNumeroValido(entradaEleccion, eleccionTransferencia) || eleccionTransferencia < 1 || eleccionTransferencia > 3) {
                std::cout << "\nOpcion no valida. Por favor, ingrese un numero valido.\n";
                break;
            }

            if (eleccionTransferencia == 3) {
                std::cout << "\nVolviendo al menu principal.\n";
                break;
            }
            // Se solicita el monto a transferir
            std::string entradaMonto, entradaTipoDeCambio;
            std::cout << "\nIngrese el monto a transferir: ";
            std::getline(std::cin, entradaMonto);
            // Se verifica que el monto sea valido
            double monto = verificarMonto(entradaMonto);
            if (monto <= 0) {
                std::cerr << "\nEntrada no valida. Por favor, introduzca un monto positivo." << std::endl;
                break;
            }
            // Se solicita el tipo de cambio
            std::cout << "\nIngrese el tipo de cambio actual: ";
            std::getline(std::cin, entradaTipoDeCambio);
            // Se verifica que el tipo de cambio sea valido
            double tipoDeCambio = verificarMonto(entradaTipoDeCambio);
            if (tipoDeCambio <= 0) {
                std::cerr << "\nEntrada no valida. Por favor, introduzca un valor positivo para el tipo de cambio." << std::endl;
                break;
            }
            switch (eleccionTransferencia) {
                case 1: // De dólares a colones
                    if (clienteSeleccionado->cuentaDolares && clienteSeleccionado->cuentaColones) {
                        clienteSeleccionado->cuentaDolares->transferirDolaresAColones(monto, tipoDeCambio, *clienteSeleccionado->cuentaColones);
                    } else {
                        std::cerr << "\nEl cliente no tiene configuradas las cuentas necesarias para realizar esta operacion." << std::endl;
                    }
                    break;
                case 2: // De colones a dólares
                    if (clienteSeleccionado->cuentaColones && clienteSeleccionado->cuentaDolares) {
                        clienteSeleccionado->cuentaColones->transferirColonesADolares(monto, tipoDeCambio, *clienteSeleccionado->cuentaDolares);
                    } else {
                        std::cerr << "\nEl cliente no tiene configuradas las cuentas necesarias para realizar esta operacion." << std::endl;
                    }
                    break;
                default:
                    std::cout << "\nOpcion no valida." << std::endl;
                    break;
            }
        break;
        }   
        case 3:{
            // Depositar dinero en una cuenta
            std::string entradaMonto;
            std::cout << "\nIngrese el monto a depositar: ";
            // La entrada se toma como string
            std::cin >> entradaMonto;

            // Seleccionar la cuenta (Colones o Dolares)
            int tipoCuenta;
            std::cout << "\nSeleccione el tipo de cuenta para el deposito (1: Colones, 2: Dolares): ";
            std::cin >> tipoCuenta;
            if (tipoCuenta == 1 && clienteSeleccionado->cuentaColones) {
                clienteSeleccionado->cuentaColones->depositar(entradaMonto);
            } else if (tipoCuenta == 2 && clienteSeleccionado->cuentaDolares) {
                clienteSeleccionado->cuentaDolares->depositar(entradaMonto);
            } else {
                std::cerr << "\nCuenta no disponible o monto no valido." << std::endl;
                
            }
            break;
        }
        case 4:{
            // Retirar dinero de una cuenta
            std::string entradaMonto;
            std::cout << "\nIngrese el monto a retirar: ";
            // La entrada se toma como string para su uso
            std::cin >> entradaMonto;

            // Se selecciona la cuenta (Colones o Dolares)
            int tipoCuenta;
            std::cout << "\nSeleccione el tipo de cuenta para el retiro (1: Colones, 2: Dolares): ";
            std::cin >> tipoCuenta;
            if (tipoCuenta == 1 && clienteSeleccionado->cuentaColones) {
                clienteSeleccionado->cuentaColones->retirar(entradaMonto);
            } else if (tipoCuenta == 2 && clienteSeleccionado->cuentaDolares) {
                clienteSeleccionado->cuentaDolares->retirar(entradaMonto);
            } else {
                std::cerr << "\nCuenta no disponible o monto no valido." << std::endl;
            }
            break;
        }
            // Lógica para retirar dinero de una cuenta
            break;
        default:
            std::cout << "\nOpcion no valida.\n";
            break;
    }
}





/**
 * @brief Muestra el menú de atención al cliente y realiza operaciones según la opción seleccionada.
 * @note Para agregar cuentas o clientes, se solicita información interactivamente al usuario.
 */
std::ofstream Cliente::archivoClientes("clientes.csv", std::ios::app);
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
                  << "6. Realizar transacciones con prestamos\n"
                  << "7. Salir\n"
                  << "Ingrese una opcion: ";
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcion) {
            case 1: {
                std::cout << "\nIngrese el ID del cliente: ";
                std::getline(std::cin, entradaID);
                int id;

                if (Cliente::esNumeroValido(entradaID, id) && !verificarIDExistente("clientes.csv", id)) {
                    // Verificar si el ID ya existe en el vector de clientes
                    auto it = std::find_if(clientes.begin(), clientes.end(), [&id](const Cliente* cliente) {
                        return cliente->id == id;
                    });

                    if (it != clientes.end()) {
                        std::cout << "\nID invalido o ya utilizado.\n";
                    } else {
                        std::cout << "\nIngrese el nombre del cliente: ";
                        std::getline(std::cin, nombre);

                        if (contieneDigitos(nombre)) {
                            std::cout << "\nError: El nombre no debe contener numeros.\n";
                        } else {
                            Cliente* nuevoCliente = new Cliente(id, nombre);
                            clientes.push_back(nuevoCliente);
                            std::cout << "\nCliente creado con exito.\n";

                            std::ofstream archivo("registro.txt", std::ios_base::app);
                            if (archivo.is_open()) {
                                auto ahora = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                                std::tm* tiempo_info = std::localtime(&ahora);
                                archivo << "-----------------------------------------------------------------------------\n";
                                archivo << "Fecha y hora: " << std::put_time(tiempo_info, "%Y-%m-%d %H:%M:%S") << "\n";
                                archivo << "Cliente registrado con ID: " << id << ", y nombre: " << nombre << ".\n";
                                archivo << "-----------------------------------------------------------------------------\n";
                                archivo.close();
                                std::cout << "\nInformacion del nuevo cliente guardada en 'registro.txt'.\n";
                            } else {
                                std::cout << "\nError al abrir el archivo para escribir.\n";
                            }
                        }
                    }
                }
                break;
            }

            case 2: {
                CDP::crearYAgregarCDPParaCliente(clientes);
                break;
            }
            case 3: {
                Cliente::agregarCuentaABanco(clientes);
                break;
            }
            case 4: {
                // Abrir el archivo en modo de escritura
                std::ofstream archivo("clientes.csv", std::ios_base::app);
                        if (archivo.is_open()) {
                            for (auto& cliente : clientes) {
                                std::time_t tiempo_actual = std::time(nullptr);
                                std::tm* tiempo_info = std::localtime(&tiempo_actual);
                                archivo << "Fecha y hora: " << std::put_time(tiempo_info, "%Y-%m-%d %H:%M:%S")
                                 << ",ID: " << cliente->obtenerID() << ", Nombre: " << cliente->obtenerNombre()
                                        << ", CDPs activos: " << cliente->obtenerContadorCDPs()
                                        << ", Cuentas activas: " << cliente->obtenerContadorCuentas()
                                        << ", Prestamos Activos: " << cliente->obtenerContadorPrestamos() << "\n";
                            }
                            std::cout << "Informacion de clientes guardada en 'clientes.txt'.\n";
                        } else {
                            std::cout << "\nError al abrir el archivo para escribir.\n";
                        }
                        archivo.close();  // Cerrar el archivo después de escribir
                        break;
            }
            case 5: {
                CuentaBancaria::realizarTransferencias(clientes);
                break;
            }
            case 6: {
                int opcionPrestamo;
                do {
                    std::cout << "\nRealizar transacciones con prestamos:\n"
                            << "1. Agregar Prestamo\n"
                            << "2. Pagar cuota de Prestamo\n"
                            << "3. Solicitar reporte de Prestamos\n"
                            << "4. Volver\n"
                            << "Seleccione una opcion: ";
                    std::cin >> opcionPrestamo;

                    switch (opcionPrestamo) {
                        case 1: {
                            // Agregar un nuevo prestamo
                            Prestamo::crearYAgregarPrestamos(clientes);
                            break;
                        }
                        case 2: {
                            // Pagar cuota de prestamo
                            std::cout << "\nIngrese el ID del cliente para pagar cuota: ";
                            int clienteID;
                            std::cin >> clienteID;
                            bool clienteEncontrado = false;
                            for (auto& cliente : clientes) {
                                if (cliente->obtenerID() == clienteID) {
                                    clienteEncontrado = true;
                                    cliente->pagarCuotaDePrestamo();
                                    cliente->actualizarRegistroDePrestamos(); 
                                    break;
                                }
                            }
                            if (!clienteEncontrado) {
                                std::cout << "\nCliente no encontrado.\n";
                            }
                            break;
                        }
                        case 3: {
                            // Solicitar reporte de prestamos
                            std::cout << "\nIngrese el ID del cliente para solicitar el reporte de prestamos: ";
                            int clienteID;
                            std::cin >> clienteID;
                            bool clienteEncontrado = false;

                            for (auto& cliente : clientes) {
                                if (cliente->obtenerID() == clienteID) {
                                    clienteEncontrado = true;
                                    // Generar y mostrar el reporte de prestamos del cliente
                                    Prestamo::generarReporteDePrestamos(cliente->obtenerPrestamos());
                                    break;
                                }
                            }
                            if (!clienteEncontrado) {
                                std::cout << "\nCliente no encontrado.\n";
                            }
                            break;
                        }

                        case 4:
                            std::cout << "\nVolviendo al menu anterior...\n";
                            break;
                        default:
                            std::cout << "\nOpcion no valida. Por favor, intente de nuevo.\n";
                    }
                } while (opcionPrestamo != 4);
                break;
            }
            case 7: {
                std::cout << "\nVolviendo al menu principal...\n";
                break;
            }
        }
        }
            Cliente::archivoClientes.close();  // Cierra el archivo después de escribir
}
