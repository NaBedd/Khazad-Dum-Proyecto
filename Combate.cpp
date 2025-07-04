#include <climits>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

struct Especie
{
    string nombre_especie;
    int danno_fortaleza;
    int salud;
    int rapidez;
    int identificador;
    Especie *siguiente;
};

struct Implemento
{
    string nombre_implemento;
    string tipo_implemento;
    int usos;
    int fortalezanecesaria;
    int valor;
    int identificador;
    Implemento *siguiente = nullptr;
};

struct Poder_magico
{
    string nombre_poder;
    string funcion;
    int identificador;
    Poder_magico *siguiente = nullptr;
};

struct mochila
{
    int identificador;
    Implemento *implementos = nullptr;
    Poder_magico *poderes = nullptr;
};

struct personaje
{
    mochila *mimochila = nullptr;
    string nombre;
    Especie *tipo;
    double vitalidad;
    int fortaleza;
    int identificador;
    personaje *siguiente = nullptr;
};

struct sala
{
    int id;
    string nombre;
    vector<personaje *> lista_heroes;
    vector<personaje *> lista_orcos;
    bool contiene_puerta_destino;
};

int obtener_entero(const string &mensaje)
{
    int valor;
    cout << mensaje;
    cin >> valor;
    return valor;
}

personaje *encontrar_orco_mas_debil(sala *sala_actual)
{
    personaje *orco_debil = nullptr;
    int min_salud = INT_MAX;

    for (personaje *orco : sala_actual->lista_orcos)
    {
        if (orco && orco->vitalidad > 0 && orco->vitalidad < min_salud)
        {
            min_salud = orco->vitalidad;
            orco_debil = orco;
        }
    }
    return orco_debil;
}

personaje *encontrar_heroe_mas_debil(sala *sala_actual)
{
    personaje *heroe_debil = nullptr;
    int min_salud = INT_MAX;

    for (personaje *heroe : sala_actual->lista_heroes)
    {
        if (heroe && heroe->vitalidad > 0 && heroe->vitalidad < min_salud)
        {
            int vitalidad_efectiva = heroe->vitalidad;
            Implemento* implemento_actual = heroe->mimochila->implementos;

            while (implemento_actual != nullptr) 
            {
                if (implemento_actual->tipo_implemento == "Proteccion")
                {
                    vitalidad_efectiva+=implemento_actual->valor;
                }
                implemento_actual = implemento_actual->siguiente;
            }
            if (vitalidad_efectiva < min_salud) {
                min_salud = vitalidad_efectiva;
                heroe_debil = heroe;
            }
        }
    }
    return heroe_debil;
}

void Poder1(Implemento *lista_implementos)
{
    Implemento *actual = lista_implementos;
    int modificados = 0;

    while (actual != nullptr)
    {
        actual->valor *= 2;
        actual->fortalezanecesaria = 0;
        modificados++;
        actual = actual->siguiente;
    }

    cout << "Se han modificado " << modificados << " implementos.\n";
    cout << "Todos los implementos ahora tienen el doble de valor y no requieren fortaleza.\n";
}

void Poder2(personaje *heroe)
{
}

void Poder3(sala *sala_actual)
{
}

void Poder4(personaje *heroe, sala *sala_actual)
{
}

