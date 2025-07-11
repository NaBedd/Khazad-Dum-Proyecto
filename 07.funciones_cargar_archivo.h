#pragma once
#include "01.funciones_genericas.h"
#include "02.funciones_tipos_especie.h"
#include "03.funciones_implementos.h"
#include "04.funciones_mochila_personajes_jugar.h"
#include "05.funciones_poder_magico.h"
#include "06.funciones_mapa.h"

//---------------------- FUNCIONES PARA CARGAR LOS ARCHIVOS -------------------------------------------

// convierte un str a un int.
int convertir_entero(string &linea)
{
    string numero_str = "";

    for (char c : linea)
    {
        if (isdigit(c))
        {
            numero_str += c;
        }
        else
        {
            // al encontrar el primer caracter no numerico para.
            break;
        }
    }

    if (numero_str.empty())
    {
        return 0; // No hay números al inicio
    }

    return stoi(numero_str);
}

// toma la primera palabra de un str.
string obtener_str_limitado(string &linea)
{
    string nuevo = "";
    for (char c : linea)
    {
        if (!isspace(c))
        { // si no es un espacio en blanco
            nuevo += c;
        }
        else
        {

            break;
        }
    }
    return nuevo;
}

// para encontrar una especie(tipo) por su nombre.
Especie *encontrar_especie_nombre(Lista_especie lista, string nombre)
{
    Especie *actual = lista.primero_especie;
    while (actual != nullptr)
    {
        if (actual->nombre_especie == nombre)
        {
            return actual;
        }
        actual = actual->siguiente;
    }
    return actual = nullptr;
}

// para cargar el archivo de especies
void cargar_especies(Lista_especie &tipos_herores, Lista_especie &tipos_orcos, bool &listo_especies)
{
    if (!listo_especies)
    {
        ifstream archivo;
        string linea; // guardara una linea de archivo.

        // Para abrir archivos siempre en escritorio:
        string desktop_path = getenv("USERPROFILE");
        desktop_path += "\\Desktop\\especie.txt";

        archivo.open(desktop_path, ios::in);
        // en caso de que no se habra el archivo.
        if (archivo.fail())
        {
            cout << "no se pudo abrir el archivo." << endl;
            return;
        }

        getline(archivo, linea); // sirver para pasar a la siguiente linea del archivo.
        int controlador = convertir_entero(linea);
        int fin = 0;
        int id;
        int controlador_colocar = 0;
        while (fin != controlador)
        {
            getline(archivo, linea);
            // Especie *nuevo = new Especie;
            if ((linea == "---") && (controlador_colocar == 0))
            {
                Especie *nuevo = new Especie;
                controlador_colocar++;

                do
                {
                    getline(archivo, linea);
                    if (controlador_colocar == 1)
                    {
                        id = convertir_entero(linea);
                        controlador_colocar++;
                    }
                    else if (controlador_colocar == 2)
                    {
                        nuevo->nombre_especie = obtener_str_limitado(linea);
                        controlador_colocar++;
                    }
                    else if (controlador_colocar == 3)
                    {
                        controlador_colocar++;
                        if (linea.substr(0, 1) == "-")
                        { // es tipo orco
                            cout << "orco." << endl;
                            nuevo->identificador = id;
                            nuevo->siguiente = tipos_orcos.primero_especie;
                            tipos_orcos.primero_especie = nuevo;
                            tipos_orcos.cantidad = tipos_orcos.cantidad + 1;
                        }
                        else
                        {                                                     // es tipo heroe.
                            nuevo->danno_fortaleza = convertir_entero(linea); // toma los primeros 3 caracteres)
                        }
                    }
                    else if (controlador_colocar == 4)
                    {
                        controlador_colocar++;

                        if (linea.substr(0, 1) == "-")
                        { // es tipo heroe
                            cout << "heroe" << endl;
                            nuevo->identificador = id;
                            nuevo->siguiente = tipos_herores.primero_especie;
                            tipos_herores.primero_especie = nuevo;
                            tipos_herores.cantidad = tipos_herores.cantidad + 1;
                        }
                        else
                        {                                                     // es tipo heroe.
                            nuevo->danno_fortaleza = convertir_entero(linea); // toma los primeros 3 caracteres)
                        }
                    }
                    else if (controlador_colocar == 5)
                    {
                        controlador_colocar++;

                        nuevo->salud = convertir_entero(linea);
                    }
                    else if (controlador_colocar == 6)
                    {
                        controlador_colocar++;

                        nuevo->rapidez = convertir_entero(linea);
                    }
                } while (controlador_colocar != 7);
                fin++;
                controlador_colocar = 0;
                cout << "el tipo " << nuevo->nombre_especie << " se agrego correctamente." << endl;
            }
        }
        cout << "fin " << endl;
        listo_especies = true;
        archivo.close();
    }
    else
    {
        return;
    }
}

