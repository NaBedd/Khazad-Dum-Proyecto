#pragma once                        // Soluciona errores de redefinicion
#include "01.funciones_genericas.h" // Funciones generales para el programa

#include <iostream>
#include <string>
using namespace std;

// Implementos
struct Implemento
{
    string nombre_implemento;
    string tipo_implemento;
    int usos;
    int fortalezanecesaria;
    int valor;
    int identificador;
    Implemento *siguiente = nullptr;
};

// Reguladores para implementos
int cantidad_implementos = 0;
int regulador_implemento = 13; // por el archivo.

string pausa2 = " "; // para que se pare el programa.

//----------------------------------- FUNCIONES IMPLEMENTOS --------------------------------------------

// para obtener el tipo de implemento.
string tipo_implemento(Implemento *Implemento)
{
    string tipo;
    int opcion = 0;
    int infinito = 0; // o lo pone bien o lo pone bien;
    do
    {
        printf("\033[0;33m"); // Amarillo
        cout << "\nLos tipos de implementos son: \n";
        cout << "1. Ataque\n";
        cout << "2. Proteccion\n";
        cout << "3. Cura\n";
        printf("\033[0;37m"); // Gris claro
        cout << "Indique que tipo de implemento sera " << Implemento->nombre_implemento << ": ";
        opcion = obtener_entero("");
        if (opcion == 1)
        {
            return tipo = "Ataque";
        }
        else if (opcion == 2)
        {
            return tipo = "Proteccion";
        }
        else if (opcion == 3)
        {
            return tipo = "Cura";
        }
        else
        {
            printf("\033[0;31m"); // Rojo
            cout << "Opcion invalida, el numero " << opcion << " no esta disponible.\n";
            printf("\033[0;37m"); // Gris claro
        }

    } while (infinito != 1);
    cout << "ESTA LINEA NO SE DEBERIA DE EJECUTAR" << endl;
    return tipo;
} // lo marca porque el bucle es infinito.

// para crear implementos.
void crear_implemento(Implemento &lista_implemento)
{
    Implemento *nuevo = new Implemento;
    printf("\033[0;33m"); // Amarillo
    cout << "Ingrese los datos del nuevo implemento.\n\n";
    printf("\033[0;37m"); // Gris claro
    nuevo->nombre_implemento = devolver_string_verificada("Nombre: ");
    nuevo->tipo_implemento = tipo_implemento(nuevo);
    nuevo->usos = obtener_entero("Usos: ");
    nuevo->fortalezanecesaria = obtener_entero("Fortaleza necesaria para usar el implemento: ");
    nuevo->valor = obtener_entero("Valor: ");
    // lo agregamos a la lista enlazada.
    nuevo->siguiente = lista_implemento.siguiente;
    lista_implemento.siguiente = nuevo;
    cantidad_implementos += 1;
    nuevo->identificador = cantidad_implementos + regulador_implemento;
    printf("\033[0;32m"); // Verde
    cout << "El implemento: " << nuevo->nombre_implemento << " se creo correctamente.\n";
    printf("\033[0;37m"); // Gris claro
}

