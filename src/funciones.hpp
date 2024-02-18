#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP
#include <string>
#include <iostream>
#include <cstdlib>

/**
 * @brief Se define esta estructura BASE, en la cual se monta el MAIN, para ejecutar 
 * todo el sistema de finanzas.
 */

struct Base
{
    int Cedula;  
};



/**
 * @brief Muestra el menú principal del programa.
 */

void MostrarMenu();

/**
 * @brief Procesa la opción seleccionada por el usuario.
 * @param cliente Referencia a un objeto de tipo Base que representa al cliente actual.
 */

void procesarOpcion(Base& cliente);


#endif