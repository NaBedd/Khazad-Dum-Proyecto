// Librerias Locales:
#pragma once
#include "01.funciones_genericas.h"          // Funciones generales y librerias para el programa
#include "02.funciones_tipos_especie.h"      // Funciones para las Especies de Heroes y Orcos
#include "03.funciones_implementos.h"        // Funciones para Implementos
#include "04.funciones_mochila_personajes_jugar.h" // Funciones de la Mochila y Personajes Jugar
#include "05.funciones_poder_magico.h"       // Funciones para los Poderes Magicos
#include "06.funciones_mapa.h"               // Funciones para el mapa (grafo)
#include "07.funciones_cargar_archivo.h"     // Funciones para la carga de archivos
#include "09.menus_main.h"                   // Todos los menus del main
#include "10.combate.h"
#include <utility> // Para std::pair
#include <queue>   // Para std::priority_queue
#include <vector>  // Para std::vector
#include <limits>  // Para INT_MAX

/*Falta:
    -Turnos de movimiento(turnos fuera de combate)
    -Aparicion de la puerta magica
        -Que la puerta se mueva
    Debo de programar TurnoFueraCombate, para controlar el movimiento de la puerta magica y la aparicion de orcos
    La energia se les va a recuperar por cada TURNO no por sala movida
    */

// Dijkstra. Encuentra los caminos mas cortos desde el nodo X a todos los demas

