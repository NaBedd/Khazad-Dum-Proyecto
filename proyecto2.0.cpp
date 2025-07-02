// GRUPO DE PROYECTO 1
// Integrantes:
// - Miguel Madera
// - Santiago Romero
// - Nabil Bedros

// Librerias Locales:
#include "01.funciones_genericas.h"                // Funciones generales y librerias para el programa
#include "02.funciones_tipos_especie.h"            // Funciones para las Especies de Heroes y Orcos
#include "03.funciones_implementos.h"              // Funciones para Implementos
#include "04.funciones_mochila_personajes_jugar.h" // Funciones de la Mochila y Personajes Jugar
#include "05.funciones_poder_magico.h"             // Funciones para los Poderes Magicos
#include "06.funciones_mapa.h"                     // Funciones para el mapa (grafo)
#include "07.funciones_cargar_archivo.h"           // Funciones para la carga de archivos
// #include "08.funciones_jugabilidad.h"  Todavia No esta listo
#include "09.menus_main.h" // Todos los menus del main

// Funcion declarada aqui porque sino daba error
// Sepa Dios por que
void poder_vigor_enano(personaje *lista_personajes_jugar)
{
    // Creacion del poder magico:
    // nuevo->nombre_poder = "Vigor de Enanos";
    // nuevo->funcion = "Poder magico que recupera la salud de todos los enanos.
    // Aumenta su salud en 100 y su fortaleza en 1000";

    personaje *actual_personaje = lista_personajes_jugar;
    bool modificado = false;

    if (actual_personaje == nullptr)
    {
        std::cout << "No hay personajes disponibles en el equipo" << endl;
    }
    while (actual_personaje != nullptr)
    {
        // SOLO FUNCIONA SI ENANO ESTA BIEN ESCRITO. "Enano" !!!!!!
        if (actual_personaje->tipo->nombre_especie == "Enano")
        {
            modificado = true;
            // Le recupera toda la vida (La devuelve a su valor original)
            actual_personaje->vitalidad = actual_personaje->tipo->salud;
            std::cout << "La vitalidad del personaje" << actual_personaje->nombre << "ha sido regenerada por completo (" << actual_personaje->vitalidad << ")" << endl;

            // Le aumenta la vida en 100
            actual_personaje->vitalidad += 100;
            std::cout << "La vitalidad del personaje" << actual_personaje->nombre << "ha sido aumentada en 100 (" << actual_personaje->vitalidad << ")" << endl;

            // Le aumenta la fortaleza en 1000
            actual_personaje->fortaleza += 1000;
            std::cout << "La fuerza del personaje ha sido aumentada en 1000 (" << actual_personaje->fortaleza << ")";

            actual_personaje = actual_personaje->siguiente;
        }
    }
    if (modificado == true)
    {
        std::cout << "Los personajes Enanos han sido modificados" << endl;
    }
    else
    {
        std::cout << "No hay personajes Enanos en el equipo" << endl;
    }
}

//-----------------------------------------------------------------------------------------------------
//----------------------------------- FUNCIONES JUGABILIDAD -------------------------------------------

// Aqui va todo lo que sea juego como tal, menu de acciones, para usar objetos, etc

//-----------------------------------------------------------------------------------------------------
//------------------------------ EJECUCION DEL PROGRAMA -----------------------------------------------

int main()
{
    // Semilla aleatoria inicializada (para el num random de orcos)
    srand(time(NULL));

    cout << "¡¡¡ Bienvenido al juego Khazad-Dum !!!" << endl;
    cout << "Se recomienda visitar todos los menus en orden descendente para una mejor experiencia de juego." << endl;

    // Menu mientras.
    do
    {
        menu_principal();
    } while (opcion_principal != 8 && !iniciar_juego); // Ambas opciones hacen que salga del menu

    // ---------------------------------- GAMEPLAY ------------------------------------
    if (opcion_principal != 8)
    {
        // Aqui va el juego: combate, etc
    }

    // --------------------------------------------------------------------------------
    // --------------- FIN DEL PROGRAMA. DESTRUCTORES DE ARCHIVOS TEMPORALES ----------

    // Destructor de especies
    destruir_lista_especie(tipoEspecieHeroe);
    destruir_lista_especie(tipoEspecieOrco); // se destruye la lista al final del programa.

    // Destructor de personajes
    destruir_lista_personajes(personajes_orco);
    destruir_lista_personajes(personajes_hero);

    // Destructor de implementos, personajes para jugar, poderes y mapa
    destruir_implementos(lista_implementos);
    destruir_poder_magico(lista_podere_magicos);
    destruir_personaje_jugar(personajes_jugar);
    destruir_grafo(grafo);

    cout << "Gracias por usar el programa. \n";
}
// fin del programa.
