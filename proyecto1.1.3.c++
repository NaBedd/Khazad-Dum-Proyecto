//
// LIBRERIAS.

#include <iostream> // para operaciones de entrada y salida de datos.
#include <string>   // para manejar string
#include <limits.h> // para los punteros NEW.

using namespace std;

//-----------------------------------------------------------------------------------------------------

//------------------------------ PARA LOS TIPOS ------------------------------------------------------
// regulador para cuando se eliminen tipos de orcos en la lista.
int regulador_tipo_orco = 0;
int regulador_tipo_heroe = 0;
// ESTRUCTURA PARA LOS TIPOS DE especies. orcos y heroes
struct Especie
{
    string nombre_especie;
    int danno_fortaleza;
    int salud;
    int rapidez;
    int identificador;
    Especie *siguiente;
};

// Estructura para crear las listas enlazadas de tipo orco.
struct Lista_especie
{
    Especie *primero_especie = nullptr;
    int cantidad = 0;
};
//-----------------------------------------------------------------------------------------------------

// funcion para liberar memoria dinamica.
void destruir_lista_especie(Lista_especie &lista)
{                                            // Toma la direccion de memoria de la lista que se le pase (del tipo).
    Especie *actual = lista.primero_especie; // declara un nodo actual para igualarlo al primer elemento de la lista.
    while (actual != nullptr)
    {                               // si es nullptr es porque es el ultimo elemento.
        Especie *eliminar = actual; // se crea una variable aux (eliminar) para darle la direccion de memoria de actual.
        actual = actual->siguiente; // se manda al siguente nodo al actual.
        delete eliminar;            // se elimina la variable aux (eliminar).
    }
    // la declaramos en null a la lista.
    lista.primero_especie = nullptr;
    lista.cantidad = 0;
}

// PARA CREAR UN NUEVO TIPO DE ORCO.
void Crear_tipo(Lista_especie &lista, int tipo) // tipo=1 orco / tipo=2 heroe
{                                               // toma la direccion de memoria de la lista.
    Especie *nuevo = new Especie();

    if (tipo == 1)
    { // si es orco
        cout << "\nIngrese los datos para la nueva especie de Orco\n";
    }
    else
    { // si es heroe
        cout << "\nIngrese los datos para la nueva especie se heroe\n";
    }
    cin.ignore(); // Limpiar el buffer

    cout << "Nombre de la especie: ";
    getline(cin, nuevo->nombre_especie);

    if (tipo == 1)
    {
        cout << "Danno: ";
        cin >> nuevo->danno_fortaleza;
    }
    else
    {
        cout << "fortaleza: ";
        cin >> nuevo->danno_fortaleza;
    }

    cout << "Salud: ";
    cin >> nuevo->salud;

    cout << "Rapidez: ";
    cin >> nuevo->rapidez;
    cout << endl;

    // inserta de primero en la lista.
    nuevo->siguiente = lista.primero_especie; // a nuevo lo pone a apuntar a lo que este apuntando la lista (nullptr o otro si ya hay elementos en la lista).
    lista.primero_especie = nuevo;            // y lista ahora apunta a nuevo ya que lista siempre es la cabeza de la lista en este caso.
    lista.cantidad = lista.cantidad + 1;

    // Sube el identificador uno mas uno
    if (tipo == 1)
    {
        nuevo->identificador = (lista.cantidad + regulador_tipo_orco); // le sumo el regulador para que el identificador no quede igual al ultimo
        // se le suma 1
        cout << "Especie de orco " << nuevo->nombre_especie << " ha sido agregada exitosamente. \n";
    }
    else
    {
        nuevo->identificador = (lista.cantidad + regulador_tipo_heroe); // le sumo el regulador para que el identificador no quede igual al ultimo
        // se le suma 1
        cout << "Especie de heroe " << nuevo->nombre_especie << " ha sido agregada exitosamente. \n";
    }
}

