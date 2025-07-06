// GRUPO DE PROYECTO 1
// Integrantes:
// - Miguel Madera
// - Santiago Romero
// - Nabil Bedros

// Librerias Locales:

#include "01.funciones_genericas.h"                // Funciones generales y librerias para el programa
#include "02.funciones_tipos_especie.h"            // Funciones para las Especies de Heroes y Orcos
#include "03.funciones_implementos.h"              // Funciones para Implementos
#include "04.funciones_mochila_personajes_jugar.h" // Funciones de la Mochila y Personajes Jugar
#include "05.funciones_poder_magico.h"             // Funciones para los Poderes Magicos
#include "06.funciones_mapa.h"                     // Funciones para el mapa (grafo)
#include "07.funciones_cargar_archivo.h"           // Funciones para la carga de archivos

//#include "08.movimiento.h"                         // Movimiento Ingame (Orcos y heroes)

#include "09.menus_main.h"                         // Todos los menus del main


//#include "10.combate.h"                            // Sistema de combate
//#include "11.turnos_jugabilidad.h"                 // Implementacion de todos los sistemas de mov y pelea

// Funcion declarada aqui porque sino daba error
// Sepa Dios por que
// 1) Poder MÃ¡gico que permite a todos los enanos recuperar su salud y
// hacer que aumente su salud en 100 y su fortaleza en 1000
void poder_vigor_enano(personaje *lista_personajes_jugar)
{
    // Creacion del poder magico:
    // nuevo->nombre_poder = "Vigor de Enanos";
    // nuevo->funcion = "Poder magico que recupera la salud de todos los enanos.
    // Aumenta su salud en 100 y su fortaleza en 1000";

    personaje *actual_personaje = lista_personajes_jugar;
    bool modificado = false;

    if (actual_personaje == nullptr)
    {
        std::cout << "No hay personajes disponibles en el equipo" << endl;
    }
    while (actual_personaje != nullptr)
    {
        if (actual_personaje->tipo->nombre_especie == "Enano")
        {
            modificado = true;
            // Le recupera toda la vida (La devuelve a su valor original)
            actual_personaje->tipo->salud = actual_personaje->tipo->salud;
            std::cout << "La vitalidad del personaje" << actual_personaje->nombre << "ha sido regenerada por completo (" << actual_personaje->tipo->salud << ")" << endl;

            // Le aumenta la vida en 100
            actual_personaje->tipo->salud += 100;
            std::cout << "La vitalidad del personaje" << actual_personaje->nombre << "ha sido aumentada en 100 (" << actual_personaje->tipo->salud << ")" << endl;

            // Le aumenta la fortaleza en 1000
            actual_personaje->tipo->salud += 1000;
            std::cout << "La fuerza del personaje ha sido aumentada en 1000 (" << actual_personaje->tipo->danno_fortaleza << ")";

            actual_personaje = actual_personaje->siguiente;
        }
    }
    if (modificado == true)
    {
        std::cout << "Los personajes Enanos han sido modificados" << endl;
    }
    else
    {
        std::cout << "No hay personajes Enanos en el equipo" << endl;
    }
}

// 2)Poder MÃ¡gico que dado dos salas traslada los orcos de la primera sala a la segunda
// vaciandolos de orcos
void cambiar_pos_orco_sala()
{
    sala *sala_1 = nullptr;
    sala *sala_2 = nullptr;
    int id;
    cout << "has utilozado el poder numero: 2" << endl;
    cout << "las salas disponibles son: ";
    mostrar_salas_grafo(grafo);
    cout << "Coloque el ID de la sala inicio: ";
    id = obtener_entero("");
    sala_1 = encontrar_sala(grafo, id);
    if (sala_1 == nullptr)
    {
        cout << "la sala con ID:" << id << " no existe" << endl;
        cout << "mal uso del poder." << endl;
        return;
    }
    cout << "Coloque el ID de la sala destino: ";
    id = obtener_entero("");
    sala_2 = encontrar_sala(grafo, id);
    cout << "aplicando poder.." << endl;
    for (int i = 0; i < sala_1->lista_orcos.size(); i++)
    {
        // le pasamos todos los orcos a la sala.
        cout << "Transfiriendo: " << sala_1->lista_orcos[i]->nombre << endl;
        sala_2->lista_orcos.push_back(sala_1->lista_orcos[i]);
    }
    // vaciando la sala origen.
    sala_1->lista_orcos.clear(); // Esto vacía el vector
    cout << "Poder aplicado exitosamente." << endl;
    return;
}