void mostrar_implementos(Implemento &lista_implemento)
{
    if (cantidad_implementos == 0)
    {
        printf("\033[0;31m");
        cout << "No hay implementos disponibles en este momento.\n";
        printf("\033[0;37m");
        return;
    }
    else
    {
        printf("\033[0;33m");
        cout << "La cantidad de implementos es: [" << cantidad_implementos << "].\n";
        printf("\033[0;37m");
    }

    stack<Implemento *> pila_ataque;
    stack<Implemento *> pila_proteccion;
    stack<Implemento *> pila_cura;
    stack<Implemento *> pila_miscelaneos;
    Implemento *actual = lista_implemento.siguiente;

    /*
    Ataque
    Proteccion
    Cura*/
    while (actual != nullptr) // Divide los implementos en distintas pilas
    {
        if (actual->tipo_implemento == "Arma") // Ataque
        {
            pila_ataque.push(actual);
        }
        else if (actual->tipo_implemento == "Defensa") // Proteccion
        {
            pila_proteccion.push(actual);
        }
        else if (actual->tipo_implemento == "Consumible") // Cura
        {
            pila_cura.push(actual);
        }
        else // Distinto a lo anterior
        {
            pila_miscelaneos.push(actual);
        }

        actual = actual->siguiente;
    };

    cout << "--- ARMAS ---" << endl;
    while (!pila_ataque.empty()) // Ataque
    {
        actual = pila_ataque.top();
        pila_ataque.pop();

        printf("\033[0;36m");
        cout << "Nombre: ";
        printf("\033[0;37m");
        cout << actual->nombre_implemento << endl;

        printf("\033[0;36m");
        cout << "ID: ";
        printf("\033[0;37m");
        cout << actual->identificador << endl;

        printf("\033[0;36m");
        cout << "Tipo: ";
        printf("\033[0;37m");
        cout << actual->tipo_implemento << endl;

        printf("\033[0;36m");
        cout << "Usos: ";
        printf("\033[0;37m");
        cout << actual->usos << endl;

        printf("\033[0;36m");
        cout << "Fortaleza necesaria para usarlo: ";
        printf("\033[0;37m");
        cout << actual->fortalezanecesaria << endl;

        printf("\033[0;36m");
        cout << "Valor: ";
        printf("\033[0;37m");
        cout << actual->valor << endl
             << endl;
    }

    cout << "--- DEFENSA ---" << endl;
    while (!pila_proteccion.empty()) // Proteccion
    {
        actual = pila_proteccion.top();
        pila_proteccion.pop();

        printf("\033[0;36m");
        cout << "Nombre: ";
        printf("\033[0;37m");
        cout << actual->nombre_implemento << endl;

        printf("\033[0;36m");
        cout << "ID: ";
        printf("\033[0;37m");
        cout << actual->identificador << endl;

        printf("\033[0;36m");
        cout << "Tipo: ";
        printf("\033[0;37m");
        cout << actual->tipo_implemento << endl;

        printf("\033[0;36m");
        cout << "Usos: ";
        printf("\033[0;37m");
        cout << actual->usos << endl;

        printf("\033[0;36m");
        cout << "Fortaleza necesaria para usarlo: ";
        printf("\033[0;37m");
        cout << actual->fortalezanecesaria << endl;

        printf("\033[0;36m");
        cout << "Valor: ";
        printf("\033[0;37m");
        cout << actual->valor << endl
             << endl;
    }

    cout << "--- CONSUMIBLES ---" << endl;
    while (!pila_cura.empty()) // Curas
    {
        actual = pila_cura.top();
        pila_cura.pop();

        printf("\033[0;36m");
        cout << "Nombre: ";
        printf("\033[0;37m");
        cout << actual->nombre_implemento << endl;

        printf("\033[0;36m");
        cout << "ID: ";
        printf("\033[0;37m");
        cout << actual->identificador << endl;

        printf("\033[0;36m");
        cout << "Tipo: ";
        printf("\033[0;37m");
        cout << actual->tipo_implemento << endl;

        printf("\033[0;36m");
        cout << "Usos: ";
        printf("\033[0;37m");
        cout << actual->usos << endl;

        printf("\033[0;36m");
        cout << "Fortaleza necesaria para usarlo: ";
        printf("\033[0;37m");
        cout << actual->fortalezanecesaria << endl;

        printf("\033[0;36m");
        cout << "Valor: ";
        printf("\033[0;37m");
        cout << actual->valor << endl
             << endl;
    }

    while (!pila_miscelaneos.empty()) // Miscelaneos. No deberia de haber ninguno
    {
        actual = pila_miscelaneos.top();
        pila_miscelaneos.pop();

        printf("\033[0;36m");
        cout << "Nombre: ";
        printf("\033[0;37m");
        cout << actual->nombre_implemento << endl;

        printf("\033[0;36m");
        cout << "ID: ";
        printf("\033[0;37m");
        cout << actual->identificador << endl;

        printf("\033[0;36m");
        cout << "Tipo: ";
        printf("\033[0;37m");
        cout << actual->tipo_implemento << endl;

        printf("\033[0;36m");
        cout << "Usos: ";
        printf("\033[0;37m");
        cout << actual->usos << endl;

        printf("\033[0;36m");
        cout << "Fortaleza necesaria para usarlo: ";
        printf("\033[0;37m");
        cout << actual->fortalezanecesaria << endl;

        printf("\033[0;36m");
        cout << "Valor: ";
        printf("\033[0;37m");
        cout << actual->valor << endl
             << endl;
    }

    cout << "No hay mas implementos disponibles\n";
}

