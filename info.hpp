#ifndef INFO_HPP
#define INFO_HPP

#include <cstdlib>
#include <vector>
#include <stdexcept>
#include <set>
#include <limits>

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

// funciones prototipo
void MostrarMenuSecundario();

void InfoPrestamoPersonal();

void InfoPrestamoPrendario();

void InfoPrestamoHipotecario();

#endif
