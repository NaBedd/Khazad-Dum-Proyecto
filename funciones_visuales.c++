#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Códigos ANSI para colores
const string original = "\033[0m"; //para resetear color
const string piso = "\033[0;33m"; // Amarillo oscuro/marrón
const vector<string> COLORES_PERSONAJES = {
    "\033[0;31m", // Rojo
    "\033[0;32m", // Verde
    "\033[0;34m", // Azul
    "\033[0;35m", // Magenta
    "\033[0;36m", // Cyan
    "\033[1;31m", // Rojo brillante
    "\033[1;32m", // Verde brillante
    "\033[1;34m"  // Azul brillante
};

// Dibujo simple de un personaje en 5 líneas
const vector<string> PERSONAJE_LINEAS = {
    "  O  ",  // cabeza
    " /|\\ ",  // brazos
    "  |  ",  // cuerpo
    " / \\ ",  // piernas
    "     "   // espacio para separar verticalmente
};

// Diseño sencillo de un orco en 4 líneas
const vector<string> ORCO_LINEAS = {
    "  @@@  ",  // cabeza
    " (o o) ",  // ojos
    "  \\_/  ",  // boca
    " / | \\ "   // cuerpo/brazos
};


void dibujar_personajes(int cantidad)
{
    if (cantidad <= 0) return;

    int max_personajes = (int)COLORES_PERSONAJES.size();
    if (cantidad > max_personajes)
        cantidad = max_personajes;

        // va por cada linea del munneco.
    for (int linea = 0; linea < (int)PERSONAJE_LINEAS.size() - 1; linea++)
    {
        for (int con = 0; con < cantidad; con++)
        {
                    //coloca el color          // coloca la linea       // pone el color normal
            cout << COLORES_PERSONAJES[con] << PERSONAJE_LINEAS[linea] << original << "   ";
        }
        cout << endl;
    }

    int ancho_piso = cantidad * 10;
    cout << piso;
    for (int i = 0; i < ancho_piso; i++)
        cout << "=";
    cout << original << endl;
}

void dibujar_orcos(int cantidad)
{
    if (cantidad <= 0) return;

    int max_orcos = (int)COLORES_PERSONAJES.size(); // para que no lo marque en amarillo
    if (cantidad > max_orcos)
        cantidad = max_orcos;

    for (int linea = 0; linea < (int)ORCO_LINEAS.size(); linea++)
    {
        for (int con = 0; con < cantidad; con++)
        {
            cout << COLORES_PERSONAJES[con] << ORCO_LINEAS[linea] << original << "   ";
        }
        cout << endl;
    }

    int ancho_piso = cantidad * 10;
    cout << piso;
    for (int i = 0; i < ancho_piso; i++)
        cout << "=";
    cout << original << endl;
}

void dibujar_enfrentados(int cantidad_heroes, int cantidad_orcos)
{
    if (cantidad_heroes <= 0 && cantidad_orcos <= 0){
        return;
    }
        

    // Limitar máximos: héroes máximo 4, orcos máximo 8
    if (cantidad_heroes > 4){
        cantidad_heroes = 4;
    } 
        
    if (cantidad_orcos > 8){
        cantidad_orcos = 8;
    } 
    

    // Altura máxima para alinear dibujos:
    // Usamos 4 líneas para héroes (sin la última vacía) y 4 para orcos
    int max_lineas = 4;

    for (int linea = 0; linea < max_lineas; linea++)
    {
        // Dibujar héroes a la izquierda (solo líneas 0 a 3)
        for (int h = 0; h < cantidad_heroes; h++)
        {
            cout << COLORES_PERSONAJES[h] << PERSONAJE_LINEAS[linea] << original << "  ";
        }

        // Espacio entre héroes y orcos (campo de batalla)
        cout << "        ";

        // Dibujar orcos a la derecha (líneas 0 a 3)
        for (int con = 0; con < cantidad_orcos; con++)
        {
            cout << COLORES_PERSONAJES[con % COLORES_PERSONAJES.size()] << ORCO_LINEAS[linea] << original << "  ";
        }

        cout << endl;
    }

    // Calcular ancho total para el piso
    int ancho_heroes = cantidad_heroes * 7; // 5 chars + 2 espacios aprox
    int ancho_orcos = cantidad_orcos * 8;   // 7 chars + 1 espacio aprox
    int ancho_espacio = 8;                   // espacio entre grupos

    int ancho_total = ancho_heroes + ancho_espacio + ancho_orcos;

    // Dibujar piso marrón debajo, ancho total
    cout << piso;
    for (int i = 0; i < ancho_total; i++){
        cout << "=";
    }

    cout << original << endl;
}


int main()
{
    int cantidad;
    cout << "Ingrese cantidad de personajes a dibujar (max 8): ";
    cin >> cantidad;
    dibujar_personajes(cantidad);

    cout << endl << endl << "Ingrese cantidad de orcos a dibujar (max 8): " << endl;
    cin >> cantidad;
    dibujar_orcos(cantidad);

    int heroes, orcos;
    cout << "Cantidad de heroes (max 4): ";
    cin >> heroes;
    cout << "Cantidad de orcos (max 8): ";
    cin >> orcos;

    dibujar_enfrentados(heroes, orcos);

    return 0;
}

