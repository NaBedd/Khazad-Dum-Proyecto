#pragma once
#include "01.funciones_genericas.h"
#include "02.funciones_tipos_especie.h"
#include "03.funciones_implementos.h"
#include "04.funciones_mochila_personajes_jugar.h"
#include "05.funciones_poder_magico.h"
#include "06.funciones_mapa.h"
#include "09.menus_main.h"

/*
Habra una funcion batalla que contenga la pelea de heroes y la de orcos
Alli estaran los couts de los turnos y todo lo general
    Se mostraran todos los orcos en sala

Recibira por parametro "orcos" o "heroes" para decidir quien empieza primero

El combate funcionara de la siguiente manera:
pelea_heroes
    Los Heroes emboscan a los orcos

pelea_orcos
    Los Orcos emboscan a los heros

Menu_pelea
Este es el menu de accion de los heroes, aca podran decidir todo durante el comabte
    Contendra distintas funciones (atacar, huir, objeto, poder magico)
    habra funciones atacar_heroes y atacar_orcos por separado

La recuperacion de los heroes ocurrira en menu_combate
    mientras se haya elegido no atacar

Las funciones dentro de menu pelea, recibiran como parametro el heroe actual, para evitar complicaciones
*/

int turno = 0;

// !No se si esto funcione. Revisar que la recuperacion si se haga con el &*
// Quitar fortaleza anterior y los cout innecesarios
void recuperar_fortaleza(Lista_especie especies_heroes, personaje *&heroe_actual)
{
    cout << "Se ha regenerado la fortaleza de " << heroe_actual->nombre << endl;
    int fortaleza_anterior = heroe_actual->tipo->danno_fortaleza;

    Especie *referencia = encontrar_especie_id(especies_heroes, heroe_actual->tipo->identificador);
    int recuperacion = referencia->danno_fortaleza * 0.1;
    heroe_actual->tipo->danno_fortaleza = min(referencia->danno_fortaleza, heroe_actual->tipo->danno_fortaleza + recuperacion); // con esto se evita que exceda el maximo de vida de su especie

    // cout temporal. Esto deberia de ir en menu_combate, no aqui
    cout << "Fortaleza: " << fortaleza_anterior << " --> " << heroe_actual->tipo->danno_fortaleza << endl;
    cout << "Aqui termina la funcion recuperar_fortaleza" << endl;
}

personaje *encontrar_orco_mas_debil(sala *sala_actual) // Encontrar orco mas debil
{
    personaje *orco_debil = nullptr;
    int min_salud = INT_MAX;

    // !Editarrr
    // encontrar_personaje(sala_actual->lista_orcos, 1);
    // se podria hacer que trabaje sin la variable auxiliar?

    for (personaje *orco : sala_actual->lista_orcos)
    {
        if (orco && orco->tipo->salud > 0 && orco->tipo->salud < min_salud)
        {
            min_salud = orco->tipo->salud;
            orco_debil = orco;
        }
    }
    return orco_debil;
}

personaje *encontrar_heroe_mas_debil(sala *sala_actual) // Encontrar heroe mas debil
{
    personaje *heroe_debil = nullptr;
    int min_salud = INT_MAX;

    for (personaje *heroe : sala_actual->lista_heroes)
    {
        if (heroe && heroe->tipo->salud > 0 && heroe->tipo->salud < min_salud)
        {
            int vitalidad_efectiva = heroe->tipo->salud;
            Implemento *implemento_actual = heroe->mimochila->implementos;

            while (implemento_actual != nullptr)
            {
                if (implemento_actual->tipo_implemento == "Defensa")
                {
                    vitalidad_efectiva += implemento_actual->valor;
                }
                implemento_actual = implemento_actual->siguiente;
            }
            if (vitalidad_efectiva < min_salud)
            {
                min_salud = vitalidad_efectiva;
                heroe_debil = heroe;
            }
        }
    }
    return heroe_debil;
}

void mostrar_orcos_sala(sala *sala_actual)
{
    if (sala_actual->lista_orcos.empty())
    {
        cout << "No hay orcos en " << sala_actual->id << ". " << sala_actual->nombre << endl;
        return;
    }
    else
    {
        cout << "Orcos en " << sala_actual->nombre << ": " << endl;
        for (personaje *orco_actual : sala_actual->lista_orcos)
        {
            cout << orco_actual->identificador << ". " << orco_actual->nombre << endl;
            cout << "  Vida: " << orco_actual->tipo->salud << endl;
            cout << "  Danno: " << orco_actual->tipo->danno_fortaleza << endl;
        }
    }
}

