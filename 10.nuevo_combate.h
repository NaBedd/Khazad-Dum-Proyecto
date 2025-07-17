#pragma once
#include "01.funciones_genericas.h"
#include "02.funciones_tipos_especie.h"
#include "03.funciones_implementos.h"
#include "04.funciones_mochila_personajes_jugar.h"
#include "05.funciones_poder_magico.h"
#include "06.funciones_mapa.h"
#include "09.menus_main.h"

/*
Habra una funcion batalla que contenga la pelea de heroes y la de orcos
Alli estaran los couts de los turnos y todo lo general
Recibira por parametro "orcos" o "heroes" para decidir quien empieza primero

El combate funcionara de la siguiente manera:
pelea_heroes
    Los Heroes emboscan a los orcos

pelea_orcos
    Los Orcos emboscan a los heros

Menu_pelea
Este es el menu de accion de los heroes, aca podran decidir todo durante el comabte
    Contendra distintas funciones (atacar, huir, objeto, poder magico)
    habra funciones atacar_heroes y atacar_orcos por separado

La recuperacion de los heroes ocurrira en menu_combate
    mientras se haya elegido no atacar

Las funciones dentro de menu pelea, recibiran como parametro el heroe actual, para evitar complicaciones
*/

int turno = 0;

// !No se si esto funcione. Revisar que la recuperacion si se haga con el &*
// Quitar fortaleza anterior y los cout innecesarios
void recuperar_fortaleza(Lista_especie especies_heroes, personaje *&heroe_actual)
{
    cout << "Se ha regenerado la fortaleza de " << heroe_actual->nombre << endl;
    int fortaleza_anterior = heroe_actual->tipo->danno_fortaleza;

    Especie *referencia = encontrar_especie_id(especies_heroes, heroe_actual->tipo->identificador);
    int recuperacion = referencia->danno_fortaleza * 0.1;
    heroe_actual->tipo->danno_fortaleza = min(referencia->danno_fortaleza, heroe_actual->tipo->danno_fortaleza + recuperacion); // con esto se evita que exceda el maximo de vida de su especie

    // cout temporal. Esto deberia de ir en menu_combate, no aqui
    cout << "Fortaleza: " << fortaleza_anterior << " --> " << heroe_actual->tipo->danno_fortaleza << endl;
    cout << "Aqui termina la funcion recuperar_fortaleza" << endl;
}

personaje *encontrar_orco_mas_debil(sala *sala_actual) // Encontrar orco mas debil
{
    personaje *orco_debil = nullptr;
    int min_salud = INT_MAX;

    // !Editarrr
    // encontrar_personaje(sala_actual->lista_orcos, 1);
    // se podria hacer que trabaje sin la variable auxiliar?

    for (personaje *orco : sala_actual->lista_orcos)
    {
        if (orco && orco->tipo->salud > 0 && orco->tipo->salud < min_salud)
        {
            min_salud = orco->tipo->salud;
            orco_debil = orco;
        }
    }
    return orco_debil;
}

personaje *encontrar_heroe_mas_debil(sala *sala_actual) // Encontrar heroe mas debil
{
    personaje *heroe_debil = nullptr;
    int min_salud = INT_MAX;

    for (personaje *heroe : sala_actual->lista_heroes)
    {
        if (heroe && heroe->tipo->salud > 0 && heroe->tipo->salud < min_salud)
        {
            int vitalidad_efectiva = heroe->tipo->salud;
            Implemento *implemento_actual = heroe->mimochila->implementos;

            while (implemento_actual != nullptr)
            {
                if (implemento_actual->tipo_implemento == "Defensa")
                {
                    vitalidad_efectiva += implemento_actual->valor;
                }
                implemento_actual = implemento_actual->siguiente;
            }
            if (vitalidad_efectiva < min_salud)
            {
                min_salud = vitalidad_efectiva;
                heroe_debil = heroe;
            }
        }
    }
    return heroe_debil;
}

void ataque_heroe(personaje *heroe_actual, personaje *orco_objetivo, sala *sala_actual)
{
    vector<Implemento *> lista_armas;
    cout << "Elija un arma" << endl;
    Implemento *arma_actual = heroe_actual->mimochila->implementos;
    int contador = 1;

    // Pendiente limitar para escoger las armas, que no ponga un numero loco
    while (arma_actual != nullptr)
    {
        if (arma_actual->tipo_implemento == "Arma")
        {
            cout << contador << ". " << arma_actual->nombre_implemento << endl;
            cout << "Danno: " << arma_actual->valor << endl;
            cout << "Fortaleza Necesaria: " << arma_actual->fortalezanecesaria << endl;
            cout << "Usos restantes: " << arma_actual->usos << endl;
            lista_armas.push_back(arma_actual);
        }
        else
        {
            cout << "TEMPORAL el implemento " << arma_actual->nombre_implemento << " no es un arma" << endl;
        }

        arma_actual = heroe_actual->mimochila->implementos->siguiente;
    }
}

void menu_combate_heroes(sala *sala_actual, personaje *heroe_actual)
{
    cout << "            Heroe: " << heroe_actual->nombre << endl;
    cout << "1. Atacar" << endl;
    cout << "2. Usar objeto" << endl;
    cout << "3. Poder Magico" << endl;
    cout << "4. Pasar Turno" << endl;
    cout << "5. Huir" << endl;
    int opcion = obtener_entero("Indique la accion del heroe: ");
    switch (opcion)
    {
    case 1: // atacar
    {

        break;
    }
    case 2: // objeto
    {
        recuperar_fortaleza(tipoEspecieHeroe, heroe_actual);
        break;
    }
    case 3: // Poder Magico
    {
        break;
    }
    case 4: // Pasar Turno
    {
        recuperar_fortaleza(tipoEspecieHeroe, heroe_actual);
        break;
    }
    case 5: // Huir
    {
        recuperar_fortaleza(tipoEspecieHeroe, heroe_actual);
        break;
    }
    default: // Default
    {
        cout << "Ingrese una opcion valida" << endl;
        break;
    }
    }
}
