#ifndef INFO_HPP
#define INFO_HPP
#include <string>
#include <iostream>
#include <cstdlib>

/**
 * @brief Clase que representa la información de un préstamo.
 * 
 * Esta clase contiene detalles sobre el titular del préstamo, el monto, la tasa de interés,
 * el plazo en meses y la moneda.
 */
class InfoPrestamo {
private:
    std::string titular; ///< Nombre del titular del préstamo.
    double monto; ///< Monto del préstamo.
    double tasaInteres; ///< Tasa de interés del préstamo.
    int plazoMeses;  ///< Plazo en meses del préstamo.
    std::string moneda; ///< Moneda en la que se otorga el préstamo.

public:
/**
     * @brief Constructor de la clase InfoPrestamo.
     * 
     * @param titular Nombre del titular del préstamo.
     * @param monto Monto del préstamo.
     * @param tasaInteres Tasa de interés del préstamo.
     * @param plazoMeses Plazo en meses del préstamo.
     * @param moneda Moneda en la que se otorga el préstamo.
     */
    InfoPrestamo(std::string titular, double monto, double tasaInteres, int plazoMeses, std::string moneda)
    : titular(titular), monto(monto), tasaInteres(tasaInteres), plazoMeses(plazoMeses), moneda(moneda) {}
     /**
     * @brief Método estático para calcular la información de un préstamo.
     * 
     * Este método realiza el cálculo del préstamo y muestra la información resultante.
     */
    static void calcularPrestamo();
};

// Funciones prototipo

/**
 * @brief Muestra el menú secundario.
 * 
 * Esta función proporciona un menú secundario para el usuario.
 */
void MostrarMenuSecundario();

/**
 * @brief Muestra la información de un préstamo personal.
 * 
 * Esta función presenta al usuario detalles sobre un préstamo personal.
 */
void InfoPrestamoPersonal();


/**
 * @brief Muestra la información de un préstamo prendario.
 * 
 * Esta función presenta al usuario detalles sobre un préstamo prendario.
 */

void InfoPrestamoPrendario();


/**
 * @brief Muestra la información de un préstamo hipotecario.
 * 
 * Esta función presenta al usuario detalles sobre un préstamo hipotecario.
 */
void InfoPrestamoHipotecario();

#endif