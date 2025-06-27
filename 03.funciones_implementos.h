#pragma once                        // Soluciona errores de redefinicion
#include "01.funciones_genericas.h" // Funciones generales para el programa

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

//----------------------------------- FUNCIONES IMPLEMENTOS --------------------------------------------

// para obtener el tipo de implemento.
string tipo_implemento(Implemento *Implemento)
{
    string tipo;
    int opcion = 0;
    int infinito = 0; // o lo pone bien o lo pone bien;
    do
    {
        cout << "\nLos tipos de implementos son: \n";
        cout << "1. Ataque\n";
        cout << "2. Proteccion.\n";
        cout << "3. Cura.\n";
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
            cout << "Opcion invalida, el numero " << opcion << " no esta disponible.\n";
        }

    } while (infinito != 1);
    cout << "ESTA LINEA NO SE DEBERIA DE EJECUTAR" << endl;
    return tipo;
} // lo marca porque el bucle es infinito.

// para crear implementos.
void crear_implemento(Implemento &lista_implemento)
{
    Implemento *nuevo = new Implemento;
    cout << "Proceda a llenar las espicificaciones del imlemento. \n\n";
    nuevo->nombre_implemento = devolver_string_verificada("Nobre:");
    nuevo->tipo_implemento = tipo_implemento(nuevo); // funcion para obteren el tipo de implemento.
    nuevo->usos = obtener_entero("Usos: ");
    nuevo->fortalezanecesaria = obtener_entero("Fortaleza necesaria para usar el implemento: ");
    nuevo->valor = obtener_entero("valor: ");
    // lo agregamos a la lista enlazada.
    nuevo->siguiente = lista_implemento.siguiente;
    lista_implemento.siguiente = nuevo;
    cantidad_implementos += 1;
    nuevo->identificador = cantidad_implementos + regulador_implemento;
    cout << "El implemento: " << nuevo->nombre_implemento << "se creo correctamente.";
}

void mostrar_implementos(Implemento &lista_implemento)
{
    if (cantidad_implementos == 0)
    {
        cout << "No hay implementos disponibles en este momento. \n";
        return;
    }
    else
    {
        cout << "la candtad de implementos es: [" << cantidad_implementos << "]. \n";
    }

    Implemento *actual = lista_implemento.siguiente;
    while (actual != nullptr)
    {
        cout << "Nombre: " << actual->nombre_implemento << endl;
        cout << "ID: " << actual->identificador << endl;
        cout << "Tipo: " << actual->tipo_implemento << endl;
        cout << "Uso: " << actual->usos << endl;
        cout << "Fortaleza necesaria para usarlo: " << actual->fortalezanecesaria << endl;
        cout << "Valor: " << actual->valor << endl
             << endl;
        actual = actual->siguiente;
    }
    cout << "no hay mas implementos disponibles\n";
}

// buscar implemento.
Implemento *buscar_implemento(Implemento &lista_implemento, int identificador)
{
    Implemento *encontrado = &lista_implemento;
    while (encontrado != nullptr)
    {
        if (encontrado->identificador == identificador)
        {
            return encontrado;
        }
        encontrado = encontrado->siguiente;
    }
    return encontrado = nullptr;
}

// para modificar los implementos.
void modificar_implemento(Implemento &lista_implemento)
{
    if (cantidad_implementos == 0)
    {
        cout << "No hay implementos disponibles para modificar \n";
        cout << "modificacion fallida.\n";
        return;
    }
    int identificador = 0;
    cout << "los impplementos disponibles son: \n";
    mostrar_implementos(lista_implemento);
    identificador = obtener_entero("Coloque el ID del implemento que desea modificar: ");
    Implemento *actualizar = buscar_implemento(lista_implemento, identificador);
    if (actualizar == nullptr)
    {
        cout << "El ID que coloco no es valido.\n";
        cout << "No hay ningun implemento con ese ID.\n";
        cout << "Actualizacion fallida.\n";
        return;
    }

    //                          VERRRRRRRRRRRRRRRRRRRR
    // coloco este mensaje porque no se porque el progra no corre normal.
    cout << "precione enter para modificar el implemto: " << actualizar->nombre_implemento;
    // hay que darle enter para que corra.

    cin.ignore();
    actualizar->nombre_implemento = devolver_string_verificada("Nombre: ");
    actualizar->tipo_implemento = tipo_implemento(actualizar);
    actualizar->usos = obtener_entero("Usos: ");
    actualizar->fortalezanecesaria = obtener_entero("Fortaleza necesaria para usarlo:");
    actualizar->valor = obtener_entero("Valor: ");
    cout << "Implemento: " << actualizar->nombre_implemento << ", modificado correctamente.\n ";
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
        cout << "No hay implementos para eliminar: \n";
        cout << "Eliminacion fallida. \n";
        return;
    }
    cout << "Los implementos disponibles son: \n";
    mostrar_implementos(lista_implemento);
    int identificador = obtener_entero("coloque el ID del implemento que desea eliminar:");
    Implemento *encontrado = buscar_implemento(lista_implemento, identificador);
    if (encontrado == nullptr)
    {
        cout << "  No existe un implemento con el ID: " << identificador;
        cout << "\nEliminacion fallida. \n";
        return;
    }

    // comiza la eliminacion del implemento.
    Implemento *actual = lista_implemento.siguiente;

    // si es el primero en la lista.
    if (actual->identificador == identificador)
    {
        lista_implemento.siguiente = actual->siguiente;
        cout << "El implemento: " << actual->nombre_implemento << "se elimino correctamente.\n";
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

    // ahora eliminamos.
    Implemento *eliminar = actual;
    anterior->siguiente = actual->siguiente;
    cout << "El elemento: " << eliminar->nombre_implemento << "se elimino correctamente. ";
    delete eliminar;
}