// Encuentra el nodo con la adyacencia de menor peso de entre los nodos Pendientes por Visitar
sala *encontrarNodoMinimo(mapaGrafo &pendientes, std::vector<int> &distancias)
{
    int distancia_minima = std::numeric_limits<int>::max(); // Usa std::numeric_limits para INT_MAX
    sala *minimo = nullptr;

    for (size_t i = 0; i < pendientes.mapa_salas.size(); i++) // Itera en los pendientes
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

std::vector<int> dijkstra(sala *nodoInicial, mapaGrafo &grafo)
{
    // 1. Validación inicial
    if (!nodoInicial || grafo.mapa_salas.empty())
    {
        std::cout << "Error: Nodo inicial inválido o grafo vacío" << std::endl;
        return {};
    }

    // 2. Inicialización
    int num_nodos = grafo.mapa_salas.size();
    std::vector<int> distancias(num_nodos, std::numeric_limits<int>::max()); // Usa std::numeric_limits para INT_MAX
    std::vector<bool> visitados(num_nodos, false);

    // Usamos una cola de prioridad: (distancia, nodo)
    std::priority_queue<std::pair<int, sala *>, std::vector<std::pair<int, sala *>>, std::greater<std::pair<int, sala *>>> cola;

    // 3. Configuración nodo inicial
    distancias[nodoInicial->id] = 0;
    cola.push({0, nodoInicial});

    // 4. Procesamiento principal
    while (!cola.empty())
    {
        // **Línea modificada para compatibilidad con C++11/14:**
        std::pair<int, sala *> top_element = cola.top();
        int dist_actual = top_element.first;
        sala *nodo_actual = top_element.second;
        cola.pop();

        // Si ya fue visitado, lo saltamos
        if (visitados[nodo_actual->id])
            continue;
        visitados[nodo_actual->id] = true;

        // Procesar vecinos
        for (const arista &conexion : nodo_actual->lista_adyacentes)
        {
            sala *vecino = conexion.destino;
            int nueva_dist = dist_actual + conexion.distancia;

            // Actualizar si encontramos un camino más corto
            if (nueva_dist < distancias[vecino->id])
            {
                distancias[vecino->id] = nueva_dist;
                cola.push({nueva_dist, vecino});
            }
        }
    }

    return distancias;
}

personaje *encontrar_heroe_lento(sala *sala_actual) // Devuelve el heroe mas lento
{
    if (!sala_actual || sala_actual->lista_heroes.empty())
    {
        std::cout << "Error en encontrar heroe lento. Sala vacia o no existente" << std::endl;
        std::cout << "Error de codigo. Retornando" << std::endl;
        return nullptr;
    }

    personaje *heroe_lento = nullptr;
    int velocidad_minima = std::numeric_limits<int>::max(); // Usa std::numeric_limits para INT_MAX

    for (personaje *heroe_actual : sala_actual->lista_heroes)
    {
        if (heroe_actual && heroe_actual->tipo->rapidez < velocidad_minima)
        {
            velocidad_minima = heroe_actual->tipo->rapidez;
            heroe_lento = heroe_actual;
        }
    }
    return heroe_lento;
}

sala *designar_sala_spawn_heroes(const mapaGrafo &grafo) // Spawnean en sala random
{
    if (grafo.mapa_salas.empty())
    {
        std::cout << "El mapa esta vacio" << std::endl;
        return nullptr;
    }

    else
    {
        sala *sala_spawn_heroes = nullptr;
        int indice_random = rand() % grafo.mapa_salas.size();
        sala_spawn_heroes = encontrar_sala(grafo, indice_random);
        std::cout << "Los heroes apareceran en: " << sala_spawn_heroes->nombre << std::endl
                  << std::endl;
        // std::cout << "Acabando funcion designar sala" << std::endl;
        return sala_spawn_heroes;
    }
}

void checkear_entidades_grafo(mapaGrafo grafo)
{
    for (sala *actual : grafo.mapa_salas)
    {
        if (!actual->lista_heroes.empty())
        {
            std::cout << "\nHAY HEROES EN: " << actual->nombre << std::endl;
        }
        else if (!actual->lista_orcos.empty())
        {
            std::cout << "\nHAY ORCOS EN: " << actual->nombre << std::endl;
        }
    }
}

void spawn_heroes(sala *&sala_spawn_heroes, personaje *lista_personajes) // Carga toda la lista de heroes en 1 sala
{
    // Carga la lista de heroes de la sala de spawn
    // NO valida que solo sean 4 heroes. Ya se valido antes de empezar el juego

    if (!sala_spawn_heroes)
    {
        std::cout << "No hay sala spawn heroes. Error de codigo" << std::endl;
        return;
    }

    personaje *actual = lista_personajes;
    while (actual != nullptr)
    {
        std::cout << "Heroe actual siendo transportado: " << actual->nombre << std::endl;
        sala_spawn_heroes->lista_heroes.push_back(actual);
        actual = actual->siguiente;
    }
}

sala *designar_sala_spawn_orcos(sala *sala_spawn_heroes, mapaGrafo &grafo, const std::vector<int> lista_pesos)
{
    sala *sala_spawn_orcos = nullptr;

    // // Una vez que el dijkstra como tal ya este completado, se elige una de las salas como spawn de orcos:
    // for (size_t i = 0; i < lista_pesos.size(); i++)
    // {
    //     if (lista_pesos[i] >= 10)
    //     {
    //         sala_spawn_orcos = grafo.mapa_salas[i];
    //         break;
    //     }
    // }
    // Si no encuentra una sala con al menos 10 de distancia, sera una sala random
    while (!sala_spawn_orcos)
    {
        int indice_random = rand() % grafo.mapa_salas.size();
        if (indice_random != sala_spawn_heroes->id)
        {
            sala_spawn_orcos = encontrar_sala(grafo, indice_random);
        }
    }
    // std::cout << "Spawn de Orcos: " << sala_spawn_orcos->nombre << std::endl;
    std::cout << "Los orcos han entrado al mapa..." << std::endl;
    return sala_spawn_orcos;
}

void spawnear_personajes_orcos(sala *sala_spawn_orcos, const Lista_especie &lista_especies_orco,
                               personaje &lista_personajes_orco)
{
    std::vector<std::string> nombresOrcos = {
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
    std::string nombre_nuevo_orco;
    bool nombre_asignado = false;

    // Cantidad de orcos a aparecer en su spawn:
    int cantidad_orcos_spawnear = (rand() % 5) + 1;

    // borrar despues
    // std::cout << "Generando " << cantidad_orcos_spawnear << " orcos en sala "
    //           << sala_spawn_orcos->nombre << " (ID: " << sala_spawn_orcos->id << ")\n";

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
            std::cout << "La lista de especies esta vacia (NUNCA DEBERIA PASAR)" << std::endl;
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
            nombre_nuevo_orco = especie_nuevo_orco->nombre_especie + " " + std::to_string(max_id + 1);
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
                nombre_nuevo_orco = "Orco " + std::to_string(max_id + 1);
            }
        }

        // Creacion del nuevo personaje orco:
        cantidad_personaje_orco += 1;
        personaje *nuevo_orco = new personaje;

        // Estadisticas del orco:
        nuevo_orco->nombre = nombre_nuevo_orco;
        nuevo_orco->identificador = max_id + 1;
        // reservamos nueva memoria para el orco y copiamos las estadisticas.
        nuevo_orco->tipo = new Especie;
        nuevo_orco->tipo->danno_fortaleza = especie_nuevo_orco->danno_fortaleza;
        nuevo_orco->tipo->identificador = especie_nuevo_orco->identificador;
        nuevo_orco->tipo->nombre_especie = especie_nuevo_orco->nombre_especie;
        nuevo_orco->tipo->rapidez = especie_nuevo_orco->rapidez;
        nuevo_orco->tipo->salud = especie_nuevo_orco->salud;
        // se termino la copia.

        // Se agrega a la lista enlazada
        nuevo_orco->siguiente = lista_personajes_orco.siguiente;
        lista_personajes_orco.siguiente = nuevo_orco;

        // Se agrega a la sala
        // std::cout << "Orco creado: " << nombre_nuevo_orco << std::endl;
        sala_spawn_orcos->lista_orcos.push_back(nuevo_orco);
    }
    // std::cout << "Total orcos en sala: " << sala_spawn_orcos->lista_orcos.size() << std::endl;
}

