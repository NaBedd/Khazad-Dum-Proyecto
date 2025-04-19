#include<iostream>
#include<conio.h>
#include<string.h>   //  para que el manejo de str se mas facil.  
#include<string>     //  para que el manejo de str se mas facil.  

using namespace std;


//sin usar clases no las en tendi y ademas el profe no las ha explicado.

//-----------------------------------------------------------------------------------------------------
// PARA CREAR LAS ESPECIES. 
// devido a que cada personaje pertenece a una especie diferente ya sea orco o heroe.

const int espacio_array=1000;  // el numero de espacio que tendran los arrays.

//  ---------------------                    ORCO                    --------------------

// Para las especies de orcos. 
typedef struct {
    /* data */
    string nombre_especie;
    int danno;
    int salud;
    int rapidez;
    string descripcion;
}Especie_orco;        
typedef Especie_orco *puntero_especie_orco;    // TIPO PUNTERO, apunta al tipo Especie_orco.
// LISTA PARA LAS ESPECIES DE ORCOS.
typedef puntero_especie_orco array_especie_orcos[espacio_array];   // tipo array para guardar las especies de los orcos.
// EXTRUCTRURA FINAL PARA GUARDAR LOS DATOS.
typedef struct {
    /* data */
    array_especie_orcos registro; // Array que guarda los datos de tipo especie_orco.
    int numero;                   // Numeros de datos guardados.
}lista_epecie_orco;

//          -----------------               HEROE               ---------------------------

// Para las especies de heroes. 
typedef struct {
    /* data */
    string nombre_especie;
    int fortaleza;
    int salud;
    int rapidez;
    string descripcion;
}Especie_heroe; 
typedef Especie_heroe *puntero_epsecie_heroe;   // TIPO PUNTERO, apunta al tipo Especie_heroe.
// LISTA PARA LA ESPESCIES DE HEROES.
typedef puntero_epsecie_heroe array_especie_heroe[espacio_array];  // tipo array para guardar los datos de o heroes.
// EXTRUCTURAFINAL PARA GUARDAR LOS DATOS.
typedef struct {
    /* data */
    array_especie_heroe registro_especie;
    int numero_especie;
}lista_especie_heroe;

//-----------------------------------------------------------------------------------------------------

// PARA CREAR LOS PERSONAJES.
/* Cada heroe y orco pertenece a una especie, cada especie tiene caracteristicas diferentes. por lo tanto,
   cada heroe y orco comparte las mismas caracteriticas que los demas integrantes de su especie, 
   lo que cambia es el nombre.
*/

// Para crear orcos.
typedef struct {
    /* data */
    string nombre_orco;
    Especie_orco especie;
}Personaje_orco;
typedef Personaje_orco *puntero_personajer_orco;
// LITA PARA LOS PERSONAJES ORCOS.
typedef puntero_epsecie_heroe array_personaje_orco[espacio_array];
// EXTRUCTURA FINAL PARA GUARDAR LOS DATOS.
typedef struct {
    /* data */
    array_personaje_orco registro_personaje;
    int numero_personaje;
}lista_personajes_orco;



// Para crar heroes.
typedef struct {
    /* data */
    string nombre_heroe;
    Especie_heroe especie;
}Personaje_heroe;
typedef Personaje_heroe *puntero_personaje_heroe;
// LISTA PARA LOS PERSONAJES HEROES.
typedef puntero_epsecie_heroe array_personje_heroe[espacio_array];
// EXTRUCTURA FINA PARA GUARDAR LOS DATOS.
typedef struct {
    /* data */
    array_personje_heroe registro_personaje;
    int numero_personaje;
}lista_personaje_heroe;
 
//-----------------------------------------------------------------------------------------------------

// PROTOTIPO DE FUNCION.

// funcio para agregar una especie.


int main(){

    return 0;
}

// DEFINICION DE FUNCIONES.