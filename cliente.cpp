// cliente.cpp

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

const char* IP_SERVIDOR = "127.0.0.1";
const int PUERTO = 7777;
const int TAMANIO_TABLERO = 15;

enum class EstadoCasilla {
    Vacio,
    Barco,
    Disparada
};

void imprimirTablero(const std::string& tablero) {
    for (int fila = 0; fila < TAMANIO_TABLERO; ++fila) {
        for (int columna = 0; columna < TAMANIO_TABLERO; ++columna) {
            std::cout << tablero[fila * TAMANIO_TABLERO + columna] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void enviarMensaje(int socket, const std::string& mensaje) {
    int longitudMensaje = mensaje.length();
    send(socket, &longitudMensaje, sizeof(longitudMensaje), 0);
    send(socket, mensaje.c_str(), longitudMensaje, 0);
}

std::string recibirMensaje(int socket) {
    int longitudMensaje;
    recv(socket, &longitudMensaje, sizeof(longitudMensaje), 0);
    char buffer[longitudMensaje + 1];
    recv(socket, buffer, longitudMensaje, 0);
    buffer[longitudMensaje] = '\0';
    return buffer;
}

int main() {
    int socketCliente = socket(AF_INET, SOCK_STREAM, 0);
    if (socketCliente == -1) {
        std::cerr << "Error al crear el socket" << std::endl;
        return 1;
    }

    sockaddr_in direccionServidor{};
    direccionServidor.sin_family = AF_INET;
    direccionServidor.sin_port = htons(PUERTO);
    if (inet_pton(AF_INET, IP_SERVIDOR, &(direccionServidor.sin_addr)) <= 0) {
        std::cerr << "Dirección inválida/No soportada" << std::endl;
        return 1;
    }

    if (connect(socketCliente, (struct sockaddr*)&direccionServidor, sizeof(direccionServidor)) == -1) {
        std::cerr << "Error al conectar al servidor" << std::endl;
        return 1;
    }

    std::string posicionesEmbarcaciones = recibirMensaje(socketCliente);
    imprimirTablero(posicionesEmbarcaciones);

    while (true) {
        std::cout << "Ingresa las coordenadas del disparo (fila columna): ";
        std::string coordenadas;
        std::cin >> coordenadas;

        enviarMensaje(socketCliente, coordenadas);

        std::string resultadoDisparo = recibirMensaje(socketCliente);
        std::string tablerosActualizados = recibirMensaje(socketCliente);

        imprimirTablero(tablerosActualizados);
        std::cout << "Resultado del disparo: " << resultadoDisparo << std::endl;

        if (resultadoDisparo == "Hundido") {
            std::cout << "¡Ganaste!" << std::endl;
            break;
        }
    }

    close(socketCliente);
    return 0;
}



