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
personaje *personajes_jugar = nullptr; // aqui estan los 4 personajes que el usuario coloque para jugar.

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

string pausa5 = " "; // para las pausas.

void menu_orcos() // Case 1 del main
{
    do
    {
        printf("\033[0;33m"); // Amarillo
        cout << "\n==========================================" << endl;
        cout << "               MENU ORCOS                  " << endl;
        cout << "==========================================" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "------------------------------------------" << endl;
        printf("\033[1;36m"); // Cyan negrita
        cout << "            -- ESPECIES ORCOS --           " << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "1. Crear especie de orco" << endl;
        cout << "2. Actualizar datos de una especie de orco" << endl;
        cout << "3. Mostrar las especies de orcos disponibles" << endl;
        cout << "4. Eliminar especie de orco" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "------------------------------------------" << endl;
        printf("\033[1;36m"); // Cyan negrita
        cout << "           -- PERSONAJES ORCOS --          " << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "5. Crear personaje orco" << endl;
        cout << "6. Mostrar personajes orco" << endl;
        cout << "7. Modificar personajes orco" << endl;
        cout << "8. Eliminar personajes orco" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "------------------------------------------" << endl;
        printf("\033[1;31m"); // Rojo negrita
        cout << "9. Salir al menu principal" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "------------------------------------------" << endl;
        printf("\033[0;34m"); // Azul
        cout << "Ingrese su opcion: ";
        opcion_interna = obtener_opcion();

        switch (opcion_interna)
        {
        case 1:
            Crear_tipo(tipoEspecieOrco, 1);
            cout << "pulse enter para continuar." << endl;
            getline(cin, pausa5);
            limpiar_pantalla();
            break;
        case 2:
            actualizar_tipo(tipoEspecieOrco, 1);
            cout << "pulse enter para continuar." << endl;
            getline(cin, pausa5);
            limpiar_pantalla();
            break;
        case 3:
            mostrar_lista(tipoEspecieOrco, 1);
            cout << "pulse enter para continuar." << endl;
            getline(cin, pausa5);
            limpiar_pantalla();
            break;
        case 4:
            eliminar_elemento_lista(tipoEspecieOrco, personajes_orco, 1);
            cout << "pulse enter para continuar." << endl;
            getline(cin, pausa5);
            limpiar_pantalla();
            break;
        case 5:
            crear_personaje(personajes_orco, tipoEspecieOrco, 1);
            cout << "pulse enter para continuar." << endl;
            getline(cin, pausa5);
            limpiar_pantalla();
            break;
        case 6:
            mostrar_personajes(personajes_orco, 1);
            cout << "pulse enter para continuar." << endl;
            getline(cin, pausa5);
            limpiar_pantalla();
            break;
        case 7:
            actualizar_personaje(personajes_orco, tipoEspecieOrco, 1);
            cout << "pulse enter para continuar." << endl;
            getline(cin, pausa5);
            limpiar_pantalla();
            break;
        case 8:
            borrar_personaje(personajes_orco, 1);
            cout << "pulse enter para continuar." << endl;
            getline(cin, pausa5);
            limpiar_pantalla();
            break;
        case 9:
            cout << "\nSaliendo al menu principal..." << endl;
            break;
        default:
            cout << "Opcion invalida. Ingrese una opcion valida." << endl;
            break;
        }
    } while (opcion_interna != 9);
}

