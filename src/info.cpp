#include "info.hpp"
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

void MostrarMenuSecundario (){
    cout << "\n ---BIENVENIDO AL MODO INFORMACION---";
    cout << "\n 1. Informacion Prestamo Personal\n";
    cout << "\n 2. Informacion Prestamo Prendario\n";
    cout << "\n 3. Informacion Prestamo Hipotecario\n";
    cout << "\n 4. Salir \n";
}

void InfoPrestamoPersonal(){
    cout << "\n ---Informacion sobre los Prestamos Personales---\n";
    cout << "Este prestamo es un financiamiento de dinero por un periodo establecido, la persona recibe una suma de dinero que luego debe de ser reembolsada junto a un porcentaje adicional (intereses generados).";
    cout << "\nEl uso que se le va a dar a este capital es un factor crucial al tomar la decision de solicitar un prestamo. Se debe de preveer la necesidad que va a cubrir, este puede ser destinado a:";
    cout << "\n     1. Gastos medicos como emergencias, en los cuales, se puede utilizar para abordar imprevistoso como tratamientos dentales de urgencia o gastos veterinarios inesperados en una mascota.";
    cout << "\n     2. Inversiones como la compra de activas con el objetivo de aumentar el patrimonio personal, como en el caso de  compras de electrodomesticos para el hogar.";
    cout << "\n     3. Consumo como solventar las necesidades cotidianas,ya sea, reemplazar una computadora averiada o comprar un celular nuevo.\n";
}

void InfoPrestamoPrendario() {
    cout << "\n ---Informacion sobre Prestamos Prendarios---\n";
    cout << "Este prestamo es una forma de financiamiento en la cual la persona ofrece una prenda como garantia o colateral para obtener un prestamo, generalmente es un bien mueble como vehiculos, motocicletas, entre otros.";
    cout << "\nPor tanto, el bien ofrecido funciona como garantia hasta que se cancele el prestamo. El bien adquirido queda prendado a favor de la entidad que brinda el financiamiento hasta que finalice el pago del prestamo.\n";
}

void InfoPrestamoHipotecario() {
    cout << "\n ---Informacion sobre Prestamos Hipotecarios---\n";
    cout << "El prestamo hipotecario es un prestamo con garantia hipotecaria, es decir, un inmueble es utilizado como garantia, estos creditos son adquiridos para la compra de lotes, viviendas, entre otros.";
    cout << "Por tanto, el bien adquirido queda hipotecado a favor de la entiendad financiera hasta que finalice el pago del prestamo.";
}

void InfoPrestamo::calcularPrestamo(){
    int monedaOpcion;
    do{
        std::cout << "\nSeleccione la moneda (1 para Colones, 2 para Dolares): ";
        std::cin >> monedaOpcion;

        if (monedaOpcion != 1 && monedaOpcion != 2) {
            std::cout << "Por favor, ingrese una opción válida (1 o 2)." << std::endl;
        std::string moneda = (monedaOpcion == 1) ? "Colones" : "Dolares";
        }
    }while (monedaOpcion != 1 && monedaOpcion != 2);
    std::string moneda = (monedaOpcion == 1) ? "Colones" : "Dolares";
    std::cout << "Ha seleccionado: " << moneda << std::endl;
        

    std::cout << "\nIngrese el monto del prestamo: ";
    double monto;
    std::cin >> monto;

    int plazoMeses;
    double tasaInteres;
    if (monedaOpcion == 1) {
        std::cout << "\nOpciones de prestamo en Colones:\n"
                  << "1. 144 meses con 12.72% de interes\n"
                  << "2. 108 meses con 25.44% de interes\n"
                  << "3. 84 meses con 38.16% de interes\n"
                  << "4. Volver al menu\n";
    } else {
        std::cout << "\nOpciones de prestamo en Dolares:\n"
                  << "1. 144 meses con 10.09% de interes\n"
                  << "2. 108 meses con 20.18% de interes\n"
                  << "3. 84 meses con 30.27% de interes\n"
                  << "4. Volver al menu\n";
    }

    std::cout << "Seleccione una opcion: ";
    int prestamoOpcion;
    std::cin >> prestamoOpcion;

    switch (prestamoOpcion) {
        case 1:
            plazoMeses = 144;
            tasaInteres = (monedaOpcion == 1) ? 12.72 : 10.09;
            break;
        case 2:
            plazoMeses = 108;
            tasaInteres = (monedaOpcion == 1) ? 25.44 : 20.18;
            break;
        case 3:
            plazoMeses = 84;
            tasaInteres = (monedaOpcion == 1) ? 38.16 : 30.27;
            break;
        case 4:
            return;
        default:
            std::cerr << "\nOpcion no valida, seleccionando opcion predeterminada.\n";
            plazoMeses = 144;
            tasaInteres = (monedaOpcion == 1) ? 12.72 : 10.09;
            break;
    }

    // calcula la cuota mensual
    double tasaInteresMensual = tasaInteres / 100 / 12;
    double cuotaMensual = monto * tasaInteresMensual / (1 - std::pow(1 + tasaInteresMensual, -plazoMeses));

    // Codigo para generar la tabla
    std::cout << std::setw(10) << std::left << "Mes"
              << std::setw(15) << std::left << "Cuota"
              << std::setw(15) << std::left << "Intereses"
              << std::setw(20) << std::left << "Pago sin Intereses"
              << std::setw(20) << std::left << "Monto Restante\n";

    double montoRestante = monto;
    for (int mes = 1; mes <= plazoMeses; ++mes) {
        double intereses = montoRestante * tasaInteresMensual;
        double amortizacion = cuotaMensual - intereses;
        montoRestante -= amortizacion;
        std::cout << std::setw(10) << mes
                  << std::setw(15) << std::fixed << std::setprecision(2) << cuotaMensual
                  << std::setw(15) << std::fixed << std::setprecision(2) << intereses
                  << std::setw(20) << std::fixed << std::setprecision(2) << amortizacion
                  << std::fixed << std::setprecision(2) << std::setw(20) << montoRestante << "\n";
    }
}