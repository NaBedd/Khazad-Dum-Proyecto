#pragma once
#include "01.funciones_genericas.h" // Funciones generales para el programa

// ACOMODAR EL "Retornando..." PENSAR EN ALGO MAS BONITO Y GENERICO

// Mapa
struct sala;
struct arista;
struct mapaGrafo;

// Para el mapa (Salas)
int regulador_salas = 61; // empieza en 60 por el archivo.

queue<int> ids_libres;
int siguiente_id_sala = 61; // Por el archivo

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

//----------------------------------- FUNCIONES MAPA ---------------------------------------
bool grafo_vacio(const mapaGrafo &grafo)
{
    if (grafo.mapa_salas.empty())
    {
        printf("\033[0;31m"); // Rojo
        cout << "El mapa esta vacio" << endl;
        printf("\033[0;37m"); // Gris claro
        return true;
    }
    return false;
}

sala *encontrar_sala(const mapaGrafo &grafo, int idSalaBuscar)
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

sala *encontrar_sala_nombre(const mapaGrafo &grafo, string nombre_sala)
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

sala *verificar_existencia_sala(const mapaGrafo &grafo, string mensaje)
{
    sala *sala_buscar = nullptr;
    int id_sala_verificar;

    if (grafo_vacio(grafo))
    {
        return nullptr;
    }

    id_sala_verificar = obtener_entero(mensaje);
    sala_buscar = encontrar_sala(grafo, id_sala_verificar);

    if (!sala_buscar)
    {
        printf("\033[0;31m"); // Rojo
        cout << "La sala no existe" << endl;
        printf("\033[0;37m"); // Gris claro
        return sala_buscar;
    }
    return sala_buscar;
}

void mostrar_salas_grafo(const mapaGrafo &grafo)
{
    if (grafo_vacio(grafo))
    {
        return;
    }

    printf("\033[0;33m"); // Amarillo
    for (sala *salaActual : grafo.mapa_salas)
    {
        cout << salaActual->id << "." << salaActual->nombre << endl;
    }
    printf("\033[0;37m"); // Gris claro
    cout << endl;
}

void preguntar_mostrar_salas(const mapaGrafo &grafo)
{
    int resp_interna;

    if (grafo_vacio(grafo))
    {
        return;
    }

    printf("\033[0;33m"); // Amarillo
    cout << "¿Desea ver todas las salas del mapa?" << endl;
    printf("\033[0;36m"); // Cyan
    cout << "   1. Si" << endl;
    cout << "   2. No" << endl;
    printf("\033[0;37m"); // Gris claro
    resp_interna = obtener_opcion();
    switch (resp_interna)
    {
    case 1:
        printf("\033[0;33m"); // Amarillo
        cout << "-------------- Salas Del Juego --------------" << endl;
        printf("\033[0;37m");
        mostrar_salas_grafo(grafo);
        break;
    case 2:
        printf("\033[0;33m");
        cout << "No se mostraran las salas del mapa" << endl;
        printf("\033[0;37m");
        break;
    default:
        printf("\033[0;31m"); // Rojo
        cout << "Ingrese una opcion valida" << endl;
        printf("\033[0;37m");
        break;
    }
}

void crear_adyacencia(sala *salaOrigen, sala *salaDestino, int distancia)
{
    for (size_t i = 0; i < salaOrigen->lista_adyacentes.size(); i++)
    {
        if (salaOrigen->lista_adyacentes[i].destino == salaDestino)
        {
            printf("\033[0;33m"); // Amarillo
            cout << "Ya existe una adyacencia entre " << salaOrigen->lista_adyacentes[i].destino->nombre << " y " << salaDestino->nombre << endl;
            cout << "Puede editar la adyacencia en el menu principal si desea modificarla" << endl;
            printf("\033[0;37m");
            return;
        }
    }
    salaOrigen->lista_adyacentes.push_back({salaDestino, distancia});
    printf("\033[0;32m"); // Verde
    cout << "Adyacencia creada con exito" << endl;
    printf("\033[0;37m");
}

void crear_adyacencia_usuario(mapaGrafo &grafo, sala *salaModificar)
{
    sala *nuevaAdyacencia = nullptr;
    int idNuevaAdyacencia;

    nuevaAdyacencia = verificar_existencia_sala(grafo, "Ingrese el ID de la nueva sala adyacente: ");
    if (!nuevaAdyacencia)
    {
        return;
    }

    int distanciaNuevaAdyacencia = obtener_entero("Ingrese la distancia entre salas: ");

    crear_adyacencia(salaModificar, nuevaAdyacencia, distanciaNuevaAdyacencia);
}