void mostrar_lista(Lista_especie &lista, int tipo) // tipo=1 orco / tipo=2 heroe
{                                                  // toma la direccion de memoria.
    if (lista.cantidad == 0)
    { // si no hay elementos no hace nada.
        cout << "la lista esta vacia. \n\n";
        return;
    }

    if (tipo == 1)
    {
        cout << "\nHay [" << lista.cantidad << "] tipos de orcos disponibles" << endl;
    }
    else
    {
        cout << "\nHay [" << lista.cantidad << "] tipos de heroes disponibles" << endl;
    }
    Especie *actual = lista.primero_especie; // se crea una variable auxiliar para igualarla al primer elemnto de la lista.
    while (actual != nullptr)
    { // si es igual a nullptr significa que es el ultimo elemento de la lista.
        cout << actual->identificador << "-";
        cout << "Nombre= " << actual->nombre_especie << endl;
        if (tipo == 1)
        {
            cout << "Danno = " << actual->danno_fortaleza << endl;
        }
        else
        {
            cout << "fortaleza = " << actual->danno_fortaleza << endl;
        }
        cout << "Salud = " << actual->salud << endl;
        cout << "Rapidez = " << actual->rapidez << "\n"
             << endl;
        actual = actual->siguiente; // pasa a siguiente elemento de la lista.
    }
    cout << "No hay mas tipos disponibles.\n"
         << endl;
}

void actualizar_tipo(Lista_especie &lista, int tipo) // tipo=1 orco / tipo=2 heroe
{
    if (lista.cantidad == 0)
    {
        cout << " la lista se encuentra vacai.\n\n";
        return; // deja de ejecutar la funcion
    }

    int referencia;
    if (tipo == 1)
    {
        cout << "Ingrese el numero del orco que decea modificar: ";
    }
    else
    {
        cout << "Ingrese el numero del heroe que decea modificar: ";
    }
    cin >> referencia;
    Especie *actual = lista.primero_especie;
    bool encontrado = false;

    while (actual != nullptr)
    {
        if (actual->identificador == referencia)
        {
            if (tipo == 1)
            {
                cout << "\nIngrese los datos a actualizar para el orco con identificador " << referencia << ":\n";
            }
            else
            {
                cout << "\nIngrese los datos a actualizar para el heroe con identificador " << referencia << ":\n";
            }
            cin.ignore(); // Limpiar el buffer

            cout << "Nombre de la especie: ";
            getline(cin, actual->nombre_especie);

            if (tipo == 1)
            {
                cout << "Daño: ";
            }
            else
            {
                cout << "fortaleza: ";
            }
            cin >> actual->danno_fortaleza;

            cout << "Salud: ";
            cin >> actual->salud;

            cout << "Rapidez: ";
            cin >> actual->rapidez;

            if (tipo == 1)
            {
                cout << "Datos del orco con ID " << referencia << " actualizados exitosamente.\n";
            }
            else
            {
                cout << "Datos del heroe con ID " << referencia << " actualizados exitosamente.\n";
            }
            encontrado = true;
            break; // Importante salir del bucle una vez encontrado
        }
        actual = actual->siguiente;
    }

    if (!encontrado)
    {
        cout << "No se encontró ningún tipo de orco con el ID: " << referencia << ".\n";
    }
}

// REVISARRRRRRRRRRRRR

