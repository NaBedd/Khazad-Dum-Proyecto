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

string p = " "; // para que se pare el programa.

// para crear poderes.
void crear_poder(Poder_magico &lista_poderes)
{
    printf("\033[0;33m"); // Amarillo
    cout << "Ten en cuenta que tu no tienes la magia suficiente para crear poderes." << endl;
    cout << "Solo los tres guerreros ancestrales de las cavernas tienen la magia suficiente actualmente." << endl;
    cout << "Aqui estaras creando una especie de prototipo que tiene que ser aprobado por ellos en la corte real." << endl;
    printf("\033[0;37m"); // Gris claro
    cout << "pulse enter para continuar:" << endl;
    getline(cin, p);
    cout << "Proceda a llenar las especificaciones del nuevo poder. \n";
    printf("\033[0;36m"); // Cyan para atributos
    Poder_magico *nuevo = new Poder_magico;
    printf("\033[0;36m");
    cout << "Nombre: ";
    printf("\033[0;37m");
    nuevo->nombre_poder = devolver_string_verificada("");
    printf("\033[0;36m");
    cout << "Funcion: ";
    printf("\033[0;37m");
    getline(cin, nuevo->funcion);
    cin.ignore();
    cantidad_poderes += 1;
    nuevo->identificador = cantidad_poderes + regulador_poderes;
    // lo agregamos a la lista enlazada.
    nuevo->siguiente = lista_poderes.siguiente;
    lista_poderes.siguiente = nuevo;
    printf("\033[0;32m"); // Verde
    cout << "El poder: " << nuevo->nombre_poder << " se creo correctamente.\n";
    printf("\033[0;37m");
    cout << "pulse enter para continuar:" << endl;
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
    printf("\033[0;33m"); // Amarillo
    cout << "La cantidad de poderes actualmente sin magia suficiente es: " << cantidad_poderes << endl
         << endl;
    printf("\033[0;37m"); // Gris claro

    Poder_magico *actual = lista_poderes.siguiente;
    while (actual != nullptr)
    {
        printf("\033[0;36m"); // Cyan para atributos
        cout << "Nombre: ";
        printf("\033[0;37m");
        cout << actual->nombre_poder << endl;

        printf("\033[0;36m");
        cout << "ID: ";
        printf("\033[0;37m");
        cout << actual->identificador << endl;

        printf("\033[0;36m");
        cout << "Funcion: ";
        printf("\033[0;37m");
        cout << actual->funcion << endl
             << endl;

        actual = actual->siguiente;
    }
    printf("\033[0;33m"); // Amarillo
    cout << "Los poderes con magia suficiente para ser usados son: " << endl;
    // Cada poder con color diferente para resaltar
    printf("\033[0;35m"); // Magenta
    cout << "1. Hechizo mortal: ";
    printf("\033[0;37m"); // Gris claro
    cout << "hace que todos los orcos de una sala tengan 1 de salud." << endl;

    printf("\033[0;36m"); // Cyan
    cout << "2. Enanos al poder: ";
    printf("\033[0;37m");
    cout << "recupera la vida de todos los enanos y le suma 1000 a su fortaleza." << endl;

    printf("\033[0;33m"); // Amarillo
    cout << "3. Maldad Fuera: ";
    printf("\033[0;37m");
    cout << "traslada a todos los orcos de una sala a otra." << endl;

    printf("\033[0;34m"); // Azul
    cout << "4. Implemento supremo: ";
    printf("\033[0;37m");
    cout << "potencia un implemento de un personaje y la fortaleza se vuelve 0." << endl;
    printf("\033[0;37m");
    cout << "No hay mas poderes disponibles.\n";
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
    return nullptr;
}

