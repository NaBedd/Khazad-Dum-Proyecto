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

sala *spawn_puerta_destino(mapaGrafo &mapa, vector<int> &salas_puerta_pasadas) // Spawnear puerta destino
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
    cout << "La Puerta del Destino se encuentra en: " << nueva_sala_puerta->nombre << endl;

    // La ubicacion más actual de la puerta será la última posición de la lista
    salas_puerta_pasadas.push_back(nueva_sala_puerta->id);
    return nueva_sala_puerta;
}

sala *movimiento_puerta_destino(mapaGrafo &mapa, vector<int> &salas_puerta_pasadas,
                                const int turno_actual) // Spawnear nueva y eliminar anterior puerta destino
{
    sala *sala_puerta = nullptr;
    // Cada 5 turnos se mueve la puerta
    if (turno_actual % 5 != 0)
    {
        return sala_puerta;
    }
    // Si no esta vacio(deberia ser siempre), entonces:
    if (!salas_puerta_pasadas.empty())
    {
        // Cambia la sala anterior a falso
        sala *ultima_sala_puerta = encontrar_sala(mapa, salas_puerta_pasadas.back());
        ultima_sala_puerta->contiene_puerta_destino = false;
    }
    // El print de la nueva ubicacion esta en la funcion de spawn
    sala_puerta = spawn_puerta_destino(mapa, salas_puerta_pasadas);
    return sala_puerta;
}

bool verificacion_heroes_puerta(vector<int> &salas_puerta_pasadas)
{
    bool heroes_ganaron;
    if (!salas_puerta_pasadas.empty())
    {
        sala *sala_puerta_actual = encontrar_sala(grafo, salas_puerta_pasadas.back());
        if (!sala_puerta_actual->lista_heroes.empty() && sala_puerta_actual->lista_orcos.empty()) // 1. Los heroes llegan y NO hay orcos
        {
            cout << endl;
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
    }
    return false;
}
// se la agrgo para poder tener las estadisticas estandar
sala *turno_heroes(sala *&sala_actual_heroes, mapaGrafo &mapa, Lista_especie especies_heroes) // Turno de heroes
{
    do
    {
        cout << "  --- TURNO HEROES ---" << endl;
        cout << "1. Moverse de Sala." << endl;
        cout << "2. Consultar estado del equipo." << endl;
        opcion_interna = obtener_opcion();

        switch (opcion_interna)
        {
        case 1: // Movimiento heroes
        {
            sala_actual_heroes = movimiento_heroes(sala_actual_heroes, mapa, especies_heroes);
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
    } while (opcion_interna != 1);
    return sala_actual_heroes;
}

void turno_orcos(sala *sala_actual_heroes, mapaGrafo &mapa) // Turno de orcos
{
    cout << "\n  --- TURNO ORCOS ---"
         << endl;
    movimiento_orcos(sala_actual_heroes, mapa);
}

// se la agrgo para poder tener las estadisticas estandar
void juego(mapaGrafo &grafo, Lista_especie tipoEspecieHeroe, vector<int> &salas_puerta_pasadas)
{
    int turno = 0;

    sala *sala_actual_heroes = designar_sala_spawn_heroes(grafo); // Inicializa la sala
    spawn_heroes(sala_actual_heroes, personajes_jugar);           // Spawnea los heroes

    vector<int> lista_pesos_sala_heroes = dijkstra(sala_actual_heroes, grafo);                              // Lista de pesos desde sala heroes
    sala *sala_spawn_orcos = designar_sala_spawn_orcos(sala_actual_heroes, grafo, lista_pesos_sala_heroes); // designa spawn orcos
    spawnear_personajes_orcos(sala_spawn_orcos, tipoEspecieOrco, personajes_orco);                          // spawnea orcos antes del juego

    sala *sala_puerta_destino = spawn_puerta_destino(grafo, salas_puerta_pasadas); // Spawnear puerta destino

    while (!acabo_juego)
    {
        if (turno >= 25) // Si llega al turno 5 (puerta se ha movido 5 veces)
        {
            cout << endl;
            cout << "Los heroes han tardado demasiado en encontrar la puerta del destino" << endl;
            cout << "           La aldea ha perecido ante los imbatibles orcos" << endl;
            cout << "               Los heroes han fracasado..." << endl;
            acabo_juego = true;
            return;
        }

        cout << "Los Heroes se encuentran en: " << sala_actual_heroes->nombre << endl;
        for (personaje *actual : sala_actual_heroes->lista_heroes)
        {
            cout << "  " << actual->identificador << "." << actual->nombre << endl;
        }

        cout << "     --- TURNO " << turno << " ---" << endl;
        sala *sala_heroes = turno_heroes(sala_actual_heroes, grafo, tipoEspecieHeroe);

        // checkear_entidades_grafo(grafo);

        spawnear_personajes_orcos(sala_spawn_orcos, tipoEspecieOrco, personajes_orco); // spawnea orcos cada turno
        cout << "Orcos generados en: " << sala_spawn_orcos->nombre << "\n";
        turno_orcos(sala_heroes, grafo);

        bool heroes_ganaron = verificacion_heroes_puerta(salas_puerta_pasadas);
        if (heroes_ganaron)
        {
            // El cout esta en la funcion de verificacion_heroes_puerta
            return;
        }

        turno += 1;
        movimiento_puerta_destino(grafo, salas_puerta_pasadas, turno); // Primero se suma el turno para que en el 0 no la genere 2 veces
    }
}