// buscar implemento.
Implemento *buscar_implemento(Implemento &lista_implemento, int identificador)
{
    Implemento *encontrado = lista_implemento.siguiente;
    while (encontrado != nullptr)
    {
        if (encontrado->identificador == identificador)
        {
            return encontrado;
        }
        encontrado = encontrado->siguiente;
    }
    return nullptr;
}

// para modificar los implementos.
void modificar_implemento(Implemento &lista_implemento)
{
    if (cantidad_implementos == 0)
    {
        printf("\033[0;31m"); // Rojo
        cout << "No hay implementos disponibles para modificar.\n";
        cout << "Modificacion fallida.\n";
        printf("\033[0;37m"); // Gris claro
        return;
    }
    int identificador = 0;
    printf("\033[0;33m"); // Amarillo
    cout << "Los implementos disponibles son:\n";
    printf("\033[0;37m"); // Gris claro
    mostrar_implementos(lista_implemento);
    identificador = obtener_entero("Coloque el ID del implemento que desea modificar: ");
    Implemento *actualizar = buscar_implemento(lista_implemento, identificador);
    if (actualizar == nullptr)
    {
        printf("\033[0;31m"); // Rojo
        cout << "El ID que coloco no es valido.\n";
        cout << "No hay ningun implemento con ese ID.\n";
        cout << "Actualizacion fallida.\n";
        printf("\033[0;37m"); // Gris claro
        return;
    }

    cout << "Proseda a modificar el implemento: " << actualizar->nombre_implemento << endl;
    actualizar->nombre_implemento = devolver_string_verificada("Nombre: ");
    actualizar->tipo_implemento = tipo_implemento(actualizar);
    actualizar->usos = obtener_entero("Usos: ");
    actualizar->fortalezanecesaria = obtener_entero("Fortaleza necesaria para usarlo: ");
    actualizar->valor = obtener_entero("Valor: ");
    printf("\033[0;32m"); // Verde
    cout << "Implemento: " << actualizar->nombre_implemento << ", modificado correctamente.\n";
    printf("\033[0;37m"); // Gris claro
}

// para destruir la lista de implementos.
void destruir_implementos(Implemento &lista_implemento)
{
    Implemento *actual = lista_implemento.siguiente;
    Implemento *eliminar = nullptr;
    while (actual != nullptr)
    {
        eliminar = actual;
        actual = actual->siguiente;
        delete eliminar;
    }
    cantidad_implementos = 0;
    regulador_implemento = 0;
}

// para borrar implementos.
void borrar_implementos(Implemento &lista_implemento)
{
    if (cantidad_implementos == 0)
    {
        printf("\033[0;31m"); // Rojo
        cout << "No hay implementos para eliminar.\n";
        cout << "Eliminacion fallida.\n";
        printf("\033[0;37m"); // Gris claro
        return;
    }
    printf("\033[0;33m"); // Amarillo
    cout << "Los implementos disponibles son:\n";
    printf("\033[0;37m"); // Gris claro
    mostrar_implementos(lista_implemento);
    int identificador = obtener_entero("Coloque el ID del implemento que desea eliminar: ");
    Implemento *encontrado = buscar_implemento(lista_implemento, identificador);
    if (encontrado == nullptr)
    {
        printf("\033[0;31m"); // Rojo
        cout << "No existe un implemento con el ID: " << identificador << endl;
        cout << "Eliminacion fallida.\n";
        printf("\033[0;37m"); // Gris claro
        return;
    }

    Implemento *actual = lista_implemento.siguiente;

    // si es el primero en la lista.
    if (actual->identificador == identificador)
    {
        lista_implemento.siguiente = actual->siguiente;
        printf("\033[0;32m"); // Verde
        cout << "El implemento: " << actual->nombre_implemento << " se elimino correctamente.\n";
        printf("\033[0;37m"); // Gris claro
        delete actual;
        cantidad_implementos -= 1;
        regulador_implemento += 1;
        return;
    }

    // si no es el primero.
    Implemento *anterior = nullptr;
    while ((actual != nullptr) && (actual->identificador != identificador))
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    Implemento *eliminar = actual;
    anterior->siguiente = actual->siguiente;
    printf("\033[0;32m"); // Verde
    cout << "El elemento: " << eliminar->nombre_implemento << " se elimino correctamente.\n";
    printf("\033[0;37m"); // Gris claro
    delete eliminar;
    cantidad_implementos -= 1;
    regulador_implemento += 1;
}
