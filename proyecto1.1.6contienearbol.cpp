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
    int identificador;
    Implemento *siguiente = nullptr;
};
int cantidad_implementos=0;
int regulador_implemento=0;

// ESTRUCTURA DE LOS PODERES MAGICOS
struct Poder_magico
{
    string nombre_poder;
    string funcion;
    int identificador;
    Poder_magico *siguiente = nullptr;
};
int cantidad_poderes=0;
int regulador_poderes=0;

// ESTRUCTURA para los tipos de especies. orcos y heroes
struct Especie
{
    string nombre_especie;
    int danno_fortaleza;
    int salud;
    int rapidez;
    int identificador;
    Especie *siguiente; // no se pone como nul poruw ela lista esta planteada de otra manera.
};

// Estructura para crear las listas enlazadas.
struct Lista_especie
{
    Especie *primero_especie = nullptr;
    int cantidad = 0;
};

//-----------------------------------------------------------------------------------------------------
//--------------------------------------PARA EL MAPA---------------------------------------------------
// Estructura para el Mapa
struct Sala
{
    string nombreSala; // Nombre de la sala
    int distancia_salida;
    int cantidadOrcos; // Cantidad de orcos en la sala
    Sala *adyacencia;
};

// Función para crear el nuevo nodo
Sala* crearMapa(string nombre) {
    Sala* nuevo_mapa = new Sala();
    nuevo_mapa->nombreSala = nombre;
    nuevo_mapa->adyacencia = nullptr;
    return nuevo_mapa;
}

// Función para agregar una sala
void Añadirsala(Sala *&mapa, string nombre){
    if(mapa!=nullptr){
        Sala *actual = new Sala();
        Sala *insertar = new Sala();
        insertar->nombreSala = nombre;
        actual = mapa;
        while(actual->adyacencia=nullptr){
            actual=actual->adyacencia;
        }
        actual->adyacencia = insertar;
        cout<<"Se inserto correctamente la sala"<<endl;
    }
    else{
        cout<<"Este mapa no existe"<<endl;
    }
    return;
}

// Función para buscar una sala por nombre
bool buscarSala(Sala* mapa, string nombre) {
    if (mapa == nullptr) {
        return false; // No se encontró
    }
    if (mapa->nombreSala == nombre) {
        return true; // Se encontró
    }
    return buscarSala(mapa->adyacencia, nombre);
}


// Función para liberar la memoria del árbol
void liberarMapa(Sala* mapa) {
    if (mapa != nullptr) {
        liberarMapa(mapa->adyacencia);
        delete mapa;
    }
}

void MostrarMapa(Sala &mapa){
    Sala *salaactual = new Sala();
    salaactual = &mapa;
    if(salaactual!=nullptr){
        while(salaactual!=nullptr){
            cout<<salaactual->nombreSala<<"->";
            salaactual=salaactual->adyacencia;
        }
        cout<<"/null"<<endl;
    }
    else{
        cout<<"Este mapa no existe"<<endl;
    }
    delete salaactual;
    return;
}

void Modificarsala(Sala*&mapa){
    if(mapa==nullptr){
        cout<<"El mapa se encuentra vacio por los momentos"<<endl;
        return;
    }
    else{
        string nombresala; cout<<"Ingrese el nombre de la sala que va a modificar= "; cin>>nombresala;
        bool modificado=false;
        if(buscarSala(mapa,nombresala)==true){
            modificado=true;
            mapa->nombreSala=devolver_string_verificada("Nombre de la sala: ");
            cout<<"La sala ha sido modificada"<<endl;
        }
        else{
            cout<<"La sala no ha sido encontrada";
        }
    }
}


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
        for (size_t i = 0; i < entrada.size(); ++i)   // entrada.size() devuelve la longitud de la cadena.
        {
            if (es_valido && !isdigit(entrada[i]))  //isdigit( es para comprovar si el caracter es un numero)
            {
                es_valido = false;
                break;
            }
        }

        // Convierte a entero mientras sea valido y no este vacio
        if (es_valido && !entrada.empty())  // empty() es para verificar si no esta vai la cadena.
        {
            valor = stoi(entrada);          // stoi convierte una cadena de caracter en entero

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

    for (char caracter : respuesta)  // itera por cada elemento de la caden.
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


// FUNCIONES REFERENTES A PERSONAJES.

// Funcion que retorna un puntero a una especie.
Especie *encontrar_especie(Lista_especie &lista, int identificador)
{
    Especie *actual = lista.primero_especie;
    while (actual != nullptr)
    {
        if (actual->identificador == identificador)
        {
            return actual;
        }
        actual = actual->siguiente;
    }
    cout << "La especie ingresada no existe." << endl;
    return nullptr;
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
        cout << endl;
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
        cout << "Actualizacion fallida \n";
    }
}