//CREA UN BOOL QUE SE LLAME PRIMEROORCOS Y PRIMEROHEROES, NO SE LO VAS A PASAR POR PARAMETRO, 
// ESE CONDICIONAL VA A ESTAR DENTRO DE CADA VEZ QUE SE MUEVAN LOS ORCOS Y CADA VEZ QUE SE MUEVAN LOS HEROES
//EJEMPLO: IF(PRIMEROORCOS==TRUE&&PRIMEROHEROES==FALSE){
//combateheroes(sala*sala_actual);}
//else if(PRIMEROORCOS==FALSE&&PRIMEROHEROES==TRUE){
//combateorcos(sala*sala_actual;}
//else continue;
void combateheroes(sala *sala_actual)
{
    if (sala_actual->lista_heroes.empty() || sala_actual->lista_orcos.empty())
    {
        return;
    }

    bool combate_terminado = false;
    int turno = 1;

    while (!combate_terminado)
    {
        cout << "\n----- TURNO " << turno << " -----\n";
        cout << "=== TURNO " << turno << " HEROES ===\n";

        bool puede_huir = (sala_actual->lista_orcos.size() >= 3 * sala_actual->lista_heroes.size()); // PROPORCION

        for (auto it = sala_actual->lista_heroes.begin(); it != sala_actual->lista_heroes.end();)
        {
            personaje *heroe_actual = *it;
            if (!heroe_actual || heroe_actual->vitalidad <= 0)
            {
                ++it;
                continue;
            }

            int recuperacion = heroe_actual->tipo->danno_fortaleza * 0.1;
            heroe_actual->fortaleza = min(heroe_actual->tipo->danno_fortaleza, heroe_actual->fortaleza + recuperacion); // con esto se evita que exceda el maximo de vida de su especie
            cout << heroe_actual->nombre << " ha recuperado " << recuperacion << " puntos de fortaleza.\n";

            cout << "\nQue deseas hacer con " << heroe_actual->nombre << "?\n";
            cout << "1. Atacar\n";
            cout << "2. Huir\n";
            cout << "3. Usar poder magico\n";
            cout << "4. Curar\n";

            int accion = obtener_entero("Opcion: ");

            switch (accion)
            {
            case 1:
            {
                personaje *orco_objetivo = encontrar_orco_mas_debil(sala_actual);
                if (!orco_objetivo)
                {
                    cout << "Todos los orcos han sido derrotados!, los heroes han ganado\n";
                    combate_terminado = true;
                    break;
                }

                cout << heroe_actual->nombre << " tiene para atacar:\n";
                vector<Implemento *> armas;
                Implemento *arma_actual = heroe_actual->mimochila->implementos;
                int contador = 1;

                while (arma_actual != nullptr)
                {
                    if (arma_actual->tipo_implemento == "Ataque" && heroe_actual->fortaleza >= arma_actual->fortalezanecesaria)
                    {
                        cout << contador << ". " << arma_actual->nombre_implemento
                             << "- Danno: " << arma_actual->valor
                             << ", Usos: " << arma_actual->usos << "\n";
                        armas.push_back(arma_actual);
                        contador++;
                    }
                    arma_actual = arma_actual->siguiente;
                }

                if (armas.empty())
                {
                    cout << heroe_actual->nombre << "No tiene armas disponibles para atacar.\n";
                    break;
                }

                int opcion = obtener_entero("Elige un arma: ") - 1;
                if (opcion < 0 || opcion >= armas.size())
                {
                    cout << "Opcion invalida!\n";
                    break;
                }

                Implemento *arma_seleccionada = armas[opcion];
                int dano = arma_seleccionada->valor;

                orco_objetivo->vitalidad -= dano;
                heroe_actual->fortaleza -= arma_seleccionada->fortalezanecesaria;
                arma_seleccionada->usos--;

                cout << "\n"
                     << heroe_actual->nombre << " ha atacado al orco " << orco_objetivo->nombre << "!\n";
                cout << "Danno causado: " << dano << "\n";
                cout << "Usos que quedan del arma: " << arma_seleccionada->usos << "\n";

                if (orco_objetivo->vitalidad <= 0)
                {
                    cout << heroe_actual->nombre << " ha matado al orco " << orco_objetivo->nombre << "!\n";
                    auto orco_it = find(sala_actual->lista_orcos.begin(), // itera dentro de la lista de orocos de principio a fin buscsndo el orco para eliminarlo
                                        sala_actual->lista_orcos.end(),
                                        orco_objetivo);
                    if (orco_it != sala_actual->lista_orcos.end())
                    {
                        sala_actual->lista_orcos.erase(orco_it);
                    }

                    if (sala_actual->lista_orcos.empty())
                    {
                        cout << "Todos los orcos han sido derrotados!, ganaron los heroes\n";
                        combate_terminado = true;
                    }
                }
                break;
            }

            case 2:
            {
                if (accion == 5 || puede_huir)
                {
                    cout << heroe_actual->nombre << " intenta huir...\n";
                    // LA LOGICA DE HUIDA VA AQUi DEL MAPA
                    cout << "Los heroes han escapado del combate!\n";
                    combate_terminado = true;
                }
                else
                {
                    cout << "No puedes huir ahora (necesitas estar superado en número 3 a 1).\n";
                }
                break;
            }

            case 3:
            { // Poder magico
                cout << "\nPoderes magicos disponibles:\n";
                Poder_magico *poder = heroe_actual->mimochila->poderes;
                int contador = 1;

                while (poder != nullptr)
                {
                    cout << contador << ". " << poder->nombre_poder << " - " << poder->funcion << "\n";
                    poder = poder->siguiente;
                    contador++;
                }

                if (contador == 1)
                {
                    cout << "No tienes poderes magicos disponibles.\n";
                    break;
                }

                int opcion_poder = obtener_entero("Elige un poder: ") - 1;

                // Obtener poder seleccionado
                poder = heroe_actual->mimochila->poderes;
                for (int i = 0; i < opcion_poder && poder != nullptr; i++)
                {
                    poder = poder->siguiente;
                }

                if (!poder)
                {
                    cout << "Poder invalido.\n";
                    break;
                }

                // Ejecutar poder
                if (poder->nombre_poder == "Poder1")
                {
                    Poder1(heroe_actual->mimochila->implementos);
                }
                else if (poder->nombre_poder == "Poder2")
                {
                    Poder2(heroe_actual);
                }
                else if (poder->nombre_poder == "Poder3")
                {
                    Poder3(sala_actual);
                }
                else if (poder->nombre_poder == "Poder4")
                {
                    Poder4(heroe_actual, sala_actual);
                }
                else
                {
                    cout << "Error, poder no existe.\n";
                }
                break;
            }

            case 4:
            { // Curar
                cout << "\nObjetos de cura disponibles:\n";
                vector<Implemento *> curas;
                Implemento *cura_actual = heroe_actual->mimochila->implementos;
                int contador = 1;

                while (cura_actual != nullptr)
                {
                    if (cura_actual->tipo_implemento == "Cura")
                    {
                        cout << contador << ". " << cura_actual->nombre_implemento
                             << " Cura: " << cura_actual->valor << "\n";
                        curas.push_back(cura_actual);
                        contador++;
                    }
                    cura_actual = cura_actual->siguiente;
                }

                if (curas.empty())
                {
                    cout << "No tienes nada para curarte.\n";
                    break;
                }

                int opcion = obtener_entero("Elige un objeto de cura: ") - 1;
                if (opcion < 0 || opcion >= curas.size())
                {
                    cout << "Opcion invalida!\n";
                    break;
                }

                Implemento *cura_seleccionada = curas[opcion];
                heroe_actual->vitalidad += cura_seleccionada->valor;

                Implemento** pp = &(heroe_actual->mimochila->implementos);//Eliminar despues de usarlo
                    while (*pp != nullptr) {
                        if (*pp == cura_seleccionada) {
                            *pp = cura_seleccionada->siguiente;
                            delete cura_seleccionada;
                            break;
                        }
                        pp = &((*pp)->siguiente);
                    }

                cout << "\nHas usado " << cura_seleccionada->nombre_implemento << "!\n";
                cout << "Has recuperado " << cura_seleccionada->valor << " puntos de vida.\n";
                cout << "La vida actual de " << heroe_actual->nombre << "es " << heroe_actual->vitalidad << "\n";
                break;
            }

            default:
                cout << "Opcion invalida\n";
                break;
            }
        }
        if (sala_actual->lista_orcos.empty()) {
            cout << "Todos los orcos han sido derrotados!, ganaron los heroes\n";
            combate_terminado = true;
            break;  
        } 
        else if (sala_actual->lista_heroes.empty()) {
            cout << "Todos los heroes han sido derrotados!, ganaron los orcos\n";
            combate_terminado = true;
            break;
        }

        // TURNO DE LOS ORCOS
        cout << "\n=== TURNO " << turno << " ORCOS ===\n";

        personaje *heroe_objetivo = encontrar_heroe_mas_debil(sala_actual);
        if (!heroe_objetivo)
        {
            cout << "Todos los heroes han sido derrotados!\n";
            combate_terminado = true;
            continue;
        }

        int dano_acumulado = 0;
        cout << "La horda de orcos ataca al heroe " << heroe_objetivo->nombre << "!\n";

        for (auto orco:sala_actual->lista_orcos)//se acumula el danno de la horda de orcos
        { 
            if (orco && orco->vitalidad>0)
            {
                dano_acumulado+=orco->tipo->danno_fortaleza;
            }
        }
            vector<Implemento*> implementos_proteccion;
            Implemento* implemento_actual = heroe_objetivo->mimochila->implementos;

            while (implemento_actual != nullptr) //Se buscan si el heroe tiene implementos que lo protegen
                                                //  y se meten los implementos que protegen al heroe en un vector
            {
                if (implemento_actual->tipo_implemento == "Proteccion")
                {
                    implementos_proteccion.push_back(implemento_actual);
                }
                implemento_actual = implemento_actual->siguiente;
            }

            if (!implementos_proteccion.empty()) //Si hay implementos que lo protegen entonces...
            {
                for (auto&proteccion_actual: implementos_proteccion) //Itera por referencia para poder cambiarlos
                {
                    if (dano_acumulado <= 0)break;//Si el danno acumulado es cero es porque ni hay orcos y para el ataque de los orocos o 
                                                    // porque ya terminaron de atacar a sus implementos y no los desgastaron a todos
                    
                    cout<<"El implemento "<<proteccion->nombre_implemento<< " ha recibido danno de los orcos!\n";
                    
                    int dano_absorbido = min(dano_acumulado, proteccion_actual->valor);
                    proteccion_actual->valor -= dano_absorbido;
                    dano_acumulado -= dano_absorbido;
                    
                    if (proteccion_actual->valor <= 0)
                    {
                        cout <<"El implemento " << proteccion_actual->nombre_implemento << " se ha desgastado completamente!\n";
                        
                        Implemento** pp = &(heroe_objetivo->mimochila->implementos); //se elimina tal cual como la cura despuesde usarse
                        while (*pp != nullptr)
                        {
                            if (*pp == proteccion_actual)
                            {
                                *pp = proteccion_actual->siguiente;
                                delete proteccion_actual;
                                break;
                            }
                            pp = &((*pp)->siguiente);
                        }
                    }
                    else
                    {
                        cout << "El implemento " << proteccion_actual->nombre_implemento << " ahora tiene " << proteccion->valor << " puntos restantes de dureza\n";
                    }
                }
            }
            if (dano_acumulado > 0 && implementos_proteccion.empty()) {
                heroe_objetivo->vitalidad -= dano_acumulado;
                cout << "El heroe " << heroe_objetivo->nombre<<" recibe danno!," << "\n";
                cout << "La vida restante de " << heroe_objetivo->nombre << " ahora es de "<< heroe_objetivo->vitalidad << "\n";
            }
        if (heroe_objetivo->vitalidad <= 0)
        {
            cout << heroe_objetivo->nombre << " ha muerto...\n";
            auto it = find(sala_actual->lista_heroes.begin(), sala_actual->lista_heroes.end(), heroe_objetivo); // del principio hasta el fin buscando al orco objetivo
            if (it != sala_actual->lista_heroes.end())
            {
                sala_actual->lista_heroes.erase(it);
            }

            if (sala_actual->lista_heroes.empty())
            {
                cout << "Todos los heroes han sido derrotados!\n";
                combate_terminado = true;
            }
        }

        if (sala_actual->lista_orcos.empty()) {
            cout << "Todos los orcos han sido derrotados!, ganaron los heroes\n";
            combate_terminado = true;
            break;  
        } 
        else if (sala_actual->lista_heroes.empty()) {
            cout << "Todos los heroes han sido derrotados!, ganaron los orcos\n";
            combate_terminado = true;
            break;
        }

        turno++;
    }
}

