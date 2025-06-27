#include "01.funciones_genericas.h"     // Funciones generales para el programa
#include "02.funciones_tipos_especie.h" //
#include "03.funciones_implementos.h"
#include "04.funciones_mochila_personajes_jugar.h"
#include "05.funciones_poder_magico.h"
#include "06.funciones_mapa.h"
#include "07.funciones_cargar_archivo.h"

// Este archivo tendra todos los menus del main del archivo principal

int opcion_principal = 0; // Opcion para el menu principal
int opcion_interna = 0;   // Opcion de cada menu interno

int res = 0; // para menu pre-juego
bool iniciar_juego = false;

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

void menu_orcos() // Case 1 del main
{
    do
    {
        cout << "\n MENU ORCOS\n";
        cout << "---------------------\n";
        cout << "1. Agregar una especie de Orco. \n";
        cout << "2. Actualizar los datos de un tipo de Orco. \n";
        cout << "3. Mostrar los tipos de Orcos disponibles. \n";
        cout << "4. Eliminar un tipo de especie. \n";
        cout << "------------------------\n";
        cout << "5. Crear personajes Orco. \n";
        cout << "6. Mostrar personajes Orco. \n";
        cout << "7. Modificar personajes Orco. \n";
        cout << "8. Eliminar personajes Orco.  \n";
        cout << "------------------------\n";
        cout << "9.Salir al menu principal.\n";
        cout << "---------------------\n";
        opcion_interna = obtener_opcion();

        switch (opcion_interna)
        {
        case 1:
            Crear_tipo(tipoEspecieOrco, 1);
            break;
        case 2:

            actualizar_tipo(tipoEspecieOrco, 1);
            break;
        case 3:
            mostrar_lista(tipoEspecieOrco, 1);
            break;
        case 4:

            eliminar_elemento_lista(tipoEspecieOrco, personajes_orco, 1);
            break;
        case 5:
            crear_personaje(personajes_orco, tipoEspecieOrco, 1);
            break;

        case 6:
            mostrar_personajes(personajes_orco, 1);
            break;
        case 7:
            actualizar_personaje(personajes_orco, tipoEspecieOrco, 1);
            break;
        case 8:
            borrar_personaje(personajes_orco, 1);
            break;
        case 9:
            cout << "\nSaliendo al Menu Principal... \n";
            break;
        default:
            cout << "Invalido. Ingrese una opcion valida \n";
            break;
        }
    } while (opcion_interna != 9); // Mientras no se salga del menu interno de orcos.
}

void menu_especies_heroes_personajes() // Case 2 del main
{
    do
    {
        cout << "\n MENU DE HEROES Y PERSONAJES\n";
        cout << "---------------------\n";
        cout << "1. Agregar una especie de Heroe \n";
        cout << "2. Actualizar los datos de un tipo de Heroe \n";
        cout << "3. Mostrar los tipos de Heroes disponibles \n";
        cout << "4. Eliminar un tipo de especie \n"; // Ya no sale del programa sino del menu de creacion, pq luego vendra el juego como tal.
        cout << "---------------------\n";
        cout << "5. Crear personaje.\n";
        cout << "6. Mostrar personajes. \n";
        cout << "7. Modificar personaje \n";
        cout << "8. Eliminar personaje  \n";
        cout << "---------------------\n";
        cout << "9. Salir al menu principal  \n";
        cout << "---------------------\n";
        opcion_interna = obtener_opcion();

        switch (opcion_interna)
        {
        case 1:
            Crear_tipo(tipoEspecieHeroe, 2);
            break;
        case 2:

            actualizar_tipo(tipoEspecieHeroe, 2);
            break;
        case 3:
            mostrar_lista(tipoEspecieHeroe, 2);
            break;
        case 4:
            eliminar_elemento_lista(tipoEspecieHeroe, personajes_hero, 2);
            break;
        case 5:
            crear_personaje(personajes_hero, tipoEspecieHeroe, 2);
            break;
        case 6:
            mostrar_personajes(personajes_hero, 2);
            break;
        case 7:
            actualizar_personaje(personajes_hero, tipoEspecieHeroe, 2);
            break;
        case 8:
            borrar_personaje(personajes_hero, 2);
            break;
        case 9:
            cout << "\nSaliendo al Menu Principal... \n";
            break;
        default:
            cout << "Invalido. Ingrese una opcion valida \n";
            break;
        }
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
            crear_implemento(lista_implementos);
            break;
        case 2:
            modificar_implemento(lista_implementos);
            break;
        case 3:
            mostrar_implementos(lista_implementos);
            break;
        case 4:
            borrar_implementos(lista_implementos);
            break;
        case 5:
            cout << "\nSaliendo al Menu Principal... \n";
            break;
        default:
            cout << "Invalido. Ingrese una opcion valida \n";
            break;
        }
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
        cout << "6. Usar poder 1 \n";
        cout << "7. Usar poder 2 \n";
        cout << "8. Usar poder 3 \n";
        cout << "9. Usar poder 4 \n";
        cout << "---------------------\n";
        opcion_interna = obtener_opcion();

        switch (opcion_interna)
        {
        case 1:
            crear_poder(lista_podere_magicos);
            break;
        case 2:
            modificar_poder(lista_podere_magicos);
            break;
        case 3:
            mostrar_poderes(lista_podere_magicos);
            break;
        case 4:
            eliminar_poder(lista_podere_magicos);
            break;
        case 5:
            cout << "\nSaliendo al Menu Principal... \n";
            break;
        case 6:
            Poder1(lista_implementos);
            break;
        default:
            cout << "Invalido. Ingrese una opcion valida \n";
            break;
        }
    } while (opcion_interna != 5);
}

