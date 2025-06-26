#include <climits> //esta libreria la uso para usar el int max o entero mximo
#include <vector>
#include <map>
#include <algorithm> 

using namespace std;

// Funciones auxiliares externas
personaje* encontrar_orco_mas_debil(sala* sala_actual) {
    personaje* orco_debil = nullptr;
    int min_salud = INT_MAX;
    
    for (personaje* orco : sala_actual->lista_orcos) {
        if (orco && orco->vitalidad > 0 && orco->vitalidad < min_salud) {
            min_salud = orco->vitalidad;
            orco_debil = orco;
        }
    }
    return orco_debil;
}

personaje* encontrar_heroe_mas_debil(sala* sala_actual) {
    personaje* heroe_debil = nullptr;
    int min_salud = INT_MAX;
    
    for (personaje* heroe : sala_actual->lista_heroes) {
        if (heroe && heroe->vitalidad > 0 && heroe->vitalidad < min_salud) {
            min_salud = heroe->vitalidad;
            heroe_debil = heroe;
        }
    }
    return heroe_debil;
}

void combate(sala* sala_actual, personaje* equipo_heroes) {
    if (sala_actual->lista_heroes.empty() || sala_actual->lista_orcos.empty()) {
        cout << "Combatir no está disponible\n";
        return;
    }

    bool combate_terminado = false;
    bool huyeron = false;
    int turno = 1;


    while (!combate_terminado) {
        cout << "\n----- TURNO " << turno << " -----\n";
        
        // Verificar proporción 3:1 para huida
        bool puede_huir = (sala_actual->lista_orcos.size() >= 3 * sala_actual->lista_heroes.size());
        
        // --- TURNO DE LOS HÉROES ---
        cout << "\n--- TURNO DE LOS HÉROES ---\n";
        
        for (auto it = sala_actual->lista_heroes.begin(); it != sala_actual->lista_heroes.end(); ) {
            personaje* heroe_actual = *it;
            bool heroe_eliminado = false;
            
            // Verificar si el héroe sigue vivo
            if (!heroe_actual || heroe_actual->vitalidad <= 0) {
                ++it;
                continue;
            }

            // Recuperación de fortaleza (10% de su fortaleza máxima)
            int recuperacion = heroe_actual->tipo->danno_fortaleza * 0.1;
            heroe_actual->fortaleza = min(heroe_actual->tipo->danno_fortaleza, 
                                        heroe_actual->fortaleza + recuperacion);
            cout << heroe_actual->nombre << " recupera " << recuperacion << " puntos de fortaleza.\n";

            cout << "\nEs el turno de " << heroe_actual->nombre << ":\n";
            cout << "1. Atacar\n";
            cout << "2. Defender\n";
            cout << "3. Usar poder mágico\n";
            cout << "4. Curar\n";
            if (puede_huir) cout << "5. Intentar huir\n";
            cout << "6. Pasar turno\n";
            
            int accion = obtener_entero("Elige una acción: ");
            bool accion_realizada = true;
            
            switch (accion) {
                case 1: // Atacar
                {
                    personaje* orco_objetivo = encontrar_orco_mas_debil(sala_actual);
                    
                    if (!orco_objetivo) {
                        cout << "No hay orcos vivos para atacar.\n";
                        accion_realizada = false;
                        break;
                    }
                    
                    cout << heroe_actual->nombre << " ataca a " << orco_objetivo->nombre << "!\n";

                    vector<Implemento*> armas;
                    Implemento* impl = heroe_actual->mimochila->implementos;
                    int contador = 1;
                    
                    cout << "\nArmas disponibles:\n";
                    while (impl != nullptr) {
                        if (impl->tipo_implemento == "Ataque" && 
                            heroe_actual->fortaleza >= impl->fortalezanecesaria) {
                            cout << contador << ". " << impl->nombre_implemento;
                            cout << " (Daño: " << impl->valor;
                            cout << ", Coste Fortaleza: " << impl->fortalezanecesaria;
                            cout << ", Usos: " << impl->usos << ")\n";
                            armas.push_back(impl);
                            contador++;
                        }
                        impl = impl->siguiente;
                    }

                    if (armas.empty()) {
                        cout << "No tienes armas disponibles para atacar.\n";
                        accion_realizada = false;
                        break;
                    }

                    int opcion_arma;
                    int num_armas = armas.size();
                    do {
                        opcion_arma = obtener_entero("\nSelecciona un arma: ") - 1;
                    } while (opcion_arma < 0 || opcion_arma >= num_armas);

                    Implemento* arma = armas[opcion_arma];
                
                    int dano = arma->valor;
                    orco_objetivo->vitalidad -= dano;
                    heroe_actual->fortaleza -= arma->fortalezanecesaria;
                    arma->usos--;
                    
                    cout << "Usa " << arma->nombre_implemento << " e inflige " << dano << " puntos de daño.\n";
                    cout << "Gasta " << arma->fortalezanecesaria << " puntos de fortaleza.\n";
                    
                    // se elimina orco derrotado
                    if (orco_objetivo->vitalidad <= 0) {
                        cout << orco_objetivo->nombre << " ha sido derrotado!\n";
                        auto orco_it = find(sala_actual->lista_orcos.begin(), sala_actual->lista_orcos.end(), orco_objetivo);
                        if (orco_it != sala_actual->lista_orcos.end()) {
                            sala_actual->lista_orcos.erase(orco_it);
                        }
                    }
                    break;
                }
                
                
