#pragma once
#include "01.funciones_genericas.h"     // Funciones generales para el programa
#include "02.funciones_tipos_especie.h" //
#include "03.funciones_implementos.h"
#include "04.funciones_mochila_personajes_jugar.h"
#include "05.funciones_poder_magico.h"
#include "06.funciones_mapa.h"
#include "07.funciones_cargar_archivo.h"

// Este archivo tendra todos los menus del main del archivo principal

// Menu Orcos
Lista_especie tipoEspecieOrco; // lista enlazada que contiene todos los tipos de orcos.
personaje personajes_orco;     // lista enlazada de personajes orcos.

// Menu Heroes y Personajes
Lista_especie tipoEspecieHeroe; // lista enlazada que contiene todos los tipos de heroes.
personaje personajes_hero;      // lista enlazada de personajes heroes.

// Menu Implementos
Implemento lista_implementos; // lista de implementos

// Menu Poderes Magicos
Poder_magico lista_podere_magicos; // lista de los poderes.

// Personajes Jugar
personaje *personajes_jugar = nullptr; // aqui estan los 4 personajes que el usuaro coloque para jugar.

// Menu Mapa
mapaGrafo grafo;
sala *sala_modificar;

int opcion_principal = 0; // Opcion para el menu principal
int opcion_interna = 0;   // Opcion de cada menu interno

int res = 0; // para menu pre-juego
bool iniciar_juego = false;

// Controladores para evitar cargar archivos varias veces
bool especies_cargadas = false;
bool implementos_cargados = false;
bool salas_cargadas = false;
bool adyacencias_cargadas = false;
bool personajes_cargados = false;

// Para puerta destino
vector<int> salas_puerta_pasadas;

// Turno
int turno = 0;

void menu_orcos() // Case 1 del main
{
    do
    {
        cout << "\n               MENU ORCOS              \n";
        cout << "------------------------------------------\n";
        cout << "           --ESPECIES ORCOS-- \n";
        cout << "1. Crear especie de Orco. \n";
        cout << "2. Actualizar datos de una especie de Orco. \n";
        cout << "3. Mostrar los especies de Orcos disponibles. \n";
        cout << "4. Eliminar especie de Orco. \n";
        cout << "------------------------------------------\n";
        cout << "            --PERSONAJES ORCOS-- \n";
        cout << "5. Crear personajes Orco. \n";
        cout << "6. Mostrar personajes Orco. \n";
        cout << "7. Modificar personajes Orco. \n";
        cout << "8. Eliminar personajes Orco.  \n";
        cout << "------------------------------------------\n";
        cout << "9. Salir al menu principal.\n";
        cout << "------------------------------------------\n";
        opcion_interna = obtener_opcion();

        switch (opcion_interna)
        {
        case 1: // Crear especie Orco
        {
            Crear_tipo(tipoEspecieOrco, 1);
            break;
        }
        case 2: // Actualizar Especie orco
        {
            actualizar_tipo(tipoEspecieOrco, 1);
            break;
        }
        case 3: // Mostrar especies orco
        {
            mostrar_lista(tipoEspecieOrco, 1);
            break;
        }
        case 4: // Eliminar especie orco
        {
            eliminar_elemento_lista(tipoEspecieOrco, personajes_orco, 1);
            break;
        }
        case 5: // Crear personaje Orco
        {
            crear_personaje(personajes_orco, tipoEspecieOrco, 1);
            break;
        }
        case 6: // Mostrar Personajes Orco
        {
            mostrar_personajes(personajes_orco, 1);
            break;
        }
        case 7: // Modificar Personajes Orco
        {
            actualizar_personaje(personajes_orco, tipoEspecieOrco, 1);
            break;
        }
        case 8: // Eliminar Personajes ORco
        {
            borrar_personaje(personajes_orco, 1);
            break;
        }
        case 9: // Salir
        {
            cout << "\nSaliendo al Menu Principal... \n";
            break;
        }
        default:
        {
            cout << "Invalido. Ingrese una opcion valida \n";
            break;
        }
        }
        limpiar_pantalla();
    } while (opcion_interna != 9); // Mientras no se salga del menu interno de orcos.
}

