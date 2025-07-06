#pragma once
#include "01.funciones_genericas.h"
#include "08.movimiento.h"
#include "10.combate.h"

/*
Para que es este archivo? → → →

Falta:
    -Turnos de movimiento(turnos fuera de combate)
    -Aparicion de la puerta magica
        -Que la puerta se mueva
    Debo de programar TurnoFueraCombate, para controlar el movimiento de la puerta magica y la aparicion de orcos
    La energia se les va a recuperar por cada TURNO de movimiento, no por sala movida
*/

void spawn_puerta_destino(mapaGrafo &mapa, vector<int> &salas_puerta_pasadas) // Spawnear puerta destino
{
    int indice_random;
    bool sala_valida = false;
    sala *nueva_sala_puerta = nullptr;

    while (!sala_valida)
    {
        // Indice aleatorio
        indice_random = rand() % mapa.mapa_salas.size();

        // Verifica si ya fue usado
        bool ya_usado = false;
        for (int indice_usado : salas_puerta_pasadas)
        {
            if (indice_random == indice_usado)
            {
                ya_usado = true;
                break;
            }
        }

        // Si no fue usado
        if (!ya_usado)
        {
            nueva_sala_puerta = encontrar_sala(mapa, indice_random);
            if (nueva_sala_puerta && !nueva_sala_puerta->contiene_puerta_destino)
            {
                sala_valida = true;
            }
        }
    }

    nueva_sala_puerta->contiene_puerta_destino = true;
    cout << "La Puerta del Destino se encuentra en " << nueva_sala_puerta->nombre << endl;

    // La ubicacion más actual de la puerta será la última posición de la lista
    salas_puerta_pasadas.push_back(nueva_sala_puerta->id);
    return;
}

void movimiento_puerta_destino(mapaGrafo &mapa, vector<int> &salas_puerta_pasadas,
                               const int turno_actual) // Spawnear nueva y eliminar anterior puerta destino
{

    // Cada 5 turnos se mueve la puerta
    if (turno_actual % 5 != 0)
    {
        return;
    }
    // Si no esta vacio(deberia ser siempre), entonces:
    if (!salas_puerta_pasadas.empty())
    {
        // Cambia la sala anterior a falso
        sala *ultima_sala_puerta = encontrar_sala(mapa, salas_puerta_pasadas.back());
        ultima_sala_puerta->contiene_puerta_destino = false;
    }
    // El print de la nueva ubicacion esta en la funcion de spawn
    spawn_puerta_destino(mapa, salas_puerta_pasadas);
}

bool verificacion_heroes_puerta(vector<int> &salas_puerta_pasadas)
{
    bool heroes_ganaron;
    sala *sala_puerta_actual = encontrar_sala(grafo, salas_puerta_pasadas.back());
    if (!sala_puerta_actual->lista_heroes.empty() && sala_puerta_actual->lista_orcos.empty()) // 1. Los heroes llegan y NO hay orcos
    {
        cout << "¡¡¡ FELICIDADES HEROES !!!" << endl;
        cout << "Han llegado a la puerta del destino" << endl;
        cout << "La aldea ha sido salvada de los malvados orcos." << endl;
        return heroes_ganaron = true;
    }
    // 2. Los heroes llegan y SI hay orcos
    // creeeo que primero se ejecuta el combate, entonces nunca pasaria este caso (????)
    else if (!sala_puerta_actual->lista_heroes.empty() && !sala_puerta_actual->lista_orcos.empty())
    {
        cout << "Verificar funcionamiento. Evitar multiples peleas" << endl;
    }
    return false;
}
// se la agrgo para poder tener las estadisticas estandar
void turno_heroes(sala *sala_actual_heroes, mapaGrafo &mapa, Lista_especie especies_herores) // Turno de heroes
{
    cout << "  --- TURNO HEROES ---" << endl;
    cout << "1. Moverse de Sala." << endl;
    cout << "2. Consultar estado del equipo." << endl;
    opcion_interna = obtener_opcion();

    switch (opcion_interna)
    {
    case 1: // Movimiento heroes
    {
        sala_actual_heroes = movimiento_heroes(sala_actual_heroes, mapa, especies_herores);
        break;
    }
    case 2: // Estado del equipo
    {
        mostrar_personajes_jugar(personajes_jugar);
        break;
    }
    default:
    {
        cout << "Invalido. Ingrese una opcion valida" << endl;
        break;
    }
    }
}
void turno_orcos(sala *sala_actual_heroes, mapaGrafo &mapa) // Turno de orcos
{
    movimiento_orcos(sala_actual_heroes, mapa);
}
// se la agrgo para poder tener las estadisticas estandar
void juego(int &turno, Lista_especie especies_heroes)
{
    sala *sala_actual_heroes;
    bool acabo_juego = false;
    if (turno == 0)
    {
        sala_actual_heroes = designar_sala_spawn_heroes(grafo);
        spawn_heroes(sala_actual_heroes, personajes_jugar);
    }

    while (!acabo_juego)
    {
        if (turno >= 25) // Si llega al turno 5 (puerta se ha movido 5 veces)
        {
            acabo_juego = true;
        }

        cout << "--- TURNO " << turno << " ---";
        turno_heroes(sala_actual_heroes, grafo, especies_heroes);
        turno_orcos(sala_actual_heroes, grafo);
        bool heroes_ganaron = verificacion_heroes_puerta(salas_puerta_pasadas);
        if (heroes_ganaron)
        {
            // El cout esta en la funcion de verificacion_heroes_puerta
            return;
        }

        movimiento_puerta_destino(grafo, salas_puerta_pasadas, turno);

        turno += 1;
    }
}