void crear_sala(mapaGrafo &grafo, string nombre)
{
    sala *salaNueva = new sala;
    if (!ids_libres.empty())
    {
        salaNueva->id = ids_libres.front();
        ids_libres.pop();
    }
    else
    {
        salaNueva->id = siguiente_id_sala++;
    }
    salaNueva->nombre = nombre;
    salaNueva->contiene_puerta_destino = false;
    grafo.mapa_salas.push_back(salaNueva);
}

void crear_sala_usuario(mapaGrafo &grafo)
{
    sala *sala_modificar = nullptr;
    int resp;
    int resp_interna;

    string nombreNuevaSala = devolver_string_verificada("Ingrese el nombre de la nueva sala: ");
    crear_sala(grafo, nombreNuevaSala);
    printf("\033[0;32m"); // Verde
    cout << "Sala " << nombreNuevaSala << " creada con exito" << endl;
    printf("\033[0;37m");

    printf("\033[0;33m"); // Amarillo
    cout << "¿Desea agregarle adyacencias a la sala?" << endl;
    printf("\033[0;36m"); // Cyan
    cout << "   1. Si" << endl;
    cout << "   2. No" << endl;
    printf("\033[0;37m");
    resp = obtener_opcion();
    switch (resp)
    {
    case 1:
        printf("\033[0;33m");
        cout << "¿Desea ver todas las salas del mapa?" << endl;
        printf("\033[0;36m");
        cout << "   1. Si" << endl;
        cout << "   2. No" << endl;
        printf("\033[0;37m");
        resp_interna = obtener_opcion();
        switch (resp_interna)
        {
        case 1:
            printf("\033[0;33m");
            cout << "-------------- Salas Del Juego --------------" << endl;
            printf("\033[0;37m");
            mostrar_salas_grafo(grafo);
            break;
        case 2:
            printf("\033[0;33m");
            cout << "No se mostraran las salas del mapa" << endl;
            printf("\033[0;37m");
            break;
        default:
            printf("\033[0;31m");
            cout << "Ingrese una opcion valida" << endl;
            printf("\033[0;37m");
            break;
        }

        sala_modificar = encontrar_sala_nombre(grafo, nombreNuevaSala);
        crear_adyacencia_usuario(grafo, sala_modificar);
        break;
    case 2:
        printf("\033[0;33m");
        cout << "No se crearon adyacencias para la sala" << endl;
        printf("\033[0;37m");
        break;
    default:
        printf("\033[0;31m");
        cout << "Ingrese una opcion valida: " << endl;
        printf("\033[0;37m");
        break;
    }
}

void mostrar_adyacencias(sala *salaOrigen)
{
    if (salaOrigen == nullptr)
    {
        printf("\033[0;31m");
        cout << "La sala no existe." << endl;
        printf("\033[0;37m");
        return;
    }
    if (salaOrigen->lista_adyacentes.empty())
    {
        printf("\033[0;31m");
        cout << "La sala no tiene adyacencias" << endl;
        printf("\033[0;37m");
        return;
    }

    printf("\033[0;33m");
    cout << "Adyacentes de " << salaOrigen->nombre << "\": " << endl;
    cout << "ID.Sala Adyacente   Distancia" << endl;
    cout << "---------------------" << endl;
    printf("\033[0;37m");
    for (arista &adyacente : salaOrigen->lista_adyacentes)
    {
        cout << adyacente.destino->id << "." << adyacente.destino->nombre << "      " << adyacente.distancia << endl;
    }
    cout << endl;
}

int encontrar_indice_sala(const mapaGrafo &grafo, int idSalaBuscar)
{
    for (size_t i = 0; i < grafo.mapa_salas.size(); i++)
    {
        if (idSalaBuscar == grafo.mapa_salas[i]->id)
        {
            return i;
        }
    }
    return -1;
}

