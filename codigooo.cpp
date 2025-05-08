//
// LIBRERIAS.

#include <iostream>  // para operaciones de entrada y salida de datos.
#include <string>    // para manejar string
#include <limits.h>  // para los punteros NEW.
#include <algorithm> // para usar .erase

using namespace std;

//-----------------------------------------------------------------------------------------------------

//------------------------------ PARA LOS TIPOS DE ESPECIES -------------------------------------------
// Regulador para cuando se eliminen tipos de orcos en la lista.
int regulador_tipo_orco = 0;
int regulador_tipo_heroe = 0;

// ESTRUCTURA DE LA MOCHILA
struct Implemento
{
    string nombre_implemento;
    string tipo_implemento;
    string uso_implemento;
    int fortalezanecesaria;
    int valor;
};

// ESTRUCTURA DE LOS PODERES MAGICOS
struct Poder_magico
{
    string nombre_poder;
    string funcion;
};

// Estructura para el Mapa
struct Mapa
{
    string nombreEstacion; // Nombre de la sala
    int distancia_salida;
    int cantidadOrcos; // Cantidad de orcos en la sala
    Mapa *der;
    // Mapa *med;
    Mapa *izq;
};

// ESTRUCTURA para los tipos de especies. orcos y heroes
struct Especie
{
    string nombre_especie;
    int danno_fortaleza;
    int salud;
    int rapidez;
    int identificador;
    Especie *siguiente;
};

// Estructura para crear las listas enlazadas.
struct Lista_especie
{
    Especie *primero_especie = nullptr;
    int cantidad = 0;
};

//-----------------------------------------------------------------------------------------------------
//------------------------------ PARA LOS PERSONAJES --------------------------------------------------
int regulador_personaje_orco = 0;
int cantidad_personaje_orco = 0;

int regulador_personaje_heroe = 0;
int cantidad_personaje_heroe = 0;

struct personaje
{
    string nombre;
    Especie *tipo;
    int identificador;
    personaje *siguiente = nullptr;
};
//

//-----------------------------------------------------------------------------------------------------
//-------------------------------------- FUNCIONES ----------------------------------------------------

// Funciones para verificar formato de respuesta

// Función para validar y leer un entero con mensaje personalizado
int obtener_entero(const string &mensaje)
{
    string entrada;
    int valor;

    while (true)
    {
        cout << mensaje;
        getline(cin, entrada);

        // Para verificar si el número es válido
        bool es_valido = true;

        // La entrada nunca deberia ser solo 0
        if (entrada == "0")
        {
            es_valido = false;
        }

        // Revisa cada caracter
        for (size_t i = 0; i < entrada.size(); ++i)
        {
            if (es_valido && !isdigit(entrada[i]))
            {
                es_valido = false;
                break;
            }
        }

        // Convierte a entero mientras sea valido y no este vacio
        if (es_valido && !entrada.empty())
        {
            valor = stoi(entrada);

            return valor;
        }

        // Mensaje de error
        cout << "Error. Ingrese solo numeros naturales \n";
    }
}

// Funcion especifica para el menu de opciones
int obtener_opcion()
{
    return obtener_entero("Ingrese una opcion: ");
}

// Verificar string:
bool verificar_string(string respuesta)
{

    // Eliminar espacios en blanco al inicio y final
    respuesta.erase(remove(respuesta.begin(), respuesta.end(), ' '), respuesta.end());

    // Si la respuesta deberia ser una letra
    if (respuesta.empty())
    {
        return false; // Si esta vacia, retorna Falso
    }

    for (char caracter : respuesta)
    {
        if (isdigit(caracter)) // Si caracter es un numero, retorna Falso
        {
            return false;
        }
    }
    return true; // Si no hay numeros, retorna true
}

