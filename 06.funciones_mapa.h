#pragma once
#include "01.funciones_genericas.h" // Funciones generales para el programa

// Mapa
struct sala;
struct arista;
struct mapaGrafo;

struct sala // Salas
{
    int id;
    string nombre;
    vector<arista> lista_adyacentes;
    vector<personaje *> lista_heroes; // Lista con los personajes heroes en la sala.
    vector<personaje *> lista_orcos;  // Lista con los personajes orcos  en la sala.
    bool contiene_puerta_destino;     // Habra una lista que contenga todas las ubicaciones previas de la puerta, para evitar repeticiones
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

// Para el mapa (Salas)
int regulador_salas = 61; // empieza en 60 por el archivo.
int cantidad_salas = 0;

//----------------------------------- FUNCIONES MAPA ---------------------------------------
bool grafo_vacio(const mapaGrafo &grafo)
{
    if (grafo.mapa_salas.empty())
    {
        cout << "El mapa esta vacio" << endl;
        return true;
    }
    return false;
}

sala *encontrar_sala(const mapaGrafo &grafo, int idSalaBuscar) // Encuentra y devuelve la sala por su ID
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

sala *encontrar_sala_nombre(const mapaGrafo &grafo, string nombre_sala) // Encuentra y devuelve la sala por su Nombre
{
    if (grafo_vacio(grafo))
    {
        return nullptr;
    }

    sala *actual = nullptr;
    for (size_t i = 0; i < grafo.mapa_salas.size(); i++)
    {
        actual = grafo.mapa_salas[i];
        if (actual->nombre == nombre_sala)
        {
            return actual;
        }
    }
    return nullptr;
}

sala *verificar_existencia_sala(const mapaGrafo &grafo, string mensaje) // Funcion generica para verificar si la sala existe
{

    sala *sala_buscar = nullptr;
    int id_sala_verificar;

    if (grafo_vacio(grafo))
    {
        return nullptr;
    }

    id_sala_verificar = obtener_entero(mensaje);
    sala_buscar = encontrar_sala(grafo, id_sala_verificar);

    if (!sala_buscar) // Si la sala es igual a null (no existe):
    {
        cout << "La sala no existe" << endl;
        cout << "Saliendo al menu principal..." << endl;
        return sala_buscar;
    }
    return sala_buscar;
}

void mostrar_salas_grafo(const mapaGrafo &grafo) // Mostrar el grafo completo
{
    if (grafo_vacio(grafo))
    {
        return;
    }

    for (sala *salaActual : grafo.mapa_salas)
    {
        cout << salaActual->id << "." << salaActual->nombre << endl;
    }
    cout << endl;
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
        if (salaOrigen->lista_adyacentes[i].destino == salaOrigen)
        {
            cout << "La sala no puede ser adyacente a si misma en este juego" << endl;
            return;
        }
    }
    // Si no existe, la crea
    salaOrigen->lista_adyacentes.push_back({salaDestino, distancia});
    cout << "Adyacencia creada con exito" << endl;
}

void crear_adyacencia_usuario(mapaGrafo &grafo, sala *salaModificar) // Crea adyacencia manualmente
{

    sala *nuevaAdyacencia = nullptr;
    int idNuevaAdyacencia;

    // Comprueba si las IDs ingresadas existen
    nuevaAdyacencia = verificar_existencia_sala(grafo, "Ingrese el ID de la nueva sala adyacente: ");
    if (!nuevaAdyacencia)
    {
        return;
    }

    int distanciaNuevaAdyacencia = obtener_entero("Ingrese la distancia entre salas: ");

    crear_adyacencia(salaModificar, nuevaAdyacencia, distanciaNuevaAdyacencia);
}

void crear_sala(mapaGrafo &grafo, string nombre) // Funcion primitiva para crear salas e IDs
{
    sala *salaNueva = new sala;
    salaNueva->id = grafo.mapa_salas.size() + regulador_salas; // para que no se
    salaNueva->nombre = nombre;
    salaNueva->contiene_puerta_destino = false;
    grafo.mapa_salas.push_back(salaNueva);
}

void crear_sala_usuario(mapaGrafo &grafo) // Funcion manual para crear salas
{
    sala *sala_modificar = nullptr;
    int resp;
    int resp_interna;

    string nombreNuevaSala = devolver_string_verificada("Ingrese el nombre de la nueva sala: ");
    crear_sala(grafo, nombreNuevaSala);
    cout << "Sala " << nombreNuevaSala << " creada con exito" << endl;

    cout << "¿Desea agregarle adyacencias a la sala?" << endl;
    cout << "1. Si" << endl;
    cout << "2. No" << endl;
    resp = obtener_opcion();
    switch (resp)
    {
    case 1: // Pregunta para mostrar las salas. Agrega Adyacencias
    {
        cout << "¿Desea ver todas las salas del mapa?" << endl;
        cout << "1. Si" << endl;
        cout << "2. No" << endl;
        resp_interna = obtener_opcion();
        switch (resp_interna) // Para mostrar o no las salas del mapa
        {
        case 1: // Muestra las salas del mapa
        {
            cout << "-------------- Salas Del Juego --------------" << endl;
            mostrar_salas_grafo(grafo);
            break;
        }
        case 2: // No muestra las salas
        {
            cout << "No se mostraran las salas del mapa" << endl;
            break;
        }
        default: // Default
        {
            cout << "Ingrese una opcion valida" << endl;
            break;
        }
        }

        // Conseguir la sala por el nombre
        sala_modificar = encontrar_sala_nombre(grafo, nombreNuevaSala);
        crear_adyacencia_usuario(grafo, sala_modificar);
        break;
    }
    case 2: // No se crean adyacencias
    {
        cout << "No se crearan adyacencias para la sala" << endl;
        break;
    }
    default: // Default
    {
        cout << "Ingrese una opcion valida: " << endl;
        break;
    }
    }
}