// para cargar el archivo de implementos.
void cargar_implementos(Implemento &lista_implemento, bool &listo_implementos)
{
    if (!listo_implementos)
    {
        ifstream archivo;
        string linea; // guardara una linea de archivo.

        // Para abrir archivos siempre en escritorio:
        string desktop_path = getenv("USERPROFILE");
        desktop_path += "\\Desktop\\implemento.txt";

        archivo.open(desktop_path, ios::in);
        if (archivo.fail())
        {
            cout << "no se pudo abrir el archivo." << endl;
            return;
        }

        getline(archivo, linea);
        int controlador = convertir_entero(linea);
        int fin = 0;
        int controlador_colocar = 0;
        while (fin != controlador)
        {
            getline(archivo, linea);
            if (obtener_str_limitado(linea) == "---")
            {
                Implemento *nuevo = new Implemento;
                cantidad_implementos++;
                do
                {
                    controlador_colocar++;
                    getline(archivo, linea);
                    if (controlador_colocar == 1)
                    {
                        nuevo->identificador = convertir_entero(linea);
                    }
                    else if (controlador_colocar == 2)
                    {
                        nuevo->nombre_implemento = linea;
                    }
                    else if (controlador_colocar == 3)
                    {
                        nuevo->tipo_implemento = obtener_str_limitado(linea);
                    }
                    else if (controlador_colocar == 4)
                    {
                        nuevo->fortalezanecesaria = convertir_entero(linea);
                    }
                    else if (controlador_colocar == 5)
                    {
                        nuevo->valor = convertir_entero(linea);
                    }
                    else if (controlador_colocar == 6)
                    {
                        nuevo->usos = convertir_entero(linea);
                        // lo agregamos a la lista enlaada.
                        nuevo->siguiente = lista_implemento.siguiente;
                        lista_implemento.siguiente = nuevo;
                    }
                } while (controlador_colocar != 6);

                fin++;
                controlador_colocar = 0;
                cout << "el implemento " << nuevo->nombre_implemento << " se agrego correctamente." << endl;
            }
        }
        cout << "fin " << endl;
        listo_implementos = true;
        archivo.close();
    }
    else
    {
        return;
    }
}

void carga_salas(mapaGrafo &grafo, bool &listo_salas) // Cargar Salas
{
    if (!listo_salas)
    {
        ifstream archivo;
        string linea; // guardara una linea de archivo.

        // Para abrir archivos siempre en escritorio:
        string desktop_path = getenv("USERPROFILE");
        desktop_path += "\\Desktop\\salas.txt";

        archivo.open(desktop_path, ios::in);
        if (archivo.fail())
        {
            cout << "no se pudo abrir el archivo." << endl;
            return;
        }

        getline(archivo, linea);
        int controlador = convertir_entero(linea);
        int fin = 0;
        int controlador_colocar = 0;
        while (fin != controlador)
        {
            getline(archivo, linea);
            if (obtener_str_limitado(linea) == "---")
            {
                sala *nueva = new sala;
                do
                {
                    getline(archivo, linea);
                    controlador_colocar++;
                    if (controlador_colocar == 1)
                    {
                        nueva->id = convertir_entero(linea);
                    }
                    else if (controlador_colocar == 2)
                    {
                        nueva->nombre = linea;
                        grafo.mapa_salas.push_back(nueva);
                    }

                } while (controlador_colocar != 2);
                fin++;
                controlador_colocar = 0;
                cout << "la sala " << nueva->nombre << " se agrego correctamente." << endl;
                cout << "ID: " << nueva->id << endl;
            }
        }
        cout << "fin " << endl;
        listo_salas = true;
        archivo.close();
    }
    else
    {
        return;
    }
}

