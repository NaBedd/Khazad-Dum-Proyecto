#include <iostream>
#include <vector>
#include <windows.h>
#include <algorithm>

// Configuración de colores (ANSI)
#define RESET "\033[0m"
#define ROJO "\033[31m"
#define VERDE "\033[32m"
#define AMARILLO "\033[33m"
#define AZUL "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define BG_DORADO "\033[48;5;178m"
#define BG_GRIS "\033[48;5;238m"
#define NEGRITA "\033[1m"

using namespace std;

void enableANSI()
{
    // Solo necesario en Windows
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

void printCentered(const string &text, int width = 50)
{
    int padding = max(0, (width - static_cast<int>(text.length())) / 2);
    cout << string(padding, ' ') << text << endl;
}

void printMenuBox(const vector<string> &options, int selected = 0)
{
    const int width = 50;
    const string corner = "+";
    const string horizontal = "-";
    const string vertical = "|";

    // Título
    cout << BG_GRIS << NEGRITA << AMARILLO;
    printCentered("╔════════════════════════╗", width);
    printCentered("║    MENU PRINCIPAL     ║", width);
    printCentered("╚════════════════════════╝", width);
    cout << RESET << endl;

    // Marco superior
    cout << "AAA" << RESET << endl;

    // Opciones
    for (int i = 0; i < static_cast<int>(options.size()); i++)
    {
        cout << BG_GRIS << vertical << RESET;

        int padding = max(0, width - 5 - static_cast<int>(options[i].length()));

        if (i == selected)
        {
            cout << BG_DORADO << NEGRITA << ROJO << " > " << options[i]
                 << string(padding, ' ');
        }
        else
        {
            cout << BG_GRIS << AZUL << "   " << options[i]
                 << string(padding, ' ');
        }

        cout << BG_GRIS << vertical << RESET << endl;
    }

    // Marco inferior
    cout << "AAA" << RESET << endl;

    // Instrucciones
    cout << VERDE << "\nUsa las flechas para navegar. Enter para seleccionar." << RESET << endl;
}

int main()
{
    enableANSI(); // Solo necesario en Windows

    vector<string> menuItems = {
        "Nueva Partida",
        "Cargar Partida",
        "Opciones",
        "Tienda",
        "Salir"};

    int selected = 0;
    bool running = true;

    while (running)
    {
        system("cls"); // Limpiar pantalla

        // Mostrar menú
        printMenuBox(menuItems, selected);

        // Capturar entrada
        bool keyPressed = false;
        if (GetAsyncKeyState(VK_UP) & 0x8000)
        {
            selected = (selected - 1 + menuItems.size()) % menuItems.size();
            keyPressed = true;
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
        {
            selected = (selected + 1) % menuItems.size();
            keyPressed = true;
        }
        else if (GetAsyncKeyState(VK_RETURN) & 0x8000)
        {
            system("cls");
            cout << BG_DORADO << NEGRITA << ROJO;
            printCentered("╔════════════════════════╗", 50);
            printCentered("║   HAS SELECCIONADO:    ║", 50);
            printCentered("╚════════════════════════╝", 50);
            cout << RESET << endl;

            cout << VERDE << "\n > " << menuItems[selected] << RESET << endl;
            cout << "\nPresiona Enter para continuar...";
            cin.sync();
            cin.get();

            if (selected == static_cast<int>(menuItems.size()) - 1)
                running = false;
            keyPressed = true;
        }

        if (keyPressed)
            Sleep(150); // Pequeña pausa para evitar repeticiones rápidas

        Sleep(50); // Reducir uso de CPU
    }

    return 0;
}