void borrar_sala_usuario(mapaGrafo &grafo)
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

    indiceBorrar = encontrar_indice_sala(grafo, salaBorrar->id);

    for (size_t i = 0; i < grafo.mapa_salas.size(); i++)
    {
        sala *actual = grafo.mapa_salas[i];
        for (int j = actual->lista_adyacentes.size() - 1; j >= 0; j--)
        {
            if (salaBorrar->id == actual->lista_adyacentes[j].destino->id)
            {
                actual->lista_adyacentes.erase(actual->lista_adyacentes.begin() + j);
                regulador_salas += 1;
            }
        }
    }

    ids_libres.push(salaBorrar->id);

    grafo.mapa_salas.erase(grafo.mapa_salas.begin() + indiceBorrar);
    delete salaBorrar;
}

void borrar_sala(mapaGrafo &grafo, int sala_borrar_id)
{
    sala *salaBorrar = nullptr;
    int indiceBorrar;

    salaBorrar = encontrar_sala(grafo, sala_borrar_id);
    indiceBorrar = encontrar_indice_sala(grafo, salaBorrar->id);

    for (size_t i = 0; i < grafo.mapa_salas.size(); i++)
    {
        sala *actual = grafo.mapa_salas[i];
        for (int j = actual->lista_adyacentes.size() - 1; j >= 0; j--)
        {
            if (salaBorrar->id == actual->lista_adyacentes[j].destino->id)
            {
                actual->lista_adyacentes.erase(actual->lista_adyacentes.begin() + j);
            }
        }
    }

    for (int j = salaBorrar->lista_heroes.size() - 1; j >= 0; j--)
    {
        salaBorrar->lista_heroes.erase(salaBorrar->lista_heroes.begin() + j);
    }

    for (int j = salaBorrar->lista_orcos.size() - 1; j >= 0; j--)
    {
        salaBorrar->lista_orcos.erase(salaBorrar->lista_orcos.begin() + j);
    }

    grafo.mapa_salas.erase(grafo.mapa_salas.begin() + indiceBorrar);

    delete salaBorrar;
}

void destruir_grafo(mapaGrafo &grafo)
{
    while (!grafo.mapa_salas.empty())
    {
        borrar_sala(grafo, grafo.mapa_salas[0]->id);
    }
}

void borrar_adyacencia(sala *salaOrigen, int idAdyacenciaBorrar)
{
    arista adyacenciaActual;
    bool existe = false;

    if (salaOrigen->lista_adyacentes.empty())
    {
        printf("\033[0;31m");
        cout << "La sala no tiene adyacencias" << endl;
        printf("\033[0;37m");
        return;
    }
    else
    {
        for (int i = salaOrigen->lista_adyacentes.size() - 1; i >= 0; i--)
        {
            adyacenciaActual = salaOrigen->lista_adyacentes[i];
            if (adyacenciaActual.destino->id == idAdyacenciaBorrar)
            {
                existe = true;
                salaOrigen->lista_adyacentes.erase(salaOrigen->lista_adyacentes.begin() + i);
                printf("\033[0;32m");
                cout << "Adyacencia borrada con exito" << endl;
                printf("\033[0;37m");
            }
        }
        if (!existe)
        {
            printf("\033[0;31m");
            cout << "La adyacencia no existe" << endl;
            printf("\033[0;37m");
            return;
        }
    }
}

void cambiar_distancias_sala(mapaGrafo &grafo, int id_sala_editar, int id_sala_destino)
{
    sala *sala_origen = encontrar_sala(grafo, id_sala_editar);
    sala *sala_destino = encontrar_sala(grafo, id_sala_destino);

    int nueva_distancia;
    bool encontrada = false;

    if (!sala_origen || !sala_destino)
    {
        printf("\033[0;31m");
        cout << "Una de las salas no existe." << endl;
        printf("\033[0;37m");
        return;
    }

    for (size_t i = 0; i < sala_origen->lista_adyacentes.size(); i++)
    {
        if (sala_origen->lista_adyacentes[i].destino->id == id_sala_destino)
        {
            nueva_distancia = obtener_entero("Ingrese la nueva distancia: ");
            sala_origen->lista_adyacentes[i].distancia = nueva_distancia;
            printf("\033[0;32m");
            cout << "Distancia actualizada de " << sala_origen->nombre << " a " << sala_destino->nombre << endl;
            printf("\033[0;37m");
            encontrada = true;
            break;
        }
    }
    if (!encontrada)
    {
        printf("\033[0;31m");
        cout << "No existe adyacencia entre las salas." << endl;
        printf("\033[0;37m");
        return;
    }
    for (size_t i = 0; i < sala_destino->lista_adyacentes.size(); i++)
    {
        if (sala_destino->lista_adyacentes[i].destino->id == id_sala_editar)
        {
            sala_destino->lista_adyacentes[i].distancia = nueva_distancia;
            printf("\033[0;32m");
            cout << "Distancia actualizada de " << sala_destino->nombre << " a " << sala_origen->nombre << endl;
            printf("\033[0;37m");
            break;
        }
    }
}

