// Librerias Locales:
#include "01.funciones_genericas.h"                // Funciones generales y librerias para el programa
#include "02.funciones_tipos_especie.h"            // Funciones para las Especies de Heroes y Orcos
#include "03.funciones_implementos.h"              // Funciones para Implementos
#include "04.funciones_mochila_personajes_jugar.h" // Funciones de la Mochila y Personajes Jugar
#include "05.funciones_poder_magico.h"             // Funciones para los Poderes Magicos
#include "06.funciones_mapa.h"                     // Funciones para el mapa (grafo)
#include "07.funciones_cargar_archivo.h"           // Funciones para la carga de archivos

#include "09.menus_main.h" // Todos los menus del main

void spawn_heroes(sala *sala_spawn_heroes, const personaje &personajes_jugar) // Carga toda la lista de heroes en 1 sala
{
    // Carga la lista de heroes de la sala de spawn
    // NO valida que solo sean 4 heroes. Ya se valido antes de empezar el juego
    personaje *actual = personajes_jugar.siguiente;
    while (actual != nullptr)
    {
        sala_spawn_heroes->lista_heroes.push_back(actual);
        actual = personajes_jugar.siguiente;
    }
}

void spawn_orcos(sala *sala_spawn_orcos)
{

    int cantidad_orcos_spawnear = (rand() % 5) + 1;
    cout << cantidad_orcos_spawnear << endl;
}

int main()
{
    sala *AA;
    for (size_t i = 0; i < 10; i++)
    {
        spawn_orcos(AA);
    }
}