// 3) Poder MÃ¡gigo que hace que todos los orcos de una sala tengan 1 de salud
void salud_0_sala()
{
    int id;
    cout << "las salas actuales son: " << endl;
    mostrar_salas_grafo(grafo);
    cout << "cololque el ID de la sala para aplicaar el poder: ";
    id = obtener_entero("");
    sala *aplicar = encontrar_sala(grafo, id);
    if (aplicar == nullptr)
    {
        cout << "la sala con ID:" << id << " no existe" << endl;
        cout << "mal uso del poder." << endl;
        return;
    }
    cout << "aplicando.." << endl;
    for (size_t i = 0; i < aplicar->lista_orcos.size(); i++)
    {
        aplicar->lista_orcos[i]->tipo->salud = 1;
        cout << "NOMBRE: " << aplicar->lista_orcos[i]->nombre << " - Vitalidad: " << aplicar->lista_orcos[i]->tipo->salud << endl;
    }
    cout << "Poder aplicado exitosamente." << endl;
    return;
}

// 4) Poder MÃ¡gico que hace que todo ataque de un implemento se duplique y
// la fortaleza para usarlo se reduzca a 0
void potenciar_implemento(personaje *&aplicar)
{
    int id;
    cout << "Los implementos disponibles son: " << endl;
    Implemento *actual_implemento = aplicar->mimochila->implementos;
    cout << "  Implementos: ";
    if (actual_implemento == nullptr)
    {
        cout << "La mochila esta vacia" << endl; // Antes decia "ninguno". Verificar
        cout << "mal uso del poder." << endl;
        return;
    }
    else
    {
        cout << endl;
        while (actual_implemento != nullptr)
        {
            cout << "ID:" << actual_implemento->identificador << " - " << actual_implemento->nombre_implemento << endl;
            actual_implemento = actual_implemento->siguiente;
        }
    }
    cout << "Coloque el ID del implemeto a aplicar el poder: ";
    id = obtener_entero("");
    actual_implemento = aplicar->mimochila->implementos;
    while (actual_implemento != nullptr)
    {
        if (actual_implemento->identificador == id)
        {
            actual_implemento->fortalezanecesaria = 0;
            actual_implemento->valor = (actual_implemento->valor * 2);
            cout << "Aplicando.." << endl;
            cout << "Fortaleza necesaria: " << actual_implemento->fortalezanecesaria << endl;
            cout << "Valor: " << actual_implemento->valor << endl;
            cout << "Poder aplicado exitosamente." << endl;
            return;
        }
    }
    cout << "El implemento con ID:" << id << " no existe" << endl;
    cout << "Mal uso del poder." << endl;
    return;
}

//-----------------------------------------------------------------------------------------------------
//----------------------------------- FUNCIONES JUGABILIDAD -------------------------------------------

// Aqui va todo lo que sea juego como tal, menu de acciones, para usar objetos, etc

//-----------------------------------------------------------------------------------------------------
//------------------------------ EJECUCION DEL PROGRAMA -----------------------------------------------

int main()
{

    // Semilla aleatoria inicializada (para el num random de orcos)
    srand(time(NULL));

    cout << "¡¡¡ Bienvenido al juego Khazad-Dum !!!" << endl;
    cout << "Se recomienda visitar todos los menus en orden descendente para una mejor experiencia de juego." << endl;

    do // Menu mientras.
    {
        menu_principal();
    } while (opcion_principal != 7 && !iniciar_juego); // Ambas opciones hacen que salga del menu

    // ---------------------------------- GAMEPLAY ------------------------------------
    
    
    
    // da error
    //if (opcion_principal != 7)
    //{
        //juego(turno);
    //}

    
    
    // --------------------------------------------------------------------------------
    // --------------- FIN DEL PROGRAMA. DESTRUCTORES DE ARCHIVOS TEMPORALES ----------

    // Destructor de especies
    destruir_lista_especie(tipoEspecieHeroe);
    destruir_lista_especie(tipoEspecieOrco); // se destruye la lista al final del programa.

    // Destructor de personajes
    destruir_lista_personajes(personajes_orco);
    destruir_lista_personajes(personajes_hero);

    // Destructor de implementos, personajes para jugar, poderes y mapa
    destruir_implementos(lista_implementos);
    destruir_poder_magico(lista_podere_magicos);
    destruir_personaje_jugar(personajes_jugar);
    destruir_grafo(grafo);

    cout << "Gracias por usar el programa. \n";
}
// fin del programa.
