#pragma once // Soluciona errores de redefinicion
#include "02.funciones_tipos_especie.h"
#include "05.funciones_poder_magico.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Declaracion adelantada para evitar errores de compilacion
struct Poder_magico;

// Mochila
struct mochila
{
    int identificador; // sera el mismo del personaje al que pertenezca.
    Implemento *implementos = nullptr;
    Poder_magico *poderes = nullptr; // no se usara en esta entrega
    string num_poder = " ";
};

// Personajes
struct personaje
{
    mochila *mimochila = nullptr;
    string nombre;
    Especie *tipo;
    int identificador;
    personaje *siguiente = nullptr;
};

//----------------------------------- PARA LOS PERSONAJES ---------------------------------------------

int regulador_personaje_orco = 7; // por el archivo
int cantidad_personaje_orco = 0;

int regulador_personaje_heroe = 7; // por el archivo
int cantidad_personaje_heroe = 0;

int cantidad_personajes_jugar = 0;
int regulador_personajes_jugar = 0;

string pausa = " "; // para que se pare el programa.

// Para crear personajes.
void crear_personaje(personaje &lista_personaje, Lista_especie &lista_tipos, int tipo)
{
    if (lista_tipos.cantidad == 0)
    {
        printf("\033[0;31m"); // Rojo
        cout << "Todavia no hay especies disponibles. Debe crearlas antes de crear un personaje." << endl;
        printf("\033[0;37m"); // Gris claro
        return;
    }
    personaje *nuevo = new personaje;
    int num_tipo = 0;
    Especie *puntero_especie = nullptr;

    if (tipo == 1)
    {
        printf("\033[0;33m"); // Amarillo
        cout << "Indique los datos para el nuevo personaje Orco." << endl;
        printf("\033[0;37m"); // Gris claro

        nuevo->nombre = devolver_string_verificada("Nombre: ");

        cout << "Ingrese la especie a la que pertenecera el Orco " << nuevo->nombre << "\n";
        cout << "Especies disponibles: " << endl;
        mostrar_lista(lista_tipos, tipo);

        cout << "Ingrese la especie del Orco " << nuevo->nombre << ": ";
        num_tipo = obtener_entero("");

        puntero_especie = encontrar_especie_id(lista_tipos, num_tipo);
    }
    else
    {
        printf("\033[0;33m"); // Amarillo
        cout << "Indique los datos para el nuevo personaje Heroe." << endl;
        printf("\033[0;37m"); // Gris claro

        nuevo->nombre = devolver_string_verificada("Nombre: ");

        cout << "Ingrese la especie a la que pertenecera el Heroe " << nuevo->nombre << "\n";
        cout << "Especies disponibles: " << endl;
        mostrar_lista(lista_tipos, tipo);

        cout << "Ingrese la especie del Personaje " << nuevo->nombre << ": ";
        num_tipo = obtener_entero("");

        puntero_especie = encontrar_especie_id(lista_tipos, num_tipo);
    }

    if (puntero_especie == nullptr)
    {
        printf("\033[0;31m"); // Rojo
        cout << "La especie debe crearse primero." << endl;
        cout << "Creacion del personaje: " << nuevo->nombre << " fue fallida." << endl;
        printf("\033[0;37m"); // Gris claro
        delete nuevo;
        return;
    }
    else
    {
        nuevo->tipo = puntero_especie;
    }

    nuevo->siguiente = lista_personaje.siguiente;
    lista_personaje.siguiente = nuevo;

    if (tipo == 1)
    {
        cantidad_personaje_orco++;
        nuevo->identificador = (cantidad_personaje_orco + regulador_personaje_orco);
        printf("\033[0;32m"); // Verde
        cout << "El orco: " << nuevo->nombre << ", se agrego correctamente." << endl;
    }
    else
    {
        cantidad_personaje_heroe++;
        nuevo->identificador = (cantidad_personaje_heroe + regulador_personaje_heroe);
        printf("\033[0;32m"); // Verde
        cout << "El heroe: " << nuevo->nombre << ", se agrego correctamente." << endl;
    }
    printf("\033[0;37m"); // Gris claro
}

