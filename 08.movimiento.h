// Librerias Locales:
#pragma once
#include "01.funciones_genericas.h"                // Funciones generales y librerias para el programa
#include "02.funciones_tipos_especie.h"            // Funciones para las Especies de Heroes y Orcos
#include "03.funciones_implementos.h"              // Funciones para Implementos
#include "04.funciones_mochila_personajes_jugar.h" // Funciones de la Mochila y Personajes Jugar
#include "05.funciones_poder_magico.h"             // Funciones para los Poderes Magicos
#include "06.funciones_mapa.h"                     // Funciones para el mapa (grafo)
#include "07.funciones_cargar_archivo.h"           // Funciones para la carga de archivos

#include "09.menus_main.h" // Todos los menus del main

/*Falta:
    -Logica para designar sala spawn orcos
    -Movimiento Heroes
    -Movimiento Orcos
    -Turnos de movimiento(turnos fuera de combate)
    -Aparicion de la puerta magica
        -Que la puerta se mueva
*/

// Dijkstra. Encuentra los caminos mas cortos desde el nodo X a todos los demas

// Encuentra el nodo con la adyacencia de menor peso de entre los nodos Pendientes por Visitar
sala *encontrarNodoMinimo(mapaGrafo &pendientes, vector<int> &distancias)
{
    int distancia_minima = INT_MAX;
    sala *minimo = nullptr;

    for (int i = 0; i < pendientes.mapa_salas.size(); i++) // Itera en los pendientes
    {
        sala *actual = pendientes.mapa_salas[i]; // Actual es un nodo todavia pendiente

        if (distancias[actual->id] < distancia_minima) // Si el actual es menor al minimo, se cambian
        {
            distancia_minima = distancias[actual->id];
            minimo = actual;
        }
    }

    return minimo; // retorna distancia minima
}

// Elimina al nodo de la lista de nodos Pendientes por Visitar
void eliminarNodoPendiente(mapaGrafo &pendientes, sala *nodoEliminar)
{
    for (size_t i = 0; i < pendientes.mapa_salas.size(); i++)
    {
        if (pendientes.mapa_salas[i] == nodoEliminar)
        {
            pendientes.mapa_salas.erase(pendientes.mapa_salas.begin() + i);
            break;
        }
    }
}

vector<int> dijkstra(sala *nodoInicial, const mapaGrafo &grafo)
{
    // Inicializacion de variables
    mapaGrafo pendientesVisitar;
    vector<bool> visitados(grafo.mapa_salas.size(), false);    // Llena el vector con False
    vector<int> lista_pesos(grafo.mapa_salas.size(), INT_MAX); // Llena el vector con Int_Max
    int peso_acumulado = 0;

    // 1. Inicializacion
    //   Agrega el nodo inicial a Pendientes por Visitar
    lista_pesos[nodoInicial->id] = 0; // La distancia del nodo hacia si mismo, es 0
    pendientesVisitar.mapa_salas.push_back(nodoInicial);

    // 2. Bucle Principal
    while (!pendientesVisitar.mapa_salas.empty()) // Mientras existan pendientes por visitar:
    {
        // Adyacente con menor peso
        sala *actual = encontrarNodoMinimo(pendientesVisitar, lista_pesos);

        eliminarNodoPendiente(pendientesVisitar, actual); // Ya se encontro su adyacencia minima. Se elimina de Pendientes

        if (!visitados[actual->id]) // Mientras el nodo actual no haya sido visitado:
        {
            for (size_t j = 0; j < actual->lista_adyacentes.size(); j++) // Recorre todos los vecinos(adyacentes) del actual
            {
                arista vecino = actual->lista_adyacentes[j];
                // Peso acumulado = Peso del nodo actual en Lista Pesos + Peso de la arista al nodo siguiente
                peso_acumulado = lista_pesos[actual->id] + vecino.distancia;

                // Si el nuevo peso (el acumulado) es mayor, se cambian
                if (peso_acumulado < lista_pesos[vecino.destino->id])
                {
                    lista_pesos[vecino.destino->id] = peso_acumulado;
                    if (!visitados[vecino.destino->id])
                    {
                        pendientesVisitar.mapa_salas.push_back(vecino.destino);
                    }
                }
            }
        }
        visitados[actual->id] = true;
    }
    return lista_pesos;
}

