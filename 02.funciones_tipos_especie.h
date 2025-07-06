#pragma once // Soluciona errores de redefinicion
// 02. Ya incluye las genericas
#include "02.funciones_tipos_especie.h"
#include <iostream>
#include <string>

using namespace std;

// Regulador para cuando se eliminen tipos de orcos en la lista.
int regulador_tipo_orco = 7;  // por el archivo
int regulador_tipo_heroe = 7; // por el archivo

// Tipos de especies: Heroes y Orcos
struct Especie
{
    string nombre_especie;
    int danno_fortaleza;
    int salud;
    int rapidez;
    int identificador;
    Especie *siguiente; // no se pone como null porque la lista esta planteada de otra manera.
};

// Listas enlazadas de Especies
struct Lista_especie
{
    Especie *primero_especie = nullptr;
    int cantidad = 0;
};

string pausa1 = " ";

// PARA CREAR UN NUEVO TIPO DE ORCO.
void Crear_tipo(Lista_especie &lista, int tipo) // tipo=1 orco / tipo=2 heroe
{
    Especie *nuevo = new Especie();

    printf("\033[0;33m"); // Amarillo
    if (tipo == 1)
    { // si es orco
        cout << "\nIngrese los datos para la nueva especie de Orco: \n";
    }
    else if (tipo == 2)
    { // si es heroe
        cout << "\nIngrese los datos para la nueva especie de Heroe: \n";
    }
    else
    {
        printf("\033[0;31m"); // Rojo
        cout << "ERROR. TIPO NO ESPECIFICADO. VERIFICAR NUMERO QUE SE LE PUSO A LA FUNCION CREAR_TIPO \n";
        printf("\033[0;37m"); // Gris claro
        cout << "Pulse enter para continuar:" << endl;
        getline(cin, pausa1);
        return;
    }

    printf("\033[0;37m"); // Gris claro
    nuevo->nombre_especie = devolver_string_verificada("Nombre de la especie: ");

    if (tipo == 1)
    {
        nuevo->danno_fortaleza = obtener_entero("Danno: ");
    }
    else if (tipo == 2)
    {
        nuevo->danno_fortaleza = obtener_entero("Fortaleza: ");
    }
    else
    {
        printf("\033[0;31m"); // Rojo
        cout << "ERROR. TIPO NO ESPECIFICADO. VERIFICAR NUMERO QUE SE LE PUSO A LA FUNCION CREAR_TIPO \n";
        printf("\033[0;37m"); // Gris claro
        cout << "Pulse enter para continuar:" << endl;
        getline(cin, pausa1);
        return;
    }

    nuevo->salud = obtener_entero("Salud: ");
    nuevo->rapidez = obtener_entero("Rapidez: ");

    cout << endl;

    // inserta de primero en la lista.
    nuevo->siguiente = lista.primero_especie;
    lista.primero_especie = nuevo;
    lista.cantidad = lista.cantidad + 1;

    if (tipo == 1)
    {
        nuevo->identificador = (lista.cantidad + regulador_tipo_orco);
        printf("\033[0;32m"); // Verde
        cout << "Especie de orco " << nuevo->nombre_especie << " ha sido agregada exitosamente. \n";
    }
    else
    {
        nuevo->identificador = (lista.cantidad + regulador_tipo_heroe);
        printf("\033[0;32m"); // Verde
        cout << "Especie de heroe " << nuevo->nombre_especie << " ha sido agregada exitosamente. \n";
    }
    printf("\033[0;37m"); // Gris claro
    cout << "Pulse enter para continuar:" << endl;
    getline(cin, pausa1);
}

// Para mostrar listas de especies
void mostrar_lista(const Lista_especie &lista, int tipo) // tipo=1 orco / tipo=2 heroe
{
    if (lista.cantidad == 0)
    {
        printf("\033[0;31m"); // Rojo
        cout << "No hay especies disponibles. \n\n";
        printf("\033[0;37m"); // Gris claro
        cout << "Pulse enter para continuar:" << endl;
        getline(cin, pausa1);
        return;
    }

    if (tipo == 1)
    {
        printf("\033[0;33m"); // Amarillo
        cout << "\nHay [" << lista.cantidad << "] especies de orcos disponibles" << endl;
    }
    else
    {
        printf("\033[0;33m"); // Amarillo
        cout << "\nHay [" << lista.cantidad << "] especies de heroes disponibles" << endl;
    }
    printf("\033[0;37m"); // Gris claro

    Especie *actual = lista.primero_especie;
    while (actual != nullptr)
    {
        cout << actual->identificador << ". ";
        cout << "Nombre: " << actual->nombre_especie << endl;

        printf("\033[0;36m"); // Cyan para atributos
        if (tipo == 1)
        {
            cout << "Danno: " << actual->danno_fortaleza << endl;
        }
        else
        {
            cout << "Fortaleza: " << actual->danno_fortaleza << endl;
        }
        cout << "Salud: " << actual->salud << endl;
        cout << "Rapidez: " << actual->rapidez << "\n"
             << endl;
        printf("\033[0;37m"); // Gris claro para resetear color

        actual = actual->siguiente;
    }
    cout << "No hay mas tipos disponibles.\n";
}