// Funcion para mostrar los personajes
void mostrar_personajes(personaje &lista, int tipo)
{
    if (tipo == 1 && cantidad_personaje_orco == 0)
    {
        printf("\033[0;31m"); // Rojo
        cout << "\nNo hay especies de orcos para mostrar actualmente.\n";
        cout << "Primero debe crearlos.\n";
        printf("\033[0;37m"); // Gris claro
        return;
    }
    if (tipo == 2 && cantidad_personaje_heroe == 0)
    {
        printf("\033[0;31m"); // Rojo
        cout << "\nNo hay personajes heroes para mostrar actualmente.\n";
        cout << "Primero debe crearlos.\n";
        printf("\033[0;37m"); // Gris claro
        return;
    }

    if (tipo == 1)
    {
        printf("\033[0;33m"); // Amarillo
        cout << "\nHay [" << cantidad_personaje_orco << "] personajes orcos" << endl;
    }
    else
    {
        printf("\033[0;33m"); // Amarillo
        cout << "\nHay [" << cantidad_personaje_heroe << "] personajes heroes" << endl;
    }
    printf("\033[0;37m"); // Gris claro

    personaje *actual = lista.siguiente;
    while (actual != nullptr)
    {
        cout << actual->identificador << " - ";
        printf("\033[0;35m"); // Magenta para el nombre
        cout << "Nombre: " << actual->nombre << endl;
        printf("\033[0;36m"); // Cyan para la especie
        cout << "Especie: " << actual->tipo->nombre_especie << endl;
        printf("\033[0;37m"); // Gris claro (resetear a color normal después)
        cout << endl;
        actual = actual->siguiente;
    }
    cout << "No hay mas personajes.\n";
    cout << endl
         << endl;
}

