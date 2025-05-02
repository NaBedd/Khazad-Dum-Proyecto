// LIBRERIAS.

#include <iostream> // para operaciones de entrada y salida de datos.
#include <string>   // para manejar string
#include <limits.h> // para los punteros NEW.

using namespace std;

// ESTRUCTURAS Y TIPOS DE DATOS
// ----------------------------------------------------------------------

// ESTRUCTURA PARA LOS TIPOS DE ORCOS.
struct Especie_orco
{
    string nombre_especie;
    int danno;
    int salud;
    int rapidez;
    int identificador;
    Especie_orco *siguiente;
};

// Estructura para crear las listas enlazadas de tipo orco.
struct Lista_especie_orcos
{
    Especie_orco *cabeza = nullptr;
    int cantidad = 0;
};

// ESTRUCTURA PARA LOS TIPO HEROE.
struct Especie_heroe
{
    string nombre_especie;
    int fortaleza;
    int salud;
    int rapidez;
    int identificador;
    Especie_heroe *siguiente;
};

// Lista enlazada de tipo heroes
struct Lista_especie_heroes
{
    Especie_heroe *cabeza = nullptr;
    int cantidad = 0;
};

// ESTRUCTURA PARA LOS IMPLEMENTOS
// *** PENDIENTE ***
struct Implementos
{
};

// FUNCIONES GENERICAS
// -----------------------------------------------------------------------

// CREADOR DE PERSONAJES, para crear nuevos tipos de personajes (orcos y heroes)
template <typename TipoDeLista, typename TipoDeDato>
void crear_tipo_personaje(TipoDeLista &lista)
{
    TipoDeDato *nuevo = new TipoDeDato();
    cout << "\nIngrese los datos para el nuevo tipo.\n";
    cin.ignore();

    cout << "Nombre de la especie: ";
    getline(cin, nuevo->nombre);

    cout << "Danno: ";
    cin >> nuevo->danno;

    cout << "Salud: ";
    cin >> nuevo->salud;

    cout << "Rapidez: ";
    cin >> nuevo->rapidez;
    cout << endl;

    // Insertar de primero en la lista:
    nuevo->siguiente = lista.cabeza; // a nuevo lo pone a apuntar a lo que este apuntando la lista (nullptr o otro si ya hay elementos en la lista).
    lista.cabeza = nuevo;            // y lista ahora apunta a nuevo ya que lista siempre es la cabeza de la lista en este caso.
    lista.cantidad++;                // Le suma 1 a lista.cantidad

    // Sube el identificador uno mas uno
    nuevo->identificador = lista.cantidad;
    // se le suma 1
    cout << "Especie " << nuevo->nombre_especie << " con ID " << nuevo->identificador << "ha sido agregada exitosamente. \n";
}

// DESTRUCTOR, destruye cualquier tipo de la lista automaticamente al finalizar.
template <typename TipoDeLista, typename TipoDeDato> // Template hace que la funcion sea como las de python, que trabaje con cualquier parametro
void destruir_lista(TipoDeLista &lista)              // Para usar la funcion:
{                                                    // destruir_lista<Tipo de la lista, nombre del tipo de dato que almacena la lista>(nombre que de la lista)
    TipoDeDato *actual = lista.cabeza;
    while (actual != nullptr)
    {
        TipoDeDato *eliminar = actual;
        actual = actual->siguiente;
        delete eliminar;
    }
    lista.cabeza = nullptr;
    lista.cantidad = 0;
}

// EDITADO DE AQUI PARA ARRIBA
// -----------------------------------

void mostrar_lista_orco(Lista_especie_orcos &lista)
{ // toma la direccion de memoria.
    if (lista.cantidad == 0)
    { // si no hay elementos no hace nada.
        cout << "No hay tipos de orcos en este momento. \n\n";
        return;
    }

    cout << "\nHay [" << lista.cantidad << "] tipos de orcos disponibles" << endl;
    Especie_orco *actual = lista.primero_especie; // se crea una variable auxiliar para igualarla al primer elemnto de la lista.
    while (actual != nullptr)
    { // si es igual a nullptr significa que es el ultimo elemento de la lista.
        cout << actual->identificador << "-";
        cout << "Nombre= " << actual->nombre_especie << endl;
        cout << "Danno = " << actual->danno << endl;
        cout << "Salud = " << actual->salud << endl;
        cout << "Rapidez = " << actual->rapidez << "\n"
             << endl;
        actual = actual->siguiente; // pasa a siguiente elemento de la lista.
    }
    cout << "No hay mas tipos de orcos disponibles.\n"
         << endl;
}

void actualizar_tipo_orco(Lista_especie_orcos &lista)
{
    int referencia;
    cout << "Ingresa que orco quieres actualizar: ";
    cin >> referencia;
    Especie_orco *actual = lista.primero_especie;
    bool encontrado = false;

    while (actual != nullptr)
    {
        if (actual->identificador == referencia)
        {
            cout << "\nIngrese los datos a actualizar para el orco con identificador " << referencia << ":\n";
            cin.ignore(); // Limpiar el buffer

            cout << "Nombre de la especie: ";
            getline(cin, actual->nombre_especie);

            cout << "Daño: ";
            cin >> actual->danno;

            cout << "Salud: ";
            cin >> actual->salud;

            cout << "Rapidez: ";
            cin >> actual->rapidez;

            cout << "Datos del orco con ID " << referencia << " actualizados exitosamente.\n";
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

int main()
{
    Lista_especie_orcos tipoEspecieOrco; // lista enlazada que contiene todos los tipos de orcos.
    int opcion = 0;

    cout << "Bienvenido ¿Que desea hacer?: " << endl;

    // menu mientras.
    do
    {
        cout << "\nMENU DE OPCIONES: \n";
        cout << "---------------------\n";
        cout << "1. Agregar una especie orco \n";
        cout << "2. Actualizar los datos de un orco \n";
        cout << "3. Mostrar los tipos de orcos disponibles \n";
        cout << "4. Salir del menu \n"; // Ya no sale del programa sino del menu de creacion, pq luego vendra el juego como tal.
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            Crear_tipo_orco(tipoEspecieOrco);
            break;
        case 2:
            actualizar_tipo_orco(tipoEspecieOrco);
            mostrar_lista_orco(tipoEspecieOrco);
            break;
        case 3:
            mostrar_lista_orco(tipoEspecieOrco);
            break;
        case 4:
            cout << "\nSaliendo del menu... \n";
            break; // Sale del programa, la opcion como tal no destruye las listas porque se destruyen automaticamente al salir del programa.

        default:
            cout << "opcion no valida, la opcion " << opcion << " no esta disponible. \n";
            break;
        }
    } while (opcion != 4);

    // Dejar esto al final del programa para que se destruyan las listas enlazadas.
    // Hay que añadir todos los tipos de listas que se vayan creando.
    destruir_lista_especie_orco(tipoEspecieOrco); // se destruye la lista al final del programa.
    cout << "Gracias por usar el programa. \n";
    return 0;
}
// fin del programa.