// para borrar un personaje.
void borrar_personaje(personaje &lista, int tipo){
    if (tipo == 1){ // para orcos.
        if (cantidad_personaje_orco == 0){
            cout << "\nNo hay personajes orcos para eliminar actualente \n";
            cout << "Primero debe crearlos\n";
            return;
        }
    }else{ // para heroes
        if (cantidad_personaje_heroe == 0){
            cout << "\nNo hay personajes heroes para eliminar actualmente \n";
            cout << "Primero debe crearlos\n";
            return;
        }
    }
    
    int identificador = 0;
    personaje *actual = lista.siguiente; // aounta al primero de la lista
    personaje *anterior = nullptr;

    cout << "Los personajes disponibles son: \n";
    mostrar_personajes(lista,tipo);
    identificador = obtener_entero("Coloque el numero del personaje a modificar: ");

    if ((actual != nullptr) && (actual->identificador == identificador)){
        lista.siguiente = actual->siguiente;
        cout << "El personaje: " << actual->nombre << " fue borrado axitosamente." << endl;
        delete actual;
        if (tipo == 1){
            regulador_personaje_orco +=1;
            cantidad_personaje_orco -=1;
        }else{
            regulador_personaje_heroe +=1;
            cantidad_personaje_heroe  -=1;
        }
        return;
    }

    while ((actual != nullptr) && (actual->identificador != identificador)){
        anterior = actual;
        actual = actual->siguiente;
    }
    
    if (actual != nullptr){
        personaje *eliminar = actual;
        anterior->siguiente = actual->siguiente;
        cout << "El personaje " << eliminar->nombre << " se elimino correctapente. \n ";
        delete eliminar; 
        
        
        if (tipo == 1){
            regulador_personaje_orco +=1;
            cantidad_personaje_orco -=1;
        } else {
            regulador_personaje_heroe +=1;
            cantidad_personaje_heroe -=1;
        }
        
        
    }else{
        cout << "El numero de personaje: " << identificador << " no se encuentra en la lista \n ";
        cout << "Eliminacion fallida \n";   
    }
}

// borra todos los personajes de un tipo (epecie).
void borrar_personajes_de_tipo(personaje &lista_personajes, Especie *tipo_borrar, int tipo) {
    personaje *actual = lista_personajes.siguiente; // El primero en la lista (después del nodo cabeza)
    personaje *anterior = &lista_personajes;      // El anterior al que se elimina (inicialmente la cabeza)
    personaje *eliminar = nullptr;               // Para almacenar el nodo a eliminar

    while (actual != nullptr) {
        if (actual->tipo != nullptr && actual->tipo->identificador == tipo_borrar->identificador) {
            eliminar = actual;
            anterior->siguiente = actual->siguiente; // Enlaza el anterior con el siguiente del nodo a eliminar
            actual = actual->siguiente;             // Avanza actual para seguir buscando

            cout << "El personaje: " << eliminar->nombre << " fue borrado." << endl;
            delete eliminar; // Se libera la memoria del personaje borrado

            if (tipo == 1) {
                regulador_personaje_orco++;
                cantidad_personaje_orco--;
            } else {
                regulador_personaje_heroe++;
                cantidad_personaje_heroe--;
            }
        } else {
            anterior = actual; // Si no se borra, el actual se convierte en el anterior
            actual = actual->siguiente; // Avanza al siguiente personaje
        }
    }
}

