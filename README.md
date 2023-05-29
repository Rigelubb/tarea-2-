Juego de Batalla Naval - Cliente y Servidor

Este es un juego de Batalla Naval que permite a dos jugadores jugar en red utilizando un modelo cliente-servidor. Uno de los jugadores actúa como servidor (Jugador 1) y el otro como cliente (Jugador 2). Ambos jugadores podrán colocar sus barcos en el tablero y tratar de hundir los barcos del oponente.

El juego utiliza sockets para establecer una conexión entre el cliente y el servidor, permitiendo que los jugadores se comuniquen y realicen sus movimientos de manera sincronizada.
Requisitos

    Compilador C++ compatible con el estándar C++11.
    Biblioteca de sockets de red (ejemplo: en Linux se utiliza <sys/socket.h>).
    Terminal o máquina para ejecutar el servidor (Jugador 1) y el cliente (Jugador 2).

Instrucciones

    Compilación:

        Servidor (Jugador 1): Ejecutar el siguiente comando en la terminal:

g++ servidor.cpp -o servidor

Cliente (Jugador 2): Ejecutar el siguiente comando en la terminal:

    g++ cliente.cpp -o cliente

Ejecución:

    Servidor (Jugador 1): Ejecutar el siguiente comando en la terminal:

    bash

./servidor

Cliente (Jugador 2): Ejecutar el siguiente comando en la terminal:

bash

    ./cliente

Juego:

    Cada jugador deberá colocar sus barcos en el tablero siguiendo las instrucciones que se mostrarán en la terminal.
    Los jugadores se turnarán para realizar sus ataques, siguiendo el formato de coordenadas indicado (por ejemplo: A1, B2, etc.).
    Se mostrará información en la terminal sobre el resultado de los ataques y el estado de los tableros.
    El juego continuará hasta que uno de los jugadores haya hundido todos los barcos del oponente.(POR EL MOMENTO LUEGO DEL PRIMER TIRO DEL JUGADOR 1 SE CONTINUA JUGANDO EN ESA TERMINAL AMBOS ,POR REPARA PERO AUN ASI SE PUEDE JUGAR Y SE HACE EL SOCKET)

¡Disfruta jugando al juego de Batalla Naval!

Espero que este README te sea útil. Si tienes más preguntas, no dudes en hacerlas. ¡Diviértete jugando!
