// Librerias Locales:
#pragma once
#include "01.funciones_genericas.h"                // Funciones generales y librerias para el programa
#include "02.funciones_tipos_especie.h"            // Funciones para las Especies de Heroes y Orcos
#include "03.funciones_implementos.h"              // Funciones para Implementos
#include "04.funciones_mochila_personajes_jugar.h" // Funciones de la Mochila y Personajes Jugar
#include "05.funciones_poder_magico.h"             // Funciones para los Poderes Magicos
#include "06.funciones_mapa.h"                     // Funciones para el mapa (grafo)
#include "07.funciones_cargar_archivo.h"           // Funciones para la carga de archivos
#include "09.menus_main.h"                         // Todos los menus del main
#include "10.combate.h"

/*Falta:
    -Turnos de movimiento(turnos fuera de combate)
    -Aparicion de la puerta magica
        -Que la puerta se mueva
    Debo de programar TurnoFueraCombate, para controlar el movimiento de la puerta magica y la aparicion de orcos
    La energia se les va a recuperar por cada TURNO no por sala movida
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

vector<int> dijkstra(sala *nodoInicial, const mapaGrafo &grafo) // Dijkstra. Devuelve la lista de pesos
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

personaje *encontrar_heroe_lento(sala *sala_actual) // Devuelve el heroe mas lento
{

    personaje *heroe_lento = nullptr;
    int velocidad_minima = INT_MAX;

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
        cout << "El mapa esta vacio" << endl;
        return nullptr;
    }

    else
    {
        sala *sala_spawn_heroes = nullptr;
        int indice_random = rand() % grafo.mapa_salas.size();
        sala_spawn_heroes = encontrar_sala(grafo, indice_random);
        return sala_spawn_heroes;
    }
}

void spawn_heroes(sala *sala_spawn_heroes, const personaje *personajes_jugar) // Carga toda la lista de heroes en 1 sala
{
    // Carga la lista de heroes de la sala de spawn
    // NO valida que solo sean 4 heroes. Ya se valido antes de empezar el juego
    personaje *actual = personajes_jugar->siguiente;
    while (actual != nullptr)
    {
        sala_spawn_heroes->lista_heroes.push_back(actual);
        actual = personajes_jugar->siguiente;
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
        sala_spawn_orcos->lista_orcos.push_back(nuevo_orco);
    }
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
        cout << "Error en Verificar Pelea. Nunca deberia de ejecutarse esto" << endl;
    }
    return false;
}

void movimiento_orcos(sala *sala_heroes, mapaGrafo &grafo) // Turno de movimiento de orcos
{
    // Se moveran un maximo de 5 orcos, los mas cercanos a los heroes
    //    Se moveran entre 1 y 5 orcos pq son tontos

    vector<sala *> salas_con_orcos; // Vector que almacena todas las salas donde hay orcos
    sala *sala_mas_cercana;
    vector<int> lista_adyacencias;
    sala *sala_moverse;
    int distancia_minima = INT_MAX;            // Se declara como infinito
    int cant_orcos_moverse = (rand() % 5) + 1; // Cantidad de orcos a mover (entre 1 y 5)

    for (sala *actual : grafo.mapa_salas) // Agrega todas las salas con orcos a la lista
    {
        if (!actual->lista_orcos.empty())
        {
            salas_con_orcos.push_back(actual);
        }
    }
    /* Una vez que ya tengo todas las salas donde hay orcos,
    Decido cual de ellos se movera*/

    for (sala *actual : salas_con_orcos) // Elegir que sala de Orcos se movera
    {
        lista_adyacencias = dijkstra(actual, grafo);
        if (lista_adyacencias[sala_heroes->id] < distancia_minima && actual != sala_heroes) // No movera a los orcos en sala heroes
        {
            distancia_minima = lista_adyacencias[sala_heroes->id];
            sala_mas_cercana = encontrar_sala(grafo, actual->id);
        }
    }

    // Decidir hacia donde se moveran los orcos de la sala elegida
    if (sala_mas_cercana && sala_mas_cercana != sala_heroes) // Comprueba que exista y no esten ya en donde los heroes
    {
        lista_adyacencias = dijkstra(sala_mas_cercana, grafo);
        distancia_minima = INT_MAX;

        // Busca el adyacente que esté más cerca de los héroes
        for (const arista &vecino : sala_mas_cercana->lista_adyacentes)
        {
            if (lista_adyacencias[vecino.destino->id] < distancia_minima)
            {
                distancia_minima = lista_adyacencias[vecino.destino->id];
                sala_moverse = vecino.destino;
            }
        }

        // Mover a los orcos a las salas seleccionadas
        for (int i = 0; i < cant_orcos_moverse; i++) // En funcion de la cantidad de orcos a mover
        {
            if (!sala_mas_cercana->lista_orcos.empty()) // Mientras la lista no este vacia:
            {
                sala_moverse->lista_orcos.push_back(sala_mas_cercana->lista_orcos[0]);
                sala_mas_cercana->lista_orcos.erase(sala_mas_cercana->lista_orcos.begin());
            }
        }
        bool pelea = verificar_pelea(sala_moverse, 2);
        if (pelea)
        {
            cout << "Los Heroes han caido en una emboscada de los Orcos." << endl;
            cout << "!!! A pelear !!!" << endl;
            combateorcos(sala_moverse, tipoEspecieHeroe);
            return;
        }
    }
}
//                                               la coloque para poder encontra las estadisticas estandar de los tipo
sala *movimiento_heroes(sala *sala_origen, mapaGrafo &grafo, Lista_especie lista_heroes) // Turno de movimiento de heroes
{
    // OJO, la funcion NO comprueba que haya o no heroes en la sala
    // Eso se deberia comprobar en la funcion de Turno General (heroes y orcos)

    personaje *heroe_lento;
    sala *sala_destino;
    heroe_lento = encontrar_heroe_lento(sala_origen);
    int energia_restante = heroe_lento->tipo->rapidez;
    bool pelea = false;

    cout << "Los heroes se encuentran en: " << sala_origen->nombre << endl;
    cout << "Pueden recorrer " << energia_restante << "km de distancia" << endl;

    mostrar_adyacencias(sala_origen);
    cout << "\n";

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
            cout << "Los heroes estan muy cansados como para ir a otra sala" << endl;
            cout << "Los heroes se quedaron dormidos en el camino... " << endl;
            break;
        }

        // 2. Como SI hay a donde moverse, le pregunta al usuario
        cout << "Indique a que sala se desea mover " << endl;
        cout << "Ingrese 0 para cancelar su turno" << endl;
        int entrada_usuario = obtener_entero("Sala: ");
        if (entrada_usuario == 0)
        {
            cout << "El jugador ha decidido no moverse." << endl;
            cout << "Turno cancelado" << endl;
            return sala_origen;
        }

        sala_destino = encontrar_sala(grafo, entrada_usuario);
        if (!sala_destino) // Comprueba que la sala exista
        {
            cout << "La sala no existe. Indique una opcion valida" << endl;
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
            cout << "La sala indicada no es adyacente" << endl;
            cout << "Ingrese una sala valida." << endl;
            continue;
        }
        if (distancia > energia_restante) // Si la sala esta muy lejos:
        {
            cout << "Los heroes estan muy cansados para ir a " << sala_destino->nombre << endl;
            cout << "Indique una sala mas cercana." << endl;
            continue;
        }

        while (!sala_origen->lista_heroes.empty()) // Traslado de heroes entre salas
        {
            personaje *personaje_actual = sala_origen->lista_heroes.front();    // .front() es igual a hacer [0]
            sala_destino->lista_heroes.push_back(personaje_actual);             // Agrega el personaje[0] a sala_destino
            sala_origen->lista_heroes.erase(sala_origen->lista_heroes.begin()); // Borra personaje[0] de sala_origen
        }
        cout << "Los heroes se han movido de " << sala_origen->nombre << " hacia " << sala_destino->nombre << endl;
        energia_restante -= distancia;
        cout << "Energia restante: " << energia_restante << endl;

        sala_origen = sala_destino; // Los heroes ya se movieron, se cambia el origen

        // Se verifica si hay que empezar pelea:
        pelea = verificar_pelea(sala_origen, 1);
        if (pelea)
        {
            cout << "Los Heroes han emboscado a los orcos." << endl;
            cout << "!!! A pelear !!!" << endl;
            combateheroes(sala_origen, tipoEspecieHeroe);
            // Si hay pelea, el movimiento se detiene
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
            heroe_actual->tipo->danno_fortaleza = min(referenci_actual->danno_fortaleza, heroe_actual->tipo->danno_fortaleza + recuperacion);
            cout << heroe_actual->nombre << " ha recuperado " << recuperacion << " puntos de fortaleza.\n";

            heroe_actual = heroe_actual->siguiente;
        }
    }

    return sala_origen;
}