void menu_especies_heroes_personajes() // Case 2 del main
{
    do
    {
        printf("\033[0;33m"); // Amarillo
        cout << "\n==========================================" << endl;
        cout << "               MENU HEROES                 " << endl;
        cout << "==========================================" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "------------------------------------------" << endl;
        printf("\033[1;36m"); // Cyan negrita
        cout << "            -- ESPECIES HEROES --          " << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "1. Crear especie de heroe" << endl;
        cout << "2. Actualizar datos de una especie de heroe" << endl;
        cout << "3. Mostrar especies de heroes disponibles" << endl;
        cout << "4. Eliminar especie de heroe" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "------------------------------------------" << endl;
        printf("\033[1;36m"); // Cyan negrita
        cout << "           -- PERSONAJES HEROES --         " << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "5. Crear personaje heroe" << endl;
        cout << "6. Mostrar personajes heroe" << endl;
        cout << "7. Modificar personaje heroe" << endl;
        cout << "8. Eliminar personaje heroe" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "------------------------------------------" << endl;
        printf("\033[1;31m"); // Rojo negrita
        cout << "9. Salir al menu principal" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "------------------------------------------" << endl;
        printf("\033[0;35m"); // Purpura
        cout << "Ingrese su opcion: ";
        opcion_interna = obtener_opcion();

        switch (opcion_interna)
        {
        case 1:
            limpiar_pantalla();
            Crear_tipo(tipoEspecieHeroe, 2);
            cout << "pulse enter para continuar." << endl;
            getline(cin, pausa5);
            limpiar_pantalla();
            break;
        case 2:
            limpiar_pantalla();
            actualizar_tipo(tipoEspecieHeroe, 2);
            cout << "pulse enter para continuar." << endl;
            getline(cin, pausa5);
            limpiar_pantalla();
            break;
        case 3:
            limpiar_pantalla();
            mostrar_lista(tipoEspecieHeroe, 2);
            cout << "pulse enter para continuar." << endl;
            getline(cin, pausa5);
            break;
        case 4:
            limpiar_pantalla();
            eliminar_elemento_lista(tipoEspecieHeroe, personajes_hero, 2);
            cout << "pulse enter para continuar." << endl;
            getline(cin, pausa5);
            break;
        case 5:
            limpiar_pantalla();
            crear_personaje(personajes_hero, tipoEspecieHeroe, 2);
            cout << "pulse enter para continuar." << endl;
            getline(cin, pausa5);
            break;
        case 6:
            limpiar_pantalla();
            mostrar_personajes(personajes_hero, 2);
            cout << "pulse enter para continuar." << endl;
            getline(cin, pausa5);
            break;
        case 7:
            limpiar_pantalla();
            actualizar_personaje(personajes_hero, tipoEspecieHeroe, 2);
            cout << "pulse enter para continuar." << endl;
            getline(cin, pausa5);
            break;
        case 8:
            limpiar_pantalla();
            borrar_personaje(personajes_hero, 2);
            cout << "pulse enter para continuar." << endl;
            getline(cin, pausa5);
            break;
        case 9:
            limpiar_pantalla();
            cout << "\nSaliendo al menu principal..." << endl;
            break;
        default:
            cout << "Opcion invalida. Ingrese una opcion valida." << endl;
            break;
        }
    } while (opcion_interna != 9);
}

void menu_implementos() // Case 3 del main
{
    do
    {
        printf("\033[0;33m"); // Amarillo
        cout << "\n==========================================" << endl;
        cout << "             MENU IMPLEMENTOS              " << endl;
        cout << "==========================================" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "1. Agregar un implemento" << endl;
        cout << "2. Actualizar un implemento" << endl;
        cout << "3. Mostrar los implementos" << endl;
        cout << "4. Eliminar un implemento" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "------------------------------------------" << endl;
        printf("\033[1;31m"); // Rojo negrita
        cout << "5. Salir al menu principal" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "------------------------------------------" << endl;
        printf("\033[0;34m"); // Azul
        cout << "Ingrese su opcion: ";
        opcion_interna = obtener_opcion();

        switch (opcion_interna)
        {
        case 1:
            limpiar_pantalla();
            crear_implemento(lista_implementos);
            cout << "pulse enter para continuar." << endl;
            getline(cin, pausa5);
            limpiar_pantalla();
            break;
        case 2:
            limpiar_pantalla();
            modificar_implemento(lista_implementos);
            cout << "pulse enter para continuar." << endl;
            getline(cin, pausa5);
            limpiar_pantalla();
            break;
        case 3:
            limpiar_pantalla();
            mostrar_implementos(lista_implementos);
            cout << "pulse enter para continuar." << endl;
            getline(cin, pausa5);
            limpiar_pantalla();
            break;
        case 4:
            limpiar_pantalla();
            borrar_implementos(lista_implementos);
            cout << "pulse enter para continuar." << endl;
            getline(cin, pausa5);
            limpiar_pantalla();
            break;
        case 5:
            limpiar_pantalla();
            cout << "\nSaliendo al menu principal..." << endl;
            break;
        default:
            limpiar_pantalla();
            cout << "Opcion invalida. Ingrese una opcion valida." << endl;
            break;
        }
    } while (opcion_interna != 5);
}

