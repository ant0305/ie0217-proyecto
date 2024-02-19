#ifndef BANCO_HPP
#define BANCO_HPP

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <set>
#include <limits>
#include <fstream>

class Cliente;

/**
 * @brief Clase que representa una cuenta bancaria.
 */
class CuentaBancaria {
public:
/**
     * @brief Constructor de la clase CuentaBancaria.
     * @param titular Nombre del titular de la cuenta.
     * @param numeroCuenta Número único de la cuenta.
     * @param moneda Tipo de moneda de la cuenta.
     * @param saldoInicial Saldo inicial de la cuenta (por defecto, 0.0).
     */
    CuentaBancaria(std::string titular, std::string numeroCuenta, std::string moneda, double saldoInicial = 0.0)
    : titular(titular), numeroCuenta(numeroCuenta), saldo(saldoInicial), moneda(moneda) {}

protected:
    std::string titular; ///< Nombre del titular de la cuenta.
    std::string numeroCuenta; ///< Número único de la cuenta.
    double saldo; ///< Saldo actual de la cuenta.
    std::string moneda; ///< Tipo de moneda de la cuenta.
};

/**
 * @brief Clase que representa un Certificado de Depósito a Plazo (CDP).
 */
class CDP {
private:
    std::string titular; ///< Titular del CDP.
    double monto; ///< Monto del CDP.
    double tasaInteres; ///< Tasa de interés del CDP.
    int plazoDias; ///< Plazo en días del CDP.
    std::string moneda; ///< Moneda del CDP.

public:
    /**
     * @brief Constructor de la clase CDP.
     * @param titular Titular del CDP.
     * @param monto Monto del CDP.
     * @param tasaInteres Tasa de interés del CDP.
     * @param plazoDias Plazo en días del CDP.
     * @param moneda Moneda del CDP.
     */
    CDP(std::string titular, double monto, double tasaInteres, int plazoDias, std::string moneda)
    : titular(titular), monto(monto), tasaInteres(tasaInteres), plazoDias(plazoDias), moneda(moneda) {}
    /**
     * @brief Método estático que crea y agrega un CDP para un cliente.
     * @param clientes Vector de punteros a objetos de la clase Cliente.
     */
    static void crearYAgregarCDPParaCliente(std::vector<Cliente*>& clientes);
    std::string obtenerInformacion() const {
        return "Titular: " + titular +
               "\nMonto: " + std::to_string(monto) +
               "\nTasa de Interés: " + std::to_string(tasaInteres) +
               "\nPlazo en Días: " + std::to_string(plazoDias) +
               "\nMoneda: " + moneda;
    }
};

/**
 * @brief Clase que representa un préstamo.
 */
class Prestamo {
private:
    std::string titular; ///< Titular del préstamo.
    double monto; ///< Monto del préstamo.
    double tasaInteres; ///< Tasa de interés del préstamo.
    int plazoMeses;  ///< Plazo en meses del préstamo.
    std::string moneda; ///< Moneda del préstamo.

public:
    /**
     * @brief Constructor de la clase Prestamo.
     * @param titular Titular del préstamo.
     * @param monto Monto del préstamo.
     * @param tasaInteres Tasa de interés del préstamo.
     * @param plazoMeses Plazo en meses del préstamo.
     * @param moneda Moneda del préstamo.
     */
    Prestamo(std::string titular, double monto, double tasaInteres, int plazoMeses, std::string moneda)
    : titular(titular), monto(monto), tasaInteres(tasaInteres), plazoMeses(plazoMeses), moneda(moneda) {}
    
    /**
     * @brief Método estático que calcula la información del préstamo.
     */
    static void calcularPrestamo();
    /**
     * @brief Metodo estatico que crea y agrega los prestamos
     * 
     */
    static void crearYAgregarPrestamos(std::vector<Cliente*>& clientes);
    /**
     * @brief Metodo para obtener la moneda del prestamo
     
     * @return el tipo de moneda 
     */
    std::string obtenerMoneda() const {
        return moneda;
    }
};

/**
 * @brief Clase que representa un préstamo.
 */