// pra saber cuantos pesonajes hay de una especie
int cantidad_personajes_por_especie(personaje &lista_personajes, Especie *mostrar){
    personaje *actual = lista_personajes.siguiente;
    int contador=0;
    while ((actual != nullptr)){
        if (actual->tipo->identificador == mostrar->identificador){
            contador +=1;
        }
        actual = actual->siguiente;
    }
    return contador;
}

// esta funcion la coloque
// para eliminar un elemento de la lista 
void eliminar_elemento_lista(Lista_especie &lista,personaje lista_personajes, int tipo)
{
    if (lista.cantidad == 0)
    {
        cout << "No hay elementos en la lista para borrar\n";
        return;
    }
    cout << "Las especies disponibles son: \n";
    mostrar_lista(lista, tipo);

    int identificador = 0;

    identificador = obtener_entero("Ingrese el numero del tipo que desea borrar: ");

    if (identificador > 0)
    {
        int controlador_eliminar=0; // para controlar si se va a eliminar o no el tipo
        
        // respecto a los tipos
        Especie *actual = lista.primero_especie;
        Especie *anterior = nullptr; // Inicializamos anterior como nullptr
        
        // respecto a los personajes
        Especie *especie_borrar=encontrar_especie(lista, identificador);
        int cantida_personajes=0;
        // Caso especial: el elemento a eliminar es el primero de la lista
        
        
            // para ver la cntidad de personajes que exixten con el tipo que desea borrar el usuario.
            cantida_personajes= cantidad_personajes_por_especie(lista_personajes,especie_borrar);
            
            // si si hay personajes se le dice al usuario a ver si de todas formas decea eliminar el tipo.    
            if (cantida_personajes > 0){
                cout << " Hay: " << cantida_personajes << "personajes de esta especie, por lo tanto. \n";
                cout << "Al eliminar la especie se boraran los personajes del tipo \n";
                cout << "eliminar de todas formas coloque 1 \n";
                cout << "no eliminar coloque 2 \n"; 
                do
                {
                    cout << "(1) o (2)\n";
                    controlador_eliminar=obtener_entero("coloque el numero:");
                } while ((controlador_eliminar != 1) && (controlador_eliminar != 2) );
                
            }else{
                cout << " no hay personajes atualmente de este tipo, no hay problema al eliminarlo. \n";
            }
            // para eliminar si el usuario dice que si
            if (controlador_eliminar == 1){
                // procedemos a borrar los personajes del tipo
                borrar_personajes_de_tipo(lista_personajes,especie_borrar,tipo);
                
            }else if (controlador_eliminar == 2)
            {
                cout <<"eliminacion del tipo " << especie_borrar->nombre_especie << " fallida.\n";
                return; 
            }
            
            // sigue el procedimiento normal para elimanar el tipo.  
            if ((actual != nullptr) && actual->identificador == identificador)
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
        while ((actual != nullptr) && (actual->identificador != identificador))
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
            cout << "Eliminacion fallida \n";
        }
    }
    else
    {
        cout << "El numero de especie ingresado no es valido. \n";
    }
}
//-----------------------------------------------------------------------------------------------------
// FUNCIONES PARA LOS IMPLEMENTOS.

// para destruir la lista de implementos.
void destruir_implementos(Implemento &lista_implemento){
    Implemento *actual = lista_implemento.siguiente;
    Implemento *eliminar=nullptr;
    while (actual != nullptr){
        eliminar = actual;
        actual = actual->siguiente;
        delete eliminar;
    }
    cantidad_implementos=0;
    regulador_implemento=0;
}