void menu_poderes_magicos() // Case 4 del main
{
    do
    {
        printf("\033[0;33m"); // Amarillo
        cout << "\n==========================================" << endl;
        cout << "           MENU PODERES MAGICOS           " << endl;
        cout << "==========================================" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "1. Agregar poder magico" << endl;
        cout << "2. Actualizar poder magico" << endl;
        cout << "3. Mostrar los poderes magicos" << endl;
        cout << "4. Eliminar un poder magico" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "------------------------------------------" << endl;
        printf("\033[1;31m"); // Rojo negrita
        cout << "5. Salir al menu principal" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "------------------------------------------" << endl;
        printf("\033[0;34m"); // Azul
        cout << "Ingrese su opcion: ";
        opcion_interna = obtener_opcion();

        switch (opcion_interna)
        {
        case 1:
            limpiar_pantalla();
            crear_poder(lista_podere_magicos);
            cout << "pulse enter para continuar." << endl;
            getline(cin, pausa5);
            limpiar_pantalla();
            break;

        case 2:
            limpiar_pantalla();
            modificar_poder(lista_podere_magicos);
            cout << "pulse enter para continuar." << endl;
            getline(cin, pausa5);
            limpiar_pantalla();
            break;

        case 3:
            limpiar_pantalla();
            mostrar_poderes(lista_podere_magicos);
            cout << "pulse enter para continuar." << endl;
            getline(cin, pausa5);
            limpiar_pantalla();
            break;
        case 4:
            limpiar_pantalla();
            eliminar_poder(lista_podere_magicos);
            cout << "pulse enter para continuar." << endl;
            getline(cin, pausa5);
            limpiar_pantalla();
            break;
        case 5:
            limpiar_pantalla();
            cout << "\nSaliendo al menu principal..." << endl;
            break;
        default:
            limpiar_pantalla();
            cout << "Opcion invalida. Ingrese una opcion valida." << endl;
            break;
        }
    } while (opcion_interna != 5);
}

void carga_archivos(bool especies_cargadas, bool personajes_cargados,
                    bool implementos_cargados, bool salas_cargadas, bool adyacencias_cargadas) // Case 5 del main
{
    limpiar_pantalla();
    printf("\033[1;33m"); // Amarillo negrita
    cout << "\n==========================================" << endl;
    cout << "           CARGANDO DATOS                 " << endl;
    cout << "==========================================" << endl;
    printf("\033[0m"); // Reset color

    cout << "\nCargando archivos..." << endl;
    cargar_especies(tipoEspecieHeroe, tipoEspecieOrco, especies_cargadas);
    cout << "\nLas especies han sido cargadas." << endl;

    cargar_personajes(personajes_hero, personajes_orco, tipoEspecieHeroe, tipoEspecieOrco, personajes_cargados);
    cout << "\nLos personajes han sido cargados." << endl;

    cargar_implementos(lista_implementos, implementos_cargados);
    cout << "\nLos implementos han sido cargados." << endl;

    carga_salas(grafo, salas_cargadas);
    cout << "\nLas salas han sido cargadas." << endl;

    cargar_adyacencias(grafo, adyacencias_cargadas);
    cout << "\nLas adyacencias han sido cargadas." << endl;

    if (especies_cargadas && implementos_cargados && salas_cargadas &&
        adyacencias_cargadas && personajes_cargados)
    {
        limpiar_pantalla();
        printf("\033[1;32m"); // Verde negrita
        cout << "\n==========================================" << endl;
        cout << "       TODOS LOS DATOS HAN SIDO CARGADOS  " << endl;
        cout << "==========================================" << endl;
        printf("\033[0m"); // Reset color
    }
}

