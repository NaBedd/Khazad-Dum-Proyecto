// LIBRERIAS.

#include <iostream> // para operaciones de entrada y salida de datos.
#include <string>   // para manejar string
#include <limits.h> // par los punteros NEW.

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
struct Lista_espesie_orcos
{
    Especie_orco *primero_especie = nullptr;
    int cantidad = 0;
};

// DESTRUCTOR, destruye la lista automaticamente al finalizar.
// funcion paa libera memoria dinamica.
void destruir_lista_especie_orco(Lista_espesie_orcos &lista)
{                                                 // tomara la direccion de memoria de la lista que se le pase (del tipo).
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
void Crear_tipo_orco(Lista_espesie_orcos &lista)
{ // toma la direccion de memoria de la lista.
    Especie_orco *nuevo = new Especie_orco();
    cout << "\ningrese los datos de la nueva especie ORCO\n";
    cin.ignore(); // Limpiar el buffer

    cout << "nobre de la especie: ";
    getline(cin, nuevo->nombre_especie);

    cout << "danno: ";
    cin >> nuevo->danno;

    cout << "salud: ";
    cin >> nuevo->salud;

    cout << "rapidez: ";
    cin >> nuevo->rapidez;
    cout<<endl;

    // inserta de primero en la lista.
    nuevo->siguiente = lista.primero_especie; // a nuevo lo pone a apuntar a lo que este apuntando la lista (nullptr o otro si ya hay elementos en la lista).
    lista.primero_especie = nuevo;            // y lista ahora apunta a nuevo ya que lista siempre es la cabeza de la lista en este caso.
    lista.cantidad = lista.cantidad + 1;  
    
    //Sube el identificador uno mas uno
    nuevo->identificador=lista.cantidad;
    // se le suma 1
    cout << "especie ORCO agregada exitosamente. \n";
}

void mostar_lista_orco(Lista_espesie_orcos &lista)
{ // toma la direccion de memoria.
    if (lista.cantidad == 0)
    { // si no hay elementos no hace nada.
        cout << "no hay tipos de orcos en este momento. \n\n";
        return;
    }

    cout << "la cantidad de tipos de orcos son: [" << lista.cantidad <<"]"<< endl;
    Especie_orco *actual = lista.primero_especie; // se crea una variable auxiliar para igualarla al primer elemnto de la lista.
    while (actual != nullptr)
    { // si es igual a nullptr significa que es el ultimo elemento de la lista.
        cout << actual->identificador<<"-";
        cout << "nombre= " << actual->nombre_especie << endl;
        cout << "danno = " << actual->danno << endl;
        cout << "salud = " << actual->salud << endl;
        cout << "rapidez = " << actual->rapidez << endl;
        actual = actual->siguiente; // pasa a siguiente elemento de la lista.


    }
    cout << "esos son todos los tipos de orcos disponibles.\n"<<endl;
}

void actualizar_tipo_orco(Lista_espesie_orcos& lista) {
    int referencia;
    cout<<"Ingresa que orco quieres actualizar= "; cin>>referencia;
    Especie_orco* actual = lista.primero_especie;
    bool encontrado = false;

    while (actual != nullptr) {
        if (actual->identificador == referencia) {
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

    if (!encontrado) {
        cout << "No se encontró ningún tipo de orco con el ID: " << referencia << ".\n";
    }
}

int main()
{
    Lista_espesie_orcos tipoEspecieOrco; // lista enlazada que contine todos los tipos de orcos.
    int opcion = 0;

    cout << "HOLA que desea hacer: " << endl;

    // menu mientras.
    do
    {
        cout << "agregar una especie orco (1) \n ";
        cout << "mostrar los tipos de orcos disponibles (2) \n";
        cout << "salir del programa (3) \n";
        cout << "Actualizar los datos de un orco (4) \n";
        cout << "coloque la opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            Crear_tipo_orco(tipoEspecieOrco);
            break;
        case 2:
            mostar_lista_orco(tipoEspecieOrco);
            break;
        case 3:
            cout << "\nsaliendo del programa \n";
            destruir_lista_especie_orco(tipoEspecieOrco);
            break;
        case 4:
            actualizar_tipo_orco(tipoEspecieOrco);
            mostar_lista_orco(tipoEspecieOrco);
            break;
        default:
            cout << "opcion no valida, la opcion " << opcion << " no esta disponible. \n";
            break;
        }
    } while (opcion != 4);

    return 0;
}
// fin del programa.
