#include "funciones.hpp"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <cmath>

void MostrarMenu (){ //Esta funcion ejecuta el menu.
    std::cout << "\n ---BIENVENIDO AL BANCO---\n";
    std::cout << "\n 1. Seleccione esta opcion si quiere consultar informacion\n";
    std::cout << "\n 2. Seleccine esta opcion si desea realizar operaciones en su cuenta.\n";
    std::cout << "\n 3. Salir\n";
}

void procesarOpcion(Cliente& cliente){
    
    int opcion;
    do{
        try{
        std::cout<< "Ingrese una opcion: "; 
        std::cin>>opcion;

        if (std::cin.fail()){
            throw std::runtime_error("Entrada no valida. Por favor, ingrese un numero.");
            }

        switch(opcion){
                case 1:
                //Modo_Informacion();
                case 2:
                //Modo_Atencion(cliente);
                case 3:
                std:: cout <<"Saliendo del programa. Gracias por utilizar nuestros servicios.\n";
                exit(0);
                default://Por si se escoge algo no valido
                std:: cout << "Opcion no valida. Intente de Nuevo...\n";   
            }
        } catch (std::exception const& e) {
            std::cerr << e.what() << std::endl;
            std::cin.clear();  // Limpiar el indicador de error
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Descartar la entrada no válida
        }
    } while (opcion != 3);

}

