#include <iostream> // para operaciones de entrada y salida de datos.
#include <string>   // para manejar string
#include <algorithm> // para usar .remove

using namespace std;

// --- Variables globales para el resto del programa ---
int regulador_tipo_sala = 0; // Para asignar IDs únicos a las salas
int regulador_tipo_orco = 0;
int regulador_tipo_heroe = 0;
int cantidad_implementos = 0;
int regulador_implemento = 0;
int cantidad_poderes = 0;
int regulador_poderes = 0;
int regulador_personaje_orco = 0;
int cantidad_personaje_orco = 0;
int regulador_personaje_heroe = 0;
int cantidad_personaje_heroe = 0;
int cantidad_personajes_jugar = 0;
int regulador_personajes_jugar = 0;

// --- Declaraciones adelantadas de estructuras mutuamente recursivas ---
struct Adyacencia;
struct Sala;

// Definiciones de las estructuras
struct Sala {
    string nombreSala;
    int distancia_sala; // Distancia a la siguiente sala en la lista secuencial
    int cantidadOrcos;    // Cantidad de orcos en la sala
    Adyacencia *adyacencias; // Lista de adyacencias de esta sala
    Sala*siguientesala;      // Puntero a la siguiente sala en la lista principal
    int id; // ID único para la sala
};

struct Adyacencia {
    string nombre; // Nombre de la sala adyacente
    Adyacencia * siguienteady; // Siguiente adyacencia en la lista de adyacencias de una sala
    Sala *salaAdyacente; // Puntero a la sala adyacente real
    int distancia;       // Distancia específica a esta sala adyacente
    int cantidadOrcos;   // Cantidad de orcos en esta adyacencia (o en la sala adyacente, según tu lógica)
};

struct Lista_mapa {
    Sala *actual_sala; // Puntero al primer nodo de la lista de salas
    int cantidad;      // Cantidad de salas en el mapa
};

struct Especie
{
    string nombre_especie;
    int danno_fortaleza; // Daño para orcos, Fortaleza para héroes
    int salud;
    int rapidez;
    int identificador;
    Especie *siguiente;
};

struct Lista_especie
{
    Especie *primero_especie = nullptr;
    int cantidad = 0;
};

struct Implemento
{
    string nombre_implemento;
    string tipo_implemento; // Arma/Mágico/Defensa/Consumible/Herramienta
    string uso_implemento;
    int fortalezanecesaria;
    int valor; // Daño/Cura/Protección
    int usos_restantes; // Añadido según el formato TXT
    int identificador;
    Implemento *siguiente = nullptr;
};

struct Poder_magico
{
    string nombre_poder;
    string funcion;
    int identificador;
    Poder_magico *siguiente = nullptr;
};

struct mochila{
    int identificador;
    Implemento *ipmplementos=nullptr;
    Poder_magico *poderes=nullptr;
    Sala *Mapa=nullptr; // Puntero a la sala actual del personaje, no al mapa completo
};

struct personaje
{
    mochila *mochilaa=nullptr;
    string nombre;
    Especie *tipo; // Puntero a la especie a la que pertenece
    int identificador;
    personaje *siguiente = nullptr;
};


// --- Funciones de Utilidad (definidas primero para evitar declaraciones adelantadas) ---

// Función personalizada para verificar si un caracter es un dígito
bool my_isdigit(char c) {
    return (c >= '0' && c <= '9');
}

