#include "banco.hpp"
#include <iostream>
#include <vector>
#include <limits>

void Cliente::agregarCDP(const CDP &nuevoCDP) {
    cdps.push_back(nuevoCDP);
}

void CDP::crearYAgregarCDPParaCliente(std::vector<Cliente*>& clientes) {
    if (clientes.empty()) {
        std::cout << "No hay clientes registrados.\n";
        return;
    }

    std::cout << "Clientes registrados:\n";
    for (const auto& cliente : clientes) {
        std::cout << "ID: " << cliente->obtenerID() << ", Nombre: " << cliente->obtenerNombre() << "\n";
    }

    std::cout << "Ingrese el ID del cliente para el CDP: ";
    int clienteID;
    std::cin >> clienteID;

    Cliente* clienteSeleccionado = nullptr;
    for (auto& cliente : clientes) {
        if (cliente->obtenerID() == clienteID) {
            clienteSeleccionado = cliente;
            break;
        }
    }

    if (!clienteSeleccionado) {
        std::cout << "Cliente no encontrado.\n";
        return;
    }

    std::cout << "Seleccione la moneda (1 para Colones, 2 para Dolares): ";
    int monedaOpcion;
    std::cin >> monedaOpcion;
    std::string moneda = (monedaOpcion == 1) ? "Colones" : "Dolares";

    std::cout << "Ingrese el monto del CDP: ";
    double monto;
    std::cin >> monto;

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

    std::cout << "Seleccione una opcion: ";
    int cdpOpcion;
    std::cin >> cdpOpcion;

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

            CDP nuevoCDP(clienteSeleccionado->obtenerNombre(), monto, tasaInteres, plazoDias, moneda);
            clienteSeleccionado->agregarCDP(nuevoCDP);


    std::cout << "CDP creado y agregado al cliente con exito.\n";
}
std::set<int> Cliente::idsAsignados;

Cliente::Cliente(int id, std::string nombre) : id(id), nombre(nombre), cuentaColones(nullptr), cuentaDolares(nullptr) {
    if (!asignarID(id)) {
        throw std::runtime_error("ID invalido o ya utilizado.");
    }
}

Cliente::~Cliente() {
    idsAsignados.erase(id);
}

bool Cliente::asignarID(int id) {
    auto resultado = idsAsignados.insert(id);
    return resultado.second;
}


bool Cliente::esNumeroValido(const std::string& str, int& numero) {
    try {
        size_t pos;
        long num = std::stol(str, &pos);
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


int Cliente::obtenerID() const {
    return id;
}

std::string Cliente::obtenerNombre() const {
    return nombre;
}


void Cliente::agregarCuentaABanco(std::vector<Cliente*>& clientes) {
    if (clientes.empty()) {
        std::cout << "No hay clientes registrados.\n";
        return;
    }
    
    std::cout << "Ingrese el ID del cliente a quien desea agregar una cuenta: ";
    int clienteID;
    std::cin >> clienteID;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Cliente* clienteSeleccionado = nullptr;
    for (auto& cliente : clientes) {
        if (cliente->obtenerID() == clienteID) {
            clienteSeleccionado = cliente;
            break;
        }
    }

    if (!clienteSeleccionado) {
        std::cout << "Cliente no encontrado.\n";
        return;
    }

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

    if (opcionMoneda == 1) {
        moneda = "CRC";
    } else if (opcionMoneda == 2) {
        moneda = "USD";
    } else {
        std::cerr << "Opcion no valida. La cuenta no fue agregada." << std::endl;
        return;
    }

    std::cout << "Ingrese el saldo inicial de la cuenta: ";
    std::cin >> saldoInicial;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    CuentaBancaria* nuevaCuenta = new CuentaBancaria(clienteSeleccionado->obtenerNombre(), numeroCuenta, moneda, saldoInicial);

    if (moneda == "CRC") {
        clienteSeleccionado->agregarCuentaColones(nuevaCuenta);
    } else if (moneda == "USD") {
        clienteSeleccionado->agregarCuentaDolares(nuevaCuenta);
    } else {
        std::cerr << "Moneda no reconocida. La cuenta no fue agregada." << std::endl;
        delete nuevaCuenta;
    }
}



void Cliente::agregarCuentaColones(CuentaBancaria* cuenta) {
    std::cout << "Intentando agregar cuenta en colones. Estado actual: " << (cuentaColones ? "Ya tiene cuenta" : "Sin cuenta") << std::endl;
    if (!cuentaColones) {
        cuentaColones = cuenta;
        std::cout << "Cuenta en colones agregada con exito." << std::endl;
    } else {
        std::cerr << "El cliente ya tiene una cuenta en colones." << std::endl;
    }
}

void Cliente::agregarCuentaDolares(CuentaBancaria* cuenta) {
    std::cout << "Intentando agregar cuenta en dolares. Estado actual: " << (cuentaDolares ? "Ya tiene cuenta" : "Sin cuenta") << std::endl;
    if (!cuentaDolares) {
        cuentaDolares = cuenta;
        std::cout << "Cuenta en dolares agregada con exito." << std::endl;
    } else {
        std::cerr << "El cliente ya tiene una cuenta en dolares." << std::endl;
    }
}


void mostrarMenuAtencion(){
std::vector<Cliente*> clientes;
    std::string entradaID, nombre;
    int id, opcion = 0;

    while (opcion != 5) {
        std::cout << "\n---BIENVENIDO AL MODO ATENCION---\n"
                  << "1. Crear Cliente\n"
                  << "2. Crear CDP para Cliente\n"
                  << "3. Mostrar Detalles del Cliente\n"
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
                std::cout << "Volviendo al menu principal...\n";
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
}