void menu_especies_heroes_personajes() // Case 2 del main
{
    do
    {
        cout << "\n            MENU DE HEROES\n";
        cout << "------------------------------------------\n";
        cout << "           --ESPECIES HEROES-- \n";
        cout << "1. Crear especie de Heroe. \n";
        cout << "2. Actualizar datos de una especie Heroe. \n";
        cout << "3. Mostrar especies de Heroes disponibles. \n";
        cout << "4. Eliminar especie de Heroe. \n"; // Ya no sale del programa sino del menu de creacion, pq luego vendra el juego como tal.
        cout << "------------------------------------------\n";
        cout << "            --PERSONAJES HEROES-- \n";
        cout << "5. Crear personaje Heroe.\n";
        cout << "6. Mostrar personajes Heroe. \n";
        cout << "7. Modificar personaje Heroe. \n";
        cout << "8. Eliminar personaje Heroe.  \n";
        cout << "------------------------------------------\n";
        cout << "9. Salir al menu principal  \n";
        cout << "------------------------------------------\n";
        opcion_interna = obtener_opcion();

        switch (opcion_interna)
        {
        case 1: // Crear especie heroe
        {
            limpiar_pantalla();
            Crear_tipo(tipoEspecieHeroe, 2);
            break;
        }
        case 2: // Actualizar especie heroe
        {
            limpiar_pantalla();
            actualizar_tipo(tipoEspecieHeroe, 2);
            break;
        }
        case 3: // Mostrar especies heroe
        {
            limpiar_pantalla();
            mostrar_lista(tipoEspecieHeroe, 2);
            cout << "Pulse enter para continuar:" << endl;
            getline(cin, pausa1);
            cout << endl
                 << endl;
            limpiar_pantalla();
            break;
        }
        case 4: // Eliminar especies heroe
        {
            limpiar_pantalla();
            eliminar_elemento_lista(tipoEspecieHeroe, personajes_hero, 2);
            break;
        }
        case 5: // Crear personaje heroe
        {
            limpiar_pantalla();
            crear_personaje(personajes_hero, tipoEspecieHeroe, 2);
            break;
        }
        case 6: // Mostrar personajes heroe
        {
            limpiar_pantalla();
            mostrar_personajes(personajes_hero, 2);
            break;
        }
        case 7: // Modificar personaje heroe
        {
            limpiar_pantalla();
            actualizar_personaje(personajes_hero, tipoEspecieHeroe, 2);
            break;
        }
        case 8: // Eliminar personaje heroe
        {
            limpiar_pantalla();
            borrar_personaje(personajes_hero, 2);
            break;
        }
        case 9: // Salir
        {
            limpiar_pantalla();
            cout << "\nSaliendo al Menu Principal... \n";
            break;
        }
        default:
        {
            cout << "Invalido. Ingrese una opcion valida \n";
            break;
        }
        }
        limpiar_pantalla();
    } while (opcion_interna != 9); // Mientras no se salga del menu interno de heroes.
}

void menu_implementos() // Case 3 del main
{
    do
    {
        cout << "\n MENU DE IMPLEMENTOS\n";
        cout << "------------------------\n";
        cout << "1. Agregar un implemento. \n";
        cout << "2. Actualizar un implemento. \n";
        cout << "3. Mostrar los implementos. \n";
        cout << "4. Eliminar un implemento \n";
        cout << "------------------------\n";
        cout << "5. Salir al menu principal  \n";
        cout << "------------------------\n";
        opcion_interna = obtener_opcion();

        switch (opcion_interna)
        {
        case 1:
            limpiar_pantalla();
            crear_implemento(lista_implementos);
            break;
        case 2:
            limpiar_pantalla();
            modificar_implemento(lista_implementos);
            break;
        case 3:
            limpiar_pantalla();
            mostrar_implementos(lista_implementos);
            break;
        case 4:
            limpiar_pantalla();
            borrar_implementos(lista_implementos);
            break;
        case 5:
            limpiar_pantalla();
            cout << "\nSaliendo al Menu Principal... \n";
            break;
        default:
            limpiar_pantalla();
            cout << "Invalido. Ingrese una opcion valida \n";
            break;
        }
        limpiar_pantalla();
    } while (opcion_interna != 5); // Mientras no desee salir a menu principal
}

