// LIBRERIAS.

#include <iostream> // para operaciones de entrada y salida de datos.
#include <string>   // para manejar string
#include <limits.h> // para los punteros NEW.

using namespace std;

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
    Especie_orco *primero_especie = nullptr;
    int cantidad = 0;
};

// DESTRUCTOR, destruye la lista automaticamente al finalizar.
// funcion para liberar memoria dinamica.
void destruir_lista_especie_orco(Lista_especie_orcos &lista)
{                                                 // Toma la direccion de memoria de la lista que se le pase (del tipo).
    Especie_orco *actual = lista.primero_especie; // declara un nodo actual para igualarlo al primer elemento de la lista.
    while (actual != nullptr)
    {                                    // si es nullptr es porque es el ultimo elemento.
        Especie_orco *eliminar = actual; // se crea una variable aux (eliminar) para darle la direccion de memoria de actual.
        actual = actual->siguiente;      // se manda al siguente nodo al actual.
        delete eliminar;                 // se elimina la variable aux (eliminar).
    }
    // la declaramos en null a la lista.
    lista.primero_especie = nullptr;
    lista.cantidad = 0;
}

// PARA CREAR UN NUEVO TIPO DE ORCO.
void Crear_tipo_orco(Lista_especie_orcos &lista)
{ // toma la direccion de memoria de la lista.
    Especie_orco *nuevo = new Especie_orco();
    cout << "\nIngrese los datos para la nueva especie de Orco\n";
    cin.ignore(); // Limpiar el buffer

    cout << "Nombre de la especie: ";
    getline(cin, nuevo->nombre_especie);

    cout << "Danno: ";
    cin >> nuevo->danno;

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
    nuevo->identificador = lista.cantidad;
    // se le suma 1
    cout << "Especie de orco " << nuevo->nombre_especie << " ha sido agregada exitosamente. \n";
}

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