// Encontrar un personaje
personaje *encontrar_personaje(personaje &lista_personajes, int identificador)
{
    personaje *actual = lista_personajes.siguiente;
    while (actual != nullptr)
    {
        if (actual->identificador == identificador)
        {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

// para saber cuantos personajes hay de una especie
int cantidad_personajes_por_especie(personaje &lista_personajes, Especie *mostrar)
{
    personaje *actual = lista_personajes.siguiente;
    int contador = 0;
    while (actual != nullptr)
    {
        if (actual->tipo->identificador == mostrar->identificador)
        {
            contador++;
        }
        actual = actual->siguiente;
    }
    return contador;
}

// funcion para modificar a los personajes.
void actualizar_personaje(personaje &lista, Lista_especie lista_tipo, int tipo)
{
    if (tipo == 1 && cantidad_personaje_orco == 0)
    {
        printf("\033[0;31m"); // Rojo
        cout << "\nNo hay personajes orcos para mostrar actualmente.\n";
        cout << "Primero debe crearlos.\n";
        printf("\033[0;37m"); // Gris claro
        return;
    }
    if (tipo == 2 && cantidad_personaje_heroe == 0)
    {
        printf("\033[0;31m"); // Rojo
        cout << "\nNo hay personajes heroes para mostrar actualmente.\n";
        cout << "Primero debe crearlos.\n";
        printf("\033[0;37m"); // Gris claro
        return;
    }

    int identificador_tipo = 0;
    int referencia;
    Especie *especie_nueva = nullptr;

    cout << "Los personajes disponibles son: \n";
    mostrar_personajes(lista, tipo);

    referencia = obtener_entero("Ingrese el numero del personaje que desea modificar: ");

    personaje *actual = lista.siguiente;
    bool encontrado = false;

    while (actual != nullptr)
    {
        if (actual->identificador == referencia)
        {
            encontrado = true;
            cout << "Ingrese los datos para actualizar al personaje " << actual->nombre << endl;
            cin.ignore();

            actual->nombre = devolver_string_verificada("Nombre del personaje: ");

            cout << "\nColoque el nuevo tipo de especie al que pertenecera el personaje\n";
            cout << "\nTipos disponibles son: " << endl;
            cout << "------------------------" << endl;
            mostrar_lista(lista_tipo, tipo);

            identificador_tipo = obtener_entero("Coloque el numero del tipo del personaje: ");

            especie_nueva = encontrar_especie_id(lista_tipo, identificador_tipo);

            if (especie_nueva == nullptr)
            {
                printf("\033[0;31m"); // Rojo
                cout << "La especie que coloco no se encuentra disponible." << endl;
                cout << "La actualizacion del personaje: " << actual->nombre << " fue fallida." << endl;
                printf("\033[0;37m"); // Gris claro
                return;
            }
            else
            {
                printf("\033[0;32m"); // Verde
                cout << "El personaje ahora de nombre: " << actual->nombre << " se actualizo correctamente." << endl;
                printf("\033[0;37m"); // Gris claro
            }
        }
        actual = actual->siguiente;
    }
    if (!encontrado)
    {
        printf("\033[0;31m"); // Rojo
        cout << "No se encontro ningun personaje con el ID: " << referencia << "." << endl;
        cout << "Actualizacion fallida." << endl;
        printf("\033[0;37m"); // Gris claro
    }
}

// Para borrar un personaje.
void borrar_personaje(personaje &lista, int tipo)
{
    if (tipo == 1 && cantidad_personaje_orco == 0)
    {
        printf("\033[0;31m"); // Rojo
        cout << "\nNo hay personajes orcos para eliminar actualmente.\n";
        cout << "Primero debe crearlos.\n";
        printf("\033[0;37m"); // Gris claro
        return;
    }
    if (tipo == 2 && cantidad_personaje_heroe == 0)
    {
        printf("\033[0;31m"); // Rojo
        cout << "\nNo hay personajes heroes para eliminar actualmente.\n";
        cout << "Primero debe crearlos.\n";
        printf("\033[0;37m"); // Gris claro
        return;
    }

    int identificador = 0;
    personaje *actual = lista.siguiente;
    personaje *anterior = nullptr;

    cout << "Los personajes disponibles son: \n";
    mostrar_personajes(lista, tipo);
    identificador = obtener_entero("Coloque el numero del personaje a modificar: ");

    if ((actual != nullptr) && (actual->identificador == identificador))
    {
        lista.siguiente = actual->siguiente;
        printf("\033[0;32m"); // Verde
        cout << "El personaje: " << actual->nombre << " fue borrado exitosamente." << endl;
        printf("\033[0;37m"); // Gris claro
        delete actual;
        if (tipo == 1)
        {
            regulador_personaje_orco++;
            cantidad_personaje_orco--;
        }
        else
        {
            regulador_personaje_heroe++;
            cantidad_personaje_heroe--;
        }
        return;
    }

    while ((actual != nullptr) && (actual->identificador != identificador))
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual != nullptr)
    {
        personaje *eliminar = actual;
        anterior->siguiente = actual->siguiente;
        printf("\033[0;32m"); // Verde
        cout << "El personaje " << eliminar->nombre << " se elimino correctamente.\n";
        printf("\033[0;37m"); // Gris claro
        delete eliminar;

        if (tipo == 1)
        {
            regulador_personaje_orco++;
            cantidad_personaje_orco--;
        }
        else
        {
            regulador_personaje_heroe++;
            cantidad_personaje_heroe--;
        }
    }
    else
    {
        printf("\033[0;31m"); // Rojo
        cout << "El numero de personaje: " << identificador << " no se encuentra en la lista.\n";
        cout << "Eliminacion fallida.\n";
        printf("\033[0;37m"); // Gris claro
    }
}

// Funcion para destruir la lista de personajes.
void destruir_lista_personajes(personaje &lista)
{
    personaje *actual = lista.siguiente;
    while (actual != nullptr)
    {
        personaje *eliminar = actual;
        actual = actual->siguiente;
        delete eliminar;
    }
    lista.siguiente = nullptr;
}

// borra todos los personajes de un tipo (especie).
void borrar_personajes_de_tipo(personaje &lista_personajes, Especie *tipo_borrar, int tipo)
{
    personaje *actual = lista_personajes.siguiente;
    personaje *anterior = &lista_personajes;
    personaje *eliminar = nullptr;

    while (actual != nullptr)
    {
        if (actual->tipo != nullptr && actual->tipo->identificador == tipo_borrar->identificador)
        {
            eliminar = actual;
            anterior->siguiente = actual->siguiente;
            actual = actual->siguiente;

            printf("\033[0;32m"); // Verde
            cout << "El personaje: " << eliminar->nombre << " fue borrado." << endl;
            printf("\033[0;37m"); // Gris claro;
            delete eliminar;

            if (tipo == 1)
            {
                regulador_personaje_orco++;
                cantidad_personaje_orco--;
            }
            else
            {
                regulador_personaje_heroe++;
                cantidad_personaje_heroe--;
            }
        }
        else
        {
            anterior = actual;
            actual = actual->siguiente;
        }
    }
}

// para eliminar un elemento de la lista
void eliminar_elemento_lista(Lista_especie &lista, personaje lista_personajes, int tipo)
{
    if (lista.cantidad == 0)
    {
        printf("\033[0;31m"); // Rojo
        cout << "No hay elementos en la lista para borrar\n";
        printf("\033[0;37m"); // Gris claro
        return;
    }
    cout << "Las especies disponibles son: \n";
    mostrar_lista(lista, tipo);

    int identificador = obtener_entero("Ingrese el numero del tipo que desea borrar: ");

    if (identificador > 0)
    {
        int controlador_eliminar = 0;

        Especie *actual = lista.primero_especie;
        Especie *anterior = nullptr;

        Especie *especie_borrar = encontrar_especie_id(lista, identificador);
        int cantida_personajes = cantidad_personajes_por_especie(lista_personajes, especie_borrar);

        if (cantida_personajes > 0)
        {
            printf("\033[0;33m"); // Amarillo
            cout << " Hay: " << cantida_personajes << " personajes de esta especie, por lo tanto.\n";
            cout << "Al eliminar la especie se borraran los personajes del tipo.\n";
            cout << "Eliminar de todas formas coloque 1.\n";
            cout << "No eliminar coloque 2.\n";
            printf("\033[0;37m"); // Gris claro (reset color)
            do
            {
                cout << "(1) o (2)\n";
                controlador_eliminar = obtener_entero("Coloque el numero: ");
            } while ((controlador_eliminar != 1) && (controlador_eliminar != 2));
        }
        else
        {
            cout << "No hay personajes actualmente de este tipo, no hay problema al eliminarlo.\n";
        }

        if (controlador_eliminar == 1)
        {
            borrar_personajes_de_tipo(lista_personajes, especie_borrar, tipo);
        }
        else if (controlador_eliminar == 2)
        {
            cout << "Eliminacion del tipo " << especie_borrar->nombre_especie << " fallida.\n";
            return;
        }

        if ((actual != nullptr) && actual->identificador == identificador)
        {
            lista.primero_especie = actual->siguiente;
            printf("\033[0;32m"); // Verde
            cout << "El tipo " << actual->nombre_especie << " se elimino correctamente." << endl;
            printf("\033[0;37m"); // Gris claro
            delete actual;
            lista.cantidad -= 1;
            if (tipo == 1)
            {
                regulador_tipo_orco++;
            }
            else
            {
                regulador_tipo_heroe++;
            }
            return;
        }

        while ((actual != nullptr) && (actual->identificador != identificador))
        {
            anterior = actual;
            actual = actual->siguiente;
        }

        if (actual != nullptr)
        {
            Especie *eliminar = actual;
            anterior->siguiente = actual->siguiente;
            printf("\033[0;32m"); // Verde
            cout << "El tipo " << eliminar->nombre_especie << " se elimino correctamente." << endl;
            printf("\033[0;37m"); // Gris claro
            delete eliminar;
            lista.cantidad -= 1;
            if (tipo == 1)
            {
                regulador_tipo_orco++;
            }
            else
            {
                regulador_tipo_heroe++;
            }
        }
        else
        {
            printf("\033[0;31m"); // Rojo
            cout << "El numero de especie: " << identificador << " no se encuentra en la lista.\n";
            cout << "Eliminacion fallida.\n";
            printf("\033[0;37m"); // Gris claro
        }
    }
    else
    {
        printf("\033[0;31m"); // Rojo
        cout << "El numero de especie ingresado no es valido.\n";
        printf("\033[0;37m"); // Gris claro
    }
}

//----------------------------------- FUNCIONES PERSONAJES JUGAR --------------------------------------

void llenar_mochila(personaje *&personaje_a_llenar, Implemento &Implementos, personaje *lista_personajes_jugar)
{
    int opcio = 0;
    int con_poderes = 0;
    int cantidad_objetos = 0;
    int identificador = 0;
    int contrilador_interno = 0;

    printf("\033[0;33m"); // Amarillo
    cout << "Puede escoger un maximo 5 objetos, entre poderes magicos o implementos.\n";
    printf("\033[0;37m"); // Gris claro

    do
    {
        cout << "Tiene " << cantidad_objetos << " objetos en la mochila.\n";

        // Opciones principales con números en cian y texto en blanco
        printf("\033[0;36m"); // Cyan para números
        cout << "1.";
        printf("\033[0;37m"); // Gris claro para texto
        cout << " Implemento.\n";

        printf("\033[0;36m"); // Cyan
        cout << "2.";
        printf("\033[0;37m");
        cout << " Poderes Magicos.\n";

        printf("\033[0;36m"); // Cyan
        cout << "3.";
        printf("\033[0;37m");
        cout << " Salir.\n";

        opcio = obtener_entero("");

        if (opcio == 1) // Llenar implementos
        {
            limpiar_pantalla();
            Implemento *nuevo_implemento = nullptr;
            do
            {
                cout << "Los implementos disponibles son:\n";
                mostrar_implementos(Implementos);
                cout << "Coloque el ID del implemento que desea colocar: ";
                identificador = obtener_entero("");
                nuevo_implemento = buscar_implemento(Implementos, identificador);

                if (nuevo_implemento == nullptr)
                {
                    printf("\033[0;31m"); // Rojo
                    cout << "El ID: " << identificador << " no existe.\n";
                    cout << "Coloque uno valido.\n";
                    printf("\033[0;37m"); // Gris claro
                }
                else if (nuevo_implemento->fortalezanecesaria > personaje_a_llenar->tipo->danno_fortaleza)
                {
                    printf("\033[0;31m"); // Rojo
                    cout << "El implemento: " << nuevo_implemento->nombre_implemento << " no puede ser usado por el personaje: " << personaje_a_llenar->nombre << endl;
                    cout << "Su fortaleza no es la suficiente." << endl;
                    cout << "La fortaleza de " << personaje_a_llenar->nombre << " es: " << personaje_a_llenar->tipo->danno_fortaleza << endl;
                    cout << "Coloque uno valido.\n";
                    cout << "Pulse enter para continuar:" << endl;
                    getline(cin, pausa);
                    printf("\033[0;37m"); // Gris claro
                }
                else
                {
                    contrilador_interno = 1;
                }
            } while (contrilador_interno != 1);

            Implemento *colocar = new Implemento;
            *colocar = *nuevo_implemento;
            colocar->siguiente = personaje_a_llenar->mimochila->implementos;
            personaje_a_llenar->mimochila->implementos = colocar;
            cantidad_objetos++;
            contrilador_interno = 0;

            printf("\033[0;32m"); // Verde
            cout << "El implemento " << colocar->nombre_implemento << " se agrego correctamente a la mochila.\n";
            printf("\033[0;37m"); // Gris claro
        }
        else if (opcio == 2) // Llenar poderes
        {
            limpiar_pantalla();
            if (con_poderes == 1)
            {
                printf("\033[0;33m"); // Amarillo
                cout << "Ya seleccionaste un poder y solo puedes tener 1." << endl;
                cout << "Por lo tanto se reemplazara el poder actual que tienes implementado." << endl;
                printf("\033[0;37m"); // Gris claro
                cout << "Pulse enter para continuar:" << endl;
                getline(cin, pausa);
            }

            printf("\033[0;33m"); // Amarillo
            cout << "Aqui solo apareceran los poderes con magia suficiente para poder ser utilizados." << endl;
            cout << "Actualmente se encuentran 4." << endl;
            cout << "Los cuales fueron creados por los tres guerreros ancestrales de las cavernas." << endl
                 << endl;
            printf("\033[0;37m"); // Gris claro

            do
            {
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

                printf("\033[0;31m"); // Rojo
                cout << "5. No quiero ningun poder." << endl;
                printf("\033[0;37m");

                opcio = obtener_entero("Elija sabiamente: ");
                if (opcio == 1)
                {
                    personaje_a_llenar->mimochila->num_poder = "hechizo mortal";
                    cantidad_objetos++;
                    opcio = 0;
                    break;
                }
                else if (opcio == 2)
                {
                    personaje_a_llenar->mimochila->num_poder = "enanos al poder";
                    cantidad_objetos++;
                    opcio = 0;
                    break;
                }
                else if (opcio == 3)
                {
                    personaje_a_llenar->mimochila->num_poder = "Maldad Fuera";
                    cantidad_objetos++;
                    opcio = 0;
                    break;
                }
                else if (opcio == 4)
                {
                    personaje_a_llenar->mimochila->num_poder = "implemento supremo";
                    cantidad_objetos++;
                    opcio = 0;
                    break;
                }
                else if (opcio == 5)
                {
                    printf("\033[0;31m"); // Rojo
                    cout << "Esto es un mal presagio.." << endl;
                    cout << "Saliendo de la eleccion de poderes.." << endl;
                    printf("\033[0;37m"); // Gris claro
                }
                else
                {
                    printf("\033[0;31m"); // Rojo
                    cout << "Le faltas el respeto a los tres guerreros ancestrales" << endl;
                    cout << "Coloque el numero de uno de los 4 poderes disponibles." << endl;
                    cout << "O 5 si eres tan tonto como para no querer ningun poder ancestral." << endl;
                    printf("\033[0;37m"); // Gris claro
                }

            } while (opcio != 5);
        }
        else if (opcio == 3)
        {
            cout << "La cantidad de objetos que coloco fue: " << cantidad_objetos << endl;
        }
        else
        {
            printf("\033[0;31m"); // Rojo
            cout << "Opcion invalida, el numero " << opcio << " no es una opcion valida.\n";
            printf("\033[0;37m"); // Gris claro
        }
    } while ((opcio != 3) && (cantidad_objetos != 5));

    if (cantidad_objetos == 5)
    {
        printf("\033[0;33m"); // Amarillo
        cout << "Ya no puedes agregar mas objetos.\n";
        cout << "La mochila del personaje " << personaje_a_llenar->nombre << " se lleno correctamente.\n";
        cout << "pulse enter para continuar." << endl;
        getline(cin, pausa);
        printf("\033[0;37m"); // Gris claro
    }
}

// para elegir el personaje y llenar la mochila.
void eleccion_personaje(personaje *&lista_jugar, personaje &heroes, Implemento &implementos)
{
    if (cantidad_personajes_jugar == 4)
    {
        printf("\033[0;33m"); // Amarillo
        cout << "Ya tienes la cantidad de personajes maxima.\n";
        cout << "La lucha sera complicada pero no tanto." << endl;
        cout << "Eleccion fallida." << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "Pulse enter para continuar:" << endl;
        getline(cin, pausa);
        return;
    }
    if (cantidad_implementos == 0)
    {
        printf("\033[0;31m"); // Rojo
        cout << "No hay implementos disponibles para equipar a los heroes.\n";
        cout << "Eleccion de personaje fallida.\n";
        printf("\033[0;37m"); // Gris claro
        cout << "Pulse enter para continuar:" << endl;
        getline(cin, pausa);
        return;
    }

    int identificador;
    personaje *seleccionado = nullptr;

    printf("\033[0;33m"); // Amarillo
    cout << "Los heroes disponibles son: \n";
    printf("\033[0;37m"); // Gris claro
    mostrar_personajes(heroes, 2);
    cout << "Coloque el ID del heroe que desea agregar al equipo: ";
    identificador = obtener_entero("");

    seleccionado = encontrar_personaje(heroes, identificador);

    if (seleccionado == nullptr)
    {
        printf("\033[0;31m"); // Rojo
        cout << "El ID: " << identificador << " no existe.\n";
        cout << "Eleccion de personaje fallida.\n";
        cout << "Esas acciones le faltan el respeto a los tres guerreros ancestrales de las cavernas." << endl;
        printf("\033[0;37m"); // Gris claro
        cout << "pulse enter para continuar." << endl;
        getline(cin, pausa);
        return;
    }
    cantidad_personajes_jugar++;
    personaje *nuevo_para_jugar = new personaje;
    nuevo_para_jugar->nombre = seleccionado->nombre;
    nuevo_para_jugar->tipo = new Especie;
    nuevo_para_jugar->tipo->danno_fortaleza = seleccionado->tipo->danno_fortaleza;
    nuevo_para_jugar->tipo->identificador = seleccionado->tipo->identificador;
    nuevo_para_jugar->tipo->nombre_especie = seleccionado->tipo->nombre_especie;
    nuevo_para_jugar->tipo->rapidez = seleccionado->tipo->rapidez;
    nuevo_para_jugar->tipo->salud = seleccionado->tipo->salud;
    nuevo_para_jugar->identificador = cantidad_personajes_jugar + regulador_personajes_jugar;
    nuevo_para_jugar->mimochila = new mochila;
    nuevo_para_jugar->mimochila->implementos = nullptr;
    nuevo_para_jugar->mimochila->poderes = nullptr;
    nuevo_para_jugar->siguiente = nullptr;

    printf("\033[0;33m"); // Amarillo
    cout << "Proceda a llenar la mochila del personaje: " << nuevo_para_jugar->nombre << endl
         << endl;
    printf("\033[0;37m"); // Gris claro
    llenar_mochila(nuevo_para_jugar, implementos, lista_jugar);

    if (lista_jugar == nullptr)
    {
        lista_jugar = nuevo_para_jugar;
    }
    else
    {
        personaje *ultimo = lista_jugar;
        while (ultimo->siguiente != nullptr)
        {
            ultimo = ultimo->siguiente;
        }
        ultimo->siguiente = nuevo_para_jugar;
    }
    printf("\033[0;32m"); // Verde
    cout << "El heroe " << nuevo_para_jugar->nombre << " se agrego al equipo.\n";
    cout << "Buena eleccion.\n";
    printf("\033[0;37m"); // Gris claro
}

void mostrar_personajes_jugar(personaje *lista_personajes_jugar)
{
    personaje *actual_personaje = lista_personajes_jugar;
    while (actual_personaje != nullptr)
    {
        printf("\033[0;35m"); // Magenta para el nombre
        cout << "Nombre: " << actual_personaje->nombre << endl;

        printf("\033[0;36m"); // Cyan para los atributos
        cout << "   ID: " << actual_personaje->identificador << endl;
        cout << "   Especie: " << actual_personaje->tipo->nombre_especie << endl;
        cout << "   Vitalidad: " << actual_personaje->tipo->salud << endl;
        cout << "   Fortaleza: " << actual_personaje->tipo->danno_fortaleza << endl;
        cout << "   Rapidez: " << actual_personaje->tipo->rapidez << endl;

        printf("\033[0;37m"); // Gris claro para el resto del texto
        cout << "Objetos de la mochila: " << endl;

        Implemento *actual_implemento = actual_personaje->mimochila->implementos;
        printf("\033[0;32m"); // Verde para "Implementos:"
        cout << "  Implementos: ";
        if (actual_implemento == nullptr)
        {
            printf("\033[0;31m"); // Rojo para mensaje de vacío
            cout << "La mochila no tiene implementos." << endl;
        }
        else
        {
            printf("\033[0;37m"); // Gris claro para lista
            cout << endl;
            while (actual_implemento != nullptr)
            {
                printf("\033[0;32m"); // Verde para cada implemento
                cout << "    - " << actual_implemento->nombre_implemento << endl;
                actual_implemento = actual_implemento->siguiente;
            }
        }

        if (actual_personaje->mimochila->num_poder == " ")
        {
            printf("\033[0;31m"); // Rojo para "no tiene poder"
            cout << "Poder: no tiene ningun poder equipado." << endl;
        }
        else
        {
            printf("\033[0;33m"); // Amarillo para poder
            cout << "Poder: " << actual_personaje->mimochila->num_poder << endl;
        }
        printf("\033[0;37m"); // Gris claro para reset
        cout << "-------------------------" << endl;
        actual_personaje = actual_personaje->siguiente;
    }
    cout << "\nNo hay mas personajes en el equipo\n\n";
}

void eliminar_personaje_jugar(personaje *&lista_jugar)
{
    if (cantidad_personajes_jugar == 0)
    {
        printf("\033[0;31m"); // Rojo
        cout << "No hay personajes disponibles para eliminar.\n";
        cout << "Eliminacion fallida.\n";
        printf("\033[0;37m"); // Gris claro
        cout << "Pulse enter para continuar:" << endl;
        getline(cin, pausa);
        return;
    }

    int identificador = 0;
    printf("\033[0;33m"); // Amarillo
    cout << "Los personajes en el equipo son:\n";
    printf("\033[0;37m"); // Gris claro
    mostrar_personajes_jugar(lista_jugar);
    cout << "Coloque el ID del personaje que desea eliminar: ";
    identificador = obtener_entero("");

    personaje *actual = lista_jugar;
    personaje *anterior = nullptr;

    while (actual != nullptr && actual->identificador != identificador)
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual != nullptr)
    {
        Implemento *actual_implemento = actual->mimochila->implementos;
        while (actual_implemento != nullptr)
        {
            Implemento *siguiente_implemento = actual_implemento->siguiente;
            delete actual_implemento;
            actual_implemento = siguiente_implemento;
        }

        Poder_magico *actual_poder = actual->mimochila->poderes;
        while (actual_poder != nullptr)
        {
            Poder_magico *siguiente_poder = actual_poder->siguiente;
            delete actual_poder;
            actual_poder = siguiente_poder;
        }

        if (anterior == nullptr)
        {
            lista_jugar = actual->siguiente;
        }
        else
        {
            anterior->siguiente = actual->siguiente;
        }

        printf("\033[0;32m"); // Verde
        cout << "Eliminacion del personaje " << actual->nombre << " exitosa.\n";
        printf("\033[0;37m"); // Gris claro
        delete actual;
        cantidad_personajes_jugar--;
    }
    else
    {
        printf("\033[0;31m"); // Rojo
        cout << "El ID " << identificador << " no existe en el equipo.\n";
        cout << "Eliminacion fallida.\n";
        printf("\033[0;37m"); // Gris claro
        cout << "Pulse enter para continuar:" << endl;
        getline(cin, pausa);
    }
}

void destruir_personaje_jugar(personaje *&lista_jugar)
{
    personaje *actual = lista_jugar;
    while (actual != nullptr)
    {
        Implemento *actual_implemento = actual->mimochila->implementos;
        while (actual_implemento != nullptr)
        {
            Implemento *siguiente_implemento = actual_implemento->siguiente;
            delete actual_implemento;
            actual_implemento = siguiente_implemento;
        }

        Poder_magico *actual_poder = actual->mimochila->poderes;
        while (actual_poder != nullptr)
        {
            Poder_magico *siguiente_poder = actual_poder->siguiente;
            delete actual_poder;
            actual_poder = siguiente_poder;
        }
        personaje *eliminar = actual;
        actual = actual->siguiente;
        delete eliminar;
    }
}

void modificar_mochila(personaje *personajes_jugar, Implemento &Implementos, Poder_magico &poderes)
{
    if (cantidad_personajes_jugar == 0)
    {
        printf("\033[0;31m"); // Rojo
        cout << "No hay personajes en el equipo para modificar.\n";
        cout << "Modificacion fallida.\n";
        printf("\033[0;37m"); // Gris claro
        cout << "Pulse enter para continuar:" << endl;
        getline(cin, pausa);
        return;
    }

    int identificador;
    printf("\033[0;33m"); // Amarillo
    cout << "Los personajes que forman parte del equipo son:\n";
    printf("\033[0;37m"); // Gris claro
    mostrar_personajes_jugar(personajes_jugar);
    cout << "Coloque el ID del personaje cuya mochila desea modificar: ";
    identificador = obtener_entero("");

    personaje *actual = personajes_jugar;
    while (actual != nullptr && actual->identificador != identificador)
    {
        actual = actual->siguiente;
    }

    if (actual != nullptr)
    {
        printf("\033[0;33m"); // Amarillo
        cout << "Proceda a llenar nuevamente la mochila del personaje: " << actual->nombre << endl;
        // printf("\033[0;37m"); // Gris claro
        // cout << "Pulse enter para continuar:" << endl;
        // getline(cin, pausa);

        Implemento *actual_implemento = actual->mimochila->implementos;
        while (actual_implemento != nullptr)
        {
            Implemento *siguiente_implemento = actual_implemento->siguiente;
            delete actual_implemento;
            actual_implemento = siguiente_implemento;
        }
        actual->mimochila->implementos = nullptr;

        Poder_magico *actual_poder = actual->mimochila->poderes;
        while (actual_poder != nullptr)
        {
            Poder_magico *siguiente_poder = actual_poder->siguiente;
            delete actual_poder;
            actual_poder = siguiente_poder;
        }
        actual->mimochila->num_poder = " ";
        actual->mimochila->poderes = nullptr;

        llenar_mochila(actual, Implementos, personajes_jugar);
        printf("\033[0;32m"); // Verde
        cout << "Actualización de la mochila completa para el personaje: " << actual->nombre << endl;
        printf("\033[0;37m"); // Gris claro
    }
    else
    {
        printf("\033[0;31m"); // Rojo
        cout << "El ID " << identificador << " no existe en el equipo.\n";
        cout << "Modificación fallida.\n";
        printf("\033[0;37m"); // Gris claro
        cout << "Pulse enter para continuar:" << endl;
        getline(cin, pausa);
    }
}

// para crear el vector de personajes para usarlo al momento de jugar.
vector<personaje *> crear_vector_personajes(personaje *&lista)
{
    personaje *actual = lista;
    vector<personaje *> nueva_lista;
    while (actual != nullptr)
    {
        nueva_lista.push_back(actual);
        actual = actual->siguiente;
    }
    return nueva_lista;
}