void combateorcos(sala *sala_actual){
    if (sala_actual->lista_heroes.empty() || sala_actual->lista_orcos.empty())
    {
        return;
    }

    bool combate_terminado = false;
    int turno = 1;

    while (!combate_terminado)
    {
        cout << "\n----- TURNO " << turno << " -----\n";
        cout << "=== TURNO " << turno << " ORCOS ===\n";

        personaje *heroe_objetivo = encontrar_heroe_mas_debil(sala_actual);
        if (!heroe_objetivo)
        {
            cout << "Todos los heroes han sido derrotados!\n";
            combate_terminado = true;
            continue;
        }

        int dano_acumulado = 0;
        cout << "La horda de orcos ataca al heroe " << heroe_objetivo->nombre << "!\n";

        for (auto orco:sala_actual->lista_orcos)
        { 
            if (orco && orco->vitalidad>0)
            {
                dano_acumulado+=orco->tipo->danno_fortaleza;
            }
        }
            vector<Implemento*> implementos_proteccion;
            Implemento* implemento_actual = heroe_objetivo->mimochila->implementos;

            while (implemento_actual != nullptr)
            {
                if (implemento_actual->tipo_implemento == "Proteccion")
                {
                    implementos_proteccion.push_back(implemento_actual);
                }
                implemento_actual = implemento_actual->siguiente;
            }

            if (!implementos_proteccion.empty())
            {
                for (auto&proteccion_actual: implementos_proteccion)
                {
                    if (dano_acumulado <= 0)break;
                    
                    cout<<"El implemento "<<proteccion_actual->nombre_implemento<< " ha recibido danno de los orcos!\n";
                    
                    int dano_absorbido = min(dano_acumulado, proteccion_actual->valor);
                    proteccion_actual->valor -= dano_absorbido;
                    dano_acumulado -= dano_absorbido;
                    
                    if (proteccion_actual->valor <= 0)
                    {
                        cout <<"El implemento " << proteccion_actual->nombre_implemento << " se ha desgastado completamente!\n";
                        
                        Implemento** pp = &(heroe_objetivo->mimochila->implementos);
                        while (*pp != nullptr)
                        {
                            if (*pp == proteccion_actual)
                            {
                                *pp = proteccion_actual->siguiente;
                                delete proteccion_actual;
                                break;
                            }
                            pp = &((*pp)->siguiente);
                        }
                    }
                    else
                    {
                        cout << "El implemento " << proteccion_actual->nombre_implemento << " ahora tiene " << proteccion_actual->valor << " puntos restantes de dureza\n";
                    }
                }
            }

        if (dano_acumulado > 0 && implementos_proteccion.empty()) {
                heroe_objetivo->vitalidad -= dano_acumulado;
                cout << "El heroe" << heroe_objetivo->nombre<<" recibe danno!," << "\n";
                cout << "La vida restante de " << heroe_objetivo->nombre << " ahora es de "<< heroe_objetivo->vitalidad << "\n";
            }

        if (heroe_objetivo->vitalidad <= 0)
        {
            cout << heroe_objetivo->nombre << " ha muerto...\n";
            auto it = find(sala_actual->lista_heroes.begin(), sala_actual->lista_heroes.end(), heroe_objetivo);
            if (it != sala_actual->lista_heroes.end())
            {
                sala_actual->lista_heroes.erase(it);
            }

            if (sala_actual->lista_heroes.empty())
            {
                cout << "Todos los heroes han sido derrotados!\n";
                combate_terminado = true;
            }
        }

        if (sala_actual->lista_orcos.empty()) {
            cout << "Todos los orcos han sido derrotados!, ganaron los heroes\n";
            combate_terminado = true;
            break;  
        } 
        else if (sala_actual->lista_heroes.empty()) {
            cout << "Todos los heroes han sido derrotados!, ganaron los orcos\n";
            combate_terminado = true;
            break;
        }

        cout << "=== TURNO " << turno << " HEROES ===\n";

        bool puede_huir = (sala_actual->lista_orcos.size() >= 3 * sala_actual->lista_heroes.size());

        for (auto it = sala_actual->lista_heroes.begin(); it != sala_actual->lista_heroes.end();)
        {
            personaje *heroe_actual = *it;
            if (!heroe_actual || heroe_actual->vitalidad <= 0)
            {
                ++it;
                continue;
            }

            int recuperacion = heroe_actual->tipo->danno_fortaleza * 0.1;
            heroe_actual->fortaleza = min(heroe_actual->tipo->danno_fortaleza, heroe_actual->fortaleza + recuperacion);
            cout << heroe_actual->nombre << " ha recuperado " << recuperacion << " puntos de fortaleza.\n";

            cout << "\nQue deseas hacer con " << heroe_actual->nombre << "?\n";
            cout << "1. Atacar\n";
            cout << "2. Huir\n";
            cout << "3. Usar poder magico\n";
            cout << "4. Curar\n";

            int accion = obtener_entero("Opcion: ");

            switch (accion)
            {
            case 1:
            {
                personaje *orco_objetivo = encontrar_orco_mas_debil(sala_actual);
                if (!orco_objetivo)
                {
                    cout << "Todos los orcos han sido derrotados!, los heroes han ganado\n";
                    combate_terminado = true;
                    break;
                }

                cout << heroe_actual->nombre << " tiene para atacar:\n";
                vector<Implemento *> armas;
                Implemento *arma_actual = heroe_actual->mimochila->implementos;
                int contador = 1;

                while (arma_actual != nullptr)
                {
                    if (arma_actual->tipo_implemento == "Ataque" && heroe_actual->fortaleza >= arma_actual->fortalezanecesaria)
                    {
                        cout << contador << ". " << arma_actual->nombre_implemento
                             << "- Danno: " << arma_actual->valor
                             << ", Usos: " << arma_actual->usos << "\n";
                        armas.push_back(arma_actual);
                        contador++;
                    }
                    arma_actual = arma_actual->siguiente;
                }

                if (armas.empty())
                {
                    cout << heroe_actual->nombre << "No tiene armas disponibles para atacar.\n";
                    break;
                }

                int opcion = obtener_entero("Elige un arma: ") - 1;
                if (opcion < 0 || opcion >= armas.size())
                {
                    cout << "Opcion invalida!\n";
                    break;
                }

                Implemento *arma_seleccionada = armas[opcion];
                int dano = arma_seleccionada->valor;

                orco_objetivo->vitalidad -= dano;
                heroe_actual->fortaleza -= arma_seleccionada->fortalezanecesaria;
                arma_seleccionada->usos--;

                cout << "\n"
                     << heroe_actual->nombre << " ha atacado al orco " << orco_objetivo->nombre << "!\n";
                cout << "Danno causado: " << dano << "\n";
                cout << "Usos que quedan del arma: " << arma_seleccionada->usos << "\n";

                if (orco_objetivo->vitalidad <= 0)
                {
                    cout << heroe_actual->nombre << " ha matado al orco " << orco_objetivo->nombre << "!\n";
                    auto orco_it = find(sala_actual->lista_orcos.begin(),
                                        sala_actual->lista_orcos.end(),
                                        orco_objetivo);
                    if (orco_it != sala_actual->lista_orcos.end())
                    {
                        sala_actual->lista_orcos.erase(orco_it);
                    }

                    if (sala_actual->lista_orcos.empty())
                    {
                        cout << "Todos los orcos han sido derrotados!, ganaron los heroes\n";
                        combate_terminado = true;
                    }
                }
                break;
            }

            case 2:
            {
                if (accion == 5 || puede_huir)
                {
                    cout << heroe_actual->nombre << " intenta huir...\n";
                    cout << "Los heroes han escapado del combate!\n";
                    combate_terminado = true;
                }
                else
                {
                    cout << "No puedes huir ahora (necesitas estar superado en número 3 a 1).\n";
                }
                break;
            }

            case 3:
            {
                cout << "\nPoderes magicos disponibles:\n";
                Poder_magico *poder = heroe_actual->mimochila->poderes;
                int contador = 1;

                while (poder != nullptr)
                {
                    cout << contador << ". " << poder->nombre_poder << " - " << poder->funcion << "\n";
                    poder = poder->siguiente;
                    contador++;
                }

                if (contador == 1)
                {
                    cout << "No tienes poderes magicos disponibles.\n";
                    break;
                }

                int opcion_poder = obtener_entero("Elige un poder: ") - 1;

                poder = heroe_actual->mimochila->poderes;
                for (int i = 0; i < opcion_poder && poder != nullptr; i++)
                {
                    poder = poder->siguiente;
                }

                if (!poder)
                {
                    cout << "Poder invalido.\n";
                    break;
                }

                if (poder->nombre_poder == "Poder1")
                {
                    Poder1(heroe_actual->mimochila->implementos);
                }
                else if (poder->nombre_poder == "Poder2")
                {
                    Poder2(heroe_actual);
                }
                else if (poder->nombre_poder == "Poder3")
                {
                    Poder3(sala_actual);
                }
                else if (poder->nombre_poder == "Poder4")
                {
                    Poder4(heroe_actual, sala_actual);
                }
                else
                {
                    cout << "Error, poder no existe.\n";
                }
                break;
            }

            case 4:
            {
                cout << "\nObjetos de cura disponibles:\n";
                vector<Implemento *> curas;
                Implemento *cura_actual = heroe_actual->mimochila->implementos;
                int contador = 1;

                while (cura_actual != nullptr)
                {
                    if (cura_actual->tipo_implemento == "Cura")
                    {
                        cout << contador << ". " << cura_actual->nombre_implemento
                             << " Cura: " << cura_actual->valor << "\n";
                        curas.push_back(cura_actual);
                        contador++;
                    }
                    cura_actual = cura_actual->siguiente;
                }

                if (curas.empty())
                {
                    cout << "No tienes nada para curarte.\n";
                    break;
                }

                int opcion = obtener_entero("Elige un objeto de cura: ") - 1;
                if (opcion < 0 || opcion >= curas.size())
                {
                    cout << "Opcion invalida!\n";
                    break;
                }

                Implemento *cura_seleccionada = curas[opcion];
                heroe_actual->vitalidad += cura_seleccionada->valor;

                Implemento** pp = &(heroe_actual->mimochila->implementos);
                    while (*pp != nullptr) {
                        if (*pp == cura_seleccionada) {
                            *pp = cura_seleccionada->siguiente;
                            delete cura_seleccionada;
                            break;
                        }
                        pp = &((*pp)->siguiente);
                    }

                cout << "\nHas usado " << cura_seleccionada->nombre_implemento << "!\n";
                cout << "Has recuperado " << cura_seleccionada->valor << " puntos de vida.\n";
                cout << "La vida actual de " << heroe_actual->nombre << "es " << heroe_actual->vitalidad << "\n";
                break;
            }

            default:
                cout << "Opcion invalida\n";
                break;
            }
        }
        if (sala_actual->lista_orcos.empty()) {
            cout << "Todos los orcos han sido derrotados!, ganaron los heroes\n";
            combate_terminado = true;
            break;  
        } 
        else if (sala_actual->lista_heroes.empty()) {
            cout << "Todos los heroes han sido derrotados!, ganaron los orcos\n";
            combate_terminado = true;
            break;
        }

        turno++;
    }
}
