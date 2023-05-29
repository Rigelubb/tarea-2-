# tarea-2-
tarea 2 
Batalla Naval - README

El código del juego de Batalla Naval consta de dos archivos: servidor.cpp y cliente.cpp. Estos archivos contienen la implementación del servidor y del cliente respectivamente.
Implementación del Servidor

El archivo servidor.cpp contiene la implementación del servidor. A continuación se describen los pasos clave de la implementación:

    Incluye las bibliotecas necesarias:

    cpp

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <thread>
#include <vector>

Define algunas constantes importantes, como el puerto y el tamaño del tablero:

cpp

    const int PUERTO = 7777;
    const int TAMANIO_TABLERO = 15;

    Implementa algunas funciones auxiliares, como enviarMensaje() y recibirMensaje(), para enviar y recibir mensajes a través del socket.

    Implementa la función manejarCliente() que se encarga de manejar la comunicación con cada cliente individualmente. En esta función se realizan las siguientes tareas:
        Generar las posiciones de las embarcaciones para el cliente.
        Enviar las posiciones de las embarcaciones al cliente.
        Recibir los disparos del cliente y procesarlos.
        Actualizar los tableros y verificar si hay un ganador.
        Enviar los resultados al cliente.

    Implementa la función main() que se encarga de iniciar el servidor, aceptar conexiones de los clientes y manejarlos en hilos separados.

Implementación del Cliente

El archivo cliente.cpp contiene la implementación del cliente. A continuación se describen los pasos clave de la implementación:

    Incluye las bibliotecas necesarias:

    cpp

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

Define algunas constantes importantes, como la dirección IP del servidor y el puerto:

cpp

    const char* DIRECCION_IP_SERVIDOR = "127.0.0.1";
    const int PUERTO_SERVIDOR = 7777;

    Implementa algunas funciones auxiliares, como enviarMensaje() y recibirMensaje(), para enviar y recibir mensajes a través del socket.

    Implementa la función jugarBatallaNaval() que se encarga de la lógica del juego. En esta función se realizan las siguientes tareas:
        Conectarse al servidor.
        Recibir las posiciones de las embarcaciones del servidor.
        Solicitar al usuario que ingrese los disparos.
        Enviar los disparos al servidor.
        Recibir los resultados del servidor y mostrarlos al usuario.
        Repetir hasta que haya un ganador.

    Implementa la función main() que se encarga de llamar a la función jugarBatallaNaval().

Compilación y Ejecución

Para compilar y ejecutar el juego de Batalla Naval en Ubuntu, puedes seguir estos pasos:

    Abre una terminal y ve al directorio que contiene los archivos servidor.cpp y cliente.cpp.

    Compila el archivo servidor.cpp:

    bash

g++ -o servidor servidor.cpp -lpthread

Compila el archivo cliente.cpp:

bash

g++ -o cliente cliente.cpp

Ejecuta el servidor en una terminal:

bash

./servidor

Ejecuta el cliente en otra terminal:

bash

    ./cliente

    Sigue las instrucciones que se muestran en la terminal del cliente para jugar la Batalla Naval.

¡Y eso es todo! Ahora puedes disfrutar del juego de Batalla Naval en tu entorno de Ubuntu. Recuerda que el servidor y el cliente deben ejecutarse en terminales separadas para que puedan comunicarse correctamente.

Espero que este breve README te sea útil para comprender y ejecutar el código del juego de Batalla Naval. Si tienes alguna otra pregunta, no dudes en preguntar. ¡Buena suerte!