void eliminar_elemento_lista(Lista_especie &lista, int tipo)
{
    if (lista.cantidad == 0)
    {
        cout << "No hay elementos en la lista para borrar\n";
        return;
    }

    mostrar_lista(lista, tipo);

    int identificador = 0;
    cout << "coloque el numero del tipo que desea borrar: \n";
    cin >> identificador;

    if (identificador > 0 && identificador <= lista.cantidad)
    {
        Especie *actual = lista.primero_especie;
        Especie *anterior = nullptr; // Inicializamos anterior como nullptr

        // Caso especial: el elemento a eliminar es el primero de la lista
        if (actual != nullptr && actual->identificador == identificador)
        {
            lista.primero_especie = actual->siguiente;
            cout << "el tipo " << actual->nombre_especie << " se elimino correctamente" << endl;
            delete actual;
            lista.cantidad -= 1;
            if (tipo == 1)
            {
                regulador_tipo_orco += 1;
            }
            else
            {
                regulador_tipo_heroe += 1;
            }
            return; // Salimos de la función después de eliminar el primer elemento
        }

        // Caso general: el elemento a eliminar no es el primero
        while (actual != nullptr && actual->identificador != identificador)
        {
            anterior = actual;
            actual = actual->siguiente;
        }

        if (actual != nullptr)
        {
            Especie *eliminar = actual;
            anterior->siguiente = actual->siguiente;
            cout << "el tipo " << eliminar->nombre_especie << " se elimino correctamente" << endl;
            delete eliminar;
            lista.cantidad -= 1;
            if (tipo == 1)
            {
                regulador_tipo_orco += 1;
            }
            else
            {
                regulador_tipo_heroe += 1;
            }
        }
        else
        {
            cout << "El numero de especie: " << identificador << " no se encuentra en la lista. \n";
        }
    }
    else
    {
        cout << "El numero de especie ingresado no es valido. \n";
    }
}

int main()
{
    Lista_especie tipoEspecieOrco;  // lista enlazada que contiene todos los tipos de orcos.
    Lista_especie tipoEspecieHeroe; // lista enlazada que contiene todos los tipos de heroes.
    int opcion = 0;

    cout << "Bienvenido ¿Que desea hacer?: " << endl;

    // menu mientras.
    do
    {
        cout << "\n      MENU \n";
        cout << "\n ORCOS:\n";
        cout << "---------------------\n";
        cout << "1. Agregar una especie orco \n";
        cout << "2. Actualizar los datos de un orco \n";
        cout << "3. Mostrar los tipos de orcos disponibles \n";
        cout << "4. Eliminar un tipo de especie \n"; // Ya no sale del programa sino del menu de creacion, pq luego vendra el juego como tal.

        cout << "\n HEROES:\n";
        cout << "\nMENU DE OPCIONES HEROES: \n";
        cout << "---------------------\n";
        cout << "5. Agregar una especie orco \n";
        cout << "6. Actualizar los datos de un orco \n";
        cout << "7. Mostrar los tipos de orcos disponibles \n";
        cout << "8. Eliminar un tipo de especie \n"; // Ya no sale del programa sino del menu de creacion, pq luego vendra el juego como tal.

        cout << "9. Salir del menu \n ";

        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            Crear_tipo(tipoEspecieOrco, 1);
            break;
        case 2:
            actualizar_tipo(tipoEspecieOrco, 1);
            break;
        case 3:
            mostrar_lista(tipoEspecieOrco, 1);
            break;
        case 4:
            eliminar_elemento_lista(tipoEspecieOrco, 1);
            break;

            // Opciones para heroes
        case 5:
            Crear_tipo(tipoEspecieHeroe, 2);
            break;
        case 6:
            actualizar_tipo(tipoEspecieHeroe, 2);
            break;
        case 7:
            mostrar_lista(tipoEspecieHeroe, 2);
            break;
        case 8:
            eliminar_elemento_lista(tipoEspecieHeroe, 2);

            break;
        case 9:
            cout << "\nSaliendo del menu... \n";
            break; // Sale del programa, la opcion como tal no destruye las listas porque se destruyen automaticamente al salir del programa

        default:
            cout << "opcion no valida, la opcion " << opcion << " no esta disponible. \n";
            break;
        }
    } while (opcion != 9);

    // Dejar esto al final del programa para que se destruyan las listas enlazadas.
    // Hay que añadir todos los tipos de listas que se vayan creando.

    destruir_lista_especie(tipoEspecieHeroe);
    destruir_lista_especie(tipoEspecieOrco); // se destruye la lista al final del programa.
    cout << "Gracias por usar el programa. \n";
    return 0;
}
// fin del programa.