bool verificar_pelea(sala *sala_siguiente, int movimiento_heroes_orcos) // Empieza la pelea si es el caso
{
    // movimiento_heroes_orcos = 1 si mueven los heroes
    // movimiento_heroes_orcos = 2 si mueven los orcos
    if (movimiento_heroes_orcos == 1) // Si los heroes hacen una emboscada:
    {
        if (!sala_siguiente->lista_orcos.empty())
        {
            return true;
        }
    }
    else if (movimiento_heroes_orcos == 2) // Si los Orcos hacen una emboscada:

    {
        if (!sala_siguiente->lista_heroes.empty())
        {

            return true;
        }
    }
    else // Else por si acaaso
    {
        std::cout << "Error en Verificar Pelea. Nunca deberia de ejecutarse esto" << std::endl;
    }
    return false;
}

void movimiento_orcos(sala *sala_heroes, mapaGrafo &grafo) // Movimiento orcos
{
    // 1. Validación básica
    if (!sala_heroes)
    {
        std::cout << "Error: Sala de héroes inválida" << std::endl;
        return;
    }

    // 2. Calcular distancias desde los héroes
    std::vector<int> distancias = dijkstra(sala_heroes, grafo);
    if (distancias.empty())
    {
        std::cout << "Error: No se pudieron calcular distancias" << std::endl;
        return;
    }

    // 3. Buscar sala con orcos más cercana
    int min_distancia = std::numeric_limits<int>::max();
    sala *sala_orcos_cercana = nullptr;

    for (sala *sala_actual : grafo.mapa_salas)
    {
        // Verificar sala válida con orcos
        if (!sala_actual->lista_orcos.empty())
        {
            // Verificar ID válido
            if (sala_actual->id >= 0 && sala_actual->id < distancias.size() && distancias[sala_actual->id] < min_distancia)
            {
                std::cout << "Los orcos se mueven hacia los heroes...\n"
                          << std::endl;
                min_distancia = distancias[sala_actual->id];
                sala_orcos_cercana = sala_actual;
            }
        }
    }

    // 4. Si no se encontraron orcos cercanos
    if (!sala_orcos_cercana)
    {
        std::cout << "No se encontraron orcos cercanos para mover" << std::endl;
        return;
    }

    // 5. Buscar mejor sala adyacente para mover
    int mejor_distancia = std::numeric_limits<int>::max();
    sala *mejor_destino = nullptr;

    for (const arista &arista_actual : sala_orcos_cercana->lista_adyacentes)
    {
        sala *vecino = arista_actual.destino;
        if (vecino->id >= 0 && vecino->id < distancias.size())
        {
            if (distancias[vecino->id] < mejor_distancia)
            {
                mejor_distancia = distancias[vecino->id];
                mejor_destino = vecino;
            }
        }
    }

    // 6. Si no hay destino válido
    if (!mejor_destino)
    {
        std::cout << "No hay destino válido para los orcos" << std::endl;
        return;
    }

    // 7. Mover los orcos (entre 1 y 5)
    int max_a_mover = std::min(5, (int)sala_orcos_cercana->lista_orcos.size());
    int cantidad_mover = rand() % max_a_mover + 1;

    for (int i = 0; i < cantidad_mover; i++)
    {
        if (!sala_orcos_cercana->lista_orcos.empty())
        {
            personaje *orco = sala_orcos_cercana->lista_orcos.back();
            sala_orcos_cercana->lista_orcos.pop_back();
            mejor_destino->lista_orcos.push_back(orco);
        }
    }

    // std::cout << cantidad_mover << " orcos movidos de "
    //           << sala_orcos_cercana->nombre << " a "
    //           << mejor_destino->nombre << std::endl;

    // 8. Verificar combate
    if (!mejor_destino->lista_heroes.empty())
    {
        std::cout << "¡Emboscada! Comienza combate..." << std::endl;
        combateorcos(mejor_destino, tipoEspecieHeroe);
    }
}