// para crear implementos.
void crear_implemento(Implemento &lista_implemento){
    Implemento *nuevo = new Implemento;
    cout << "Proceda a llenar las espicificaciones del imlemento. \n\n";
    nuevo->nombre_implemento = devolver_string_verificada("Nobre:");
    nuevo->tipo_implemento = devolver_string_verificada("Tipo: ");
    nuevo->uso_implemento = devolver_string_verificada("Uso: ");
    nuevo->fortalezanecesaria = obtener_entero("Fortaleza necesaria para usar el implemento: ");
    nuevo->valor = obtener_entero("valor: ");
    // lo agregamos a la lista enlazada.
    nuevo->siguiente = lista_implemento.siguiente;
    lista_implemento.siguiente = nuevo;
    cantidad_implementos +=1;
    nuevo->identificador= cantidad_implementos + regulador_implemento;
    cout << "El implemento: " << nuevo->nombre_implemento << "se creo correctamente.";
}

// buscar implemento.
Implemento* buscar_implemento(Implemento &lista_implemento, int identificador){
    Implemento *encontrado = lista_implemento.siguiente;
    while ((encontrado != nullptr) && (encontrado->identificador != identificador)){
        encontrado= encontrado->siguiente;
    }
    if (encontrado->identificador == identificador){
        return encontrado;
    } else{
        return encontrado = nullptr;
    }
    
    
    
}

void mostar_implementos(Implemento &lista_implemento){
    if (cantidad_implementos == 0){
        cout << "No hay implementos disponibles en este momento. \n";
        return;
    }else{
        cout << "la candtad de implementos es: ["<< cantidad_implementos <<"]. \n";
    }
    
    Implemento *actual = lista_implemento.siguiente;
    while (actual != nullptr){
        cout << "\nNombre: " << actual->nombre_implemento <<endl;
        cout << "\nID: " << actual->identificador;
        cout << "\nTipo: " << actual->tipo_implemento;
        cout << "\nUso: " << actual->uso_implemento;
        cout << "\nFortaleza necesaria para usarlo: " << actual->fortalezanecesaria;
        cout << "\nValor: " << actual->valor;
        cout <<endl<<endl; 
        actual = actual->siguiente; 
    }
    cout << "no hay mas implementos disponibles\n";
}

void modificar_implemento(Implemento &lista_implemento){
    if (cantidad_implementos == 0){
        cout << "No hay implementos disponibles para modificar \n";
        return;
    }
    int identificador=0;
    cout << "los impplementos disponibles son: \n";
    mostar_implementos(lista_implemento);
    identificador = obtener_entero("Coloque el ID del implemento que desea modificar: ");
    Implemento *actualizar = buscar_implemento(lista_implemento,identificador);
    if (actualizar == nullptr){
        cout << "El ID que coloco no es valido.\n";
        cout << "No hay ninun implemento con ese ID.\n";
        cout << "Actualizacion fallida.\n";
        return;
    } 
    
    //                          VERRRRRRRRRRRRRRRRRRRR
    // coloco este menaje porque no s porque el progra no corre normal.
    cout << "precione enter para modificar el implemto: " << actualizar->nombre_implemento;
    // hay que daele enter para que corra.

    cin.ignore();
    actualizar->nombre_implemento =devolver_string_verificada("Nombre: ");
    actualizar->tipo_implemento = devolver_string_verificada("Tipo: ");
    actualizar->uso_implemento = devolver_string_verificada("Uso: ");
    actualizar->fortalezanecesaria = obtener_entero("Fortaleza necesaria para usarlo:");
    actualizar->valor = obtener_entero("Valor: ");
    cout << "Implemento: " << actualizar->nombre_implemento <<", modificado correctamente.\n ";
}