// Para actualizar tipos de especies.
void actualizar_tipo(Lista_especie &lista, int tipo) // tipo=1 orco / tipo=2 heroe
{
    if (lista.cantidad == 0)
    {
        printf("\033[0;31m"); // Rojo
        cout << "La lista se encuentra vacia.\n\n";
        printf("\033[0;37m"); // Gris claro
        cout << "Pulse enter para continuar:" << endl;
        getline(cin, pausa1);
        return;
    }

    int referencia;
    printf("\033[0;33m"); // Amarillo
    cout << "\nLas especies disponibles son: " << endl;
    printf("\033[0;37m"); // Gris claro
    cout << "------------------------" << endl;
    mostrar_lista(lista, tipo);
    if (tipo == 1)
    {
        referencia = obtener_entero("Ingrese el numero de especie orco a modificar: ");
    }
    else if (tipo == 2)
    {
        referencia = obtener_entero("Ingrese el numero de especie heroe a modificar: ");
    }
    else
    {
        printf("\033[0;31m"); // Rojo
        cout << "ERROR. VERIFICAR CODIGO. ACTUALIZAR_TIPO" << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "Pulse enter para continuar:" << endl;
        getline(cin, pausa1);
        return;
    }
    Especie *actual = lista.primero_especie;
    bool encontrado = false;

    while (actual != nullptr)
    {
        if (actual->identificador == referencia)
        {
            if (tipo == 1)
            {
                printf("\033[0;33m"); // Amarillo
                cout << "\nIngrese los datos a actualizar para la especie orco con identificador " << referencia << ":\n";
            }
            else
            {
                printf("\033[0;33m"); // Amarillo
                cout << "\nIngrese los datos a actualizar para la especie heroe con identificador " << referencia << ":\n";
            }
            printf("\033[0;37m"); // Gris claro

            actual->nombre_especie = devolver_string_verificada("Nombre de la especie: ");

            if (tipo == 1)
            {
                actual->danno_fortaleza = obtener_entero("Danno: ");
            }
            else
            {
                actual->danno_fortaleza = obtener_entero("Fortaleza: ");
            }

            actual->salud = obtener_entero("Salud: ");
            actual->rapidez = obtener_entero("Rapidez: ");

            printf("\033[0;32m"); // Verde
            if (tipo == 1)
            {
                cout << "Datos de la especie orco " << actual->nombre_especie << " actualizados exitosamente.\n";
            }
            else
            {
                cout << "Datos de la especie heroe " << actual->nombre_especie << " actualizados exitosamente.\n";
            }
            printf("\033[0;37m"); // Gris claro
            cout << "Pulse enter para continuar:" << endl;
            getline(cin, pausa1);
            encontrado = true;
            break;
        }
        actual = actual->siguiente;
    }

    if (!encontrado)
    {
        printf("\033[0;31m"); // Rojo
        cout << "No se encontro ninguna especie con ID: " << referencia << ".\n";
        printf("\033[0;37m"); // Gris claro
        cout << "Pulse enter para continuar:" << endl;
        getline(cin, pausa1);
    }
}

// funcion para liberar memoria dinamica.
void destruir_lista_especie(Lista_especie &lista)
{
    Especie *actual = lista.primero_especie;
    while (actual != nullptr)
    {
        Especie *eliminar = actual;
        actual = actual->siguiente;
        delete eliminar;
    }
    lista.primero_especie = nullptr;
    lista.cantidad = 0;
}

// Funcion que retorna un puntero a una especie.
Especie *encontrar_especie_id(Lista_especie &lista, int identificador)
{
    Especie *actual = lista.primero_especie;
    while (actual != nullptr)
    {
        if (actual->identificador == identificador)
        {
            return actual;
        }
        actual = actual->siguiente;
    }
    printf("\033[0;31m"); // Rojo
    cout << "La especie ingresada no existe." << endl;
    printf("\033[0;37m"); // Gris claro
    return nullptr;
}