// Función para validar y leer un entero con mensaje personalizado
int obtener_entero(const string &mensaje)
{
    string entrada;
    int valor;

    while (true)
    {
        cout << mensaje;
        getline(cin, entrada);

        bool es_valido = true;
        if (entrada.empty()) { // No permitir entrada vacía
            es_valido = false;
        } else {
            for (size_t i = 0; i < entrada.size(); ++i) {
                if (!my_isdigit(entrada[i])) { // Usar my_isdigit
                    es_valido = false;
                    break;
                }
            }
        }
        
        if (es_valido)
        {
            valor = stoi(entrada);
            return valor;
        }
        cout << "Error. Ingrese solo numeros naturales.\n";
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
    respuesta.erase(remove(respuesta.begin(), respuesta.end(), ' '), respuesta.end());

    if (respuesta.empty())
    {
        return false;
    }

    for (char caracter : respuesta)
    {
        if (my_isdigit(caracter)) // Usar my_isdigit
        {
            return false;
        }
    }
    return true;
}

// Pide y devuelve valor del string ya verificado
string devolver_string_verificada(const string &mensaje)
{
    string entrada;
    cout << mensaje;
    getline(cin, entrada);

    while (!(verificar_string(entrada)))
    {
        cout << "Formato Invalido. No ingrese numeros ni deje el campo vacio.\n";
        cout << mensaje;
        getline(cin, entrada);
    }
    return (entrada);
}

// --- Declaraciones adelantadas de funciones ---
void mostrar_implementos(Implemento& lista_imp);
void mostrar_poderes(Poder_magico &lista_poderes);
void mostrar_personajes_jugar(personaje *lista_personajes_jugar);


// --- Funciones del Mapa ---

// Función para crear una nueva sala
Sala* crearSala(string& nombre, int& distancia) {
    Sala* nuevaSala = new Sala();
    if (nuevaSala) {
        nuevaSala->id = ++regulador_tipo_sala; // Asignar un ID único automáticamente
        nuevaSala->nombreSala = nombre;
        nuevaSala->siguientesala = nullptr;
        nuevaSala->adyacencias = nullptr;
        nuevaSala->distancia_sala = distancia;
        nuevaSala->cantidadOrcos = 0;
    } else {
        cerr << "Error: No se pudo asignar memoria para la sala.\n";
    }
    return nuevaSala;
}

// Función para agregar una sala a la Lista_mapa
void AñadirSalaALista(Lista_mapa &lista_mapa, string& nombre, int& distancia) {
    Sala* nuevaSala = crearSala(nombre, distancia); // Usar la función crearSala
    if (nuevaSala) {
        if (lista_mapa.actual_sala == nullptr) {
            lista_mapa.actual_sala = nuevaSala;
        } else {
            Sala* actual = lista_mapa.actual_sala;
            while (actual->siguientesala != nullptr) {
                actual = actual->siguientesala;
            }
            actual->siguientesala = nuevaSala;
        }
        lista_mapa.cantidad++;
        cout << "Se insertó correctamente la sala: " << nombre << endl;
    } else {
        cerr << "No se pudo agregar la sala: " << nombre << endl; // Ya se imprime error en crearSala
    }
}

// Función para buscar una sala por nombre en la Lista_mapa
Sala* buscarSalaEnLista(Lista_mapa& lista_mapa, string& nombre) {
    Sala* actual = lista_mapa.actual_sala;
    while (actual != nullptr) {
        if (actual->nombreSala == nombre) {
            return actual;
        }
        actual = actual->siguientesala;
    }
    return nullptr;
}

// Función para buscar una sala por ID en la Lista_mapa
Sala* buscarSalaPorID(Lista_mapa& lista_mapa, int id) {
    Sala* actual = lista_mapa.actual_sala;
    while (actual != nullptr) {
        if (actual->id == id) {
            return actual;
        }
        actual = actual->siguientesala;
    }
    return nullptr;
}

// Función para liberar la memoria de la Lista_mapa
void liberarMapa(Lista_mapa &lista_mapa) {
    Sala* actual = lista_mapa.actual_sala;
    while (actual != nullptr) {
        Sala* siguienteSala = actual->siguientesala;

        // Liberar adyacencias de la sala actual
        Adyacencia* actualAdyacencia = actual->adyacencias;
        while (actualAdyacencia != nullptr) {
            Adyacencia* siguienteAdyacencia = actualAdyacencia->siguienteady;
            delete actualAdyacencia;
            actualAdyacencia = siguienteAdyacencia;
        }
        delete actual; // Liberar la sala
        actual = siguienteSala;
    }
    lista_mapa.actual_sala = nullptr; // Asegura que el puntero se pone a null
    lista_mapa.cantidad = 0;             // y la cantidad a 0
}

// Función para mostrar el mapa usando Lista_mapa
void MostrarMapa(const Lista_mapa& lista_mapa) {
    Sala* actual = lista_mapa.actual_sala;
    if (actual == nullptr) {
        cout << "El mapa está vacío." << endl;
        return;
    }
    cout << "Contenido del Mapa:" << endl;
    while (actual != nullptr) {
        cout << "Sala ID: " << actual->id << ", Nombre: " << actual->nombreSala;

        if (actual->siguientesala != nullptr) {
            cout << " (Distancia de salida: " << actual->distancia_sala << " a " << actual->siguientesala->nombreSala << ")";
        } else {
            cout << " (Última sala en la secuencia)";
        }

        cout << ", Orcos en sala: " << actual->cantidadOrcos;

        if (actual->adyacencias != nullptr) {
            cout << " -> Adyacencias: ";
            Adyacencia* adyacente = actual->adyacencias;
            while (adyacente != nullptr) {
                if (adyacente->salaAdyacente != nullptr) {
                    cout << adyacente->nombre << " (Dist: " << adyacente->distancia << ", Orcos: " << adyacente->cantidadOrcos << ")";
                } else {
                    cout << " (Adyacencia inválida - Sala adyacente nula)";
                }

                if (adyacente->siguienteady != nullptr) {
                    cout << ", ";
                }
                adyacente = adyacente->siguienteady;
            }
        } else {
            cout << " -> No tiene adyacencias directas.";
        }
        cout << endl;
        actual = actual->siguientesala;
    }
}

// Función para modificar una sala
void Modificarsala(Lista_mapa &lista_mapa) {
    if (lista_mapa.actual_sala == nullptr) {
        cout << "El mapa se encuentra vacío por los momentos" << endl;
        return;
    }

    string nombreSala = devolver_string_verificada("Ingrese el nombre de la sala que va a modificar: ");
    Sala* salaAModificar = buscarSalaEnLista(lista_mapa, nombreSala);

    if (salaAModificar != nullptr) {
        cout << "Nombre actual de la sala: " << salaAModificar->nombreSala << endl;
        string nuevoNombre = devolver_string_verificada("Ingrese el nuevo nombre de la sala: ");
        salaAModificar->nombreSala = nuevoNombre;
        cout << "La sala ha sido modificada" << endl;
    } else {
        cout << "La sala no ha sido encontrada" << endl;
    }
}

// Función para agregar una adyacencia
void AgregarAdyacencia(Lista_mapa& lista_mapa, const string& nombreSala, const string& nombreAdyacente, int distancia, int cantidadOrcos) {
    string temp_nombreSala = nombreSala;
    string temp_nombreAdyacente = nombreAdyacente;

    Sala* sala = buscarSalaEnLista(lista_mapa, temp_nombreSala);
    Sala* salaAdy = buscarSalaEnLista(lista_mapa, temp_nombreAdyacente);

    if (sala == nullptr || salaAdy == nullptr) {
        cout << "Una o ambas salas no existen." << endl;
        return;
    }

    // Verificar si la adyacencia ya existe para evitar duplicados
    Adyacencia* checkAdy = sala->adyacencias;
    while(checkAdy != nullptr) {
        if (checkAdy->salaAdyacente == salaAdy) {
            cout << "La adyacencia entre " << nombreSala << " y " << nombreAdyacente << " ya existe.\n";
            return;
        }
        checkAdy = checkAdy->siguienteady;
    }

    Adyacencia* nuevaAdyacencia1 = new Adyacencia();
    if (nuevaAdyacencia1) {
        nuevaAdyacencia1->nombre = nombreAdyacente;
        nuevaAdyacencia1->distancia = distancia;
        nuevaAdyacencia1->cantidadOrcos = cantidadOrcos;
        nuevaAdyacencia1->salaAdyacente = salaAdy;
        nuevaAdyacencia1->siguienteady = sala->adyacencias;
        sala->adyacencias = nuevaAdyacencia1;
    } else {
        cerr << "Error: No se pudo asignar memoria para la adyacencia.\n";
        return;
    }

    Adyacencia* nuevaAdyacencia2 = new Adyacencia();
    if (nuevaAdyacencia2) {
        nuevaAdyacencia2->nombre = nombreSala;
        nuevaAdyacencia2->distancia = distancia;
        nuevaAdyacencia2->cantidadOrcos = cantidadOrcos;
        nuevaAdyacencia2->salaAdyacente = sala;
        nuevaAdyacencia2->siguienteady = salaAdy->adyacencias;
        salaAdy->adyacencias = nuevaAdyacencia2;
    } else {
        cerr << "Error: No se pudo asignar memoria para la adyacencia.\n";
        delete nuevaAdyacencia1;
        return;
    }

    cout << "Adyacencia agregada entre " << nombreSala << " y " << nombreAdyacente << endl;
}

void EliminarSala(Lista_mapa &lista_mapa, string nombresala) {
    if (lista_mapa.actual_sala == nullptr) {
        cout << "El mapa se encuentra vacío por los momentos" << endl;
        return;
    }

    Sala* salaAEliminar = nullptr;
    Sala* actual = lista_mapa.actual_sala;
    Sala* anterior = nullptr;

    while (actual != nullptr && actual->nombreSala != nombresala) {
        anterior = actual;
        actual = actual->siguientesala;
    }

    salaAEliminar = actual;

    if (salaAEliminar == nullptr) {
        cout << "La sala que desea eliminar no existe." << endl;
        return;
    }

    if (anterior == nullptr) {
        lista_mapa.actual_sala = salaAEliminar->siguientesala;
    } else {
        anterior->siguientesala = salaAEliminar->siguientesala;
    }

    Adyacencia* currentAdy = salaAEliminar->adyacencias;
    while (currentAdy != nullptr) {
        Adyacencia* nextAdy = currentAdy->siguienteady;
        delete currentAdy;
        currentAdy = nextAdy;
    }
    salaAEliminar->adyacencias = nullptr;

    Sala* recorrerMapa = lista_mapa.actual_sala;
    while (recorrerMapa != nullptr) {
        Adyacencia* adyacenciaActual = recorrerMapa->adyacencias;
        Adyacencia* adyacenciaAnterior = nullptr;
        while (adyacenciaActual != nullptr) {
            if (adyacenciaActual->salaAdyacente == salaAEliminar) {
                if (adyacenciaAnterior == nullptr) {
                    recorrerMapa->adyacencias = adyacenciaActual->siguienteady;
                } else {
                    adyacenciaAnterior->siguienteady = adyacenciaActual->siguienteady;
                }
                Adyacencia* tempAdy = adyacenciaActual;
                adyacenciaActual = adyacenciaActual->siguienteady;
                delete tempAdy;
            } else {
                adyacenciaAnterior = adyacenciaActual;
                adyacenciaActual = adyacenciaActual->siguienteady;
            }
        }
        recorrerMapa = recorrerMapa->siguientesala;
    }

    delete salaAEliminar;
    lista_mapa.cantidad--;
    cout << "La sala: " << nombresala << " se ha eliminado correctamente." << endl;
}

// Funciones de Especies
void destruir_lista_especie(Lista_especie &lista)
{
    Especie *actual = lista.primero_especie;
    while (actual != nullptr)
    {
        Especie *eliminar = actual;
        actual = actual->siguiente;
        delete eliminar;
    }
    lista.primero_especie = nullptr;
    lista.cantidad = 0;
}

void Crear_tipo(Lista_especie &lista, int tipo)
{
    Especie *nuevo = new Especie();

    if (tipo == 1) {
        cout << "\nIngrese los datos para la nueva especie de Orco: \n";
    } else if (tipo == 2) {
        cout << "\nIngrese los datos para la nueva especie de Heroe: \n";
    } else {
        cout << "ERROR. TIPO NO ESPECIFICADO. VERIFICAR NUMERO QUE SE LE PUSO A LA FUNCION CREAR_TIPO \n";
    }

    nuevo->nombre_especie = devolver_string_verificada("Nombre de la especie: ");
    if (tipo == 1) {
        nuevo->danno_fortaleza = obtener_entero("Danno: ");
    } else if (tipo == 2) {
        nuevo->danno_fortaleza = obtener_entero("Fortaleza: ");
    } else {
        cout << "ERROR. TIPO NO ESPECIFICADO. VERIFICAR NUMERO QUE SE LE PUSO A LA FUNCION CREAR_TIPO \n";
    }
    nuevo->salud = obtener_entero("Salud: ");
    nuevo->rapidez = obtener_entero("Rapidez: ");
    cout << endl;

    nuevo->siguiente = lista.primero_especie;
    lista.primero_especie = nuevo;
    lista.cantidad = lista.cantidad + 1;

    if (tipo == 1) {
        nuevo->identificador = (lista.cantidad + regulador_tipo_orco);
        cout << "Especie de orco " << nuevo->nombre_especie << " ha sido agregada exitosamente. \n";
    } else {
        nuevo->identificador = (lista.cantidad + regulador_tipo_heroe);
        cout << "Especie de heroe " << nuevo->nombre_especie << " ha sido agregada exitosamente. \n";
    }
}

void mostrar_lista(Lista_especie &lista, int tipo)
{
    if (lista.cantidad == 0) {
        cout << "No hay tipos de Orcos disponibles. \n\n";
        return;
    }

    if (tipo == 1) {
        cout << "\nHay [" << lista.cantidad << "] tipos de orcos disponibles" << endl;
    } else {
        cout << "\nHay [" << lista.cantidad << "] tipos de heroes disponibles" << endl;
    }
    Especie *actual = lista.primero_especie;
    while (actual != nullptr) {
        cout << actual->identificador << "-";
        cout << "Nombre= " << actual->nombre_especie << endl;
        if (tipo == 1) {
            cout << "Danno = " << actual->danno_fortaleza << endl;
        } else {
            cout << "fortaleza = " << actual->danno_fortaleza << endl;
        }
        cout << "Salud = " << actual->salud << endl;
        cout << "Rapidez = " << actual->rapidez << "\n" << endl;
        actual = actual->siguiente;
    }
    cout << "No hay mas tipos disponibles.\n" << endl;
}

void actualizar_tipo(Lista_especie &lista, int tipo)
{
    if (lista.cantidad == 0) {
        cout << "La lista se encuentra vacia.\n\n";
        return;
    }

    int referencia;
    cout << "\nLos tipos de especie disponible son: ";
    cout << "------------------------" << endl;
    mostrar_lista(lista, tipo);
    if (tipo == 1) {
        referencia = obtener_entero("Ingrese el numero del tipo de orco que desea modificar: ");
    } else if (tipo == 2) {
        referencia = obtener_entero("ingrese el numero del tipo de heroe que desea modificar: ");
    } else {
        cout << "ERROR. VERIFICAR CODIGO. ACTUALIZAR_TIPO" << endl;
    }
    Especie *actual = lista.primero_especie;
    bool encontrado = false;

    while (actual != nullptr) {
        if (actual->identificador == referencia) {
            if (tipo == 1) {
                cout << "\nIngrese los datos a actualizar para el orco con identificador " << referencia << ":\n";
            } else {
                cout << "\nIngrese los datos a actualizar para el heroe con identificador " << referencia << ":\n";
            }

            actual->nombre_especie = devolver_string_verificada("Nombre de la especie: ");
            if (tipo == 1) {
                actual->danno_fortaleza = obtener_entero("Danno: ");
            } else {
                actual->danno_fortaleza = obtener_entero("Fortaleza: ");
            }
            actual->salud = obtener_entero("Salud: ");
            actual->rapidez = obtener_entero("Rapidez: ");

            if (tipo == 1) {
                cout << "Datos del orco con ID " << referencia << " actualizados exitosamente.\n";
            } else {
                cout << "Datos del heroe con ID " << referencia << " actualizados exitosamente.\n";
            }
            encontrado = true;
            break;
        }
        actual = actual->siguiente;
    }

    if (!encontrado) {
        cout << "No se encontró ningún tipo de orco con el ID: " << referencia << ".\n";
        cout << "Actualizacion fallida \n";
    }
}

// Funciones de Personajes
Especie *encontrar_especie(Lista_especie &lista, int identificador)
{
    Especie *actual = lista.primero_especie;
    while (actual != nullptr) {
        if (actual->identificador == identificador) {
            return actual;
        }
        actual = actual->siguiente;
    }
    cout << "La especie ingresada no existe." << endl;
    return nullptr;
}

personaje *encontar_personaje(personaje &lista_personajes, int identificador){
    personaje *actual = lista_personajes.siguiente;
    while (actual != nullptr){
        if (actual->identificador == identificador){
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

void crear_personaje(personaje &lista_personaje, Lista_especie &lista_tipos, int tipo)
{
    if (lista_tipos.cantidad == 0) {
        cout << "Todavia no hay especies disponibles. Debe crearlas antes de crear un personaje." << endl;
        return;
    } else {
        personaje *nuevo = new personaje;
        if (!nuevo) {
            cerr << "Error: No se pudo asignar memoria para el personaje.\n";
            return;
        }
        int num_tipo = 0;
        Especie *puntero_especie = nullptr;

        if (tipo == 1) {
            cout << "Indique los datos para el nuevo personaje Orco." << endl;
            nuevo->nombre = devolver_string_verificada("Nombre: ");
            cout << "Ingrese la especie al que pertenecerá el Orco " << nuevo->nombre << "\n";
            cout << "Especies disponibles: " << endl;
            mostrar_lista(lista_tipos, tipo);
            num_tipo = obtener_entero("Ingrese la especie del Orco: ");
            puntero_especie = encontrar_especie(lista_tipos, num_tipo);
        } else {
            cout << "Indique los datos para el nuevo personaje Heroe. " << endl;
            nuevo->nombre = devolver_string_verificada("Nombre: ");
            cout << "Ingrese la especie al que pertenecerá el Heroe " << nuevo->nombre << "\n";
            cout << "Especies disponibles: " << endl;
            mostrar_lista(lista_tipos, tipo);
            num_tipo = obtener_entero("Ingrese la especie del Personaje: ");
            puntero_especie = encontrar_especie(lista_tipos, num_tipo);
        }

        if (puntero_especie == nullptr) {
            cout << "La especie debe crearse primero." << endl;
            cout << "Creacion del personaje: " << nuevo->nombre << " fue fallida." << endl;
            delete nuevo;
            return;
        } else {
            nuevo->tipo = puntero_especie;
        }
        nuevo->siguiente = lista_personaje.siguiente;
        lista_personaje.siguiente = nuevo;

        if (tipo == 1) {
            cantidad_personaje_orco += 1;
            nuevo->identificador = (cantidad_personaje_orco + regulador_personaje_orco);
            cout << "El orco: " << nuevo->nombre << ", se agrego correctamente." << endl;
        } else {
            cantidad_personaje_heroe += 1;
            nuevo->identificador = (cantidad_personaje_heroe + regulador_personaje_heroe);
            cout << "El heroe: " << nuevo->nombre << ", se agrego correctamente." << endl;
        }
    }
}

void destruir_lista_personajes(personaje &lista)
{
    personaje *actual = lista.siguiente;
    while (actual != nullptr) {
        personaje *eliminar = actual;
        actual = actual->siguiente;
        delete eliminar;
    }
    lista.siguiente = nullptr;
}

void mostrar_personajes(personaje &lista, int tipo)
{
    if (tipo == 1) {
        if (cantidad_personaje_orco == 0) {
            cout << "\nNo hay personajes orcos para mostrar actualmente.\n";
            cout << "Primero debe crearlos.\n";
            return;
        }
    } else {
        if (cantidad_personaje_heroe == 0) {
            cout << "\nNo hay personajes heroes para mostrar actualmente.\n";
            cout << "Primero debe crearlos.\n";
            return;
        }
    }

    if (tipo == 1) {
        cout << "\nHay [" << cantidad_personaje_orco << "] personajes orcos" << endl; // Usando variable global
    } else {
        cout << "\nHay [" << cantidad_personaje_heroe << "] personajes heroes" << endl; // Usando variable global
    }
    personaje *actual = lista.siguiente;
    while (actual != nullptr) {
        cout << actual->identificador << "-";
        cout << "Nombre= " << actual->nombre << endl;
        cout << "Especie= " << actual->tipo->nombre_especie << endl;
        cout << endl;
        actual = actual->siguiente;
    }
    cout << "No hay mas personajes.\n" << endl;
}

void actualizar_personaje(personaje &lista, Lista_especie lista_tipo, int tipo)
{
    // La condición lista.cantidad == 0 es para Lista_especie, no para personaje.
    // Usamos las variables globales de cantidad_personaje_orco/heroe.
    if (tipo == 1) {
        if (cantidad_personaje_orco == 0) { // Usando variable global
            cout << "\nNo hay personajes orcos para modificar actualmente.\n";
            cout << "Primero debe crearlos.\n";
            return;
        }
    } else {
        if (cantidad_personaje_heroe == 0) { // Usando variable global
            cout << "\nNo hay personajes heroes para modificar actualmente.\n";
            cout << "Primero debe crearlos.\n";
            return;
        }
    }
    int identificador_tipo = 0;
    int referencia;
    Especie *especie_nueva = nullptr;

    cout << "Los personajes disponibles son: \n";
    mostrar_personajes(lista, tipo);

    referencia = obtener_entero("Ingrese el numero del personaje que desea modificar: ");

    personaje *actual = lista.siguiente;
    bool encontrado = false;

    while (actual != nullptr) {
        if (actual->identificador == referencia) {
            encontrado = true;
            cout << "ingrese los datos para actualizar al personaje " << actual->nombre << endl;

            actual->nombre = devolver_string_verificada("Nombre del personaje: ");

            cout << "\n Coloque el nuevo tipo de de especie al que pertenecerá el personje \n";
            cout << "\n Tipos disponibles son: " << endl;
            cout << "------------------------" << endl;
            mostrar_lista(lista_tipo, tipo);

            identificador_tipo = obtener_entero("Coloque el numero del tipo del personaje: ");
            especie_nueva = encontrar_especie(lista_tipo, identificador_tipo);

            if (especie_nueva == nullptr) {
                cout << "La que coloco no se encuentra disponible." << endl;
                cout << "La actualiacion del personaje: " << actual->nombre << " fue fallida." << endl;
                return;
            } else {
                actual->tipo = especie_nueva;
                cout << "El personaje ahora de nombre: " << actual->nombre << " se actualizo correctamente." << endl;
            }
            break;
        }
        actual = actual->siguiente;
    }
    if (!encontrado) {
        cout << "No se encontró ningún personaje con el ID: " << referencia << ".\n";
        cout << "Actualizacion fallida.\n";
    }
}

void borrar_personaje(personaje &lista, int tipo){
    if (tipo == 1) {
        if (cantidad_personaje_orco == 0) {
            cout << "\nNo hay personajes orcos para eliminar actualmente.\n";
            cout << "Primero debe crearlos.\n";
            return;
        }
    } else {
        if (cantidad_personaje_heroe == 0) {
            cout << "\nNo hay personajes heroes para eliminar actualmente.\n";
            cout << "Primero debe crearlos.\n";
            return;
        }
    }

    int identificador = 0;
    personaje *actual = lista.siguiente;
    personaje *anterior = nullptr;

    cout << "Los personajes disponibles son: \n";
    mostrar_personajes(lista,tipo);
    identificador = obtener_entero("Coloque el numero del personaje a eliminar: ");

    if (actual != nullptr && actual->identificador == identificador){
        lista.siguiente = actual->siguiente;
        cout << "El personaje: " << actual->nombre << " fue borrado exitosamente." << endl;
        delete actual;
        if (tipo == 1){
            regulador_personaje_orco +=1;
            cantidad_personaje_orco -=1;
        }else{
            regulador_personaje_heroe +=1;
            cantidad_personaje_heroe -=1;
        }
        return;
    }

    while (actual != nullptr && actual->identificador != identificador){
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual != nullptr){
        personaje *eliminar = actual;
        anterior->siguiente = actual->siguiente;
        cout << "El personaje " << eliminar->nombre << " se elimino correctamente.\n";
        delete eliminar;

        if (tipo == 1){
            regulador_personaje_orco +=1;
            cantidad_personaje_orco -=1;
        } else {
            regulador_personaje_heroe +=1;
            cantidad_personaje_heroe -=1;
        }
    }else{
        cout << "El numero de personaje: " << identificador << " no se encuentra en la lista.\n";
        cout << "Eliminacion fallida.\n";
    }
}

void borrar_personajes_de_tipo(personaje &lista_personajes, Especie *especie_a_borrar, int tipo) {
    personaje *actual = lista_personajes.siguiente;
    personaje *anterior = &lista_personajes;

    while (actual != nullptr) {
        if (actual->tipo == especie_a_borrar) {
            personaje *eliminar = actual;
            anterior->siguiente = actual->siguiente;
            cout << "Eliminando personaje '" << eliminar->nombre << "' de la especie '" << especie_a_borrar->nombre_especie << "'.\n";
            if (eliminar->mochilaa != nullptr) {
                Implemento *current_imp = eliminar->mochilaa->ipmplementos;
                while(current_imp != nullptr) {
                    Implemento *next_imp = current_imp->siguiente;
                    delete current_imp;
                    current_imp = next_imp;
                }
                Poder_magico *current_poder = eliminar->mochilaa->poderes;
                while(current_poder != nullptr) {
                    Poder_magico *next_poder = current_poder->siguiente;
                    delete current_poder;
                    current_poder = next_poder;
                }
                delete eliminar->mochilaa;
            }
            delete eliminar;

            if (tipo == 1) {
                cantidad_personaje_orco--;
                regulador_personaje_orco++;
            } else {
                cantidad_personaje_heroe--;
                regulador_personaje_heroe++;
            }
            actual = anterior->siguiente;
        } else {
            anterior = actual;
            actual = actual->siguiente;
        }
    }
}

void eliminar_elemento_lista(Lista_especie &lista_especie, personaje &lista_personajes, int tipo) {
    if (lista_especie.cantidad == 0) {
        cout << "No hay tipos de especie para eliminar.\n";
        return;
    }

    mostrar_lista(lista_especie, tipo);
    int id_especie_a_eliminar = obtener_entero("Ingrese el ID del tipo de especie a eliminar: ");

    Especie *actual_especie = lista_especie.primero_especie;
    Especie *anterior_especie = nullptr;
    Especie *especie_a_borrar = nullptr;

    while (actual_especie != nullptr && actual_especie->identificador != id_especie_a_eliminar) {
        anterior_especie = actual_especie;
        actual_especie = actual_especie->siguiente;
    }

    especie_a_borrar = actual_especie;

    if (especie_a_borrar == nullptr) {
        cout << "El ID de especie no fue encontrado.\n";
        return;
    }

    if (anterior_especie == nullptr) {
        lista_especie.primero_especie = especie_a_borrar->siguiente;
    } else {
        anterior_especie->siguiente = especie_a_borrar->siguiente;
    }

    if (tipo == 1) {
        regulador_tipo_orco++;
    } else {
        regulador_tipo_heroe++;
    }
    lista_especie.cantidad--;

    cout << "Especie '" << especie_a_borrar->nombre_especie << "' eliminada correctamente.\n";

    borrar_personajes_de_tipo(lista_personajes, especie_a_borrar, tipo);

    delete especie_a_borrar;
}


// Funciones de Implementos
Implemento *buscar_implemento(Implemento &Implementos, int identificador) {
    Implemento *actual = Implementos.siguiente;
    while (actual != nullptr) {
        if (actual->identificador == identificador) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

void crear_implemento(Implemento& lista_imp) {
    Implemento* nuevo = new Implemento();
    if (!nuevo) {
        cerr << "Error: No se pudo asignar memoria para el implemento.\n";
        return;
    }

    nuevo->nombre_implemento = devolver_string_verificada("Nombre del implemento: ");
    nuevo->tipo_implemento = devolver_string_verificada("Tipo de implemento: ");
    nuevo->uso_implemento = devolver_string_verificada("Uso del implemento: ");
    nuevo->fortalezanecesaria = obtener_entero("Fortaleza necesaria: ");
    nuevo->valor = obtener_entero("Valor: ");
    nuevo->usos_restantes = obtener_entero("Usos restantes: "); // Añadido para coincidir con la estructura TXT

    cantidad_implementos++;
    nuevo->identificador = cantidad_implementos + regulador_implemento;

    nuevo->siguiente = lista_imp.siguiente;
    lista_imp.siguiente = nuevo;

    cout << "Implemento '" << nuevo->nombre_implemento << "' agregado correctamente.\n";
}

void modificar_implemento(Implemento& lista_imp) {
    if (cantidad_implementos == 0) {
        cout << "No hay implementos disponibles para modificar.\n";
        return;
    }
    mostrar_implementos(lista_imp);
    int id = obtener_entero("Ingrese el ID del implemento a modificar: ");
    Implemento* imp = buscar_implemento(lista_imp, id);

    if (imp) {
        cout << "Modificando implemento: " << imp->nombre_implemento << endl;
        imp->nombre_implemento = devolver_string_verificada("Nuevo nombre: ");
        imp->tipo_implemento = devolver_string_verificada("Nuevo tipo: ");
        imp->uso_implemento = devolver_string_verificada("Nuevo uso: ");
        imp->fortalezanecesaria = obtener_entero("Nueva fortaleza necesaria: ");
        imp->valor = obtener_entero("Nuevo valor: ");
        imp->usos_restantes = obtener_entero("Nuevos usos restantes: "); // Añadido
        cout << "Implemento modificado correctamente.\n";
    } else {
        cout << "Implemento con ID " << id << " no encontrado.\n";
    }
}

void mostrar_implementos(Implemento& lista_imp) {
    if (cantidad_implementos == 0) {
        cout << "No hay implementos disponibles.\n";
        return;
    }
    cout << "\n--- Lista de Implementos ---\n";
    Implemento* actual = lista_imp.siguiente;
    while (actual != nullptr) {
        cout << "ID: " << actual->identificador << endl;
        cout << "Nombre: " << actual->nombre_implemento << endl;
        cout << "Tipo: " << actual->tipo_implemento << endl;
        cout << "Uso: " << actual->uso_implemento << endl;
        cout << "Fortaleza Necesaria: " << actual->fortalezanecesaria << endl;
        cout << "Valor: " << actual->valor << endl;
        cout << "Usos Restantes: " << actual->usos_restantes << endl << endl; // Añadido
        actual = actual->siguiente;
    }
}

void borrar_implementos(Implemento& lista_imp) {
    if (cantidad_implementos == 0) {
        cout << "No hay implementos para eliminar.\n";
        return;
    }
    mostrar_implementos(lista_imp);
    int id = obtener_entero("Ingrese el ID del implemento a eliminar: ");

    Implemento* actual = lista_imp.siguiente;
    Implemento* anterior = &lista_imp;

    while (actual != nullptr && actual->identificador != id) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual != nullptr) {
        anterior->siguiente = actual->siguiente;
        cout << "Implemento '" << actual->nombre_implemento << "' eliminado correctamente.\n";
        delete actual;
        cantidad_implementos--;
        regulador_implemento++;
    } else {
        cout << "Implemento con ID " << id << " no encontrado.\n";
    }
}

void destruir_implementos(Implemento& lista) {
    Implemento* actual = lista.siguiente;
    while (actual != nullptr) {
        Implemento* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
    lista.siguiente = nullptr;
    cantidad_implementos = 0;
    regulador_implemento = 0;
}

// Funciones de Poderes Mágicos
Poder_magico *encontar_poder(Poder_magico &lista_poderes, int identificador){
    Poder_magico *encontrar = lista_poderes.siguiente;
    while ((encontrar != nullptr) && (encontrar->identificador != identificador)){
        encontrar = encontrar->siguiente;
    }
    if (encontrar != nullptr && encontrar->identificador == identificador){
        return encontrar;
    } else {
        return nullptr;
    }
}

void crear_poder(Poder_magico& lista_poder) {
    Poder_magico* nuevo = new Poder_magico();
    if (!nuevo) {
        cerr << "Error: No se pudo asignar memoria para el poder mágico.\n";
        return;
    }

    nuevo->nombre_poder = devolver_string_verificada("Nombre del poder: ");
    nuevo->funcion = devolver_string_verificada("Función del poder: ");

    cantidad_poderes++;
    nuevo->identificador = cantidad_poderes + regulador_poderes;

    nuevo->siguiente = lista_poder.siguiente;
    lista_poder.siguiente = nuevo;

    cout << "Poder mágico '" << nuevo->nombre_poder << "' agregado correctamente.\n";
}

void mostrar_poderes(Poder_magico &lista_poderes){
    if (cantidad_poderes == 0){
        cout << "No hay poderes mágicos disponibles para mostrar.\n";
        return;
    }
    Poder_magico *actual = lista_poderes.siguiente;
    cout << "La cantidad de poderes actualmente es: " << cantidad_poderes <<endl<<endl;
    while (actual != nullptr){
        cout << "Nombre: " << actual->nombre_poder <<endl;
        cout << "ID: " << actual->identificador <<endl;
        cout << "Funcion: " << actual->funcion <<endl<<endl;
        actual= actual->siguiente;
    }
    cout << "No hay mas poderes disponibles.\n";
}

void modificar_poder(Poder_magico &lista_poderes){
    if (cantidad_poderes == 0){
        cout << "No hay poderes mágicos disponibles para modificar.\n";
        return;
    }
    int identificador=0;
    Poder_magico *actualizar = nullptr;
    cout << "Los poderes disponibles son: \n";
    mostrar_poderes(lista_poderes);
    identificador = obtener_entero("Coloque el ID del poder mágico que desea modificar: ");
    actualizar = encontar_poder(lista_poderes, identificador);
    if (actualizar == nullptr){
        cout << "El ID que coloco no existe. \n";
        cout << "Modificacion fallida.\n";
        return;
    }
    cout << "Proceda a actualizar el poder: " << actualizar->nombre_poder<<endl;
    actualizar->nombre_poder = devolver_string_verificada("Nombre: ");
    actualizar->funcion = devolver_string_verificada("Funcion: ");

    cout << "Poder mágico: " <<actualizar->nombre_poder << " actualizado correctamente.\n";
}

void eliminar_poder(Poder_magico &lista_poder){
    if (cantidad_poderes == 0){
        cout << "No hay poderes mágicos disponibles para eliminar. \n";
        cout << "Eliminacion fallida. \n";
        return;
    }
    int identificador = 0;
    Poder_magico *validar = nullptr;
    cout << "Los poderes mágicos disponibles son: \n";
    mostrar_poderes(lista_poder);
    identificador = obtener_entero("Coloque el ID del poder que desea eliminar: ");
    validar = encontar_poder(lista_poder, identificador);
    if (validar == nullptr){
        cout << "El ID que coloco no existe.\n";
        cout << "Eliminacion fallida.\n";
        return;
    }
    Poder_magico *actual = lista_poder.siguiente;
    Poder_magico *anterior = nullptr;
    if (actual->identificador == identificador){
        lista_poder.siguiente = actual->siguiente;
        cout << "El poder mágico: " << actual->nombre_poder << " se eliminó correctamente.\n";
        delete actual;
        cantidad_poderes -=1;
        regulador_poderes +=1;
        return;
    }
    while ((actual != nullptr) && (actual->identificador != identificador)){
        anterior = actual;
        actual = actual->siguiente;
    }
    Poder_magico *eliminar = actual;
    anterior->siguiente = actual->siguiente;
    cout << "El poder mágico: " << eliminar->nombre_poder << " se eliminó correctamente.\n";
    delete eliminar;
    cantidad_poderes -=1;
    regulador_poderes +=1;
}

void destruir_poder_magico(Poder_magico& lista) {
    Poder_magico* actual = lista.siguiente;
    while (actual != nullptr) {
        Poder_magico* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
    lista.siguiente = nullptr;
    cantidad_poderes = 0;
    regulador_poderes = 0;
}

// Funciones de Personajes para Jugar (Equipo)
void llenar_mochila(personaje *&personaje_a_llenar, Implemento &Implementos, Poder_magico &poderes){
    int opcio = 0;
    int cantidad_objetos = 0;
    int contrilador_interno = 0;
    cout << "Puedes escoger maximo 5 objetos, poderes magicos o implementos. \n";
    do
    {
        cout << "Llevas " << cantidad_objetos << " objetos en tu mochila.\n";
        cout << "Que objeto deseas agregar.\n";
        cout << "1. Implemento.\n";
        cout << "2. Poderes magicos.\n";
        cout << "3. Salir.\n";
        opcio = obtener_entero("");
        if (opcio == 1){
            Implemento *nuevo_implemento = nullptr;
            do
            {
                cout << "Los implementos disponibles son:\n";
                mostrar_implementos(Implementos);
                int identificador = obtener_entero("Coloque el ID del implemento que desea colocar: ");
                nuevo_implemento = buscar_implemento(Implementos,identificador);
                if (nuevo_implemento == nullptr){
                    cout << "El ID: " << identificador << " no existe.\n";
                    cout << "Coloque uno valido.\n";
                } else{
                    contrilador_interno = 1;
                }
            } while (contrilador_interno != 1);
            Implemento *colocar = new Implemento;
            if (!colocar) {
                cerr << "Error: No se pudo asignar memoria para el implemento en mochila.\n";
                break;
            }
            *colocar = *nuevo_implemento;
            colocar->siguiente = personaje_a_llenar->mochilaa->ipmplementos;
            personaje_a_llenar->mochilaa->ipmplementos = colocar;
            cantidad_objetos += 1;
            contrilador_interno =0;
            cout << "El implemento "<< colocar->nombre_implemento << " se agrego correctamente a la mochila.\n";

        }else if (opcio == 2){
            Poder_magico *nuevo_poder = nullptr;
            do
            {
                cout << "Los poderes magicos disponibles son:\n";
                mostrar_poderes(poderes);
                int identificador = obtener_entero("Coloque el ID del poder que desea colocar: ");
                nuevo_poder = encontar_poder(poderes,identificador);
                if (nuevo_poder == nullptr){
                    cout << "El ID: " << identificador << " no existe.\n";
                    cout << "Coloque uno valido.\n";
                } else{
                    contrilador_interno = 1;
                }
            } while (contrilador_interno != 1);
            Poder_magico *colocar = new Poder_magico;
            if (!colocar) {
                cerr << "Error: No se pudo asignar memoria para el poder en mochila.\n";
                break;
            }
            *colocar = *nuevo_poder;
            colocar->siguiente = personaje_a_llenar->mochilaa->poderes;
            personaje_a_llenar->mochilaa->poderes = colocar;
            cantidad_objetos +=1;
            contrilador_interno=0;
            cout << "El poder "<< colocar->nombre_poder << " se agrego correctamente a la mochila.\n";

        }else if (opcio == 3){
            cout << "La cantidad de objetos que coloco fue: " <<cantidad_objetos<<endl;

        }else {
            cout << "Opcion invalida, el numero "<<opcio<<" no es una opcion valida.\n";
        }

    } while ((opcio != 3) && (cantidad_objetos !=5));
    if (cantidad_objetos == 5){
        cout << "Ya no puedes agregar mas objetos.\n";
        cout << "La mochila del personaje " << personaje_a_llenar->nombre << " se lleno correctamente. ";
    }
}

void eleccio_personaje(personaje *&lista_jugar, personaje &heroes, Implemento &implementos, Poder_magico &poderes) {
    if (cantidad_personaje_heroe <= 0) {
        cout << "No hay heroes disponibles para elegir.\n";
        cout << "Eleccion de personaje fallida.\n";
        return;
    }
    if (cantidad_personajes_jugar == 4) {
        cout << "Ya tienes la cantidad de personajes máxima.\n";
        return;
    }

    int identificador;
    personaje *seleccionado = nullptr;

    cout << "Los heroes disponibles son: \n";
    mostrar_personajes(heroes, 2);
    identificador = obtener_entero("Coloque el ID del heroe que desea agregar al equipo: ");

    seleccionado = encontar_personaje(heroes, identificador);

    if (seleccionado == nullptr) {
        cout << "El ID: " << identificador << " no existe.\n";
        cout << "Eleccion de personaje fallida.\n";
        return;
    }
    personaje* temp_check = lista_jugar;
    while(temp_check != nullptr) {
        if(temp_check->nombre == seleccionado->nombre && temp_check->tipo == seleccionado->tipo) {
            cout << "El personaje '" << seleccionado->nombre << "' ya está en el equipo.\n";
            cout << "Eleccion de personaje fallida.\n";
            return;
        }
        temp_check = temp_check->siguiente;
    }


    cantidad_personajes_jugar +=1;
    personaje *nuevo_para_jugar = new personaje;
    if (!nuevo_para_jugar) {
        cerr << "Error: No se pudo asignar memoria para el personaje a jugar.\n";
        cantidad_personajes_jugar--;
        return;
    }
    nuevo_para_jugar->nombre = seleccionado->nombre;
    nuevo_para_jugar->tipo = seleccionado->tipo;
    nuevo_para_jugar->identificador = cantidad_personajes_jugar + regulador_personajes_jugar;
    nuevo_para_jugar->mochilaa = new mochila;
    if (!nuevo_para_jugar->mochilaa) {
        cerr << "Error: No se pudo asignar memoria para la mochila del personaje a jugar.\n";
        delete nuevo_para_jugar;
        cantidad_personajes_jugar--;
        return;
    }
    nuevo_para_jugar->mochilaa->ipmplementos = nullptr;
    nuevo_para_jugar->mochilaa->poderes = nullptr;
    nuevo_para_jugar->mochilaa->identificador = nuevo_para_jugar->identificador;
    nuevo_para_jugar->mochilaa->Mapa = nullptr;
    nuevo_para_jugar->siguiente = nullptr;

    cout << "Proceda a llenar la mochila del personaje: " << nuevo_para_jugar->nombre << endl << endl;
    llenar_mochila(nuevo_para_jugar, implementos, poderes);


    if (lista_jugar == nullptr) {
        lista_jugar = nuevo_para_jugar;
    } else {
        personaje *ultimo = lista_jugar;
        while (ultimo->siguiente != nullptr) {
            ultimo = ultimo->siguiente;
        }
        ultimo->siguiente = nuevo_para_jugar;
    }
    cout << "El heroe " << nuevo_para_jugar->nombre << " se agregó al equipo.\n";
}

void mostrar_personajes_jugar(personaje *lista_personajes_jugar) {
    personaje *actual_personaje = lista_personajes_jugar;
    if (actual_personaje == nullptr) {
        cout << "No hay personajes en el equipo para mostrar.\n";
        return;
    }
    while (actual_personaje != nullptr) {
        cout << "Nombre: " << actual_personaje->nombre << endl;
        cout << "ID: " << actual_personaje->identificador << endl;
        cout << "Especie: " << actual_personaje->tipo->nombre_especie << endl;
        cout << "Objetos de la mochila: " << endl;

        Implemento *actual_implemento = actual_personaje->mochilaa->ipmplementos;
        cout << "  Implementos: ";
        if (actual_implemento == nullptr) {
            cout << "Ninguno" << endl;
        } else {
            cout << endl;
            while (actual_implemento != nullptr) {
                cout << "    - " << actual_implemento->nombre_implemento << endl;
                actual_implemento = actual_implemento->siguiente;
            }
        }

        Poder_magico *actual_poder = actual_personaje->mochilaa->poderes;
        cout << "  Poderes Magicos: ";
        if (actual_poder == nullptr) {
            cout << "Ninguno" << endl;
        } else {
            cout << endl;
            while (actual_poder != nullptr) {
                cout << "    - " << actual_poder->nombre_poder<< endl;
                actual_poder = actual_poder->siguiente;
            }
        }
        cout << endl;
        actual_personaje = actual_personaje->siguiente;
    }
    cout << "\nNo hay mas personajes en el equipo.\n\n ";
}

void modificar_mochila(personaje *personajes_jugar, Implemento &Implementos, Poder_magico &poderes) {
    if (cantidad_personajes_jugar == 0) {
        cout << "No hay personajes en el equipo para modificar.\n";
        cout << "Modificacion fallida.\n";
        return;
    }

    int identificador;
    cout << "Los personajes que forman parte del equipo son: \n";
    mostrar_personajes_jugar(personajes_jugar);
    identificador = obtener_entero("Coloque el ID del personaje cuya mochila desea modificar: ");

    personaje *actual = personajes_jugar;
    while ((actual != nullptr) && (actual->identificador != identificador)) {
        actual = actual->siguiente;
    }

    if (actual != nullptr) {
        cout << "Proceda a llenar nuevamente la mochila del personaje: " << actual->nombre << endl;

        Implemento *actual_implemento = actual->mochilaa->ipmplementos;
        while (actual_implemento != nullptr) {
            Implemento *siguiente_implemento = actual_implemento->siguiente;
            delete actual_implemento;
            actual_implemento = siguiente_implemento;
        }
        actual->mochilaa->ipmplementos = nullptr;

        Poder_magico *actual_poder = actual->mochilaa->poderes;
        while (actual_poder != nullptr) {
            Poder_magico *siguiente_poder = actual_poder->siguiente;
            delete actual_poder;
            actual_poder = siguiente_poder;
        }
        actual->mochilaa->poderes = nullptr;

        llenar_mochila(actual, Implementos, poderes);
        cout << "Actualización de la mochila completa para el personaje: " << actual->nombre << endl;
    } else {
        cout << "El ID " << identificador << " no existe en el equipo.\n";
        cout << "Modificación fallida.\n";
    }
}

void eliminar_personaje_jugar(personaje *&lista_jugar) {
    if (cantidad_personajes_jugar == 0) {
        cout << "No hay personajes disponibles para eliminar. \n";
        cout << "Eliminacion fallida.\n";
        return;
    }

    int identificador = 0;
    cout << "Los personajes en el equipo son: \n";
    mostrar_personajes_jugar(lista_jugar);
    identificador = obtener_entero("Coloque el ID del personaje que desea eliminar: ");

    personaje *actual = lista_jugar;
    personaje *anterior = nullptr;

    while (actual != nullptr && actual->identificador != identificador) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual != nullptr) {
        Implemento *actual_implemento = actual->mochilaa->ipmplementos;
        while (actual_implemento != nullptr) {
            Implemento *siguiente_implemento = actual_implemento->siguiente;
            delete actual_implemento;
            actual_implemento = siguiente_implemento;
        }
        Poder_magico *actual_poder = actual->mochilaa->poderes;
        while (actual_poder != nullptr) {
            Poder_magico *siguiente_poder = actual_poder->siguiente;
            delete actual_poder;
            actual_poder = siguiente_poder;
        }
        delete actual->mochilaa;
        actual->mochilaa = nullptr;


        if (anterior == nullptr) {
            lista_jugar = actual->siguiente;
        } else {
            anterior->siguiente = actual->siguiente;
        }

        cout << "Eliminacion del personaje " << actual->nombre << " exitosa.\n";
        delete actual;
        cantidad_personajes_jugar--;
    } else {
        cout << "El ID " << identificador << " No existe en el equipo. \n";
        cout << "Eliminacion fallida.\n";
    }
}

void destruir_personaje_jugar(personaje *&lista_jugar){
    personaje *actual = lista_jugar;
    while (actual != nullptr){
        if (actual->mochilaa != nullptr) {
            Implemento *actual_implemento = actual->mochilaa->ipmplementos;
            while (actual_implemento != nullptr) {
                Implemento *siguiente_implemento = actual_implemento->siguiente;
                delete actual_implemento;
                actual_implemento = siguiente_implemento;
            }
            Poder_magico *actual_poder = actual->mochilaa->poderes;
            while (actual_poder != nullptr) {
                Poder_magico *siguiente_poder = actual_poder->siguiente;
                delete actual_poder;
                actual_poder = siguiente_poder;
            }
            delete actual->mochilaa;
            actual->mochilaa = nullptr;
        }

        personaje *eliminar = actual;
        actual = actual->siguiente;
        delete eliminar;
    }
    lista_jugar = nullptr;
    cantidad_personajes_jugar = 0;
    regulador_personajes_jugar = 0;
}

//------------------------------ EJECUCION DEL PROGRAMA -----------------------------------------------

int main()
{
    Lista_mapa mapa;
    mapa.actual_sala = nullptr;
    mapa.cantidad = 0;

    Lista_especie tipoEspecieOrco;
    Lista_especie tipoEspecieHeroe;

    personaje personajes_orco;
    personajes_orco.siguiente = nullptr;
    personaje personajes_hero;
    personajes_hero.siguiente = nullptr;

    Implemento lista_implementos;
    lista_implementos.siguiente = nullptr;

    Poder_magico lista_podere_magicos;
    lista_podere_magicos.siguiente = nullptr;

    personaje *personajes_jugar=nullptr;

    int opcion_principal = 0;
    int opcion_interna = 0;

    cout << "Bienvenido ¿Que desea hacer?: " << endl;

    do
    {
        cout << "\n         MENU PRINCIPAL \n";
        cout << "1. Ingresar al Menu de Orcos" << "\n";
        cout << "2. Ingresar al Menu de Heroes" << "\n";
        cout << "3. Ingresar al Menu de Implementos" << "\n";
        cout << "4. Ingrese al menu de poderes magicos \n";
        cout << "5. Escoger personajes para jugar.\n";
        cout << "6. Menu del Mapa.\n";
        cout << "7. Salir de Menu Principal" << "\n";
        opcion_principal = obtener_opcion();

        switch (opcion_principal)
        {
        case 1: // Menu Orcos
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
                cout << "8. Eliminar personaje  \n";
                cout << "------------------------\n";
                cout << "9.Salir al menu principal.\n";
                cout << "---------------------\n";
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
                    eliminar_elemento_lista(tipoEspecieOrco,personajes_orco,1);
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
                    borrar_personaje(personajes_orco,1);
                    break;
                case 9:
                    cout << "\nSaliendo al Menu Principal... \n";
                    break;
                default:
                    cout << "Invalido. Ingrese una opcion valida \n";
                    break;
                }
            } while (opcion_interna != 9);
            break;

        case 2: // Menu Heroes
            do
            {
                cout << "\n MENU DE HEROES:\n";
                cout << "---------------------\n";
                cout << "1. Agregar una especie de Heroe \n";
                cout << "2. Actualizar los datos de un tipo de Heroe \n";
                cout << "3. Mostrar los tipos de Heroes disponibles \n";
                cout << "4. Eliminar un tipo de especie \n";
                cout << "---------------------\n";
                cout << "5. Crear personaje.\n";
                cout << "6. Mostrar personajes. \n";
                cout << "7. Modificar personaje \n";
                cout << "8. Eliminar personaje  \n";
                cout << "---------------------\n";
                cout << "9. Salir al menu principal  \n";
                cout << "---------------------\n";
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
                    eliminar_elemento_lista(tipoEspecieHeroe,personajes_hero, 2);
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
                    borrar_personaje(personajes_hero,2);
                    break;
                case 9:
                    cout << "\nSaliendo al Menu Principal... \n";
                    break;
                default:
                    cout << "Invalido. Ingrese una opcion valida \n";
                    break;
                }
            } while (opcion_interna != 9);
            break;

        case 3: // Menu Implementos
            do
            {
                cout << "\n MENU DE IMPLEMENTOS:\n";
                cout << "------------------------\n";
                cout << "1. Agregar un implemento. \n";
                cout << "2. Actualizar un implemento. \n";
                cout << "3. Mostrar los implementos. \n";
                cout << "4. Eliminar un implemento \n";
                cout << "------------------------\n";
                cout << "5. Salir al menu principal  \n";
                cout << "------------------------\n";
                opcion_interna = obtener_opcion();

                switch (opcion_interna)
                {
                case 1:
                    crear_implemento(lista_implementos);
                    break;
                case 2:
                    modificar_implemento(lista_implementos);
                    break;
                case 3:
                    mostrar_implementos(lista_implementos);
                    break;
                case 4:
                    borrar_implementos(lista_implementos);
                    break;
                case 5:
                    cout << "\nSaliendo al Menu Principal... \n";
                    break;
                default:
                    cout << "Invalido. Ingrese una opcion valida \n";
                    break;
                }
            } while (opcion_interna != 5);

            break;

        case 4: // Menu Poderes Mágicos
            do
            {
                cout << "\n MENU DE PODERES MAGICOS:\n";
                cout << "---------------------\n";
                cout << "1. Agregar poder magico. \n";
                cout << "2. Actualizar poder magico. \n";
                cout << "3. Mostrar los poderes magicos. \n";
                cout << "4. Eliminar un poder magico. \n";
                cout << "---------------------\n";
                cout << "5. Salir al menu principal  \n";
                cout << "---------------------\n";
                opcion_interna = obtener_opcion();

                switch (opcion_interna)
                {
                case 1:
                    crear_poder(lista_podere_magicos);
                    break;
                case 2:
                    modificar_poder(lista_podere_magicos);
                    break;
                case 3:
                    mostrar_poderes(lista_podere_magicos);
                    break;
                case 4:
                    eliminar_poder(lista_podere_magicos);
                    break;
                case 5:
                    cout << "\nSaliendo al Menu Principal... \n";
                    break;
                default:
                    cout << "Invalido. Ingrese una opcion valida \n";
                    break;
                }

            } while (opcion_interna != 5);
            break;

        case 5: // Menu Personajes para Jugar
            do
            {
                cout << "\n MENU DE PERSONAJES PARA JUGAR:\n";
                cout << "---------------------\n";
                cout << "1. Elegir personaje y objetos del mismo \n";
                cout << "2. Mostrar personaje del equipo. \n";
                cout << "3. Modificar mochila. \n";
                cout << "4. Eliminar personaje. \n";
                cout << "---------------------\n";
                cout << "5. Salir al menu principal  \n";
                cout << "---------------------\n";
                opcion_interna = obtener_opcion();

                switch (opcion_interna)
                {
                case 1:
                    eleccio_personaje(personajes_jugar,personajes_hero,lista_implementos,lista_podere_magicos);
                    break;
                case 2:
                    mostrar_personajes_jugar(personajes_jugar);
                    break;
                case 3:
                    modificar_mochila(personajes_jugar,lista_implementos,lista_podere_magicos);
                    break;
                case 4:
                    eliminar_personaje_jugar(personajes_jugar);
                    break;
                case 5:
                    cout << "\nSaliendo al Menu Principal... \n";
                    break;
                default:
                    cout << "Invalido. Ingrese una opcion valida \n";
                    break;
                }

            } while (opcion_interna != 5);
            break;

        case 6: // Menu del Mapa
            {
                string nombre_sala_temp;
                string nombre_sala1_ady, nombre_sala2_ady;
                int distancia_ady, cantidad_orcos_ady;
                int distancia_sala_temp;

                do
                {
                    cout << "\n MENU DEL MAPA:\n";
                    cout << "---------------------\n";
                    cout << "1. Agregar una sala al mapa.\n";
                    cout << "2. Mostrar el mapa.\n";
                    cout << "3. Modificar una sala.\n";
                    cout << "4. Agregar adyacencia (manual).\n";
                    cout << "5. Eliminar sala. \n";
                    cout << "6. Liberar mapa completo.\n";
                    cout << "7. Salir al menu principal.\n";
                    cout << "---------------------\n";
                    opcion_interna = obtener_opcion();

                    switch (opcion_interna)
                    {
                    case 1:
                        nombre_sala_temp = devolver_string_verificada("Ingrese el nombre de la nueva sala: ");
                        distancia_sala_temp = obtener_entero("Ingrese la distancia de salida de esta sala (para la adyacencia automatica): ");
                        AñadirSalaALista(mapa, nombre_sala_temp, distancia_sala_temp);
                        break;
                    case 2:
                        MostrarMapa(mapa);
                        break;
                    case 3:
                        Modificarsala(mapa);
                        break;
                    case 4:
                        if (mapa.actual_sala == nullptr) {
                            cout << "Primero debe crear al menos una sala para añadir adyacencias." << endl;
                            break;
                        }
                        nombre_sala1_ady = devolver_string_verificada("Ingrese el nombre de la primera sala: ");
                        nombre_sala2_ady = devolver_string_verificada("Ingrese el nombre de la segunda sala: ");
                        distancia_ady = obtener_entero("Ingrese la distancia entre las salas: ");
                        cantidad_orcos_ady = obtener_entero("Ingrese la cantidad de orcos en la adyacencia (0 si no aplica): ");
                        AgregarAdyacencia(mapa, nombre_sala1_ady, nombre_sala2_ady, distancia_ady, cantidad_orcos_ady);
                        break;
                    case 5:
                        {
                            string nombre_salaeliminar = devolver_string_verificada("Ingrese el nombre de la sala a eliminar: ");
                            EliminarSala(mapa, nombre_salaeliminar);
                        }
                        break;
                    case 6:
                        liberarMapa(mapa);
                        cout << "Mapa completo liberado." << endl;
                        break;
                    case 7:
                        cout << "\nSaliendo al Menu Principal... \n";
                        break;
                    default:
                        cout << "Invalido. Ingrese una opcion valida \n";
                        break;
                    }
                } while (opcion_interna != 7);
                break;
            }

        case 7:
            cout << "\nSaliendo del Menu Principal... \n";
            cout << "Entrando al Juego... \n";
            break;

        default:
            cout << "Invalido. Ingrese una opcion valida";
            break;
        }

    } while (opcion_principal != 7);

    // Liberar toda la memoria al final del programa
    destruir_lista_especie(tipoEspecieHeroe);
    destruir_lista_especie(tipoEspecieOrco);
    destruir_lista_personajes(personajes_orco);
    destruir_lista_personajes(personajes_hero);
    destruir_implementos(lista_implementos);
    destruir_poder_magico(lista_podere_magicos);
    destruir_personaje_jugar(personajes_jugar);
    liberarMapa(mapa);

    cout << "Gracias por usar el programa. \n";
    return 0;
}