void menu_mapas() // Case 6 del main
{
    do
    {
        printf("\033[0;33m"); // Amarillo
        cout << "\n==========================================" << endl;
        cout << "              MENU DEL MAPA                " << endl;
        cout << "==========================================" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "1. Crear sala" << endl;
        cout << "2. Mostrar mapa" << endl;
        cout << "3. Mostrar adyacencias de una sala" << endl;
        cout << "4. Borrar sala" << endl;
        cout << "5. Editar sala" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "------------------------------------------" << endl;
        printf("\033[1;31m"); // Rojo negrita
        cout << "6. Salir al menu principal" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "------------------------------------------" << endl;
        printf("\033[0;34m"); // Azul
        cout << "Ingrese su opcion: ";
        opcion_interna = obtener_opcion();

        switch (opcion_interna)
        {
        case 1:
            limpiar_pantalla();
            crear_sala_usuario(grafo);
            break;
        case 2:
            limpiar_pantalla();
            printf("\033[1;35m"); // Magenta negrita
            cout << "-------------- Salas del Juego --------------" << endl;
            printf("\033[0m"); // Reset color
            mostrar_salas_grafo(grafo);
            break;
        case 3:
            limpiar_pantalla();
            preguntar_mostrar_salas(grafo);
            sala_modificar = verificar_existencia_sala(grafo, "Ingrese el ID de la sala para mostrar adyacencias: ");
            mostrar_adyacencias(sala_modificar);
            break;
        case 4:
            limpiar_pantalla();
            preguntar_mostrar_salas(grafo);
            borrar_sala_usuario(grafo);
            break;
        case 5:
            limpiar_pantalla();
            if (grafo_vacio(grafo))
            {
                printf("\033[0;31m"); // Rojo
                cout << "No hay salas para editar." << endl;
                printf("\033[0m"); // Reset color
                break;
            }
            cout << "Antes de ingresar el ID de la sala para modificar:" << endl;
            preguntar_mostrar_salas(grafo);
            sala_modificar = verificar_existencia_sala(grafo, "Ingrese el ID de la sala que desea modificar: ");
            editar_sala(grafo, sala_modificar->id);
            break;
        case 6:
            limpiar_pantalla();
            cout << "Saliendo al menu principal..." << endl;
            break;
        default:
            limpiar_pantalla();
            cout << "Opcion invalida. Ingrese una opcion valida." << endl;
            break;
        }
    } while (opcion_interna != 6);
}

void menu_pre_juego()
{
    limpiar_pantalla();

    // VERIFICACIONES
    if (cantidad_personaje_heroe < 4)
    {
        printf("\033[0;31m"); // Rojo
        cout << "No hay heroes suficientes para empezar el juego." << endl;
        cout << "Saliendo al menu principal..." << endl;
        printf("\033[0m"); // Reset color
        return;
    }
    if (cantidad_personaje_orco < 4)
    {
        printf("\033[0;31m"); // Rojo
        cout << "No hay orcos suficientes para empezar el juego." << endl;
        cout << "Saliendo al menu principal..." << endl;
        printf("\033[0m"); // Reset color
        return;
    }
    if (cantidad_implementos < 5)
    {
        printf("\033[0;31m"); // Rojo
        cout << "No hay implementos suficientes para empezar el juego." << endl;
        cout << "Saliendo al menu principal..." << endl;
        printf("\033[0m"); // Reset color
        return;
    }

    // Mensaje de confirmacion (solo una vez)
    printf("\033[0;33m"); // Amarillo
    cout << "\n==========================================" << endl;
    cout << "          CONFIRMACION DE JUEGO            " << endl;
    cout << "==========================================" << endl;
    printf("\033[0;37m"); // Gris claro
    cout << "Esta conforme con las modificaciones realizadas?" << endl;
    cout << "Tenga en cuenta que al empezar el juego no podra modificar lo siguiente:" << endl;
    printf("\033[1;36m"); // Cyan negrita
    cout << "  - Tipos de heroes y orcos." << endl;
    cout << "  - Personajes heroes y orcos." << endl;
    cout << "  - Poderes, implementos y mapa." << endl;
    printf("\033[0;37m"); // Gris claro
    cout << "Los cambios realizados anteriormente seran permanentes para esta partida." << endl;
    printf("\033[1;32m"); // Verde negrita
    cout << "1. Si, estoy conforme" << endl;
    printf("\033[1;31m"); // Rojo negrita
    cout << "2. No, no estoy conforme" << endl;
    printf("\033[0;34m"); // Azul
    cout << "Ingrese su opcion: ";

    res = 0;
    while (res != 1 && res != 2)
    {
        res = obtener_opcion();
        if (res == 2)
        {
            printf("\033[1;31m"); // Rojo
            cout << "Retornando al menu principal..." << endl;
            printf("\033[0m"); // Reset color
            return;            // Salir del menu_pre_juego
        }
        else if (res != 1)
        {
            printf("\033[0;31m"); // Rojo
            cout << "Opcion invalida. Ingrese una opcion valida." << endl;
            printf("\033[0m"); // Reset color
        }
    }

    // Menu de seleccion de personajes y opciones
    do
    {
        limpiar_pantalla();
        printf("\033[0;33m"); // Amarillo
        cout << "\n==========================================" << endl;
        cout << "           MENU DE PERSONAJES PARA JUGAR  " << endl;
        cout << "==========================================" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "1. Elegir personaje y sus objetos" << endl;
        cout << "2. Mostrar personajes del equipo actual" << endl;
        cout << "3. Modificar mochila" << endl;
        cout << "4. Eliminar personaje del equipo" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "------------------------------------------" << endl;
        printf("\033[1;32m"); // Verde negrita
        cout << "5. Empezar a jugar" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "------------------------------------------" << endl;
        printf("\033[0;34m"); // Azul
        cout << "Ingrese su opcion: ";

        opcion_interna = obtener_opcion();

        switch (opcion_interna)
        {
        case 1:
            eleccion_personaje(personajes_jugar, personajes_hero, lista_implementos);
            limpiar_pantalla();
            break;
        case 2:
            mostrar_personajes_jugar(personajes_jugar);
            cout << "pulse enter para continuar." << endl;
            getline(cin, pausa5);
            limpiar_pantalla();
            break;
        case 3:
            modificar_mochila(personajes_jugar, lista_implementos, lista_podere_magicos);
            limpiar_pantalla();
            break;
        case 4:
            eliminar_personaje_jugar(personajes_jugar);
            limpiar_pantalla();
            break;
        case 5:
            if (cantidad_personajes_jugar == 4)
            {
                printf("\033[0;32m"); // Verde
                cout << "\nEquipo actual: " << endl;
                mostrar_personajes_jugar(personajes_jugar);
                cout << "Entrando al juego..." << endl;
                printf("\033[0m"); // Reset color
                iniciar_juego = true;
                break;
            }
            else
            {
                printf("\033[0;31m"); // Rojo
                cout << "Actualmente te faltan personajes para iniciar el juego." << endl;
                printf("\033[0m"); // Reset color
                cout << "Pulse enter para continuar." << endl;
                getline(cin, pausa5);
                limpiar_pantalla();
            }

        default:
            printf("\033[0;31m"); // Rojo
            cout << "Opcion invalida. Ingrese una opcion valida." << endl;
            printf("\033[0m"); // Reset color
            break;
        }
    } while (opcion_interna != 5 && !iniciar_juego);
}