void carga_archivos() // Case 5 del main
{
    cout << "Cargando archivos..." << endl;
    cargar_especies(tipoEspecieHeroe, tipoEspecieOrco);
    cout << endl
         << endl
         << "listo.tipos" << endl
         << endl;
    cargar_personajes(personajes_hero, personajes_orco, tipoEspecieHeroe, tipoEspecieOrco);
    cout << endl
         << endl
         << "listo.personajes" << endl
         << endl;
    cargar_implementos(lista_implementos);
    cout << endl
         << endl
         << "listo.implementos" << endl
         << endl;
    carga_salas(grafo);
    cout << endl
         << endl
         << "listo.salas" << endl
         << endl;
    cargar_adyacencias(grafo);
    cout << endl
         << endl
         << "listo.adyacencias" << endl
         << endl;
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
            crear_sala_usuario(grafo);
            break;
        }
        case 2: // Mostrar mapa
        {
            cout << "-------------- Salas Del Juego -------------- " << endl; // Cambiar por un nombre mas epico
            mostrar_salas_grafo(grafo);
            break;
        }
        case 3: // Muestra adyacencias
        {
            int resp_interna;
            if (grafo_vacio(grafo))
            {
                break;
            }

            cout << "¿Desea ver todas las salas del mapa?" << endl;
            cout << "1. Si" << endl;
            cout << "2. No" << endl;
            resp_interna = obtener_opcion();
            switch (resp_interna) // Para mostrar o no las salas del mapa
            {
            case 1: // Muestra las salas del mapa
            {
                cout << "-------------- Salas Del Juego --------------" << endl;
                mostrar_salas_grafo(grafo);
                break;
            }
            case 2: // No muestra las salas
            {
                cout << "No se mostraran las salas del mapa" << endl;
                break;
            }
            default: // Default
            {
                cout << "Ingrese una opcion valida" << endl;
                break;
            }
            }

            // Verifica que exista y muestra adyacencias:
            sala_modificar = verificar_existencia_sala(grafo, "Ingrese el ID de la sala a mostrar adyacencias: ");
            mostrar_adyacencias(grafo, sala_modificar);
            break;
        }
        case 4: // Borrar sala
        {
            borrar_sala_usuario(grafo);
            break;
        }
        case 5: // Editar sala
        {
            int resp = 0;

            if (grafo_vacio(grafo)) // Verifica que el grafo no este vacio
            {
                cout << "No hay salas para editar" << endl;
                break;
            }
            cout << "Antes de ingresar el ID de la sala para modificar. " << endl;
            cout << "¿Desea ver todas las salas del mapa?" << endl;
            cout << "1. Si" << endl;
            cout << "2. No" << endl;
            resp = obtener_opcion();
            switch (resp)
            {
            case 1: // Se muestra todo el mapa
            {
                cout << "Salas del mapa: " << endl;
                mostrar_salas_grafo(grafo);
                break;
            }
            case 2: // No se muestra el mapa
            {
                cout << "No se mostraran las salas del mapa" << endl;
                break;
            }
            default: // Si elige una opcion distinta
            {
                cout << "Ingrese una opcion valida" << endl;
                break;
            }
            }

            sala_modificar = verificar_existencia_sala(grafo, "Ingrese el ID de la sala que desea modificar: ");
            editar_sala(grafo, sala_modificar->id);
            break;
        }
        case 6: // Salir al menu
        {
            cout << "Saliendo al menu principal..." << endl;
            break;
        }
        default: // Default
        {
            cout << "Invalido. Ingrese una opcion valida \n";
            break;
        }
        }
    } while (opcion_interna != 6);
}