void menu_poderes_magicos() // Case 4 del main
{
    do
    {
        cout << "\n MENU DE PODERES MAGICOS\n";
        cout << "---------------------\n";
        cout << "1. Agregar poder magico. \n";
        cout << "2. Actualizar poder magico. \n";
        cout << "3. Mostrar los poderes magicos. \n";
        cout << "4. Eliminar un poder magico. \n";
        cout << "---------------------\n";
        cout << "5. Salir al menu principal  \n";
        cout << "---------------------\n";
        opcion_interna = obtener_opcion();

        switch (opcion_interna)
        {
        case 1:
        {
            limpiar_pantalla();
            crear_poder(lista_podere_magicos);
            break;
        }
        case 2:
        {
            limpiar_pantalla();
            modificar_poder(lista_podere_magicos);
            break;
        }
        case 3:
        {
            limpiar_pantalla();
            mostrar_poderes(lista_podere_magicos);
            break;
        }
        case 4:
        {
            limpiar_pantalla();
            eliminar_poder(lista_podere_magicos);
            break;
        }
        case 5:
        {
            limpiar_pantalla();
            cout << "\nSaliendo al Menu Principal... \n";
            break;
        }
        default:
        {
            limpiar_pantalla();
            cout << "Invalido. Ingrese una opcion valida \n";
            break;
        }
        }
        limpiar_pantalla();
    } while (opcion_interna != 5);
}

void carga_archivos(bool especies_cargadas, bool personajes_cargados,
                    bool implementos_cargados, bool salas_cargadas, bool adyacencias_cargadas) // Case 5 del main
{
    limpiar_pantalla();
    cout << "Cargando archivos..." << endl;
    cargar_especies(tipoEspecieHeroe, tipoEspecieOrco, especies_cargadas);
    cout << endl
         << endl
         << "Las especies ya han sido cargadas." << endl
         << endl;
    cargar_personajes(personajes_hero, personajes_orco, tipoEspecieHeroe, tipoEspecieOrco, personajes_cargados);
    cout << endl
         << endl
         << "Los personajes ya han sido cargados." << endl
         << endl;
    cargar_implementos(lista_implementos, implementos_cargados);
    cout << endl
         << endl
         << "Los implementos ya han sido cargados." << endl
         << endl;
    carga_salas(grafo, salas_cargadas);
    cout << endl
         << endl
         << "Las salas ya han sido cargadas." << endl
         << endl;
    cargar_adyacencias(grafo, adyacencias_cargadas);
    cout << endl
         << endl
         << "Las adyacencias ya han sido cargadas." << endl
         << endl;

    if (especies_cargadas && implementos_cargados && salas_cargadas &&
        adyacencias_cargadas && personajes_cargados)
    {
        limpiar_pantalla();
        cout << "Todos los datos han sido cargados exitosamente" << endl;
    }
}