sala *designar_sala_spawn_heroes(const mapaGrafo &grafo) // Spawnean en sala random
{
    sala *sala_spawn_heroes = nullptr;
    int indice_random = rand() % grafo.mapa_salas.size();
    sala_spawn_heroes = encontrar_sala(grafo, indice_random);
    return sala_spawn_heroes;
}

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

sala *designar_sala_spawn_orcos(sala *sala_spawn_heroes, mapaGrafo &grafo, const vector<int> lista_pesos)
{
    sala *sala_spawn_orcos = nullptr;

    // Una vez que el dijkstra como tal ya este completado, se elige una de las salas como spawn de orcos:
    for (size_t i = 0; i < lista_pesos.size(); i++)
    {
        if (lista_pesos[i] >= 10)
        {
            sala_spawn_orcos = grafo.mapa_salas[i];
            break;
        }
    }
    // Si no encuentra una sala con al menos 10 de distancia, sera una sala random
    while (!sala_spawn_orcos)
    {
        int indice_random = rand() % grafo.mapa_salas.size();
        if (indice_random != sala_spawn_heroes->id)
        {
            sala_spawn_orcos = encontrar_sala(grafo, indice_random);
        }
    }
    return sala_spawn_orcos;
}

void spawnear_personajes_orcos(sala *sala_spawn_orcos, const Lista_especie &lista_especies_orco,
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
            cout << "La lista de especies esta vacia (NUNCA DEBERIA PASAR)" << endl;
            return;
        }

        // Asignacion de nombre para el nuevo orco:
        personaje *actual = lista_personajes_orco.siguiente;
        int max_id = 0;
        bool repetido = true;
        int nombres_restantes = nombresOrcos.size();
        // Si el jugador decide cargar los orcos del archivo
        // Usaran los mismos nombres con otro un numero al final
        while (actual != nullptr)
        {
            if (especie_nuevo_orco->nombre_especie == actual->tipo->nombre_especie) // Logica medio errada
            {
                // Nuevo nombre sera "Orco 1", "Orco 2", etc
                // Si hay varios de una misma especie, deberia de sumarle 1 al ID del ultimo(mayor ID)
                if (actual->identificador > max_id)
                {
                    max_id = actual->identificador;
                }
            }
            actual = actual->siguiente;
        }
        if (max_id > 0)
        {
            // Si ya hay orcos de la especie, agarra el mismo nombre + 1
            nombre_nuevo_orco = especie_nuevo_orco->nombre_especie + " " + to_string(max_id + 1);
        }
        else
        {
            // Sino, se asigna un nombre random de la lista
            // Se comprueba que no exista ya en ningun otro orco
            while (repetido && nombres_restantes > 0)
            {
                int indice_random = rand() % nombresOrcos.size();
                nombre_nuevo_orco = nombresOrcos[indice_random];
                repetido = false;
                personaje *verificar_nombre_actual = lista_personajes_orco.siguiente;
                while (verificar_nombre_actual != nullptr)
                {
                    if (verificar_nombre_actual->nombre == nombre_nuevo_orco)
                    {
                        repetido = true;
                        break;
                    }
                    verificar_nombre_actual = verificar_nombre_actual->siguiente;
                }
                // Si llega aca, es porque esta no repetido
                nombres_restantes--;
            }
            if (repetido)
            {
                // Si todos los nombres estan ocupados, pone uno generico
                nombre_nuevo_orco = "Orco " + to_string(max_id + 1);
            }
        }

        // Creacion del nuevo personaje orco:
        cantidad_personaje_orco += 1;
        personaje *nuevo_orco = new personaje;

        // Estadisticas del orco:
        nuevo_orco->nombre = nombre_nuevo_orco;
        nuevo_orco->identificador = max_id + 1;
        nuevo_orco->vitalidad = especie_nuevo_orco->salud;
        nuevo_orco->tipo = especie_nuevo_orco;

        // Se agrega a la lista enlazada
        nuevo_orco->siguiente = lista_personajes_orco.siguiente;
        lista_personajes_orco.siguiente = nuevo_orco;

        // Se agrega a la sala
        sala_spawn_orcos->lista_orcos.push_back(nuevo_orco);
    }
}
