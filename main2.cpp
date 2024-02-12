#include "info.hpp"
#include <iostream>
#include <stdexcept>
#include <limits>
using namespace std;

int main () {
    while(true){
        MostrarMenuSecundario();
        int opcion_secundario;
        do{
            try{
                cout << "\nIngrese una opcion: "; 
                cin >> opcion_secundario;

                if (cin.fail()){
                    throw runtime_error("\nOpcion no valida. Por favor, ingrese un numero valido.\n");
                }

                switch(opcion_secundario){
                    case 1:
                        InfoPrestamoPersonal();
                        Prestamo::calcularPrestamo();
                        break;
                    case 2:
                        InfoPrestamoPrendario();
                        Prestamo::calcularPrestamo();
                        break;
                    case 3:
                        InfoPrestamoHipotecario();
                        Prestamo::calcularPrestamo();
                        break;
                    case 4:
                        exit(0);
                    default:
                        cout << "\nOpcion no valida. Intente de nuevo.\n";
                        break;
                }
            } catch (exception const& e) {
                cerr << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits < streamsize> :: max(), '\n');
            }
        } while(opcion_secundario != 4);
    }
    return 0;
}