// Pide y devuelve valor del string ya verificado
string devolver_string_verificada(const string &mensaje)
{

    string entrada;

    cout << mensaje;
    getline(cin, entrada);

    while (!(verificar_string(entrada)))
    {
        cout << "Formato Invalido." << endl;
        cout << mensaje;
        getline(cin, entrada);
    }

    return (entrada);
}

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
        cout << "\nIngrese los datos para la nueva especie de Orco: \n";
    }
    else if (tipo == 2)
    { // si es heroe
        cout << "\nIngrese los datos para la nueva especie de Heroe: \n";
    }
    else
    {
        cout << "ERROR. TIPO NO ESPECIFICADO. VERIFICAR NUMERO QUE SE LE PUSO A LA FUNCION CREAR_TIPO \n";
    }

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
        cout << "ERROR. TIPO NO ESPECIFICADO. VERIFICAR NUMERO QUE SE LE PUSO A LA FUNCION CREAR_TIPO \n";
    }

    nuevo->salud = obtener_entero("Salud: ");
    nuevo->rapidez = obtener_entero("Rapidez: ");

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

// Para mostrar listas de especies
void mostrar_lista(Lista_especie &lista, int tipo) // tipo=1 orco / tipo=2 heroe
{                                                  // toma la direccion de memoria.
    if (lista.cantidad == 0)
    { // si no hay elementos no hace nada.
        cout << "No hay tipos de Orcos disponibles. \n\n";
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

// Para actalizar tipos de especies.
void actualizar_tipo(Lista_especie &lista, int tipo) // tipo=1 orco / tipo=2 heroe
{
    if (lista.cantidad == 0)
    {
        cout << "La lista se encuentra vacia.\n\n";
        return; // deja de ejecutar la funcion
    }

    int referencia;
    cout << "\nLos tipos de especie disponible son: ";
    cout << "------------------------" << endl;
    mostrar_lista(lista, tipo);
    if (tipo == 1)
    {
        referencia = obtener_entero("Ingrese el numero del tipo de orco que desea modificar: ");
    }
    else if (tipo == 2)
    {
        referencia = obtener_entero("ingrese el numero del tipo de heroe que desea modificar: ");
    }
    else
    {
        cout << "ERROR. VERIFICAR CODIGO. ACTUALIZAR_TIPO" << endl;
    }
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

    identificador = obtener_entero("Ingrese el numero del tipo que desea borrar: ");

    if (identificador > 0 && identificador <= lista.cantidad)
    {
        Especie *actual = lista.primero_especie;
        Especie *anterior = nullptr; // Inicializamos anterior como nullptr

        // Caso especial: el elemento a eliminar es el primero de la lista
        if (actual != nullptr && actual->identificador == identificador)
        {
            lista.primero_especie = actual->siguiente;
            cout << "El tipo " << actual->nombre_especie << " se elimino correctamente" << endl;
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
            cout << "El tipo " << eliminar->nombre_especie << " se elimino correctamente" << endl;
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
// FUNCIONES REFERENTES A PERSONAJES.

// Funcion que retorna un puntero a una especie.
Especie *encontrar_especie(Lista_especie &lista, int identificador)
{
    Especie *actual = lista.primero_especie;
    while ((actual->identificador != identificador) && (actual->siguiente != nullptr))
    {
        actual = actual->siguiente;
    }
    if (actual->identificador == identificador)
    {
        return actual;
    }
    else
    {
        cout << "La especie ingresada no existe." << endl;
        actual = nullptr;
        return actual;
    }
}

// para crear personajes.
void crear_personaje(personaje &lista_personaje, Lista_especie &lista_tipos, int tipo)
{
    if (lista_tipos.cantidad == 0)
    { // si no hay tipos creados se sale.
        cout << "Todavia no hay especies disponibles. Debe crearlas antes de crear un personaje." << endl;
        return;
    }
    else
    {
        personaje *nuevo = new personaje;
        int num_tipo = 0;                   // numero del tipo del personaje (identificador)
        Especie *puntero_especie = nullptr; // puntero al que se le asignara la especie.

        if (tipo == 1)
        {
            cout << "Indique los datos para el nuevo personaje Orco." << endl;

            nuevo->nombre = devolver_string_verificada("Nombre: ");

            cout << "Ingrese la especie al que pertenecera el Orco" << nuevo->nombre << "\n";
            cout << "Especies disponibles: " << endl;
            mostrar_lista(lista_tipos, tipo);

            cout << "Ingrese la especie del Orco " << nuevo->nombre << ": ";
            num_tipo = obtener_entero("");

            puntero_especie = encontrar_especie(lista_tipos, num_tipo);
        }
        else
        { // lo mismo pero para heroes.
            cout << "Indique los datos para el nuevo personaje Heroe. " << endl;

            nuevo->nombre = devolver_string_verificada("Nombre: ");

            cout << "Ingrese la especie al que pertenecera el Heroe" << nuevo->nombre << "\n";
            cout << "Especies disponibles: " << endl;
            mostrar_lista(lista_tipos, tipo);

            cout << "Ingrese la especie del Personaje" << nuevo->nombre << ":";
            num_tipo = obtener_entero("");

            puntero_especie = encontrar_especie(lista_tipos, num_tipo);
            // para validar que si esta la especie en la lista.
        }

        if (puntero_especie == nullptr)
        {
            cout << " La especie debe crearse primero." << endl;
            cout << "Creacion del personaje: " << nuevo->nombre << " fue fallida " << endl;
            delete nuevo; // liberamos memoria dinamica
            return;
        }
        else
        {
            nuevo->tipo = puntero_especie;
        }
        // lo mandamos a la lista enlazada.
        nuevo->siguiente = lista_personaje.siguiente;
        lista_personaje.siguiente = nuevo;

        if (tipo == 1)
        {
            cantidad_personaje_orco += 1; // sumamos a la cantidad de orcos.
            nuevo->identificador = (cantidad_personaje_orco + regulador_personaje_orco);
            cout << "El orco: " << nuevo->nombre << ", se agrego correctamente." << endl;
        }
        else
        {
            cantidad_personaje_heroe += 1; // sumamos a la cantidad de heroes.
            nuevo->identificador = (cantidad_personaje_heroe + regulador_personaje_heroe);
            cout << "El heroe: " << nuevo->nombre << ", se agrego correctamente." << endl;
        }
    }
}

// funcion para destruir la lista de personajes.
void destruir_lista_personajes(personaje &lista)
{                                        // Toma la direccion de memoria de la lista que se le pase (del tipo).
    personaje *actual = lista.siguiente; // declara un nodo actual para igualarlo al primer elemento de la lista.
    while (actual != nullptr)
    {                                 // si es nullptr es porque es el ultimo elemento.
        personaje *eliminar = actual; // se crea una variable aux (eliminar) para darle la direccion de memoria de actual.
        actual = actual->siguiente;   // se manda al siguente nodo al actual.
        delete eliminar;              // se elimina la variable aux (eliminar).
    }
    // la declaramos en null a la lista.
}

// funcion para mostrar los personajes
void mostrar_personajes(personaje &lista, int tipo) // tipo=1 orco / tipo=2 heroe
{                                                   // toma la direccion de memoria.
    // para validar que si hay personajes para mostrar.
    if (tipo == 1)
    { // para orcos.
        if (cantidad_personaje_orco == 0)
        {
            cout << "\nno hay personajes orcos para mostra actualmente \n";
            cout << "primero deve crerlos\n";
            return;
        }
    }
    else
    { // para heroes
        if (cantidad_personaje_heroe == 0)
        {
            cout << "\nno hay personajes heroes para mostra actualmente \n";
            cout << "primero deve crerlos\n";
        }
    }

    if (tipo == 1)
    {
        cout << "\nHay [" << cantidad_personaje_orco << "] personajes orcos" << endl;
    }
    else
    {
        cout << "\nHay [" << cantidad_personaje_heroe << "] personajes heroes" << endl;
    }
    personaje *actual = lista.siguiente; // se crea una variable auxiliar para igualarla al primer elemnto de la lista.
    while (actual != nullptr)
    { // si es igual a nullptr significa que es el ultimo elemento de la lista.
        cout << actual->identificador << "-";
        cout << "Nombre= " << actual->nombre << endl;
        cout << "Especie= " << actual->tipo->nombre_especie << endl;
        actual = actual->siguiente;
    }
    cout << "No hay mas personajes.\n"
         << endl;
}

// funcion para modificar a los personajes.
void actualizar_personaje(personaje &lista, Lista_especie lista_tipo, int tipo) // tipo=1 orco / tipo=2 heroe
{
    if (tipo == 1)
    { // para orcos.
        if (cantidad_personaje_orco == 0)
        {
            cout << "\nNo hay personajes orcos para mostrar actualmente \n";
            cout << "Primero debe crearlos\n";
            return;
        }
    }
    else
    { // para heroes
        if (cantidad_personaje_heroe == 0)
        {
            cout << "\nNo hay personajes heroes para mostrar actualmente \n";
            cout << "primero debe crearlos\n";
            return;
        }
    }
    // el procedimineto es similar al de crear personajes.
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
            cout << "ingrese los datos para actualizar al personaje " << actual->nombre << endl;
            cin.ignore(); // Limpiar el buffer

            actual->nombre = devolver_string_verificada("Nombre del personaje: ");

            cout << "\n Coloque el nuevo tipo de de especie al que pertenecera el personje \n";
            cout << "\n Tipos disponibles son: " << endl;
            cout << "------------------------" << endl;
            mostrar_lista(lista_tipo, tipo);

            // Identificador
            identificador_tipo = obtener_entero("Coloque el numero del tipo del personaje: ");

            especie_nueva = encontrar_especie(lista_tipo, identificador_tipo);

            if (especie_nueva == nullptr)
            {
                cout << "La que coloco no se encuentra disponible." << endl;
                cout << "La actualiacion del personaje: " << actual->nombre << " fue fallida " << endl;
                return;
            }
            else
            {
                cout << "El personaje ahora de nombre: " << actual->nombre << " se actualizo correctamente";
            }
        }
        actual = actual->siguiente;
    }
    if (!encontrado)
    {
        cout << "No se encontró ningún tipo de orco con el ID: " << referencia << ".\n";
        cout << "actualizacion fallida \n";
    }
}

//-----------------------------------------------------------------------------------------------------
//------------------------------ EJECUCION DEL PROGRAMA -----------------------------------------------

int main()
{

    Lista_especie tipoEspecieOrco;  // lista enlazada que contiene todos los tipos de orcos.
    Lista_especie tipoEspecieHeroe; // lista enlazada que contiene todos los tipos de heroes.

    personaje personajes_orco; // lista enlazada de personajes orcos.
    personaje personajes_hero; // lista enlazada de personajes heroes.

    int opcion_principal = 0;
    int opcion_interna = 0;

    cout << "Bienvenido ¿Que desea hacer?: " << endl;

    // Menu mientras.

    do
    {
        cout << "\n      MENU PRINCIPAL \n";
        cout << "1. Ingresar al Menu de Orcos" << "\n";
        cout << "2. Ingresar al Menu de Heroes" << "\n";
        cout << "3. Ingresar al Menu de Implementos" << "\n"; // Por agregar
        cout << "4. Salir de Menu Principal" << "\n";
        opcion_principal = obtener_opcion();

        // Switch para Menu Principal
        switch (opcion_principal)
        {
        // Menu Orcos
        case 1:
            do
            {
                cout << "\n MENU ORCOS:\n";
                cout << "---------------------\n";
                cout << "1. Agregar una especie de Orco \n";
                cout << "2. Actualizar los datos de un tipo de Orco \n";
                cout << "3. Mostrar los tipos de Orcos disponibles \n";
                cout << "4. Eliminar un tipo de especie \n";
                cout << "------------------------\n";
                cout << "5. Crear personaje \n";
                cout << "6. Mostrar personajes \n";
                cout << "7. Modificar personaje \n";
                cout << "------------------------\n";
                cout << "8.Salir al menu principal.\n";
                opcion_interna = obtener_opcion();

                switch (opcion_interna)
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
                case 5:
                    crear_personaje(personajes_orco, tipoEspecieOrco, 1);
                    break;

                case 6:
                    mostrar_personajes(personajes_orco, 1);
                    break;
                case 7:
                    actualizar_personaje(personajes_orco, tipoEspecieOrco, 1);
                    break;
                case 8:
                    cout << "\nSaliendo al Menu Principal... \n";
                    break;
                default:
                    cout << "Invalido. Ingrese una opcion valida \n";
                    break;
                }
            } while (opcion_interna != 8); // Mientras no se salga del menu interno de orcos.
            break;

        // Menu Heroes
        case 2:
            do
            {
                cout << "\n MENU DE HEROES:\n";
                cout << "---------------------\n";
                cout << "1. Agregar una especie de Heroe \n";
                cout << "2. Actualizar los datos de un tipo de Heroe \n";
                cout << "3. Mostrar los tipos de Heroes disponibles \n";
                cout << "4. Eliminar un tipo de especie \n"; // Ya no sale del programa sino del menu de creacion, pq luego vendra el juego como tal.
                cout << "---------------------\n";
                cout << "5. Crear personaje.\n";
                cout << "6. Mostrar personajes. \n";
                cout << "7. Modificar personaje \n";
                cout << "---------------------\n";
                cout << "8. Salir al menu principal  \n";
                opcion_interna = obtener_opcion();

                switch (opcion_interna)
                {
                case 1:
                    Crear_tipo(tipoEspecieHeroe, 2);
                    break;
                case 2:

                    actualizar_tipo(tipoEspecieHeroe, 2);
                    break;
                case 3:
                    mostrar_lista(tipoEspecieHeroe, 2);
                    break;
                case 4:
                    eliminar_elemento_lista(tipoEspecieHeroe, 2);
                    break;
                case 5:
                    crear_personaje(personajes_hero, tipoEspecieHeroe, 2);
                    break;
                case 6:
                    mostrar_personajes(personajes_hero, 2);
                    break;
                case 7:
                    actualizar_personaje(personajes_hero, tipoEspecieHeroe, 2);
                    break;
                case 8:
                    cout << "\nSaliendo al Menu Principal... \n";
                    break;
                default:
                    cout << "Invalido. Ingrese una opcion valida \n";
                    break;
                }
            } while (opcion_interna != 8); // Mientras no se salga del menu interno de heroes.
            break;

        // Menu Implementos
        case 3:
            // Cuando se agreguen las cosas, hay que hacer el do while
            cout << "\n MENU DE IMPLEMENTOS:\n";
            cout << "TODAVIA NO EXISTE OJO \n";
            cout << "DEVOLVIENDO AL MENU PRINCIPAL... \n";
            // opcion_interna = obtener_opcion();

            break;

        case 4:
            cout << "\nSaliendo del Menu Principal... \n";
            cout << "Entrando al Juego... \n";
            break;

        // Default del Menu Principal:
        default:
            cout << "Invalido. Ingrese una opcion valida";
            break;
        }

    } while (opcion_principal != 4);

    // Dejar esto al final del programa para que se destruyan las listas enlazadas.
    // Hay que añadir todos los tipos de listas que se vayan creando.
    destruir_lista_especie(tipoEspecieHeroe);
    destruir_lista_especie(tipoEspecieOrco); // se destruye la lista al final del programa.

    destruir_lista_personajes(personajes_orco);
    destruir_lista_personajes(personajes_hero);

    cout << "Gracias por usar el programa. \n";
    return 0;
}
// fin del programa.