// para modificar los poderes.
void modificar_poder(Poder_magico &lista_poderes)
{
    if (cantidad_poderes == 0)
    {
        printf("\033[0;31m"); // Rojo
        cout << "No hay poderes magicos disponibles para modificar.\n";
        printf("\033[0;37m");
        return;
    }
    int identificador = 0;
    Poder_magico *actualizar = nullptr;
    printf("\033[0;33m"); // Amarillo
    cout << "Los poderes disponibles son: \n";
    printf("\033[0;37m");
    mostrar_poderes(lista_poderes);

    identificador = obtener_entero("Coloque el ID del poder magico que desea modificar: ");
    // para valiadar que el poder existe.
    actualizar = encontrar_poder(lista_poderes, identificador);
    if (actualizar == nullptr)
    {
        printf("\033[0;31m"); // Rojo
        cout << "El ID que coloco no existe. \n";
        cout << "Modificacion fallida \n";
        printf("\033[0;37m");
        return;
    }
    printf("\033[0;33m"); // Amarillo
    cout << "Proceda a actualizar el poder: ";
    printf("\033[0;35m"); // Magenta
    cout << actualizar->nombre_poder << endl;
    printf("\033[0;36m"); // Cyan para atributos
    cout << "Nuevo Nombre: ";
    printf("\033[0;37m");
    actualizar->nombre_poder = devolver_string_verificada("");
    printf("\033[0;36m");
    cout << "Nueva Funcion: ";
    printf("\033[0;37m");
    getline(cin, actualizar->funcion);
    printf("\033[0;32m"); // Verde
    cout << "Poder magico: " << actualizar->nombre_poder << " ha sido actualizado correctamente.\n";
    printf("\033[0;37m");
}

// para eliminar un poder.
void eliminar_poder(Poder_magico &lista_poder)
{
    if (cantidad_poderes == 0)
    {
        printf("\033[0;31m"); // Rojo
        cout << "No hay poderes magicos disponibles para eliminar. \n";
        cout << "Eliminacion fallida. \n";
        printf("\033[0;37m");
        return;
    }
    int identificador = 0;
    Poder_magico *validar = nullptr;
    printf("\033[0;33m"); // Amarillo
    cout << "Los poderes magicos disponibles son: \n";
    printf("\033[0;37m");
    mostrar_poderes(lista_poder);
    printf("\033[0;33m"); // Amarillo
    cout << "IMPORTANTE. No tines la magia suficiente." << endl;
    cout << "No puedes borrar un poder creado por los tres guerreros ancestrales de las cavernas." << endl;
    printf("\033[0;37m"); // Gris claro
    identificador = obtener_entero("Ingrese el ID del poder a borrar: ");
    // para validar que el id exista.
    validar = encontrar_poder(lista_poder, identificador);
    // Si no existe:
    if (validar == nullptr)
    {
        printf("\033[0;31m"); // Rojo
        cout << "El ID que coloco no existe.\n";
        cout << "Eliminacion fallida.\n";
        printf("\033[0;37m");
        return;
    }
    // comienza el procedimiento para borrar el poder.
    Poder_magico *actual = lista_poder.siguiente;
    Poder_magico *anterior = nullptr;
    // en caso de que sea el primero de la lista.
    if (actual->identificador == identificador)
    {
        lista_poder.siguiente = actual->siguiente;
        printf("\033[0;32m"); // Verde
        cout << "El poder magico: " << actual->nombre_poder << " se elimino correctamente.\n ";
        printf("\033[0;37m");
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
    printf("\033[0;32m"); // Verde
    cout << "El poder magico: " << eliminar->nombre_poder << " se elimino correctamente.\n";
    printf("\033[0;37m");
    cout << "pulse enter para continuar:" << endl;
    getline(cin, p);
    delete eliminar;
    cantidad_poderes -= 1;
    regulador_poderes += 1;
}

// Ejemplo de poder especial sobre implementos
void Poder1(Implemento *lista_implementos)
{
    if (lista_implementos == nullptr)
    {
        printf("\033[0;31m"); // Rojo
        cout << "No hay implementos para aplicarles el poder" << endl;
        printf("\033[0;37m");
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

    printf("\033[0;32m"); // Verde
    cout << "Se han modificado " << modificados << " implementos exitosamente." << endl;
    cout << "Todos los implementos ahora tienen el doble de valor y no requieren fortaleza.\n";
    printf("\033[0;37m");
}
