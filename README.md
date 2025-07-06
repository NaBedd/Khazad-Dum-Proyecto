# Pendientes para la Nueva Entrega:

### Pendiente:

- [ ] El juego NO termina si todos los heroes mueren. Cambiar !!!!
- [ ] Terminar juego si las condiciones de victoria o derrota se cumplen

  - Condiciones para perder:
    - [ ] Todos los heroes han muerto
    - [ ] Ya la puerta se movio 5 veces y se acabo el tiempo
  - Condiciones para ganar:
    - [ ] Los heroes han llegado a la puerta del destino y mataron a los orcos de esa sala (si es que los hay)
      - Ya hice la condicion para ganar pero hay que probar que funcione OJO!!!!

- [ ] Cambiar el main para que se ejecute todo el combate
- [ ] Comprobar que la recuperacion al moverse y NO pelear este bien. Archivo 08.
- [ ] Acomodar opcion huir

- [x] Hacer que solo se puedan cargar archivos 1 vez
- [x] Hacer el ciclo for para el combate. Recorrer todos los heroes e ir preguntando al usuario que desea hacer para cada uno. El jugador NO elige que heroe usar, son secuenciales
- [x] Hacer movimiento de Heroes y Orcos
- [x] Opcion saltar turno en el combate
- [x] Designar spawn de Orcos
- [x] Implementar movimiento de Orcos Dijkstra
- [x] Agregar Print al combate (X Orco tiene Y vida, X Heroe tiene Y vida, etc... despues de un ataque)
- [ ] a
  - [x] [Heroe] atacó a [Orco]
    - [x] Si el orco No murio: [Orco] ahora tiene [vida] vida
    - [x] Si el orco murio: [Orco] ha sido debilitado
    - [x] [Arma] de [Heroe] ahora tiene [durabilidad] durabilidad
  - [ ] Se permite la opcion de pasar turno en caso de que no se pueda realizar ninguna de las opciones, pero siempre va a estar en el menu
  - [x] Poder curar fuera de combate (Curar fuera de combate, hace que se pase el turno)

### General:

- [x] Preguntarle al usuario si desea ver TODAS las salas antes de editar, eliminar, etc en el CRUD del Mapa!!!
- [ ] Mejorar los prints al momento de Cargar Archivos
- [ ] Añadir los 4 poderes que dijo el profe
- [x] Agregar atributo defensa a las especies (orcos y heroes)
- [x] Asegurarnos de que NADA explote (numeros grandes)
- [x] Arreglar la edicion de Armas y Personajes
- [ ] La funcion mostrar listas, las muestra de la ultima a la primera (3→2→1) en vez de (1→2→3)
- [ ] Funcion para borrar toda la mochila
- [ ] Ordenar Main(orden de opciones)

### Mapa:

- [x] Crear movimiento de orcos y heroes (los orcos nacen todos en 1 sola sala)
  - [x] Cantidad minima de orcos debe de moverse (No se podran mover menos de X orcos por turno)
- [x] Hacer mapa con grafos
- [x] Acomodar sistema de mapas: Adyacencias, numero de orcos en sala (lista de orcos)
- [x] El turno se acaba cuando se acaba la energia para moverse entre salas
- [ ] Asignacion de Puerta Magica
- [x] Crear sitio de aparicion aleatorio en el mapa

### Sistemas y Jugabilidad

- [x] Hacer sistema de combate (pelear, curar, magia, huir)
- [x] Implementar todos los poderes
- [x] Los poderes magicos se usan SOLO en batalla
- [x] En el menu de batalla, se deben de poder elegir entre varias armas para atacar

### Opcional

- [ ] usar system("cls") para limpiar la pantalla de Menus
- [ ] Podemos hacer una opcion de eliminar, o sino hacer que el usuario ingrese 0 en todas las caracteristicas
- [ ] Revisar redundancia en funciones (eliminar personajes, ...)

### Nuevos errores conocidos

- [ ] De momento, inexistentes

### Para la primera entrega (Listo):

- [x] Para marcar algo como listo lo escriben asi (ver archivo)
- [x] En funcion eliminar especie primero hay que eliminar todos los personajes

- [x] Hacer las funciones para Orcos, Heroes e Implementos
- [x] Estructura para los implementos
- [x] Acomodar funcion search mediante menu (revisar pdf de rubrica)
- [x] Crud de poderes
- [x] Crud de armas

- [x] Borrar todos los datos dinamicos siempre al final del programa (actualmente solo se hace si el usuario elige la opcion)
- [x] Validaciones (No explotar al meter letras en Danno)
- [x] Que las Magias esten limitadas a 1 por personaje
- [x] Menu ajustes personaje:
  - [x] Crear
  - [x] Modificar
  - [x] Destruir

### Errores Conocidos

- [x] Al agregar especie orco tienes que darle a Enter por alguna razon
- [x] Al terminar de agregar especie orco, el obtener_opcion() te marca como si hubieras puesto una opcion invalida
