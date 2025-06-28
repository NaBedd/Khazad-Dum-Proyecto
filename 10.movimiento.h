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

// NO le paren, pendiente terminar
void spawn_orcos(sala *sala_spawn_orcos, const Lista_especie &lista_especies_orco,
                 personaje &lista_personajes_orco)
{
    vector<string> nombresOrcos = {
        "Fenrir",
        "Grishnakh",
        "Ugluk",
        "Nazgul",
        "Dracula",
        "Goroth",
        "Mauhúr",
        "Shagrat",
        "Snaga",
        "Bolg",
        "Lugdush",
        "Ragash",
        "Thrak",
        "Zogrot",
        "Feo",
        "Ghash",
        "Durbag",
        "Muzgash",
        "Skorg",
        "Yaznaigh"};

    Especie *especie_nuevo_orco; // se declara para evitar problemas
    string nombre_nuevo_orco;
    bool nombre_asignado = false;

    // Cantidad de orcos a aparecer en su spawn:
    int cantidad_orcos_spawnear = (rand() % 5) + 1;

    // Selecciona las especies que apareceran y crea los personajes Orco
    for (size_t i = 0; i < cantidad_orcos_spawnear; i++)
    {
        // Si la lista es 0, no hace nada
        if (lista_especies_orco.cantidad > 0)
        {
            especie_nuevo_orco = lista_especies_orco.primero_especie;
            int especie_aleatoria = rand() % lista_especies_orco.cantidad;
            // Elige un num random dentro de la cantidad de especies
            for (size_t j = 0; j < especie_aleatoria; j++)
            {
                // Recorre la lista enlazada hasta dicho numero random
                especie_nuevo_orco = especie_nuevo_orco->siguiente;
            }
        }
        else // Nunca deberia de ejecutarse el else
        {
            cout << "La lista esta vacia (NUNCA DEBERIA PASAR)" << endl;
            return;
        }

        // Asignacion de nombre para el nuevo orco:
        personaje *actual = lista_personajes_orco.siguiente;
        // Si el jugador decide cargar los orcos del archivo
        // Usaran los mismos nombres con otro un numero al final
        while (actual != nullptr)
        {
            if (especie_nuevo_orco->nombre_especie == actual->tipo->nombre_especie) // Logica medio errada
            {
                // Nuevo nombre sera "Orco 1", "Orco 2", etc
                // El ciclo se repetira hasta recorrer toda la lista
                // Si hay varios de una misma especie, deberia de sumarle 1 al ID del ultimo
                // No necesariamente pq las listas no son ordenadas AAAAAAAAAAAAAAAAA
                nombre_nuevo_orco = actual->nombre + to_string(actual->identificador + 1);
                nombre_asignado = true;
            }
            actual = actual->siguiente;
        }
        if (!nombre_asignado) // Si hay orcos creados pero no de la especie seleccionada:
        // Tengo que asegurar que el nombre que salio no este repetido
        {
            int indice_random = rand() % nombresOrcos.size();
            nombre_nuevo_orco = nombresOrcos[indice_random];
        }

        // Creacion del nuevo personaje orco:
        cantidad_personaje_orco += 1;
        personaje *nuevo_orco = new personaje;

        nuevo_orco->vitalidad = especie_nuevo_orco->salud;

        nuevo_orco->tipo = especie_nuevo_orco;
    }
}
