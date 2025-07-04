
#pragma once // Soluciona errores de redefinicion
// 02. Ya incluye las genericas
#include "02.funciones_tipos_especie.h"
#include "05.funciones_poder_magico.h"

// Mochila
struct mochila
{
    int identificador; // sera el mismo del personaje al que pernenezca.
    Implemento *implementos = nullptr;
    Poder_magico *poderes = nullptr;
    // aqui va el mapa.
};

// Personajes
struct personaje
{
    mochila *mimochila = nullptr;
    string nombre;
    Especie *tipo;
    double vitalidad; // Double para que no explote con vigor enano
    int fortaleza;
    int velocidad;
    int identificador;
    personaje *siguiente = nullptr;
};

//----------------------------------- PARA LOS PERSONAJES ---------------------------------------------

// Para los personajes
int regulador_personaje_orco = 7; // por el archivo
int cantidad_personaje_orco = 0;

int regulador_personaje_heroe = 7; // por el archivo
int cantidad_personaje_heroe = 0;

int cantidad_personajes_jugar = 0;
int regulador_personajes_jugar = 0;

// Para crear personajes.
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

            puntero_especie = encontrar_especie_id(lista_tipos, num_tipo);
        }
        else
        { // lo mismo pero para heroes.
            cout << "Indique los datos para el nuevo personaje Heroe. " << endl;

            nuevo->nombre = devolver_string_verificada("Nombre: ");

            cout << "Ingrese la especie al que pertenecera el Heroe" << nuevo->nombre << "\n";
            cout << "Especies disponibles: " << endl;
            mostrar_lista(lista_tipos, tipo);

            cout << "Ingrese la especie del Personaje " << nuevo->nombre << ":";
            num_tipo = obtener_entero("");

            puntero_especie = encontrar_especie_id(lista_tipos, num_tipo);
            // para validar que si esta la especie en la lista.
        }

        if (puntero_especie == nullptr)
        {
            cout << "La especie debe crearse primero." << endl;
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

// Funcion para mostrar los personajes
void mostrar_personajes(personaje &lista, int tipo) // tipo=1 orco / tipo=2 heroe
{                                                   // toma la direccion de memoria.
    // para validar que si hay personajes para mostrar.
    if (tipo == 1)
    { // para orcos.
        if (cantidad_personaje_orco == 0)
        {
            cout << "\nNo hay especies de orcos para mostra actualmente \n";
            cout << "primero debe crearlos\n";
            return;
        }
    }
    else
    { // para heroes
        if (cantidad_personaje_heroe == 0)
        {
            cout << "\nno hay personajes heroes para mostra actualmente \n";
            cout << "primero debe crerlos\n";
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
        cout << "Nombre: " << actual->nombre << endl;
        cout << "Especie: " << actual->tipo->nombre_especie << endl;
        cout << endl;
        actual = actual->siguiente;
    }
    cout << "No hay mas personajes.\n"
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
    return actual = nullptr;
}

// para saber cuantos pesonajes hay de una especie
int cantidad_personajes_por_especie(personaje &lista_personajes, Especie *mostrar)
{
    personaje *actual = lista_personajes.siguiente;
    int contador = 0;
    while ((actual != nullptr))
    {
        if (actual->tipo->identificador == mostrar->identificador)
        {
            contador += 1;
        }
        actual = actual->siguiente;
    }
    return contador;
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

            especie_nueva = encontrar_especie_id(lista_tipo, identificador_tipo);

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
        cout << "No se encontró ningún personaje con el ID: " << referencia << ".\n";
        cout << "Actualizacion fallida \n";
    }
}

// Para borrar un personaje.
void borrar_personaje(personaje &lista, int tipo)
{
    if (tipo == 1)
    { // para orcos.
        if (cantidad_personaje_orco == 0)
        {
            cout << "\nNo hay personajes orcos para eliminar actualente \n";
            cout << "Primero debe crearlos\n";
            return;
        }
    }
    else
    { // para heroes
        if (cantidad_personaje_heroe == 0)
        {
            cout << "\nNo hay personajes heroes para eliminar actualmente \n";
            cout << "Primero debe crearlos\n";
            return;
        }
    }

    int identificador = 0;
    personaje *actual = lista.siguiente; // aounta al primero de la lista
    personaje *anterior = nullptr;

    cout << "Los personajes disponibles son: \n";
    mostrar_personajes(lista, tipo);
    identificador = obtener_entero("Coloque el numero del personaje a modificar: ");

    if ((actual != nullptr) && (actual->identificador == identificador))
    {
        lista.siguiente = actual->siguiente;
        cout << "El personaje: " << actual->nombre << " fue borrado axitosamente." << endl;
        delete actual;
        if (tipo == 1)
        {
            regulador_personaje_orco += 1;
            cantidad_personaje_orco -= 1;
        }
        else
        {
            regulador_personaje_heroe += 1;
            cantidad_personaje_heroe -= 1;
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
        cout << "El personaje " << eliminar->nombre << " se elimino correctapente. \n ";
        delete eliminar;

        if (tipo == 1)
        {
            regulador_personaje_orco += 1;
            cantidad_personaje_orco -= 1;
        }
        else
        {
            regulador_personaje_heroe += 1;
            cantidad_personaje_heroe -= 1;
        }
    }
    else
    {
        cout << "El numero de personaje: " << identificador << " no se encuentra en la lista \n ";
        cout << "Eliminacion fallida \n";
    }
}

// Funcion para destruir la lista de personajes.
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

// borra todos los personajes de un tipo (epecie).
void borrar_personajes_de_tipo(personaje &lista_personajes, Especie *tipo_borrar, int tipo)
{
    personaje *actual = lista_personajes.siguiente; // El primero en la lista (después del nodo cabeza)
    personaje *anterior = &lista_personajes;        // El anterior al que se elimina (inicialmente la cabeza)
    personaje *eliminar = nullptr;                  // Para almacenar el nodo a eliminar

    while (actual != nullptr)
    {
        if (actual->tipo != nullptr && actual->tipo->identificador == tipo_borrar->identificador)
        {
            eliminar = actual;
            anterior->siguiente = actual->siguiente; // Enlaza el anterior con el siguiente del nodo a eliminar
            actual = actual->siguiente;              // Avanza actual para seguir buscando

            cout << "El personaje: " << eliminar->nombre << " fue borrado." << endl;
            delete eliminar; // Se libera la memoria del personaje borrado

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
            anterior = actual;          // Si no se borra, el actual se convierte en el anterior
            actual = actual->siguiente; // Avanza al siguiente personaje
        }
    }
}

// esta funcion la coloque
// para eliminar un elemento de la lista
void eliminar_elemento_lista(Lista_especie &lista, personaje lista_personajes, int tipo)
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
        int controlador_eliminar = 0; // para controlar si se va a eliminar o no el tipo

        // respecto a los tipos
        Especie *actual = lista.primero_especie;
        Especie *anterior = nullptr; // Inicializamos anterior como nullptr

        // respecto a los personajes
        Especie *especie_borrar = encontrar_especie_id(lista, identificador);
        int cantida_personajes = 0;
        // Caso especial: el elemento a eliminar es el primero de la lista

        // para ver la cntidad de personajes que exixten con el tipo que desea borrar el usuario.
        cantida_personajes = cantidad_personajes_por_especie(lista_personajes, especie_borrar);

        // si si hay personajes se le dice al usuario a ver si de todas formas decea eliminar el tipo.
        if (cantida_personajes > 0)
        {
            cout << " Hay: " << cantida_personajes << "personajes de esta especie, por lo tanto. \n";
            cout << "Al eliminar la especie se boraran los personajes del tipo \n";
            cout << "eliminar de todas formas coloque 1 \n";
            cout << "no eliminar coloque 2 \n";
            do
            {
                cout << "(1) o (2)\n";
                controlador_eliminar = obtener_entero("coloque el numero:");
            } while ((controlador_eliminar != 1) && (controlador_eliminar != 2));
        }
        else
        {
            cout << " no hay personajes atualmente de este tipo, no hay problema al eliminarlo. \n";
        }
        // para eliminar si el usuario dice que si
        if (controlador_eliminar == 1)
        {
            // procedemos a borrar los personajes del tipo
            borrar_personajes_de_tipo(lista_personajes, especie_borrar, tipo);
        }
        else if (controlador_eliminar == 2)
        {
            cout << "eliminacion del tipo " << especie_borrar->nombre_especie << " fallida.\n";
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

//----------------------------------- FUNCIONES PERSONAJES JUGAR --------------------------------------

void llenar_mochila(personaje *&personaje_a_llenar, Implemento &Implementos, Poder_magico &poderes)
{
    int opcio = 0;
    int cantidad_objetos = 0;
    int identificador = 0;
    int contrilador_interno = 0;
    cout << "Puede escoger un maximo 5 objetos, entre poderes magicos o implementos. \n";
    do
    {
        cout << "Tiene " << cantidad_objetos << " objetos en la mochila.\n";
        cout << " Que tipo de objeto desea agregar.\n";
        cout << "1. Implemento.\n";
        cout << "2. Poderes Magicos.\n";
        cout << "3. Salir.\n";
        opcio = obtener_entero("");
        if (opcio == 1)
        {
            Implemento *nuevo_implemento = nullptr;
            // para verificar si el ID es valido, lo pone bien o lo pone bien.
            do
            {
                cout << "Los implementos disponibles son:\n";
                mostrar_implementos(Implementos);
                cout << "coloque el ID del implemento que desea colocar: ";
                identificador = obtener_entero("");
                nuevo_implemento = buscar_implemento(Implementos, identificador);

                if (nuevo_implemento == nullptr)
                {
                    cout << "El ID: " << identificador << " no existe.\n";
                    cout << "coloque uno valido.\n";
                }
                else if (nuevo_implemento->fortalezanecesaria > personaje_a_llenar->tipo->danno_fortaleza)
                {
                    cout << "El implemento: " << nuevo_implemento->nombre_implemento << " no puede ser usado por el personaje: " << personaje_a_llenar->nombre << endl;
                    cout << "Coloque uno valido.\n";
                }
                else
                {
                    contrilador_interno = 1;
                }
            } while (contrilador_interno != 1);
            // procedemos a colocar el implemento en la mochila.
            // cramos nuva memoria dinamica.
            Implemento *colocar = new Implemento;
            *colocar = *nuevo_implemento;
            // ahora la asignamos a la mochila.
            colocar->siguiente = personaje_a_llenar->mimochila->implementos;
            personaje_a_llenar->mimochila->implementos = colocar;
            cantidad_objetos += 1;
            contrilador_interno = 0; // poria.
            cout << "El implemento " << colocar->nombre_implemento << " se agrego correctamente a la mochila.\n";
        }
        else if (opcio == 2)
        {
            Poder_magico *nuevo_poder = nullptr;
            // para verificar si el ID es valido, lo pone bien o lo pone bien.
            do
            {
                cout << "Los poderes magicos disponibles son:\n";
                mostrar_poderes(poderes);
                cout << "coloque el ID del poder que desea colocar: ";
                identificador = obtener_entero("");
                nuevo_poder = encontrar_poder(poderes, identificador);
                if (nuevo_poder == nullptr)
                {
                    cout << "El ID: " << identificador << " no existe.\n";
                    cout << "coloque uno valido.\n";
                }
                else
                {
                    contrilador_interno = 1;
                }
            } while (contrilador_interno != 1);
            // procedemos a colocar el poder en la mochila.
            // cramos nuva memoria dinamica.
            Poder_magico *colocar = new Poder_magico;
            *colocar = *nuevo_poder;
            // ajhora la asignamos a la mochila.
            colocar->siguiente = personaje_a_llenar->mimochila->poderes;
            personaje_a_llenar->mimochila->poderes = colocar;
            cantidad_objetos += 1;
            contrilador_interno = 0; // porcia.
            cout << "El poder " << colocar->nombre_poder << " se agrego correctamente a la mochila.\n";
        }
        else if (opcio == 3)
        {
            cout << "La cantidad de objetos que coloco fue: " << cantidad_objetos << endl;
        }
        else
        {
            cout << "opcion invaida, el numero " << opcio << " no es una opcion valida.\n";
        }

    } while ((opcio != 3) && (cantidad_objetos != 5));
    if (cantidad_objetos == 5)
    {
        cout << "Ya no pudes agregar mas objetos.\n";
        cout << "La mochila del personaje " << personaje_a_llenar->nombre << " se lleno correctamente. ";
    }
}

// para elegir el personaje y llenar la mochila.
void eleccion_personaje(personaje *&lista_jugar, personaje &heroes, Implemento &implementos, Poder_magico &poderes)
{
    if (cantidad_personaje_heroe <= 0)
    {
        cout << "No hay heroes disponibles para elegir.\n";
        cout << "Eleccion de personaje fallida \n";
        return;
    }
    if (cantidad_personajes_jugar == 4)
    {
        cout << "Ya tienes la cantidad de personajes maxima.\n";
        return;
    }
    if (cantidad_implementos == 0)
    {
        cout << "No hay implementos disponibles para equipar a los heroes.\n";
        cout << "Eleccion de personaje fallida.\n";
        return;
    }

    int identificador;
    personaje *seleccionado = nullptr;

    cout << "Los heroes disponibles son: \n";
    mostrar_personajes(heroes, 2);
    cout << "Coloque el ID del heroe que desea agregar al equipo: ";
    identificador = obtener_entero("");

    seleccionado = encontrar_personaje(heroes, identificador);

    if (seleccionado == nullptr)
    {
        cout << "El ID: " << identificador << " no existe.\n";
        cout << "Eleccion de personaje fallida.\n";
        return;
    }
    cantidad_personajes_jugar += 1;
    // se copia para evitar probles (daba error si no lo hacia asi)
    personaje *nuevo_para_jugar = new personaje;
    nuevo_para_jugar->nombre = seleccionado->nombre;
    nuevo_para_jugar->tipo = seleccionado->tipo;
    nuevo_para_jugar->identificador = cantidad_personajes_jugar + regulador_personajes_jugar; // Nuevo ID para el equipo
    nuevo_para_jugar->mimochila = new mochila;
    nuevo_para_jugar->mimochila->implementos = nullptr; // porsia
    nuevo_para_jugar->mimochila->poderes = nullptr;
    nuevo_para_jugar->siguiente = nullptr;

    cout << "Proceda a llenar la mochila del personaje: " << nuevo_para_jugar->nombre << endl
         << endl;
    llenar_mochila(nuevo_para_jugar, implementos, poderes);

    // verrr la logica de incertar en un poco diferente a las demas funciones. los pone a final.
    // Insertar el nuevo personaje en la lista de personajes para jugar
    if (*&lista_jugar == nullptr)
    {
        *&lista_jugar = nuevo_para_jugar;
    }
    else
    {
        personaje *ultimo = *&lista_jugar;
        while (ultimo->siguiente != nullptr)
        {
            ultimo = ultimo->siguiente;
        }
        ultimo->siguiente = nuevo_para_jugar;
    }
    cout << "El heroe " << nuevo_para_jugar->nombre << " se agrago al equipo.\n";
}

// para mostrar con copia para no destruir la lista al mometo de mostrar.
void mostrar_personajes_jugar(personaje *lista_personajes_jugar)
{
    personaje *actual_personaje = lista_personajes_jugar;
    while (actual_personaje != nullptr)
    {
        cout << "Nombre: " << actual_personaje->nombre << endl;
        cout << "   ID: " << actual_personaje->identificador << endl;
        cout << "   Especie: " << actual_personaje->tipo->nombre_especie << endl; // Asumiendo que 'tipo' es un puntero a Especie
        cout << "   Vitalidad: " << actual_personaje->vitalidad << endl;
        cout << "   Fortaleza: " << actual_personaje->fortaleza << endl;

        // para la mochila.
        cout << "Objetos de la mochila: " << endl;

        Implemento *actual_implemento = actual_personaje->mimochila->implementos;
        cout << "  Implementos: ";
        if (actual_implemento == nullptr)
        {
            cout << "La mochila esta vacia" << endl; // Antes decia "ninguno". Verificar
        }
        else
        {
            cout << endl;
            while (actual_implemento != nullptr)
            {
                cout << "    - " << actual_implemento->nombre_implemento << endl;
                actual_implemento = actual_implemento->siguiente;
            }
        }

        // Mostrar poderes de la mochila
        Poder_magico *actual_poder = actual_personaje->mimochila->poderes;
        cout << "  Poderes Magicos: ";
        if (actual_poder == nullptr)
        {
            cout << "Ninguno" << endl;
        }
        else
        {
            cout << endl;
            while (actual_poder != nullptr)
            {
                cout << "    - " << actual_poder->nombre_poder << endl;
                actual_poder = actual_poder->siguiente;
            }
        }
        cout << endl;
        actual_personaje = actual_personaje->siguiente; // Pasa al siguiente personaje
    }
    cout << "\n No hay mas personajes en el equipo\n\n ";
}

void eliminar_personaje_jugar(personaje *&lista_jugar)
{
    if (cantidad_personajes_jugar == 0)
    {
        cout << "No hay personajes disponibles para eliminar. \n";
        cout << "Eliminacion fallida.\n";
        return;
    }

    int identificador = 0;
    cout << "Los personajes en el equipo son: \n";
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
        // Liberar la memoria de la mochila del personaje a eliminar
        // implemento
        Implemento *actual_implemento = actual->mimochila->implementos;
        while (actual_implemento != nullptr)
        {
            Implemento *siguiente_implemento = actual_implemento->siguiente;
            delete actual_implemento;
            actual_implemento = siguiente_implemento;
        }
        // poder magico.
        Poder_magico *actual_poder = actual->mimochila->poderes;
        while (actual_poder != nullptr)
        {
            Poder_magico *siguiente_poder = actual_poder->siguiente;
            delete actual_poder;
            actual_poder = siguiente_poder;
        }

        // Eliminar el nodo del personaje de la lista
        // en caso sea el primer nodo.
        if (anterior == nullptr)
        {
            lista_jugar = actual->siguiente;
        }
        else
        { // en caso de que no lo sea
            anterior->siguiente = actual->siguiente;
        }

        cout << "Eliminacion del personaje " << actual->nombre << " exitosa.\n";
        delete actual;
        cantidad_personajes_jugar--;
    }
    else
    {
        cout << "El ID " << identificador << " No existe en el equipo. \n";
        cout << "Eliminacion fallida.\n";
    }
}

// para destrir todooo, los personajes con sus mochilas.
void destruir_personaje_jugar(personaje *&lista_jugar)
{
    personaje *actual = lista_jugar;
    while (actual != nullptr)
    {
        // para liberar la memoria de la mochila.
        // Implementos.
        Implemento *actual_implemento = actual->mimochila->implementos;
        while (actual_implemento != nullptr)
        {
            Implemento *siguiente_implemento = actual_implemento->siguiente;
            delete actual_implemento;
            actual_implemento = siguiente_implemento;
        }
        // poderes.
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

// para editar los personajes
void modificar_mochila(personaje *personajes_jugar, Implemento &Implementos, Poder_magico &poderes)
{
    if (cantidad_personajes_jugar == 0)
    {
        cout << "No hay personajes en el equipo para modificar\n";
        cout << "Modificacion fallida\n";
        return;
    }

    int identificador;
    cout << "Los personajes que forman parte del equipo son: \n";
    mostrar_personajes_jugar(personajes_jugar);
    cout << "Coloque el ID del personaje cuya mochila desea modificar: ";
    identificador = obtener_entero("");

    personaje *actual = personajes_jugar;
    while ((actual != nullptr) && (actual->identificador != identificador))
    {
        actual = actual->siguiente;
    }

    if (actual != nullptr)
    {
        cout << "Proceda a llenar nuevamente la mochila del personaje: " << actual->nombre << endl;

        // Liberamos la memoria de los poderes actuales.
        Implemento *actual_implemento = actual->mimochila->implementos;
        while (actual_implemento != nullptr)
        {
            Implemento *siguiente_implemento = actual_implemento->siguiente;
            delete actual_implemento;
            actual_implemento = siguiente_implemento;
        }
        actual->mimochila->implementos = nullptr; // la ponemos vacia

        // Liberar mos la memoria de los poderes actuales.
        Poder_magico *actual_poder = actual->mimochila->poderes;
        while (actual_poder != nullptr)
        {
            Poder_magico *siguiente_poder = actual_poder->siguiente;
            delete actual_poder;
            actual_poder = siguiente_poder;
        }
        actual->mimochila->poderes = nullptr; // la ponemso vacia.

        // se llama a la funcion llenar mochila.
        llenar_mochila(actual, Implementos, poderes);
        cout << "Actualización de la mochila completa para el personaje: " << actual->nombre << endl;
    }
    else
    {
        cout << "El ID " << identificador << " no existe en el equipo.\n";
        cout << "Modificación fallida.\n";
    }
}

// para crear el vetor de personaje para usarlo al momemto de jugar.
vector<personaje*> crear_vector_personajes(personaje *&lista){ // se le psa lista_personajes_jugar.
    personaje *actual =   lista->siguiente;
    vector<personaje*> nueva_lista;
    while (actual!=nullptr){
        nueva_lista.push_back(actual);
        actual=actual->siguiente;
    }
    return nueva_lista;
}