bool validar_seleccion_implemento(personaje *heroe_actual, vector<Implemento *> lista_implemento, int opcion)
{

    if (opcion <= 0 || opcion > lista_implemento.size())
    {
        cout << "Opcion invalida." << endl;
        return false;
    }

    // Se le resta 1 porque contador empieza en 1, el index en 0
    else if (lista_implemento[opcion - 1]->fortalezanecesaria > heroe_actual->tipo->danno_fortaleza)
    {
        cout << "El heroe no posee la fuerza necesaria para usar el implemento" << endl;
        return false;
    }

    else if (lista_implemento[opcion - 1]->usos < 1)
    {
        cout << "El implemento se ha desgastado, no tiene mas usos..." << endl;
        return false;
    }

    return true;
}

bool ataque_heroe(personaje *heroe_actual, sala *sala_actual)
{
    bool turno_terminado = false;
    int contador = 1;
    bool arma_valida = false;
    int opcion_arma = 0;
    personaje *orco_objetivo = encontrar_orco_mas_debil(sala_actual); // Encontrar orco mas debil
    vector<Implemento *> lista_armas;
    Implemento *arma_actual = heroe_actual->mimochila->implementos;

    if (sala_actual->lista_orcos.empty()) // Manejo de errores por si acaso
    {
        cout << "Error en codigo. No hay orcos en la sala" << endl;
        return false;
    }
    if (sala_actual->lista_heroes.empty()) // Manejo de errores por si acaso
    {
        cout << "Error en codigo. No hay heroes en la sala" << endl;
        return false;
    }

    cout << "Armas disponibles: " << endl;
    while (arma_actual != nullptr) // Muestra todas las armas del heroe, incluyendo las que no puede usar
    {
        if (arma_actual->tipo_implemento == "Arma")
        {
            cout << contador << ". " << arma_actual->nombre_implemento << endl;
            cout << "Danno: " << arma_actual->valor << endl;
            cout << "Fortaleza Necesaria: " << arma_actual->fortalezanecesaria << endl;
            cout << "Usos restantes: " << arma_actual->usos << endl;
            lista_armas.push_back(arma_actual);
        }
        else // Borrar este cout, es para ver si recorre todo bien
        {
            cout << "TEMPORAL. el implemento " << arma_actual->nombre_implemento << " no es un arma" << endl;
        }
        arma_actual = heroe_actual->mimochila->implementos->siguiente;
    }

    if (lista_armas.empty()) // Si no puede atacar, lo retorna
    {
        cout << "El heroe no tienen ningun arma para atacar" << endl;
        return turno_terminado;
    }

    while (!arma_valida) // Valida la seleccion del arma
    {
        opcion_arma = obtener_entero("Indique su arma: ");
        arma_valida = validar_seleccion_implemento(heroe_actual, lista_armas, opcion_arma);
    }
    Implemento *arma_actual = lista_armas[opcion_arma - 1];
    int dano = arma_actual->valor;

    orco_objetivo->tipo->salud -= dano;
    if (orco_objetivo->tipo->salud < 0) // Si llegase a ser negativa, se iguala a 0
        orco_objetivo->tipo->salud = 0;

    heroe_actual->tipo->danno_fortaleza -= arma_actual->fortalezanecesaria;
    arma_actual->usos--;

    cout << endl;
    cout << heroe_actual->nombre << " ha atacado al orco " << orco_objetivo->nombre << endl;
    cout << "La vida del orco " << orco_objetivo->nombre << " ha bajado a " << orco_objetivo->tipo->salud << endl;

    // !Revisar que la eliminacion funcione correctamente ↓↓↓
    if (orco_objetivo->tipo->salud == 0) // Si mataron al orco, lo anuncia y borra de la lista
    {
        int indice_orco = 0;
        cout << "El orco " << orco_objetivo->nombre << " ha sido debilitado!!" << endl;
        for (personaje *orco_muerto : sala_actual->lista_orcos) // Elimina al orco de la sala
        {
            if (orco_muerto->identificador == orco_objetivo->identificador)
            {
                sala_actual->lista_orcos.erase(sala_actual->lista_orcos.begin() + indice_orco);
                break;
            }
            indice_orco++;
        }
    }
    if (sala_actual->lista_orcos.empty())
    {
        cout << "Todos los orcos han sido eliminados." << endl;
        cout << "Los heroes han ganado la batalla!" << endl;
    }
    return turno_terminado = true;
}

