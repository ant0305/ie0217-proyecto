#include "info.hpp"
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