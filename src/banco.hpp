#ifndef BANCO_HPP
#define BANCO_HPP

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <set>
#include <limits>

class Cliente;

class CuentaBancaria {
public:
    CuentaBancaria(std::string titular, std::string numeroCuenta, std::string moneda, double saldoInicial = 0.0)
    : titular(titular), numeroCuenta(numeroCuenta), saldo(saldoInicial), moneda(moneda) {}

protected:
    std::string titular;
    std::string numeroCuenta;
    double saldo;
    std::string moneda;
};

class CDP {
private:
    std::string titular;
    double monto;
    double tasaInteres;
    int plazoDias;
    std::string moneda;

public:
    CDP(std::string titular, double monto, double tasaInteres, int plazoDias, std::string moneda)
    : titular(titular), monto(monto), tasaInteres(tasaInteres), plazoDias(plazoDias), moneda(moneda) {}

    static void crearYAgregarCDPParaCliente(std::vector<Cliente*>& clientes);
};


class Cliente {
private:
    static std::set<int> idsAsignados;
    int id;
    std::string nombre;
    CuentaBancaria* cuentaColones;
    CuentaBancaria* cuentaDolares;
    CDP* cdp;

public:

    Cliente(int id, std::string nombre);

    static bool asignarID(int id);

    int obtenerID() const;
    std::string obtenerNombre() const;

    static bool esNumeroValido(const std::string& str, int& numero);

    void agregarCDP(const CDP &nuevoCDP);
    std::vector<CDP> cdps;

    void agregarCuentaColones(CuentaBancaria* cuenta);
    void agregarCuentaDolares(CuentaBancaria* cuenta);
    static void agregarCuentaABanco(std::vector<Cliente*>& clientes);
    ~Cliente();

};

class Prestamo {
private:
    std::string titular;
    double monto;
    double tasaInteres;
    int plazoMeses;
    std::string moneda;

public:
    Prestamo(std::string titular, double monto, double tasaInteres, int plazoMeses, std::string moneda)
    : titular(titular), monto(monto), tasaInteres(tasaInteres), plazoMeses(plazoMeses), moneda(moneda) {}

    static void calcularPrestamo();
};

void mostrarMenuAtencion();
#endif
