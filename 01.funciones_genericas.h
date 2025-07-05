
#pragma once // Soluciona errores de redefinicion
// Librerias Para todo el programa.

#include <iostream>  // para operaciones de entrada y salida de datos.
#include <string>    // para manejar string
#include <limits.h>  // para los punteros NEW.
#include <algorithm> // para usar .erase
#include <fstream>   // para la lectura de archivos.
#include <vector>    // para manejo de vectores.
#include <string>    // Strings
#include <climits>   // para int max
#include <cstdlib>   // Ambas librerias para generar numeros aleatorios
#include <ctime>
#include <map>
#include <queue> // Para la cola de ids

using namespace std;

// Funciones para verificar formato de respuesta
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

// Funcion especifica para el menu de opciones
// Se ve mas bonito asi
int obtener_opcion()
{
    return obtener_entero("Ingrese una opcion: ");
}

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
