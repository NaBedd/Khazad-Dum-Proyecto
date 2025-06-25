#include <climits> //esta libreria la uso para usar el int max o entero mximo
#include <vector>
#include <algorithm> 

using namespace std;

personaje* encontrar_orco_mas_debil(sala* sala_actual) {
    personaje* orco_debil = nullptr;
    int min_salud = INT_MAX;
    
    for (personaje* orco : sala_actual->lista_orcos) {
        if (orco && orco->vitalidad > 0 && orco->vitalidad < min_salud) {
            min_salud = orco->vitalidad;
            orco_debil = orco;
        }
    }
    return orco_debil;
}

personaje* encontrar_orco_mas_debil(sala* sala_actual) {
    personaje* heroe_lento = nullptr;
    int min_rapidez = INT_MAX;
    
    for (personaje* heroe : sala_actual->lista_heroes) {
        if (heroe && heroe->rapidez > 0 && heroe->rapidez < min_rapidez) {
            min_rapidez = heroe->rapidez;
            heroe_lento = heroe;
        }
    }
    return heroe_lento;
}

