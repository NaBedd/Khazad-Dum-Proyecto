// LIBRERIAS.

#include<iostream>
#include<string>
#include<limits.h>

using namespace std;

// EXTRUCTURA PARA LOS TIPOS DE ORCOS.
struct Especie_orco{
    /* data */
    string nombre_especie;
    int danno;
    int salud;
    int rapidez;
    Especie_orco* siguiente;
};
// CLASE PARA CRAR LA LISATAS ENLAZADAS DE TIPO ORCO.
class lista_espesie_orco{

private:
    Especie_orco* primero_especie;   // punteto de tipo Especie_orco (para que pueda ser dinamico)
    int cantidad;                    // controla la cantidad de tipos que tenga la lista.

public:
    lista_espesie_orco() : primero_especie(nullptr) , cantidad(0) {} // inicializa las variables anteriomente declaaradas.

    // DESTRUCTOR, se encarga de destruir la lista al finalizar el programa, de manera automatica.
    ~lista_espesie_orco() {
        Especie_orco* actual = primero_especie;  // crea un nuevo puntero detipo Especie_orco y lo igula al principo de la lista 
        while (actual != nullptr){               // si es igual a nullptr significa que es el ultimo elemento de la lista.   
            Especie_orco* eliminar = actual;     // se crea una varible auxiliar eliminar.
            actual = actual->siguiente;          // actual lo mandamos al siguente nodo (creo que se dice asi)
            delete eliminar;                     // la variabele auxiliar se elimina.
        }
    }

    // PARA CREAR UN NUEVO TIPO DE ORCO.
    void Crear_tipo_orco(){
        Especie_orco* nuevo = new Especie_orco();
        cout << "\ningrese los datos de la nueva especie ORCO\n";
        cout << "danno: ";
        cin >> nuevo->danno;

        cout << "salud: ";
        cin >> nuevo->salud;

        cout<<"rapidez: ";
        cin>>nuevo->rapidez;


        // esta parte la entedi asi, no se si este correcto la manera en la que la intento explicar.
        nuevo->siguiente = primero_especie;  // nuevo->siguente se iguala a primer_especio paraque apunte a nullptr la vairible siguente de esa estructura(primer elemento de la lista).
        primero_especie = nuevo;             // primero_especie se iguala a nuevo paraque en ves de apuntar a nullpr apunte al nuevo nodo que se creo. 
        cantidad= cantidad + 1;             // se le suma uno a la variable 

        cout<<"especie ORCO agregada exitosamente. \n";
    }

    void mostar_lista_orco(){
        if ( cantidad == 0){    // si no hay elementos no ace nada.
            cout<<"no hay tipos de orcos en este monmento. \n\n";
            return;
        }
        
        cout<<"la cantidad de tipos de cos son: "<<cantidad<<endl;
        Especie_orco* actual = primero_especie;  // se crea una variable auxiliar para igualarla al primer elemnto de la lista.
        int num=1;                        
        while (actual != nullptr){      // si es igual a nullptr significa que es el ultimo elemento de la lista.
            cout<<"especie orco nuemro: "<<num<<endl;
            cout<<"danno = "<<actual->danno<<endl;
            cout<<"salud = "<<actual->salud<<endl;
            cout<<"rapidez = "<<actual->rapidez<<endl<<endl;
            actual = actual->siguiente;      // pasa a siguiente elemento de la lista. 
            
            num++;
        }
        cout<<"esos son todos los tipos de orcos disponibles.\n";
    }


    void actualizar_tipo_orco(){

    }
};


int main(){
    lista_espesie_orco tipoEspecieOrco;
    int opcion=0;
    
    cout<<"HOLA que desea hacer: "<<endl;
    
    // menu mientras.
    do
    {
        cout<<"agregar una especie orco (1) \n ";
        cout<<"mostrar los tipos de orcos disponibles (2) \n";
        cout<<"salir del programa (3) \n";
        cout<<"coloque la opcion: ";
        cin>> opcion;

        switch (opcion)
        {
        case 1 :
            tipoEspecieOrco.Crear_tipo_orco();
            break;
        case 2:
            tipoEspecieOrco.mostar_lista_orco();
            break;
        case 3:
            cout<<"\nsaliendo del programa \n";
            break;
        default:
            cout<<"opcion no valida, la opcion "<<opcion<<" no esta disponible. \n";
            break;
        }
    } while (opcion != 3);
    


    
    return 0;    
}

