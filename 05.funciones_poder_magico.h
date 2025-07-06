#pragma once // Soluciona errores de redefinicion
// 03. Ya incluye las genericas
#include "03.funciones_implementos.h"
#include "04.funciones_mochila_personajes_jugar.h"

// Poderes Magicos

struct Poder_magico
{
    string nombre_poder;
    string funcion;
    int identificador;
    Poder_magico *siguiente = nullptr;
};

// Reguladores para Poderes
int cantidad_poderes = 0;
int regulador_poderes = 0;

string p=" "; // para que se pare el programa.

// para crear poderes.
void crear_poder(Poder_magico &lista_poderes)
{
    Poder_magico *nuevo = new Poder_magico;
    cout << "Proceda a llenar las espesificaciones del nuevo poder. \n";
    nuevo->nombre_poder = devolver_string_verificada("Nombre: ");
    // lo coloco sin validar porque imagino que podra colocar numero y eso en la funcion del poder.
    cout << "Funcion: ";
    getline(cin, nuevo->funcion);
    cin.ignore();
    cantidad_poderes += 1;
    nuevo->identificador = cantidad_poderes + regulador_poderes;
    // lo agregamos a la lista enlazada.
    nuevo->siguiente = lista_poderes.siguiente;
    lista_poderes.siguiente = nuevo;
    cout << "El poder: " << nuevo->nombre_poder << "se creo correctamente.\n";
    cout <<"pulse enter para continuar:"<<endl;
    getline(cin, p);
}

void destruir_poder_magico(Poder_magico &lista_poderes)
{
    Poder_magico *actual = lista_poderes.siguiente;
    while (actual != nullptr)
    {
        Poder_magico *eliminar = actual;
        actual = actual->siguiente;
        delete eliminar;
    }
    cantidad_poderes = 0;
    regulador_poderes = 0;
}

// para mostrar los poderes.
void mostrar_poderes(Poder_magico &lista_poderes)
{
    // para ver si hay poderes creados.
    if (cantidad_poderes == 0)
    {
        cout << "No hay poderes disponibles actualmente. \n";
        cout <<"pulse enter para continuar:"<<endl;
        getline(cin, p);
        return;
    }
    Poder_magico *actual = lista_poderes.siguiente;
    cout << "La cantidad de poderes actualmente es: " << cantidad_poderes << endl
         << endl;
    while (actual != nullptr)
    {
        cout << "Nombre: " << actual->nombre_poder << endl;
        cout << "ID: " << actual->identificador << endl;
        cout << "Funcion: " << actual->funcion << endl
             << endl;
        actual = actual->siguiente;
    }
    cout << "No hay mas poderes disponibles.\n";
    cout <<"pulse enter para continuar:"<<endl;
    getline(cin, p);
}

// para encontrar un poder
Poder_magico *encontrar_poder(Poder_magico &lista_poderes, int identificador)
{
    Poder_magico *encontrar = &lista_poderes;
    while (encontrar != nullptr)
    {
        if (encontrar->identificador == identificador)
        {
            return encontrar;
        }
        encontrar = encontrar->siguiente;
    }
    return encontrar = nullptr;
}

// para modificar los poderes.
void modificar_poder(Poder_magico &lista_poderes)
{
    if (cantidad_poderes == 0)
    {
        cout << "No hay poder magicos disponibles para modificar.\n";
        cout <<"pulse enter para continuar:"<<endl;
        getline(cin, p);
        return;
    }
    int identificador = 0;
    Poder_magico *actualizar = nullptr;
    cout << "Los poderes disponibles son: \n";
    mostrar_poderes(lista_poderes);

    identificador = obtener_entero("Coloque el ID del poder magico que desea modificar: ");
    // para valiadar que el poder existe.
    actualizar = encontrar_poder(lista_poderes, identificador);
    if (actualizar == nullptr)
    {
        cout << "El ID que coloco no existe. \n";
        cout << "Modificacion fallida \n";
        cout <<"pulse enter para continuar:"<<endl;
        getline(cin, p);
        return;
    }
    cout << "Proceda a actualizar el poder: " << actualizar->nombre_poder << endl;
    actualizar->nombre_poder = devolver_string_verificada("Nuevo Nombre: ");
    // lo coloco sin validar porque imagino que podra colocar numero y eso en la funcion del poder.
    cout << "Nueva Funcion: ";
    getline(cin, actualizar->funcion);

    cout << "Poder magico: " << actualizar->nombre_poder << " ha sido actualizado correctamente.\n";
    cout <<"pulse enter para continuar:"<<endl;
    getline(cin, p);
}

// para eliminar un poder.
void eliminar_poder(Poder_magico &lista_poder)
{
    if (cantidad_poderes == 0)
    {
        cout << "No hay poderes magicos disponibles para eliminar. \n";
        cout << "Eliminacion fallida. \n";
        cout <<"pulse enter para continuar:"<<endl;
        getline(cin, p);
        return;
    }
    int identificador = 0;
    Poder_magico *validar = nullptr;
    cout << "Los poderes magicos disponibles son: \n";
    mostrar_poderes(lista_poder);
    identificador = obtener_entero("Ingrese el ID del personaje a modificar: ");
    // para validar que e id exista.
    validar = encontrar_poder(lista_poder, identificador);
    // Si no existe:
    if (validar == nullptr)
    {
        cout << "El ID que coloco no existe.\n";
        cout << "Eliminacion fallida.\n";
        cout <<"pulse enter para continuar:"<<endl;
        getline(cin, p);
        return;
    }
    // comienza el procedimiento para borrar el poder.
    Poder_magico *actual = lista_poder.siguiente;
    Poder_magico *anterior = nullptr;
    // en caso de que sea el primero de la lista.
    if (actual->identificador == identificador)
    {
        lista_poder.siguiente = actual->siguiente;
        cout << "el poder magico: " << actual->nombre_poder << " se elimino correctamente.\n ";
        cout <<"pulse enter para continuar:"<<endl;
        getline(cin, p);
        delete actual;
        cantidad_poderes -= 1;
        regulador_poderes += 1;
        return;
    }
    // en caso de que no sea el primero.
    while ((actual != nullptr) && (actual->identificador != identificador))
    {
        anterior = actual;
        actual = actual->siguiente;
    }
    // ahora eliminamos.
    Poder_magico *eliminar = actual;
    anterior->siguiente = actual->siguiente;
    cout << "El poder magico: " << eliminar->nombre_poder << " se elimino correctamente.\n";
    cout <<"pulse enter para continuar:"<<endl;
    getline(cin, p);
    delete eliminar;
    cantidad_poderes -= 1;
    regulador_poderes += 1;
}

// Poderes del Juego:
// Vigor Enano esta en el main

//REVISARRRRR.
// nose para que es esto.
void Poder1(Implemento *lista_implementos)
{
    if (lista_implementos == nullptr)
    {
        cout << "No hay implementos para aplicarles el poder" << endl;
        return;
    }
    Implemento *actual = lista_implementos;
    int modificados = 0;

    while (actual != nullptr)
    {
        actual->valor *= 2;
        actual->fortalezanecesaria = 0;
        modificados++;
        actual = actual->siguiente;
    }

    cout << "Se han modificado " << modificados << " implementos exitosamente." << endl;
    cout << "Todos los implementos ahora tienen el doble de valor y no requieren fortaleza.\n";
}