sala *movimiento_heroes(sala *sala_origen, mapaGrafo &grafo, Lista_especie lista_heroes) // Turno de movimiento de heroes
{
    // OJO, la funcion NO comprueba que haya o no heroes en la sala
    // Eso se deberia comprobar en la funcion de Turno General (heroes y orcos)

    if (sala_origen->lista_heroes.empty()) // Por si acaso
    {
        std::cout << "No hay heroes en la sala " << sala_origen->nombre << std::endl;
        std::cout << "Retornando..." << std::endl;
        return sala_origen;
    }

    sala *sala_destino;
    personaje *heroe_lento = encontrar_heroe_lento(sala_origen);

    if (!heroe_lento) // Por si acaso
    {
        std::cout << "No se puedo encontrar el heroe mas lento. Error en el juego" << std::endl;
        std::cout << "Retornando..." << std::endl;
        return sala_origen;
    }

    int energia_restante = heroe_lento->tipo->rapidez;
    bool pelea = false;

    std::cout << "Los heroes se encuentran en: " << sala_origen->nombre << std::endl;
    std::cout << "Pueden recorrer " << energia_restante << "km de distancia" << std::endl;

    std::cout << "\n";

    while (energia_restante > 0) // Ejecutar mientras los heroes no se hayan movido
    {
        bool pueden_moverse = false;

        // 1. Verifica si hay salas a donde moverse:
        for (arista actual : sala_origen->lista_adyacentes)
        {
            if (energia_restante >= actual.distancia)
            {
                pueden_moverse = true;
                break;
            }
        }
        if (!pueden_moverse) // Basicamente, el caso base
        {
            std::cout << "Los heroes estan muy cansados como para ir a otra sala" << std::endl;
            std::cout << "Los heroes se quedaron dormidos en el camino... " << std::endl;
            break;
        }

        // 2. Como SI hay a donde moverse, le pregunta al usuario
        std::cout << "Ingrese 0 para cancelar su turno" << std::endl;
        mostrar_adyacencias(sala_origen);

        int entrada_usuario = obtener_entero("Indique a que sala se desea mover: ");
        if (entrada_usuario == 0)
        {
            std::cout << "El jugador ha decidido no moverse." << std::endl;
            std::cout << "Turno cancelado. " << std::endl;
            return sala_origen;
        }

        sala_destino = encontrar_sala(grafo, entrada_usuario);
        if (!sala_destino) // Comprueba que la sala exista
        {
            std::cout << "La sala no existe. Indique una opcion valida" << std::endl;
            continue;
        }

        // 3. Buscar distancia de Origen a Destino
        int distancia = -1;
        for (arista actual : sala_origen->lista_adyacentes) // Obtiene la distancia de origen a destino
        {
            if (actual.destino == sala_destino)
            {
                distancia = actual.distancia;
                break;
            }
        }
        if (distancia == -1) // Si las salas no estan conectadas:
        {                    // Si el jugador indica el ID de la sala_origen, si esta conectada consigo misma se podra mover, sino no
            std::cout << "La sala indicada no es adyacente" << std::endl;
            std::cout << "Ingrese una sala valida." << std::endl;
            continue;
        }
        if (distancia > energia_restante) // Si la sala esta muy lejos:
        {
            std::cout << "Los heroes estan muy cansados para ir a " << sala_destino->nombre << std::endl;
            std::cout << "Indique una sala mas cercana." << std::endl;
            continue;
        }

        while (!sala_origen->lista_heroes.empty()) // Traslado de heroes entre salas
        {
            personaje *personaje_actual = sala_origen->lista_heroes.front();    // .front() es igual a hacer [0]
            sala_destino->lista_heroes.push_back(personaje_actual);             // Agrega el personaje[0] a sala_destino
            sala_origen->lista_heroes.erase(sala_origen->lista_heroes.begin()); // Borra personaje[0] de sala_origen
        }
        std::cout << "Los heroes se han movido de " << sala_origen->nombre << " hacia " << sala_destino->nombre << std::endl;
        energia_restante -= distancia;
        std::cout << "Energia restante: " << energia_restante << std::endl;

        sala_origen = sala_destino; // Los heroes ya se movieron, se cambia el origen

        // Se verifica si hay que empezar pelea:
        pelea = verificar_pelea(sala_origen, 1);
        if (pelea)
        {
            std::cout << "Los Heroes han emboscado a los orcos." << std::endl;
            std::cout << "!!! A pelear !!!" << std::endl;
            combateheroes(sala_origen, tipoEspecieHeroe);
            // Si hay pelea, el movimiento se detiene
            return sala_origen;
        }

        // Se verifica que sea la sala de la puerta destino
        if (sala_origen->contiene_puerta_destino == true)
        {
            // EL mensaje de felicidades y todo lo demas, esta en el main
            return sala_origen;
        }
    }
    // Una vez que ya hizo todos los movimientos:

    if (!pelea)
    {
        personaje *heroe_actual = personajes_jugar->siguiente;
        while (heroe_actual != nullptr)
        {
            Especie *referenci_actual = encontrar_especie_id(lista_heroes, heroe_actual->tipo->identificador);
            int recuperacion = heroe_actual->tipo->danno_fortaleza * 0.1;
            heroe_actual->tipo->danno_fortaleza = std::min(referenci_actual->danno_fortaleza, heroe_actual->tipo->danno_fortaleza + recuperacion);
            std::cout << heroe_actual->nombre << " ha recuperado " << recuperacion << " puntos de fortaleza.\n";

            heroe_actual = heroe_actual->siguiente;
        }
    }

    return sala_origen;
}