void menu_mapas() // Case 6 del main
{
    do
    {
        cout << "\n MENU DE MAPAS:\n";
        cout << "---------------------\n";
        cout << "1. Crear sala \n";
        cout << "2. Mostrar mapa. \n";
        cout << "3. Mostrar adyacencias de una sala. \n";
        cout << "4. Borrar sala. \n";
        cout << "5. Editar sala. \n";
        cout << "---------------------\n";
        cout << "6. Salir al menu principal  \n";
        cout << "---------------------\n";
        opcion_interna = obtener_opcion();

        switch (opcion_interna)
        {
        case 1: // Crear sala
        {
            limpiar_pantalla();
            crear_sala_usuario(grafo);
            break;
        }
        case 2: // Mostrar mapa
        {
            limpiar_pantalla();
            cout << "-------------- Salas Del Juego -------------- " << endl; // Cambiar por un nombre mas epico
            mostrar_salas_grafo(grafo);
            break;
        }
        case 3: // Muestra adyacencias
        {
            limpiar_pantalla();
            preguntar_mostrar_salas(grafo);

            // Verifica que exista y muestra adyacencias:
            sala_modificar = verificar_existencia_sala(grafo, "Ingrese el ID de la sala a mostrar adyacencias: ");
            mostrar_adyacencias(sala_modificar);
            break;
        }
        case 4: // Borrar sala
        {
            limpiar_pantalla();
            preguntar_mostrar_salas(grafo);
            borrar_sala_usuario(grafo);
            break;
        }
        case 5: // Editar sala
        {
            limpiar_pantalla();
            int resp = 0;

            if (grafo_vacio(grafo)) // Verifica que el grafo no este vacio
            {
                cout << "No hay salas para editar" << endl;
                break;
            }
            cout << "Antes de ingresar el ID de la sala para modificar. " << endl;
            preguntar_mostrar_salas(grafo);

            sala_modificar = verificar_existencia_sala(grafo, "Ingrese el ID de la sala que desea modificar: ");
            editar_sala(grafo, sala_modificar->id);
            break;
        }
        case 6: // Salir al menu
        {
            limpiar_pantalla();
            cout << "Saliendo al menu principal..." << endl;
            break;
        }
        default: // Default
        {
            limpiar_pantalla();
            cout << "Invalido. Ingrese una opcion valida \n";
            break;
        }
        }
        limpiar_pantalla();
    } while (opcion_interna != 6);
}

void menu_pre_juego() // Caso 7 del main
{
    limpiar_pantalla();
    do
    {
        // VERIFICACIONES
        if (cantidad_personaje_heroe < 4)
        {
            cout << "No hay heroes suficientes para empezar el juego." << endl;
            cout << "Saliendo al menu principal..." << endl;
            break;
        }
        else if (cantidad_personaje_orco < 4)
        {
            cout << "No hay orcos suficientes para empezar el juego." << endl;
            cout << "Saliendo al menu principal..." << endl;
            break;
        }
        else if (cantidad_implementos < 5)
        {
            cout << "No hay implementos suficientes para empezar el juego." << endl;
            cout << "Saliendo al menu principal..." << endl;
            break;
        }
        else if (grafo.mapa_salas.size() < 4)
        {
            cout << "No hay salas suficientes para empezar el juego (minimo 4)." << endl;
            cout << "Saliendo al menu principal..." << endl;
            break;
        }

        cout << "¿Esta contento con las modificaciones realizadas?" << endl;
        cout << "Tome en cuenta que al empezar el juego no podra modificar lo siguiente:" << endl;
        cout << "   Tipos de heroes y orcos." << endl;
        cout << "   Personajes heroes y orcos." << endl;
        cout << "   Poderes, implementos y mapa.\n"
             << endl;
        cout << "Los cambios realizados anteriormente seran permanentes para esta partida" << endl;
        cout << "   1. Si, estoy conforme" << endl;
        cout << "   2. No, no estoy conforme" << endl;

        // Pregunta al usuario si desea jugar o seguir editando
        // Si la respuesta es no, hace el break
        while (res != 1 && res != 2)
        {
            res = obtener_opcion();
            if (res == 1)
            {
                cout << "Inicializando juego..." << endl; // no se que mensaje poner jaja
            }
            else if (res == 2)
            {
                cout << "Retornando al menu principal..." << endl;
                break;
            }
            else
            {
                cout << "La opcion " << res << " no existe" << endl;
                cout << "Ingrese una opcion valida" << endl;
            }
        }

        // Si el usuario ingresa que desea seguir jugando:
        // Empieza el pre-juego (seleccion de personajes, equipamiento, etc)
        limpiar_pantalla();

        cout << "\n     MENU DE PERSONAJES PARA JUGAR:\n";
        cout << "------------------------------------------\n";
        cout << "       Seleccion de Personajes  " << endl;
        cout << "------------------------------------------\n";
        cout << "1. Elegir personaje y sus objetos\n";
        cout << "2. Mostrar personaje del equipo actual. \n";
        cout << "3. Modificar mochila. \n";
        cout << "4. Eliminar personaje del equipo. \n";
        cout << "------------------------------------------\n";
        cout << "5. Empezar a jugar.  \n";
        cout << "---------------------\n";
        opcion_interna = obtener_opcion();

        switch (opcion_interna)
        {
        case 1:
            eleccion_personaje(personajes_jugar, personajes_hero, lista_implementos); //, lista_podere_magicos
            break;
        case 2:
            mostrar_personajes_jugar(personajes_jugar);
            break;
        case 3:
            modificar_mochila(personajes_jugar, lista_implementos, lista_podere_magicos);
            break;
        case 4:
            eliminar_personaje_jugar(personajes_jugar);
            break;
        case 5:
            cout << "Equipo actual: " << endl;
            mostrar_personajes_jugar(personajes_jugar);

            cout << "Entrando al juego..." << endl;
            cout << "\nIMPLEMENTAR JUEGO JAJAJAJA... \n";
            iniciar_juego = true;
            break;
        default:
            cout << "Invalido. Ingrese una opcion valida \n";
            break;
        }
        limpiar_pantalla();
    } while (opcion_interna != 5);
}