class Prestamo {
private:
    std::string titular; ///< Titular del préstamo.
    double monto; ///< Monto del préstamo.
    double tasaInteres; ///< Tasa de interés del préstamo.
    int plazoMeses;  ///< Plazo en meses del préstamo.
    std::string moneda; ///< Moneda del préstamo.

public:
    /**
     * @brief Constructor de la clase Prestamo.
     * @param titular Titular del préstamo.
     * @param monto Monto del préstamo.
     * @param tasaInteres Tasa de interés del préstamo.
     * @param plazoMeses Plazo en meses del préstamo.
     * @param moneda Moneda del préstamo.
     */
    Prestamo(std::string titular, double monto, double tasaInteres, int plazoMeses, std::string moneda)
    : titular(titular), monto(monto), tasaInteres(tasaInteres), plazoMeses(plazoMeses), moneda(moneda) {}
    
    /**
     * @brief Método estático que calcula la información del préstamo.
     */
    static void calcularPrestamo();
    /**
     * @brief Metodo estatico que crea y agrega los prestamos
     * 
     */
    static void crearYAgregarPrestamos(std::vector<Cliente*>& clientes);
    /**
     * @brief Metodo para obtener la moneda del prestamo
     
     * @return el tipo de moneda 
     */
    std::string obtenerMoneda() const {
        return moneda;
    }
};


/**
 * @brief Clase que representa a un cliente del banco.
 */
class Cliente {

public:
    int contadorCDPs = 0;
    int obtenerContadorCDPs() const {
            return contadorCDPs;
        }
    void incrementarContadorCDPs() {
        contadorCDPs++;
    }
    static std::set<int> idsAsignados; ///< Conjunto de IDs asignados a clientes.
    int id; ///< ID del cliente.
    std::string nombre; ///< Nombre del cliente.
    CuentaBancaria* cuentaColones; ///< Puntero a la cuenta en colones del cliente.
    CuentaBancaria* cuentaDolares; ///< Puntero a la cuenta en dólares del cliente.
    CDP* cdp;  ///< Puntero al Certificado de Depósito a Plazo (CDP) del cliente.
    static std::ofstream archivoClientes; ///< Flujo de salida para el archivo de clientes.
    Prestamo* prestamo; ///< Puntero al Prestamo del cliente.


    /**
     * @brief Constructor de la clase Cliente.
     * @param id ID del cliente.
     * @param nombre Nombre del cliente.
     */
    Cliente(int id, std::string nombre);

    /**
     * @brief Método estático para asignar un ID único al cliente.
     * @param id ID a asignar.
     * @return true si el ID se asigna correctamente, false si ya está en uso.
     */
    static bool asignarID(int id);

    /**
     * @brief Obtiene el ID del cliente.
     * @return ID del cliente.
     */
    int obtenerID() const;

    /**
     * @brief Obtiene el nombre del cliente.
     * @return Nombre del cliente.
     */
    std::string obtenerNombre() const;

    /**
     * @brief Obtiene el tipo de moneda.
     * @return el tipo de moneda
     */
    std::string obtenerMoneda() const {
        if (!prestamos.empty()) {
            return prestamos[0].obtenerMoneda();
        } else {
            return "";
        }
    }
    /**
     * @brief Metodo para obtener la lista de prestamos del cliente
     *
     * @return la lista
     */
    const std::vector<Prestamo>& obtenerPrestamos() const {
        return prestamos;
    }


    /**
     * @brief Método estático para verificar si una cadena es un número válido.
     * @param str Cadena a verificar.
     * @param numero Variable donde se almacenará el número convertido.
     * @return true si la cadena es un número válido, false de lo contrario.
     */
    static bool esNumeroValido(const std::string& str, int& numero);
    /**
     * @brief Agrega un Certificado de Depósito a Plazo (CDP) al cliente.
     * @param nuevoCDP Nuevo CDP a agregar.
     */
    void agregarCDP(const CDP &nuevoCDP);
    std::vector<CDP> cdps;///< Vector que almacena los CDPs del cliente.

    /**
     * @brief Agrega un Prestamo al cliente.
     * @param nuevoPrestamo  Nuevo Prestamo a agregar
     */
    void agregarPrestamo(const Prestamo &nuevoPrestamo);
    std::vector<Prestamo> prestamos; ///< Vector que almacena los prestamos del cliente.

    /**
     * @brief Agrega una cuenta al cliente.
     * @param clientes Vector de punteros a objetos de la clase Cliente.
     */
    void agregarCuentaColones(CuentaBancaria* cuenta);
    void agregarCuentaDolares(CuentaBancaria* cuenta);
    static void agregarCuentaABanco(std::vector<Cliente*>& clientes);
    /**
     * @brief Destructor de la clase Cliente.
     */
    ~Cliente();
};


/**
 * @brief Función que muestra el menú de atención.
 */
void mostrarMenuAtencion();



#endif