void menu_principal() // MENU PRINCIPAL !!!
{
    do
    {
        printf("\033[0;33m"); // Amarillo
        cout << "\n==========================================" << endl;
        cout << "             MENU PRINCIPAL                " << endl;
        cout << "==========================================" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "0. Cargar datos predeterminados" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "------------------------------------------" << endl;
        printf("\033[1;36m"); // Cyan negrita
        cout << "1. Menu de Orcos" << endl;
        cout << "2. Menu de Heroes" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "------------------------------------------" << endl;
        printf("\033[1;34m"); // Azul negrita
        cout << "3. Menu de Implementos" << endl;
        cout << "4. Menu de Poderes Magicos" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "------------------------------------------" << endl;
        printf("\033[1;35m"); // Magenta negrita
        cout << "5. Menu del Mapa" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "------------------------------------------" << endl;
        printf("\033[1;32m"); // Verde negrita
        cout << "6. Empezar el juego" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "------------------------------------------" << endl;
        printf("\033[1;31m"); // Rojo negrita
        cout << "7. Salir del programa" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "------------------------------------------" << endl;
        printf("\033[0;34m"); // Azul
        cout << "Ingrese su opcion: ";
        opcion_principal = obtener_opcion();
        printf("\033[0m"); // Reset color

        switch (opcion_principal)
        {
        case 0:
        {
            limpiar_pantalla();
            carga_archivos(especies_cargadas, personajes_cargados, implementos_cargados, salas_cargadas, adyacencias_cargadas);
            break;
        }
        case 1:
        {
            limpiar_pantalla();
            menu_orcos();
            break;
        }
        case 2:
        {
            limpiar_pantalla();
            menu_especies_heroes_personajes();
            break;
        }
        case 3:
        {
            limpiar_pantalla();
            menu_implementos();
            break;
        }
        case 4:
        {
            limpiar_pantalla();
            menu_poderes_magicos();
            break;
        }
        case 5:
        {
            limpiar_pantalla();
            menu_mapas();
            break;
        }
        case 6:
        {
            limpiar_pantalla();
            menu_pre_juego();
            break;
        }
        case 7:
        {
            limpiar_pantalla();
            cout << "Saliendo del programa... Hasta pronto!" << endl;
            break;
        }
        default:
            limpiar_pantalla();
            printf("\033[0;31m"); // Rojo
            cout << "Opcion invalida. Ingrese una opcion valida." << endl;
            printf("\033[0m"); // Reset color
            break;
        }
    } while (opcion_principal != 7 && !iniciar_juego);
}