void menu_principal() // MENU PRINCIPAL !!!
{

    cout << "\n MENU PRINCIPAL \n";
    cout << "---------------------\n";
    cout << "0. Cargar Datos Predeterminados.\n";
    cout << "---------------------\n";
    cout << "1. Menu de Orcos" << "\n";
    cout << "2. Menu de Heroes" << "\n";
    cout << "---------------------\n";
    cout << "3. Menu de Implementos" << "\n";
    cout << "4. Menu de Poderes Magicos \n";
    cout << "---------------------\n";
    cout << "5. Menu del Mapa.\n";
    cout << "---------------------\n";
    cout << "6. EMPEZAR EL JUEGO. \n ";
    cout << "---------------------\n";
    cout << "7. Salir del programa completo." << "\n";
    opcion_principal = obtener_opcion();

    // Switch para Menu Principal
    switch (opcion_principal)
    {
    case 0: // Carga de archivos.
    {
        limpiar_pantalla();
        carga_archivos(especies_cargadas, implementos_cargados, salas_cargadas,
                       adyacencias_cargadas, personajes_cargados);
        break;
    }
    case 1: // Menu Orcos
    {
        limpiar_pantalla();
        menu_orcos();
        break;
    }
    case 2: // Menu Heroes
    {
        limpiar_pantalla();
        menu_especies_heroes_personajes();
        break;
    }
    case 3: // Menu Implementos
    {
        limpiar_pantalla();
        menu_implementos();
        break;
    }
    case 4: // Menu de poderes magicos
    {
        limpiar_pantalla();
        menu_poderes_magicos();
        break;
    }
    case 5: // Menu de Mapa
    {
        limpiar_pantalla();
        menu_mapas();
        break;
    }
    case 6: // Menu para antes de Jugar
    {
        limpiar_pantalla();
        menu_pre_juego();
        break;
    }
    case 7: // Salir del programa
    {
        limpiar_pantalla();
        cout << "Saliendo del programa... " << endl;
        break;
    }
    default: // Default del Menu Principal
    {
        limpiar_pantalla();
        cout << "Invalido. Ingrese una opcion valida";
        break;
    }
    }
}