void mostrar_adyacencias(const mapaGrafo &grafo, sala *salaOrigen) // Muestra las adyacencias de la sala origen
{
    if (grafo_vacio(grafo))
    {
        return;
    }

    if (salaOrigen == nullptr)
    {
        cout << "La sala no existe." << endl;
        return;
    }

    cout << salaOrigen->nombre << " tiene como adyacentes: " << endl;
    cout << "ID.Sala Adyacente" << "   " << "Distancia" << endl;
    for (arista &adyacente : salaOrigen->lista_adyacentes)
    {
        cout << adyacente.destino->id << "." << adyacente.destino->nombre << "      " << adyacente.distancia << endl;
    }
    cout << endl;
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

void borrar_sala_usuario(mapaGrafo &grafo) // Borrar sala del grafo y listas de adyacencias
{
    sala *salaBorrar = nullptr;
    int indiceBorrar;

    if (grafo_vacio(grafo))
    {
        return;
    }

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
                regulador_salas += 1;
            }
        }
    }

    // Se borra del grafo (vector)
    grafo.mapa_salas.erase(grafo.mapa_salas.begin() + indiceBorrar);

    // Se borra el auxiliar usado
    delete salaBorrar;
}

void borrar_sala(mapaGrafo &grafo, int sala_borrar_id) // Borra sala. Solo usar para destruir_grafo
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

void destruir_grafo(mapaGrafo &grafo) // Borra el grafo completo
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
    sala *nuevaAdyacencia = nullptr;
    int idNuevaAdyacencia;
    int idBorrarAdyacencia;
    int opcion = 0;

    if (grafo_vacio(grafo))
    {
        return;
    }

    sala_editar = encontrar_sala(grafo, id_sala_editar);

    if (!sala_editar)
    {
        return;
    }

    do
    {
        mostrar_adyacencias(grafo, sala_editar);
        cout << "Menu de Adyacencias" << endl;
        cout << "---------------------" << endl;
        cout << "1. Crear nueva adyacencia" << endl;
        cout << "2. Mostrar Adyacencias actuales" << endl;
        cout << "3. Borrar adyacencia existente" << endl;
        cout << "4. Cambiar distancia entre salas" << endl;
        cout << "5. Cancelar edicion" << endl;
        cout << "---------------------" << endl;

        opcion = obtener_opcion();

        switch (opcion)
        {
        case 1: // Agregar adyacencia
        {
            idNuevaAdyacencia = obtener_entero("Ingrese el ID de la nueva adyacencia: ");
            nuevaAdyacencia = encontrar_sala(grafo, idNuevaAdyacencia);
            // Comprobar que la sala para agregar exista en el grafo
            if (nuevaAdyacencia == nullptr) // Si no existe:
            {
                cout << "La sala no existe" << endl;
                cout << "Saliendo al menu principal..." << endl;
                return;
            }

            int distanciaNuevaAdyacencia = obtener_entero("Ingrese la distancia entre salas: ");
            // Crear adyacencia ya comprueba que no exista la adyacencia que se esta creando. Que no haya duplicados
            crear_adyacencia(sala_editar, nuevaAdyacencia, distanciaNuevaAdyacencia);
            break;
        }
        case 2:
        {
            mostrar_adyacencias(grafo, sala_editar);
            break;
        }
        case 3: // Borrar Adyacencia
        {
            sala_borrar = verificar_existencia_sala(grafo, "Ingrese el ID de la adyacencia a borrar: ");
            if (!sala_borrar)
            {
                return;
            }
            idBorrarAdyacencia = sala_borrar->id;
            borrar_adyacencia(sala_editar, idBorrarAdyacencia);
            break;
        }
        case 4: // Modificar Distancias entre salas
        {
            sala_objetivo = verificar_existencia_sala(grafo, "Ingrese el ID de la sala con la distancia a modificar: ");
            if (!sala_objetivo)
            {
                return;
            }
            cambiar_distancias_sala(grafo, sala_editar->id, sala_objetivo->id);
            break;
        }
        case 5: // Salir al menu principal
        {
            cout << "Saliendo al menu principal" << endl;
            break;
        }
        default: // Default
        {
            cout << "Opcion invalida." << endl;
            break;
        }
        }
    } while (opcion != 5);
}

void editar_sala(mapaGrafo &grafo, int id_sala_editar) // Editar sala
{
    sala *sala_editar = nullptr;
    int opcion;
    string nuevo_nombre;

    if (grafo_vacio(grafo)) // Si el grafo esta vacio:
    {
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
        cout << "Menu de Edicion de Sala" << endl;
        cout << "---------------------" << endl;
        cout << "Actualmente editando Sala: " << sala_editar->id << "." << sala_editar->nombre << endl;
        cout << "---------------------" << endl;
        cout << "1. Editar Nombre" << endl;
        cout << "2. Editar Adyacencias" << endl;
        cout << "3. Cancelar Edicion" << endl;
        cout << "---------------------" << endl;

        opcion = obtener_opcion();

        switch (opcion)
        {
        case 1: // Editar nombre sala
        {
            nuevo_nombre = devolver_string_verificada("Ingrese el nuevo nombre para la sala: ");
            sala_editar->nombre = nuevo_nombre;
            break;
        }
        case 2: // Editar Adyacencias
        {
            editar_adyacencias(grafo, id_sala_editar);
            break;
        }
        case 3: // Cancelar edicion
        {
            cout << "Se cancelo la edicion de la sala" << endl;
            break;
        }
        default:
        {
            cout << "Opcion invalida." << endl;
            break;
        }
        }
    } while (opcion != 3);
}
