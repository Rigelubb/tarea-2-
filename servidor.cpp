// servidor.cpp

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <thread>
#include <vector>

const int PUERTO = 7777;
const int TAMANIO_TABLERO = 15;

enum class EstadoCasilla {
    Vacio,
    Barco,
    Disparada
};

struct Tablero {
    EstadoCasilla casillas[TAMANIO_TABLERO][TAMANIO_TABLERO];
};

struct Cliente {
    int socket;
    Tablero tablero;
};

int crearSocket() {
    int socketServidor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketServidor == -1) {
        std::cerr << "Error al crear el socket" << std::endl;
        exit(1);
    }
    return socketServidor;
}

void enlazarSocket(int socketServidor, int puerto) {
    sockaddr_in direccionServidor{};
    direccionServidor.sin_family = AF_INET;
    direccionServidor.sin_addr.s_addr = INADDR_ANY;
    direccionServidor.sin_port = htons(puerto);

    if (bind(socketServidor, (struct sockaddr*)&direccionServidor, sizeof(direccionServidor)) == -1) {
        std::cerr << "Error al enlazar el socket" << std::endl;
        exit(1);
    }
}

void escucharSocket(int socketServidor) {
    if (listen(socketServidor, 1) == -1) {
        std::cerr << "Error al poner en escucha el socket" << std::endl;
        exit(1);
    }
}

int aceptarConexion(int socketServidor) {
    sockaddr_in direccionCliente{};
    socklen_t tamanoDireccion = sizeof(direccionCliente);
    int socketCliente = accept(socketServidor, (struct sockaddr*)&direccionCliente, &tamanoDireccion);
    if (socketCliente == -1) {
        std::cerr << "Error al aceptar la conexión" << std::endl;
        exit(1);
    }
    return socketCliente;
}

void cerrarSocket(int socket) {
    close(socket);
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

void definirPosicionesEmbarcaciones(Tablero& tablero) {
    // Lógica para definir las posiciones de las embarcaciones
    // ...
}

std::string generarPosicionesEmbarcaciones() {
    Tablero tablero;
    definirPosicionesEmbarcaciones(tablero);

    std::string posiciones;
    for (int fila = 0; fila < TAMANIO_TABLERO; ++fila) {
        for (int columna = 0; columna < TAMANIO_TABLERO; ++columna) {
            char estadoCasilla = ' ';
            if (tablero.casillas[fila][columna] == EstadoCasilla::Barco) {
                estadoCasilla = 'B';
            }
            posiciones += estadoCasilla;
        }
    }
    return posiciones;
}

std::string obtenerTablerosActualizados(const std::vector<Cliente>& clientes) {
    std::string tableros;
    for (const auto& cliente : clientes) {
        for (int fila = 0; fila < TAMANIO_TABLERO; ++fila) {
            for (int columna = 0; columna < TAMANIO_TABLERO; ++columna) {
                char estadoCasilla = ' ';
                if (cliente.tablero.casillas[fila][columna] == EstadoCasilla::Disparada) {
                    estadoCasilla = 'X';
                }
                tableros += estadoCasilla;
            }
        }
    }
    return tableros;
}

bool verificarJugada(const std::string& coordenadas, const Tablero& tablero) {
    // Lógica para verificar si una jugada es válida
    // ...
    return true;
}

std::string procesarDisparo(const std::string& coordenadas, int turnoCliente) {
    // Lógica para procesar el disparo y determinar el resultado
    // ...
    return "Hundido";
}

bool hayGanador(const std::vector<Cliente>& clientes) {
    // Lógica para determinar si hay un ganador
    // ...
    return false;
}

void manejarCliente(int socketCliente, std::vector<Cliente>& clientes, int& turnoCliente) {
    std::string posicionesEmbarcaciones = generarPosicionesEmbarcaciones();
    enviarMensaje(socketCliente, posicionesEmbarcaciones);

    while (!hayGanador(clientes)) {
        std::string mensaje = recibirMensaje(socketCliente);
        std::string resultadoDisparo = procesarDisparo(mensaje, turnoCliente);
        turnoCliente = (turnoCliente + 1) % clientes.size();

        std::string tablerosActualizados = obtenerTablerosActualizados(clientes);
        enviarMensaje(socketCliente, resultadoDisparo);
        enviarMensaje(socketCliente, tablerosActualizados);
    }

    cerrarSocket(socketCliente);
}

int main() {
    int socketServidor = crearSocket();
    enlazarSocket(socketServidor, PUERTO);
    escucharSocket(socketServidor);

    std::vector<Cliente> clientes;
    int turnoCliente = 0;

    while (true) {
        int socketCliente = aceptarConexion(socketServidor);
        clientes.push_back({ socketCliente });

        std::thread clienteThread(manejarCliente, socketCliente, std::ref(clientes), std::ref(turnoCliente));
        clienteThread.detach();
    }

    cerrarSocket(socketServidor);
    return 0;
}
