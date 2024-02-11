#include "info.hpp"
#include <stdexcept>
#include <limits>
using namespace std;

int main () {
    while(true){
        MostrarMenuSecundario();
        int opcion_secundario;
        do{
            try{
                cout << "Ingrese una opcion: "; 
                cin >> opcion_secundario;

                if (cin.fail()){
                    throw runtime_error("Opcion no valida. Por favor, ingrese un numero valido.");
                }

                switch(opcion_secundario){
                    case 1:
                        InfoPrestamoPersonal();
                        break;
                    case 2:
                        InfoPrestamoPrendario();
                        break;
                    case 3:
                        InfoPrestamoHipotecario();
                        break;
                    case 4:
                        exit(0);
                    default:
                        cout << "Opcion no valida. Intente de nuevo.\n";
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