bool ataque_orco(personaje *orco_actual, sala *sala_actual)
{
    bool turno_terminado = false;
    int danno_acumulado = 0;
    int defensa;

    if (sala_actual->lista_orcos.empty()) // Manejo de errores por si acaso
    {
        cout << "Error en codigo. No hay orcos en la sala" << endl;
        return false;
    }
    if (sala_actual->lista_heroes.empty()) // Manejo de errores por si acaso
    {
        cout << "Error en codigo. No hay heroes en la sala" << endl;
        return false;
    }
    personaje *heroe_objetivo = encontrar_heroe_mas_debil(sala_actual);

    cout << "La horda de orcos esta atacando al heroe" << heroe_objetivo->nombre << endl;

    // Se calcula el danno de los orcos
    for (personaje *orco : sala_actual->lista_orcos)
    {
        danno_acumulado += orco->tipo->danno_fortaleza;
    }

    // Se calcula la defensa del heroe segun sus implementos
    int defensa_total = 0;
    Implemento *implemento_actual = heroe_objetivo->mimochila->implementos;
    int danno_restante = danno_acumulado;

    // Recorre los implementos de defensa y aplica el daño
    while (implemento_actual != nullptr && danno_restante > 0)
    {
        if (implemento_actual->tipo_implemento == "Defensa" && implemento_actual->valor > 0)
        {
            if (danno_restante >= implemento_actual->valor)
            {
                danno_restante -= implemento_actual->valor;
                implemento_actual->valor = 0; // Se agota la defensa del implemento
            }
            else
            {
                implemento_actual->valor -= danno_restante;
                danno_restante = 0;
                cout << "Los orcos no han lastimado al heroe, su vida quedo intacta" << endl;
            }
        }
        cout << "La defensa de " << implemento_actual->nombre_implemento << "se ha reducido a" << implemento_actual->valor << endl;
        implemento_actual = implemento_actual->siguiente;
    }

    // Si queda daño, se resta a la salud del héroe
    if (danno_restante > 0)
    {
        heroe_objetivo->tipo->salud -= danno_restante;
        if (heroe_objetivo->tipo->salud < 0) // Si es negativa, se iguala a 0
        {
            heroe_objetivo->tipo->salud = 0;
        }
        cout << "La vida del heroe " << heroe_objetivo->nombre << " ha bajado a " << heroe_objetivo->tipo->salud << endl;
    }

    if (heroe_objetivo->tipo->salud == 0)
    {
        int indice_heroe = 0;
        cout << "El heroe " << heroe_objetivo->nombre << " ha sido eliminado" << endl;
        for (personaje *heroe_muerto : sala_actual->lista_heroes)
        {
            if (heroe_muerto->identificador == heroe_objetivo->identificador)
            {
                sala_actual->lista_orcos.erase(sala_actual->lista_orcos.begin() + indice_heroe);
                break;
            }
            indice_heroe++;
        }
    }
    if (sala_actual->lista_heroes.empty())
    {
        cout << "Todos los heroes han sido eliminados" << endl;
        cout << "Los heroes han fracasado en su travesia" << endl;
        cout << "El pueblo sufrira la furia de los orcos..." << endl;
    }
    return turno_terminado = true;
}

