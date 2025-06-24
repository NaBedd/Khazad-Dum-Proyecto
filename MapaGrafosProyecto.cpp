#include <iostream>  // para operaciones de entrada y salida de datos.
#include <string>    // para manejar string
#include <limits.h>  // para los punteros NEW.
#include <algorithm> // para usar .erase
#include <vector>
using namespace std;

// Funcion especifica para el menu de opciones
// Se ve mas bonito asi

// Booleano para verificar string:
bool verificar_string(string respuesta)
{

    // Eliminar espacios en blanco al inicio y final
    respuesta.erase(remove(respuesta.begin(), respuesta.end(), ' '), respuesta.end());

    // Si la respuesta esta vacia, retorna Falso
    if (respuesta.empty())
    {
        return false;
    }

    for (char caracter : respuesta) // itera por cada elemento de la cadena.
    {
        if (isdigit(caracter)) // Si caracter es un numero, retorna Falso
        {
            return false;
        }
    }
    return true; // Si no hay numeros, retorna true
}

// Pide y devuelve valor del string ya verificado
// Mas practico para implementar en codigo
string devolver_string_verificada(const string &mensaje)
{
    string entrada;

    // Imprime el mensaje indicado y pide respuesta
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

// Función para validar y leer un entero con mensaje personalizado
int obtener_entero(const string &mensaje)
{
    string entrada;
    int valor;
    const size_t MAX_DIGITOS = 10; // Un límite seguro para la mayoría de los 'int'

    while (true)
    {
        cout << mensaje;
        getline(cin, entrada);

        bool es_valido = true;

        if (entrada == "0")
        {
            es_valido = false;
        }

        if (entrada.length() > MAX_DIGITOS)
        {
            es_valido = false;
            cout << "Error. El número ingresado es demasiado grande.\n";
            continue; // Volver al inicio del bucle para pedir una nueva entrada
        }

        for (char c : entrada)
        {
            if (!isdigit(c))
            {
                es_valido = false;
                break;
            }
        }

        if (es_valido && !entrada.empty())
        {
            try
            {
                valor = stoi(entrada);
                return valor;
            }
            catch (const out_of_range &oor)
            {
                cout << "Error. El número ingresado está fuera del rango permitido.\n";
                // No es estrictamente necesario aquí si ya validamos la longitud,
                // pero es una buena práctica para cubrir otros casos.
            }
        }
        else
        {
            cout << "Error. Ingrese solo números naturales.\n";
        }
    }
}

struct sala;
struct arista;
struct mapaGrafo;
struct personaje_heroe;
struct personaje_orco;
int regulador_id_salas = 0;

struct sala // Salas
{
    int id;
    string nombre;
    vector<arista> lista_adyacentes;
    vector<personaje_heroe> lista_heroes; // Lista con los personajes heroes en la sala.
    vector<personaje_orco> lista_orcos;   // Lista con los personajes orcos  en la sala.
    bool contiene_puerta_destino;         // Habra una lista que contenga todas las ubicaciones previas de la puerta, para evitar repeticiones
};

struct arista // Caminos entre las salas
{
    sala *destino;
    int distancia;
};

struct mapaGrafo // Mapa que contiene todas las salas
{
    vector<sala *> mapa_salas;
};

sala *verificar_existencia_sala(const mapaGrafo &grafo, string mensaje) // Funcion generica para verificar si la sala existe
{

    sala *sala_buscar = nullptr;
    int id_sala_verificar;

    id_sala_verificar = obtener_entero(mensaje);
    sala_buscar = encontrar_sala(grafo, id_sala_verificar);

    if (sala_buscar == nullptr) // Si no existe:
    {
        cout << "La sala no existe" << endl;
        cout << "Saliendo al menu principal..." << endl;
        return sala_buscar;
    }
    return sala_buscar;
}

void crear_sala(mapaGrafo &grafo, string nombre) // Funcion primitiva para crear salas e IDs
{
    sala *salaNueva = new sala;
    salaNueva->id = grafo.mapa_salas.size() + 1 + regulador_id_salas; // La id es igual al tamaño total del grafo. +1 para que no haya ID 0
    salaNueva->nombre = nombre;
    salaNueva->contiene_puerta_destino = false;
    grafo.mapa_salas.push_back(salaNueva);
}

void crear_sala_usuario(mapaGrafo &grafo) // Funcion manual para crear salas
{
    string nombreNuevaSala = devolver_string_verificada("Ingrese el nombre de la sala: ");
    crear_sala(grafo, nombreNuevaSala);
}

void mostrar_salas_grafo(const mapaGrafo &grafo) // Mostrar el grafo completo
{
    for (sala *salaActual : grafo.mapa_salas)
    {
        cout << salaActual->id << "." << salaActual->nombre << endl;
    }
    cout << endl;
}

void mostrar_adyacencias(sala *salaOrigen) // Muestra las adyacencias de la sala origen
{
    cout << salaOrigen->nombre << " tiene como adyacentes: " << endl;
    cout << "ID.Sala Adyacente" << "   " << "Distancia" << endl;
    for (arista &adyacente : salaOrigen->lista_adyacentes)
    {
        cout << adyacente.destino->id << "." << adyacente.destino->nombre << "      " << adyacente.distancia << endl;
    }
    cout << endl;
}

sala *encontrar_sala(const mapaGrafo &grafo, int idSalaBuscar) // Encuentra una sala por ID
{
    for (sala *sala : grafo.mapa_salas)
    {
        if (idSalaBuscar == sala->id)
        {
            return sala;
        }
    }
    return nullptr;
}

int encontrar_indice_sala(const mapaGrafo &grafo, int idSalaBuscar) // Devuelve el Indice de la sala en el grafo
{
    // Se recorre el grafo y devuelve el indice
    // Si no se encuentra, devuelve -1
    for (size_t i = 0; i < grafo.mapa_salas.size(); i++)
    {
        if (idSalaBuscar == grafo.mapa_salas[i]->id)
        {
            return i;
        }
    }
    return -1;
}

void crear_adyacencia(sala *salaOrigen, sala *salaDestino, int distancia) // Crea una adyacencia
{
    // Comprueba que no exista:
    for (size_t i = 0; i < salaOrigen->lista_adyacentes.size(); i++)
    {
        if (salaOrigen->lista_adyacentes[i].destino == salaDestino)
        {
            cout << "Ya existe una adyacencia entre " << salaOrigen->lista_adyacentes[i].destino->nombre << " y " << salaDestino->nombre << endl;
            cout << "Puede editar la adyacencia en el menu principal si desea modificarla" << endl;
            return;
        }
    }
    // Si no existe, la crea
    salaOrigen->lista_adyacentes.push_back({salaDestino, distancia});
    cout << "Adyacencia creada con exito" << endl;
}

void crear_adyacencia_usuario(mapaGrafo &grafo) // Crea adyacencia manualmente
{
    sala *salaModificar = nullptr;
    sala *nuevaAdyacencia = nullptr;
    int idSalaModificar;
    int idNuevaAdyacencia;

    cout << "Salas disponibles: " << endl;
    mostrar_salas_grafo(grafo);

    // Comprueba si las IDs ingresadas existen
    salaModificar = verificar_existencia_sala(grafo, "Ingrese el ID de la sala a modificar: ");
    if (!salaModificar)
    {
        return;
    }

    nuevaAdyacencia = verificar_existencia_sala(grafo, "Ingrese el ID de la nueva sala adyacente: ");
    if (!nuevaAdyacencia)
    {
        return;
    }

    int distanciaNuevaAdyacencia = obtener_entero("Ingrese la distancia entre salas: ");

    crear_adyacencia(salaModificar, nuevaAdyacencia, distanciaNuevaAdyacencia);
}

void borrar_sala_usuario(mapaGrafo &grafo) // Borrar sala del grafo y listas de adyacencias
{
    sala *salaBorrar = nullptr;
    int indiceBorrar;

    salaBorrar = verificar_existencia_sala(grafo, "Ingrese el ID de la sala a borrar: ");
    if (!salaBorrar)
    {
        return;
    }

    // No valido que el indice no exista porque ya lo valide arriba con la sala
    indiceBorrar = encontrar_indice_sala(grafo, salaBorrar->id);

    // Es removido de la lista de adyacencias de todas las salas que lo apunten
    for (size_t i = 0; i < grafo.mapa_salas.size(); i++)
    {
        sala *actual = grafo.mapa_salas[i];
        for (int j = actual->lista_adyacentes.size() - 1; j >= 0; j--) // Se recorre en reversa para evitar problemas
        {
            if (salaBorrar->id == actual->lista_adyacentes[j].destino->id)
            {
                actual->lista_adyacentes.erase(actual->lista_adyacentes.begin() + j);
                regulador_id_salas += 1;
            }
        }
    }

    // Se borra del grafo (vector)
    grafo.mapa_salas.erase(grafo.mapa_salas.begin() + indiceBorrar);

    // Se borra el auxiliar usado
    delete salaBorrar;
}

void borrar_sala(mapaGrafo &grafo, int sala_borrar_id) // Borra sala. Solo usar para borrar_grafo
{
    // Esta funcion solo se usa para eliminar el grafo completo
    // No agrega 1 al regulador de IDs
    {
        sala *salaBorrar = nullptr;
        int indiceBorrar;

        salaBorrar = encontrar_sala(grafo, sala_borrar_id);
        indiceBorrar = encontrar_indice_sala(grafo, salaBorrar->id);

        // Es removido de la lista de adyacencias de todas las salas que lo apunten
        for (size_t i = 0; i < grafo.mapa_salas.size(); i++)
        {
            sala *actual = grafo.mapa_salas[i];
            for (int j = actual->lista_adyacentes.size() - 1; j >= 0; j--) // Se recorre en reversa para evitar problemas
            {
                if (salaBorrar->id == actual->lista_adyacentes[j].destino->id)
                {
                    actual->lista_adyacentes.erase(actual->lista_adyacentes.begin() + j);
                }
            }
        }

        // Se borra del grafo (vector)
        grafo.mapa_salas.erase(grafo.mapa_salas.begin() + indiceBorrar);

        // Se borra el auxiliar usado
        delete salaBorrar;
    }
}

void borrar_grafo(mapaGrafo &grafo) // Borra el grafo completo
{
    while (!grafo.mapa_salas.empty()) // Mientras no este vacio
    {
        borrar_sala(grafo, grafo.mapa_salas[0]->id); // Borra siempre el primero
    }
}

void borrar_adyacencia(sala *salaOrigen, int idAdyacenciaBorrar) // Borra una sala de la lista de adyacencias de la sala origen
{
    arista adyacenciaActual;
    bool existe = false;

    if (salaOrigen->lista_adyacentes.empty()) // Si no hay adyacencias, no hace nada
    {
        cout << "La sala no tiene adyacencias" << endl;
        return;
    }
    else // Borrado de la adyacencia:

    {
        for (int i = salaOrigen->lista_adyacentes.size() - 1; i >= 0; i--)
        {
            adyacenciaActual = salaOrigen->lista_adyacentes[i];
            if (adyacenciaActual.destino->id == idAdyacenciaBorrar)
            {
                existe = true;
                salaOrigen->lista_adyacentes.erase(salaOrigen->lista_adyacentes.begin() + i);
                cout << "Adyacencia borrada con exito" << endl;
            }
        }
        if (!existe)
        {
            cout << "La adyacencia no existe" << endl;
            return;
        }
    }
}

void cambiar_distancias_sala(mapaGrafo &grafo, int id_sala_editar, int id_sala_destino) // Cambia las distancias entre salas en ambas direcciones
{
    sala *sala_origen = encontrar_sala(grafo, id_sala_editar);
    sala *sala_destino = encontrar_sala(grafo, id_sala_destino);

    int nueva_distancia;
    bool encontrada = false;

    if (!sala_origen || !sala_destino)
    {
        cout << "Una de las salas no existe." << endl;
        return;
    }

    // Cambiar distancia de origen a destino
    for (size_t i = 0; i < sala_origen->lista_adyacentes.size(); i++)
    {
        if (sala_origen->lista_adyacentes[i].destino->id == id_sala_destino)
        {
            nueva_distancia = obtener_entero("Ingrese la nueva distancia: ");
            sala_origen->lista_adyacentes[i].distancia = nueva_distancia;
            cout << "Distancia actualizada de " << sala_origen->nombre << " a " << sala_destino->nombre << endl;
            encontrada = true;
            break;
        }
    }
    if (!encontrada)
    {
        cout << "No existe adyacencia entre las salas." << endl;
        return;
    }
    // Cambiar distancia de destino a origen (si existe)
    for (size_t i = 0; i < sala_destino->lista_adyacentes.size(); i++)
    {
        if (sala_destino->lista_adyacentes[i].destino->id == id_sala_editar)
        {
            sala_destino->lista_adyacentes[i].distancia = nueva_distancia;
            cout << "Distancia actualizada de " << sala_destino->nombre << " a " << sala_origen->nombre << endl;
            break;
        }
    }
}

void editar_adyacencias(mapaGrafo &grafo, int id_sala_editar) // Crud de adyacencias
{
    sala *sala_editar = nullptr;
    sala *sala_objetivo = nullptr;
    sala *sala_borrar = nullptr;
    sala *nuevaAdyacencia;
    int idNuevaAdyacencia;
    int idBorrarAdyacencia;
    int opcion;

    if (grafo.mapa_salas.empty()) // Si el grafo esta vacio:
    {
        cout << "Todavia no existe ninguna sala" << endl;
        return;
    }

    sala_editar = encontrar_sala(grafo, id_sala_editar);

    if (!sala_editar)
    {
        return;
    }

    do
    {
        mostrar_adyacencias(sala_editar);
        cout << "¿Que desea hacer con las adyacencias?" << endl;
        cout << "1. Crear nueva adyacencia" << endl;
        cout << "2. Borrar adyacencia existente" << endl;
        cout << "3. Cambiar distancia de adyacencias" << endl;
        cout << "4. Salir" << endl;
        opcion = obtener_entero("Ingrese la opcion: ");

        switch (opcion)
        {
        case 1:
            idNuevaAdyacencia = obtener_entero("Ingrese el ID de la nueva adyacencia: ");
            nuevaAdyacencia = encontrar_sala(grafo, idNuevaAdyacencia);
            // Comprobar que la sala para agregar exista
            if (nuevaAdyacencia == nullptr) // Si no existe:
            {
                cout << "La sala no existe" << endl;
                cout << "Saliendo al menu principal..." << endl;
                return;
            }

            int distanciaNuevaAdyacencia = obtener_entero("Ingrese la distancia entre salas: ");
            crear_adyacencia(sala_editar, nuevaAdyacencia, distanciaNuevaAdyacencia);
            break;

        case 2:
            sala_borrar = verificar_existencia_sala(grafo, "Ingrese el ID de la adyacencia a borrar: ");
            if (!sala_borrar)
            {
                return;
            }
            idBorrarAdyacencia = sala_borrar->id;
            borrar_adyacencia(sala_editar, idBorrarAdyacencia);
            break;

        case 3:
            sala_objetivo = verificar_existencia_sala(grafo, "Ingrese el ID de la sala con la distancia a modificar: ");
            if (!sala_objetivo)
            {
                return;
            }
            cambiar_distancias_sala(grafo, sala_editar->id, sala_objetivo->id);
            break;
        case 4:
            cout << "Saliendo al menu principal" << endl;
            break;
        default:
            cout << "Opcion invalida." << endl;
            break;
        }
    } while (opcion != 4);
}

void editar_sala(mapaGrafo &grafo, int id_sala_editar) // Editar sala
{
    sala *sala_editar = nullptr;
    int opcion;
    string nuevo_nombre;

    if (grafo.mapa_salas.empty()) // Si el grafo esta vacio:
    {
        cout << "Todavia no existe ninguna sala" << endl;
        return;
    }

    // Comprobar que la sala exista
    sala_editar = encontrar_sala(grafo, id_sala_editar);
    if (sala_editar == nullptr) // Si sala no existe:
    {
        cout << "La sala no existe" << endl;
        cout << "Saliendo al menu principal..." << endl;
        return;
    }

    do
    {
        // Menu de edicion de la sala
        cout << "¿Que desea editar de la sala " << sala_editar->id << "." << sala_editar->nombre << "?" << endl;
        cout << "1. Nombre" << endl;
        cout << "2. Adyacencias" << endl;
        cout << "3. Cancelar" << endl;
        opcion = obtener_entero("Ingrese la opcion que desea editar: ");

        switch (opcion)
        {
        case 1:
            nuevo_nombre = devolver_string_verificada(" Ingrese el nuevo nombre para la sala ");
            sala_editar->nombre = nuevo_nombre;
            break;

        case 2:
            editar_adyacencias(grafo);
            break;

        case 3:
            cout << "Se cancelo la edicion de la sala" << endl;
            break;
        default:
            cout << "Opcion invalida." << endl;

            break;
        }
    } while (opcion != 3);
}
