Juego de Batalla Naval - Servidor y Cliente

Este es un juego de Batalla Naval implementado en C++, que consta de un servidor y múltiples clientes que pueden conectarse para jugar entre sí.
Requisitos del sistema

    Se recomienda tener instalado el compilador de C++ (g++) en el sistema.
    Se requiere el paquete libpthread para admitir hilos en el programa. Puedes instalarlo en Ubuntu con el siguiente comando:



sudo apt-get install libpthread-stubs0-dev

Compilación y ejecución

    Descarga los archivos servidor.cpp y cliente.cpp en la misma carpeta.

    Abre una terminal y navega hasta la carpeta que contiene los archivos descargados.

    Compila el servidor con el siguiente comando:

g++ servidor.cpp -o servidor -pthread

    Compila el cliente con el siguiente comando:

g++ cliente.cpp -o cliente

    Ejecuta el servidor con el siguiente comando:

bash

./servidor

    En otra terminal, ejecuta el cliente con el siguiente comando:

bash

./cliente

    Sigue las instrucciones en la terminal del cliente para jugar al juego de Batalla Naval.

Funcionalidades

    El servidor espera la conexión de múltiples clientes.
    El juego comienza cuando se conectan al menos dos clientes.
    Los clientes pueden realizar disparos en el tablero y recibir actualizaciones del estado del juego.
    El servidor coordina los turnos de los clientes y valida las jugadas.
    El juego continúa hasta que haya un ganador o los clientes decidan salir.

Personalización

    Puedes personalizar el tamaño del tablero de juego y el número de embarcaciones en el archivo servidor.cpp. Modifica las constantes TAM_TABLERO y NUM_EMBARCACIONES según tus preferencias.

¡Disfruta jugando al juego de Batalla Naval!

Espero que este README te sea útil. Si tienes más preguntas, no dudes en hacerlas. ¡Diviértete jugando!
