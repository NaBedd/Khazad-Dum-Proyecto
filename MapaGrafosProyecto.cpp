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

struct sala // Salas
{
    int id;
    string nombre;
    vector<arista> lista_adyacentes;
    vector<personaje_heroe> lista_heroes;
    vector<personaje_orco> lista_orcos;
    bool contiene_puerta_destino; // Habra una lista que contenga todas las ubicaciones previas de la puerta, para evitar repeticiones
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

void crear_sala(mapaGrafo &grafo, string nombre) // Funcion primitiva para crear salas
{
    sala *salaNueva = new sala;
    salaNueva->id = grafo.mapa_salas.size() + 1; // La id es igual al tamaño total del grafo. +1 para que no haya ID 0
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

void crear_adyacencia(sala *salaOrigen, sala *salaDestino, int distancia) // Crea una adyacencia
{
    salaOrigen->lista_adyacentes.push_back({salaDestino, distancia});
}

void crear_adyacencia_usuario(mapaGrafo &grafo) // Crea adyacencia manualmente
{
    sala *salaModificar = nullptr;
    sala *nuevaAdyacencia = nullptr;
    int idSalaModificar;
    int idNuevaAdyacencia;

    cout << "Salas disponibles: " << endl;
    mostrar_salas_grafo(grafo);

    do // Pide el ID de la sala a crear adyacencia y comprueba que exista
    {
        int idSalaModificar = obtener_entero("Ingrese el ID de la sala a la cual le quiere agregar adyacencias: ");
        salaModificar = encontrar_sala(grafo, idSalaModificar);
    } while (salaModificar == nullptr);

    do
    {
        int idNuevaAdyacencia = obtener_entero("Ingrese el ID de la nueva adyacencia: ");
        nuevaAdyacencia = encontrar_sala(grafo, idNuevaAdyacencia);
    } while (nuevaAdyacencia == nullptr);

    int distanciaNuevaAdyacencia = obtener_entero("Ingrese la distancia entre salas: ");

    crear_adyacencia(salaModificar, nuevaAdyacencia, distanciaNuevaAdyacencia);
}

void borrar_sala(mapaGrafo &grafo, int idSalaBorrar) // Borrar sala
{
    sala *salaBorrar = nullptr;
    int indiceBorrar;

    // Se encuentra la sala:
    for (size_t i = 0; i < grafo.mapa_salas.size(); i++)
    {
        if (idSalaBorrar == grafo.mapa_salas[i]->id)
        {
            salaBorrar = grafo.mapa_salas[i];
            int indiceBorrar = i;
            break;
        }
    }
    if (salaBorrar == nullptr)
    {
        cout << "Sala no encontrada" << endl;
        return;
    }

    // Es removido de la lista de adyacencias de todas las salas que la apuntan
    for (size_t i = 0; i < grafo.mapa_salas.size(); i++)
    {
        sala *actual = grafo.mapa_salas[i];
        for (int j = actual->lista_adyacentes.size() - 1; j >= 0; j--)
        // Se recorre en reversa para evitar problemas
        // Como solo se elimina 1 elemento no deberian de existir, pero por si acaso
        {
            if (idSalaBorrar == actual->lista_adyacentes[j].destino->id)
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

void borrar_grafo(mapaGrafo &grafo) // Borra el grafo completo
{
    while (!grafo.mapa_salas.empty()) // Mientras no este vacio
    {
        borrar_sala(grafo, grafo.mapa_salas[0]->id); // Borra siempre el primero
    }
}

void borrar_adyacencia(sala *salaOrigen, int idAdyacenciaBorrar)
{
    arista adyacenciaActual;
    bool existe = false;

    if (salaOrigen->lista_adyacentes.empty())
    {
        cout << "La sala no tiene adyacencias" << endl;
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

void editar_sala()
{
    // PendientesssssssssssssssSS
}

void editar_adyacencias()
{
    // Deberia de poder editarse nada mas la distancia entre salas
    // Al cambiar distancia de X → Y
    // Deberia buscarse si existe adyacencia entre Y → X
    // si es el caso, tambien se cambia
}

int main()
{
    cout << "AAAA" << endl;
}