bool curar_heroe_objeto(personaje *heroe_actual, sala *sala_actual)
{
    bool turno_terminado = false;
    bool opcion_valida = false;

    vector<Implemento *> lista_objetos_cura;
    Implemento *implemento_actual = heroe_actual->mimochila->implementos;

    int contador = 1;
    int opcion_curar;

    while (implemento_actual != nullptr) // Llena la lista con todos los implementos de cura
    {
        if (implemento_actual->tipo_implemento == "Cura")
        {
            lista_objetos_cura.push_back(implemento_actual);
        }
        implemento_actual = implemento_actual->siguiente;
    }
    if (lista_objetos_cura.empty()) // Si no tiene curas, lo retorna
    {
        cout << "El heroe " << heroe_actual->nombre << " no tiene implementos para curarse" << endl;
        return turno_terminado = false;
    }

    // Le muestra al jugador los implementos
    for (Implemento *cura_actual : lista_objetos_cura)
    {
        cout << contador << ". " << cura_actual->nombre_implemento << endl;
        cout << "  Curacion: " << cura_actual->valor << endl;
        cout << "  Usos restantes : " << cura_actual->usos << endl;
        contador++;
    }

    cout << "0 para cancelar." << endl;
    while (!opcion_valida) // El usuario selecciona la cura a usar
    {
        opcion_curar = obtener_entero("Indique con que se desea curar: ");
        if (opcion_curar == 0) // Cancelar accion
        {
            cout << "Se ha cancelado la accion" << endl;
            return turno_terminado = false;
        }

        opcion_valida = validar_seleccion_implemento(heroe_actual, lista_objetos_cura, opcion_curar);
    }
    Implemento *cura_usar = lista_objetos_cura[opcion_curar - 1];

    mostrar_personajes_jugar(personajes_jugar);

    personaje *personaje_curar = nullptr;
    while (!personaje_curar) // Pide al usuario el personaje a curar
    {
        int id_personaje_curar = obtener_entero("Indique a quien desea curar: ");

        for (personaje *heroe_en_sala : sala_actual->lista_heroes) // Busca al personaje
        {
            if (heroe_en_sala->identificador == id_personaje_curar)
            {
                personaje_curar = heroe_en_sala;
                break;
            }
        }
        if (!personaje_curar)
        {
            cout << "No se encontro un heroe con ese ID." << endl;
        }
    }

    // Cura al heroe sin exceder la vida de la especie
    Especie *referencia = encontrar_especie_id(tipoEspecieHeroe, heroe_actual->tipo->identificador);

    int salud_max = referencia->salud;
    int salud_antes = personaje_curar->tipo->salud;
    personaje_curar->tipo->salud = min(salud_max, personaje_curar->tipo->salud + cura_usar->valor);

    cout << personaje_curar->nombre << " ha sido curado de " << salud_antes << " a " << personaje_curar->tipo->salud << " puntos de vida." << endl;

    // Restar un uso al implemento de curación
    cura_usar->usos--;

    if (cura_usar->usos <= 0) // Lo elimina de la mochila
    {
        cout << "El implemento " << cura_usar->nombre_implemento << " se ha agotado y se elimina de la mochila." << endl;
        // Eliminar manualmente el implemento de la mochila enlazada
        Implemento *actual = heroe_actual->mimochila->implementos;
        Implemento *anterior = nullptr;
        while (actual != nullptr)
        {
            if (actual == cura_usar)
            {
                if (anterior == nullptr) // Si es el primer implemento
                {
                    heroe_actual->mimochila->implementos = actual->siguiente;
                }
                else
                {
                    anterior->siguiente = actual->siguiente;
                }
                delete actual;
                break;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
    }

    return turno_terminado = true;
}

void menu_combate_heroes(sala *sala_actual, personaje *heroe_actual)
{
    cout << "            Heroe: " << heroe_actual->nombre << endl;
    cout << "1. Atacar" << endl;
    cout << "2. Curar" << endl;
    cout << "3. Poder Magico" << endl;
    cout << "4. Pasar Turno" << endl;
    cout << "5. Huir" << endl;
    int opcion = obtener_entero("Indique la accion del heroe: ");
    bool turno_terminado;
    switch (opcion)
    {
    case 1: // atacar
    {
        turno_terminado = ataque_heroe(heroe_actual, sala_actual);
        if (turno_terminado) // Solo acaba el turno si el heroe ataco, sino, break y pregunta otra vez
            return;
        break;
    }
    case 2: // objeto
    {
        recuperar_fortaleza(tipoEspecieHeroe, heroe_actual);
        break;
    }
    case 3: // Poder Magico
    {
        break;
    }
    case 4: // Pasar Turno
    {
        recuperar_fortaleza(tipoEspecieHeroe, heroe_actual);
        break;
    }
    case 5: // Huir
    {
        recuperar_fortaleza(tipoEspecieHeroe, heroe_actual);
        break;
    }
    default: // Default
    {
        cout << "Ingrese una opcion valida" << endl;
        break;
    }
    }
}