void cargar_adyacencias(mapaGrafo &grafo, bool &listo_adyacencias) // Cargar Adyacencias de Salas
{
    if (!listo_adyacencias)
    {

        ifstream archivo;
        string linea; // guardara una linea de archivo.

        // Para abrir archivos siempre en escritorio:
        string desktop_path = getenv("USERPROFILE");
        desktop_path += "\\Desktop\\salas.txt";

        archivo.open(desktop_path, ios::in);
        if (archivo.fail())
        {
            cout << "no se pudo abrir el archivo." << endl;
            return;
        }

        getline(archivo, linea);
        int controlador = convertir_entero(linea);
        int fin = 0;
        int id_sala = 0;
        int id_sala_destino = 0;
        int peso = 0;
        string colocar = "";

        string ir_colocando = "";
        while (fin != controlador +1)
        {
            getline(archivo, linea);
            if (obtener_str_limitado(linea) == "---")
            {
                getline(archivo, linea);
                id_sala = convertir_entero(linea);
                sala *nueva = encontrar_sala(grafo, id_sala);
                sala *destino = nullptr;
                // ara llegra al la linea donde estan las adyacencias.
                getline(archivo, linea);
                getline(archivo, linea);
                getline(archivo, linea);
                
                linea = linea + "|";
                
                for (char caracter : linea)
                {
                    if (caracter == ':')
                    {
                        id_sala_destino = convertir_entero(colocar);
                        // buscamos la sala destino.
                        destino = encontrar_sala(grafo, id_sala_destino);
                        colocar = "";
                        continue;
                    }
                    else if (caracter == '|')
                    { // agregamos la adyacencia.
                        peso = convertir_entero(colocar);
                        // creamos la adyacencia.
                        crear_adyacencia(nueva, destino, peso);
                        colocar = "";
                        continue;
                    }
                    colocar = colocar + caracter;
                }
                // la ultima no se agrega ya que no tine |.
                if (!colocar.empty() && nueva != nullptr && destino != nullptr)
                {
                    peso = convertir_entero(colocar);
                    crear_adyacencia(nueva, destino, peso);
                }
                fin++;
                cout << "la sala " << nueva->nombre << " se le colocaron sus adyacencias." << endl;
                cout << "ID: " << nueva->id << endl;
                mostrar_adyacencias(nueva);
            }
        }
        cout << "fin " << endl;
        listo_adyacencias = true;
        archivo.close();
    }
    else
    {
        return;
    }
}

// para acargar el archivo de personajes.
void cargar_personajes(personaje &lis_heroes, personaje &lis_orco, Lista_especie &tipos_heroes,
                       Lista_especie &tipos_orcos, bool &listo_personajes)
{
    if (!listo_personajes)
    {
        ifstream archivo;
        string linea; // guardara una linea de archivo.

        // Para abrir archivos siempre en escritorio:
        string desktop_path = getenv("USERPROFILE");
        desktop_path += "\\Desktop\\Personajes.txt";

        archivo.open(desktop_path, ios::in);
        if (archivo.fail())
        {
            cout << "no se pudo abrir el archivo." << endl;
            return;
        }

        getline(archivo, linea);
        int controlador = convertir_entero(linea);
        int fin = 0;
        int id = 0;
        int controlador_colocar = 0;
        while (fin != controlador)
        {
            getline(archivo, linea);
            if (linea.substr(0, 3) == "---")
            {
                personaje *nuevo = new personaje;

                do
                {
                    controlador_colocar++;
                    getline(archivo, linea);
                    if (controlador_colocar == 1)
                    {

                        id = convertir_entero(linea);
                    }
                    else if (controlador_colocar == 2)
                    {

                        nuevo->tipo = encontrar_especie_nombre(tipos_heroes, obtener_str_limitado(linea));
                        if (nuevo->tipo == nullptr)
                        { // no es tipo heroe.
                            nuevo->tipo = encontrar_especie_nombre(tipos_orcos, obtener_str_limitado(linea));
                            if (nuevo->tipo == nullptr)
                            {
                                cout << "el tipo " << linea << " no existe." << endl;
                            }
                            else
                            {
                                cantidad_personaje_orco++;
                                nuevo->identificador = id;
                                // lo metemos a la lista de personajes.
                                nuevo->siguiente = lis_orco.siguiente;
                                lis_orco.siguiente = nuevo;
                                cout << "tipo orco. " << endl;
                            }
                        }
                        else
                        { // si es heroe.
                            cantidad_personaje_heroe++;
                            nuevo->identificador = id;
                            // lo metemos a la lista.
                            nuevo->siguiente = lis_heroes.siguiente;
                            lis_heroes.siguiente = nuevo;
                            cout << "tipo heroe." << endl;
                        }
                    }
                    else if (controlador_colocar == 3)
                    {
                        nuevo->nombre = obtener_str_limitado(linea);
                    }
                } while (controlador_colocar != 3);
                fin++;
                controlador_colocar = 0;
                if (nuevo->tipo == nullptr)
                {
                    cout << "el personaje " << nuevo->nombre << " no se agrego." << endl;
                }
                else
                {
                    cout << "el personaje " << nuevo->nombre << " se agrego correctamente." << endl
                         << endl;
                }
            }
        }
        cout << "fin " << endl;
        listo_personajes = true;
        archivo.close();
    }
    else
    {
        return;
    }
}