// para borrar implementos.
void borrar_implementos(Implemento &lista_implemento){
    if (cantidad_implementos == 0){
        cout << "No hay implementos para eliminar: \n";
        cout << "Eliminacion fallida. \n"; 
    }
    cout << "Los implementos disponibles son: \n";
    mostar_implementos(lista_implemento);
    int identificador = obtener_entero("coloque el ID del implemento que desea eliminar:");
    Implemento *encontrado = buscar_implemento(lista_implemento,identificador);
    if (encontrado == nullptr){
        cout << "  No existe un implemento con el ID: " << identificador;
        cout << "\nEliminacion fallida. \n";
        return;
    }

    // comiza la eliminacion del implemento.
    Implemento *actual = lista_implemento.siguiente;
    
    // si es el primero en la lista.
    if (actual->identificador == identificador){
        lista_implemento.siguiente = actual->siguiente;
        cout << "El implemento: " << actual->nombre_implemento << "se elimino correctamente.\n";
        delete actual;
        cantidad_implementos -=1;
        regulador_implemento +=1;
        return;
    }
    
    // si no es el primero.
    Implemento *anterior = nullptr;
    while ((actual != nullptr) && (actual->identificador != identificador)){
        anterior = actual;
        actual = actual->siguiente;
    }
    
    // ahora eliminamos.
    Implemento *eliminar = actual;
    anterior->siguiente = actual->siguiente;
    cout << "El elemento: " << eliminar->nombre_implemento << "se elimino correctamente. ";
    delete eliminar;
}


// funciones para poderes magicos.
// para destruir la lista de los poderes.
void destruir_poder_magico(Poder_magico &lista_poderes){
    Poder_magico *actual = lista_poderes.siguiente;
    while (actual != nullptr){
        Poder_magico *eliminar = actual;
        actual = actual->siguiente;
        delete eliminar;
    }
    cantidad_poderes=0;
    regulador_poderes=0;
}

// para crear poderes.
void crear_poder(Poder_magico &lista_poderes){
    Poder_magico *nuevo = new Poder_magico;
    cout << "Proceda a llenar las espesificaciones del nuevo poder. \n";
    nuevo->nombre_poder = devolver_string_verificada("Nombre: ");
    // lo coloco sin validar porque imagino que podra colocar numero y eso en la funcion del poder.
    cout << "Funcion: ";
    cin >> nuevo->funcion;
    cantidad_poderes += 1;
    nuevo->identificador = cantidad_poderes + regulador_poderes;
    // lo agregamos a la lista enlazada.
    nuevo->siguiente = lista_poderes.siguiente;
    lista_poderes.siguiente = nuevo;
    cout << "El poder: " << nuevo->nombre_poder << "se creo correctamente.\n";
}

