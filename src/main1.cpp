#include <iostream>
#include "funciones.hpp"
#include <cstdlib>
 

/**
 * @brief Función principal que inicia el programa.
 * 
 * @return 0 si el programa se ejecuta con éxito.
 */
int main () {
    // Se crea un objeto de la clase Base llamado cliente.
    Base cliente;

    // Bucle infinito para mantener el programa en ejecución.
    while(1){
        // Se muestra el menú principal.
        MostrarMenu();
        // Se procesa la opción seleccionada por el usuario para el cliente actual.
        procesarOpcion(cliente);
    }
    // El programa nunca llegará a este punto, pero se incluye para indicar que la función ha terminado.
    return 0;
}