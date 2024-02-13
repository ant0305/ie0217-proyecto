#include <iostream>
#include "funciones.hpp"
#include <cstdlib>
 
int main () {
    Base cliente;

    while(1){
        MostrarMenu();
        procesarOpcion(cliente);
    }
    return 0;
}