// para mostrar los poderes.
void mostar_poderes(Poder_magico &lista_poderes){
    // para ver si hay poderes creados.
    if (cantidad_poderes == 0){
        cout << "No hay poderes disponibles actualmente. \n";
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

// para encontrar un poder
Poder_magico *encontar_poder(Poder_magico &lista_poderes, int identificador){
    Poder_magico *encontrar = lista_poderes.siguiente;
    while ((encontrar != nullptr) && (encontrar->identificador != identificador)){
        encontrar = encontrar->siguiente;
    }
    if (encontrar->identificador == identificador){
        return encontrar;
    } else {
        return encontrar = nullptr;
    }
}



// para modificar los poderes.
void modificar_poder(Poder_magico &lista_poderes){
    if (cantidad_poderes == 0){
        cout << "No hay poder magicos disponibles para modificar.\n";
        return;
    }
    int identificador=0;
    Poder_magico *actualizar = nullptr;
    cout << "Los poderes disponibles son: \n";
    mostar_poderes(lista_poderes);
    cout << "Coloque el ID del poder magico que desea modificar: ";
    cin >> identificador;
    // para valiadar que el poder existe.
    actualizar = encontar_poder(lista_poderes, identificador);
    if (actualizar == nullptr){
        cout << "El ID que coloco no existe. \n";
        cout << "Modificacion fallida \n";
        return;
    }
    cout << "Proceda a actulizar el poder: " << actualizar->nombre_poder<<endl;
    actualizar->nombre_poder = devolver_string_verificada("Nombre: ");
    // lo coloco sin validar porque imagino que podra colocar numero y eso en la funcion del poder.
    cout << "Funcion: ";
    cin >> actualizar->funcion;

    cout << "Poder magico: " <<actualizar->nombre_poder << "actualizado correctamente.\n";
}

// para eliminar un poder.
void eliminar_poder(Poder_magico &lista_poder){
    if (cantidad_poderes == 0){
        cout << "No hay poderes magicos disponibles para eliminar. \n";
        cout << "Eliminacion fallida. \n";
        return; 
    }
    int identificador = 0;
    Poder_magico *validar = nullptr;
    cout << "Los poderes magicos disponibles son: \n";
    mostar_poderes(lista_poder);
    identificador = obtener_entero("Coloqe el ID del personaje que desea modificar: ");
    // para validar que e id exisa.
    validar = encontar_poder(lista_poder, identificador);
    if (validar == nullptr){
        cout << "El ID que coloco no existe.\n";
        cout << "Eliminacion fallida.\n";
        return;
    }
    // comienza el procedimiento para borrar el poder.
    Poder_magico *actual = lista_poder.siguiente;
    Poder_magico *anterior = nullptr;
    // en caso de que sea el primero de la lista.
    if (actual->identificador == identificador){
        lista_poder.siguiente = actual->siguiente;
        cout << "el poder magico: " << actual->nombre_poder << " se elimino correctamente.\n ";
        delete actual;
        cantidad_poderes -=1;
        regulador_poderes +=1;
        return;
    }
    // en caso de que no sea el primenro.
    while ((actual != nullptr) && (actual->identificador != identificador)){
        anterior = actual;
        actual = actual->siguiente;
    }
    // ahora eliminamos.
    Poder_magico *eliminar = actual;
    anterior->siguiente = actual->siguiente;
    cout << "El poder magico: " << eliminar->nombre_poder << " se elimino correctamente.\n";
    delete eliminar;
    cantidad_poderes -=1;
    regulador_poderes +=1;
}



//------------------------------ EJECUCION DEL PROGRAMA -----------------------------------------------

int main()
{

    Lista_especie tipoEspecieOrco;  // lista enlazada que contiene todos los tipos de orcos.
    Lista_especie tipoEspecieHeroe; // lista enlazada que contiene todos los tipos de heroes.

    personaje personajes_orco; // lista enlazada de personajes orcos.
    personaje personajes_hero; // lista enlazada de personajes heroes.

    Implemento lista_implementos; // lista de implementos

    Poder_magico lista_podere_magicos; // lista de los poderes.

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
        cout << "4. Ingrese al menu de poderes magicos \n";
        cout << "5. Salir de Menu Principal" << "\n";
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
            } while (opcion_interna != 9); // Mientras no se salga del menu interno de orcos.
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
            } while (opcion_interna != 9); // Mientras no se salga del menu interno de heroes.
            break;

        // Menu Implementos
        case 3:
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
                    mostar_implementos(lista_implementos);
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

        case 4:   
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
                mostar_poderes(lista_podere_magicos);
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

        case 5:
            cout << "\nSaliendo del Menu Principal... \n";
            cout << "Entrando al Juego... \n";
            break;

        // Default del Menu Principal:
        default:
            cout << "Invalido. Ingrese una opcion valida";
            break;
        }

    } while (opcion_principal != 5);

    // Dejar esto al final del programa para que se destruyan las listas enlazadas.
    // Hay que añadir todos los tipos de listas que se vayan creando.
    destruir_lista_especie(tipoEspecieHeroe);
    destruir_lista_especie(tipoEspecieOrco); // se destruye la lista al final del programa.

    destruir_lista_personajes(personajes_orco);
    destruir_lista_personajes(personajes_hero);

    destruir_implementos(lista_implementos);

    destruir_poder_magico(lista_podere_magicos);

    cout << "Gracias por usar el programa. \n";
    return 0;
}
// fin del programa.