void menu_pre_juego() // Caso 7 del main
{
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
        else if (cantidad_poderes < 4)
        {
            cout << "No hay poderes suficientes para empezar el juego." << endl;
            cout << "Saliendo al menu principal..." << endl;
            break;
        }

        // faltaria el validar que este el mapa
        // los poderes no porque ya son funciones predeterminadas.
        cout << "¿Esta contento con las modificaciones realizadas?" << endl;
        cout << "Tome en cuenta que al empezar el juego no podra modificar lo siguiente:" << endl;
        cout << "   Tipos de heroes y orcos." << endl;
        cout << "   Personajes heroes y orcos." << endl;
        cout << "   Poderes, implementos y mapa.\n"
             << endl;
        cout << "Los cambios realizados anteriormente seran permanentes para esta partida" << endl;
        cout << "1. Si, estoy conforme" << endl;
        cout << "2. No, no estoy conforme" << endl;

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
        cout << "Seleccion de Personajes" << endl;

        cout << "\n MENU DE PERSONAJES PARA JUGAR:\n";
        cout << "---------------------\n";
        cout << "1. Elegir personaje y sus objetos\n";
        cout << "2. Mostrar personaje del equipo actual. \n";
        cout << "3. Modificar mochila. \n";
        cout << "4. Eliminar personaje del equipo. \n";
        cout << "---------------------\n";
        cout << "5. EQUIPO TERMINADO. Empezar a jugar.  \n";
        cout << "---------------------\n";
        opcion_interna = obtener_opcion();

        switch (opcion_interna)
        {
        case 1:
            eleccion_personaje(personajes_jugar, personajes_hero, lista_implementos, lista_podere_magicos);
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
    } while (opcion_interna != 5);
}

void menu_principal() // MENU PRINCIPAL !!!
{

    cout << "\n MENU PRINCIPAL \n";
    cout << "---------------------\n";
    cout << "1. Menu de Especies de Orcos" << "\n";
    cout << "2. Menu de Especies de Heroes y Personajes" << "\n";
    cout << "---------------------\n";
    cout << "3. Menu de Implementos" << "\n";
    cout << "4. Menu de Poderes Magicos \n";
    cout << "5. cargar archivos predeterminados del juego.\n";
    cout << "---------------------\n";
    cout << "6. Menu del Mapa.\n";
    cout << "---------------------\n";
    cout << "7. EMPEZAR EL JUEGO. \n ";
    cout << "---------------------\n";
    cout << "8. Salir del programa completo." << "\n";
    opcion_principal = obtener_opcion();

    // Switch para Menu Principal
    switch (opcion_principal)
    {
    // Menu Orcos
    case 1:
        menu_orcos();
        break;

    // Menu Heroes
    case 2:
        menu_especies_heroes_personajes();
        break;

    // Menu Implementos
    case 3:
        menu_implementos();
        break;

    // Menu de poderes magicos
    case 4:
        menu_poderes_magicos();
        break;

    // carga de archivos.
    case 5:
        carga_archivos();
        break;

    // Menu de Mapa
    case 6:
        menu_mapas();
        break;

    // Menu para antes de Jugar
    case 7:
        menu_pre_juego();
        break;

    case 8:
        cout << "Saliendo del programa... " << endl;
        break;

    // Default del Menu Principal:
    default:
        cout << "Invalido. Ingrese una opcion valida";
        break;
    }
}