void editar_adyacencias(mapaGrafo &grafo, int id_sala_editar)
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
        mostrar_adyacencias(sala_editar);
        printf("\033[0;33m");
        cout << "Menu de Adyacencias" << endl;
        cout << "---------------------" << endl;
        printf("\033[0;36m");
        cout << "1. Crear nueva adyacencia" << endl;
        cout << "2. Mostrar Adyacencias actuales" << endl;
        cout << "3. Borrar adyacencia existente" << endl;
        cout << "4. Cambiar distancia entre salas" << endl;
        cout << "5. Cancelar edicion" << endl;
        printf("\033[0;33m");
        cout << "---------------------" << endl;
        printf("\033[0;37m");

        opcion = obtener_opcion();

        switch (opcion)
        {
        case 1:
        {
            idNuevaAdyacencia = obtener_entero("Ingrese el ID de la nueva adyacencia: ");
            nuevaAdyacencia = encontrar_sala(grafo, idNuevaAdyacencia);
            if (nuevaAdyacencia == nullptr)
            {
                printf("\033[0;31m");
                cout << "La sala no existe" << endl;
                printf("\033[0;37m");
                return;
            }

            int distanciaNuevaAdyacencia = obtener_entero("Ingrese la distancia entre salas: ");
            crear_adyacencia(sala_editar, nuevaAdyacencia, distanciaNuevaAdyacencia);
            break;
        }
        case 2:
        {
            mostrar_adyacencias(sala_editar);
            break;
        }
        case 3:
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
        case 4:
        {
            sala_objetivo = verificar_existencia_sala(grafo, "Ingrese el ID de la sala con la distancia a modificar: ");
            if (!sala_objetivo)
            {
                return;
            }
            cambiar_distancias_sala(grafo, sala_editar->id, sala_objetivo->id);
            break;
        }
        case 5:
        {
            printf("\033[0;33m");
            cout << "Saliendo al menu principal" << endl;
            printf("\033[0;37m");
            break;
        }
        default:
        {
            printf("\033[0;31m");
            cout << "Opcion invalida." << endl;
            printf("\033[0;37m");
            break;
        }
        }
    } while (opcion != 5);
}

void editar_sala(mapaGrafo &grafo, int id_sala_editar)
{
    sala *sala_editar = nullptr;
    int opcion;
    string nuevo_nombre;

    if (grafo_vacio(grafo))
    {
        return;
    }

    sala_editar = encontrar_sala(grafo, id_sala_editar);
    if (sala_editar == nullptr)
    {
        printf("\033[0;31m");
        cout << "La sala no existe" << endl;
        printf("\033[0;37m");
        return;
    }

    do
    {
        printf("\033[0;33m");
        cout << "Menu de Edicion de Sala" << endl;
        cout << "---------------------" << endl;
        printf("\033[0;36m");
        cout << "Actualmente editando Sala: " << sala_editar->id << "." << sala_editar->nombre << endl;
        printf("\033[0;33m");
        cout << "---------------------" << endl;
        cout << "1. Editar Nombre" << endl;
        cout << "2. Editar Adyacencias" << endl;
        cout << "3. Cancelar Edicion" << endl;
        printf("\033[0;37m");

        opcion = obtener_opcion();

        switch (opcion)
        {
        case 1:
        {
            nuevo_nombre = devolver_string_verificada("Ingrese el nuevo nombre para la sala: ");
            sala_editar->nombre = nuevo_nombre;
            break;
        }
        case 2:
        {
            editar_adyacencias(grafo, id_sala_editar);
            break;
        }
        case 3:
        {
            printf("\033[0;33m");
            cout << "Se cancelo la edicion de la sala" << endl;
            printf("\033[0;37m");
            break;
        }
        default:
        {
            printf("\033[0;31m");
            cout << "Opcion invalida." << endl;
            printf("\033[0;37m");
            break;
        }
        }
    } while (opcion != 3);
}
