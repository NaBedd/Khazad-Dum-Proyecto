#pragma once
#include "01.funciones_genericas.h"
#include "08.movimiento.h"
#include "10.combate.h"

/*
Para que es este archivo?

Falta:
    -Turnos de movimiento(turnos fuera de combate)
    -Aparicion de la puerta magica
        -Que la puerta se mueva
    Debo de programar TurnoFueraCombate, para controlar el movimiento de la puerta magica y la aparicion de orcos
    La energia se les va a recuperar por cada TURNO de movimiento, no por sala movida
*/

void turno_movimiento()
{
    int turno = 1;
    cout << "--- TURNO " << turno << "---";
}