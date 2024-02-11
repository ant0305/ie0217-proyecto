#include <iostream>
#include "funciones.hpp"
#include <cstdlib>
 
int main () {
    Cliente cliente;

    while(1){
        MostrarMenu();
        procesarOpcion(cliente);
    }
    return 0;
}
