#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <unistd.h> // Para usar la función close()
#include <thread>   // Para utilizar hilos




// Función para enviar un mensaje al cliente
void enviarMensaje(int socketCliente, const std::string& mensaje) {
    send(socketCliente, mensaje.c_str(), mensaje.size(), 0);
}

// Función para recibir un mensaje del cliente
std::string recibirMensaje(int socketCliente) {
    const int TAMANIO_BUFFER = 1024;
    char buffer[TAMANIO_BUFFER];
    memset(buffer, 0, TAMANIO_BUFFER);
    recv(socketCliente, buffer, TAMANIO_BUFFER, 0);
    return std::string(buffer);
}








// Función para procesar un disparo del cliente
std::string procesarDisparo(const std::string& coordenadas, int turnoCliente) {
    // Implementa la lógica para procesar el disparo del cliente y devuelve el resultado
}

// Función para verificar si hay un ganador en el juego
bool hayGanador() {
    // Implementa la lógica para verificar si hay un ganador y devuelve true o false
}

// Función para obtener los tableros actualizados
std::string obtenerTablerosActualizados() {
    // Implementa la lógica para obtener los tableros actualizados y devuelve la representación en cadena
}

// Función para cerrar un socket
void cerrarSocket(int socket) {
    close(socket);
}





























     void manejarCliente(int socketCliente) {
    std::string mensaje;

    // Generar posiciones de embarcaciones aleatorias para el cliente
    std::string posicionesEmbarcaciones = generarPosicionesEmbarcaciones();
    enviarMensaje(socketCliente, posicionesEmbarcaciones);

    // Determinar quién comienza el juego
    bool turnoCliente = (rand() % 2 == 0);
    std::string mensajeTurno = turnoCliente ? "cliente" : "servidor";
    enviarMensaje(socketCliente, mensajeTurno);

    while (true) {
        // Recibir coordenadas de disparo
        mensaje = recibirMensaje(socketCliente);

        // Procesar disparo
        std::string resultadoDisparo = procesarDisparo(mensaje, turnoCliente);

        // Enviar resultado del disparo
        enviarMensaje(socketCliente, resultadoDisparo);

        // Enviar tableros actualizados
        std::string tablerosActualizados = obtenerTablerosActualizados();
        enviarMensaje(socketCliente, tablerosActualizados);

        // Verificar si hay un ganador
        if (hayGanador()) {
            break;
        }

        // Cambiar turno
        turnoCliente = !turnoCliente;
        mensajeTurno = turnoCliente ? "cliente" : "servidor";
        enviarMensaje(socketCliente, mensajeTurno);
    }

    // Cerrar conexión con el cliente
    cerrarSocket(socketCliente);
}








   

int main(int argc, char* argv[]) {
    // Verificar argumentos de línea de comandos
    if (argc != 2) {
        std::cout << "Uso: " << argv[0] << " <puerto_servidor>" << std::endl;
        return 1;
    }

    int puertoServidor = std::stoi(argv[1]);

    int socketServidor = crearSocket();
    enlazarSocket(socketServidor, puertoServidor);
    escucharSocket(socketServidor);

    std::cout << "Esperando conexiones..." << std::endl;

    while (true) {
        int socketCliente = aceptarConexion(socketServidor);

        // Crear un hilo para manejar la conexión con el cliente
        std::thread clienteThread(manejarCliente, socketCliente);
        clienteThread.detach();
    }

    cerrarSocket(socketServidor);

    return 0;
}

        
        
        
        
        
        
        
        
        
        
        
        
        



void definirPosicionesEmbarcaciones(char tablero[][15]) {
    std::srand(std::time(nullptr));  // Inicializar la semilla para generar números aleatorios

    // Definir las posiciones de los barcos
    colocarBarco(tablero, 'P', 5);  // Portaaviones
    colocarBarco(tablero, 'B', 4);  // Buque 1
    colocarBarco(tablero, 'B', 4);  // Buque 2
    colocarBarco(tablero, 'S', 3);  // Submarino 1
    colocarBarco(tablero, 'S', 3);  // Submarino 2
    colocarBarco(tablero, 'L', 1);  // Lancha 1
    colocarBarco(tablero, 'L', 1);  // Lancha 2
    colocarBarco(tablero, 'L', 1);  // Lancha 3
}

void colocarBarco(char tablero[][15], char tipoBarco, int longitud) {
    bool colocado = false;
    while (!colocado) {
        int fila = std::rand() % 15;      // Generar una fila aleatoria
        int columna = std::rand() % 15;   // Generar una columna aleatoria
        int direccion = std::rand() % 2;  // Generar una dirección aleatoria (0: horizontal, 1: vertical)

        // Verificar si el barco cabe en esa posición
        if (direccion == 0 && columna + longitud <= 15) {
            bool espacioDisponible = true;
            for (int i = columna; i < columna + longitud; i++) {
                if (tablero[fila][i] != ' ') {
                    espacioDisponible = false;
                    break;
                }
            }

            // Colocar el barco en el tablero
            if (espacioDisponible) {
                for (int i = columna; i < columna + longitud; i++) {
                    tablero[fila][i] = tipoBarco;
                }
                colocado = true;
            }
        } else if (direccion == 1 && fila + longitud <= 15) {
            bool espacioDisponible = true;
            for (int i = fila; i < fila + longitud; i++) {
                if (tablero[i][columna] != ' ') {
                    espacioDisponible = false;
                    break;
                }
            }

            // Colocar el barco en el tablero
            if (espacioDisponible) {
                for (int i = fila; i < fila + longitud; i++) {
                    tablero[i][columna] = tipoBarco;
                }
                colocado = true;
            }
        }
    }
}

        
        
        
        
        
        
        
        
        
        int seleccionarTurno() {
    std::srand(std::time(nullptr));  // Inicializar la semilla para generar números aleatorios
    return std::rand() % 2;  // Generar un número aleatorio entre 0 y 1 (0: cliente, 1: servidor)
}







std::string generarDisparo() {
    std::string coordenadas;

    // Generar coordenadas de disparo al azar
    char letra = 'A' + (std::rand() % 15);  // Generar una letra aleatoria entre A y O
    int numero = 1 + (std::rand() % 15);    // Generar un número aleatorio entre 1 y 15

    coordenadas = letra + std::to_string(numero);

    return coordenadas;
}



bool verificarJugada(const std::string& coordenadas, const Tablero& tablero) {
    // Obtener las coordenadas en forma de fila y columna
    int fila = coordenadas[0] - 'A';
    int columna = std::stoi(coordenadas.substr(1)) - 1;

    // Verificar si la casilla ya ha sido disparada
    if (tablero.casillas[fila][columna] == EstadoCasilla::Disparada) {
        return false;
    }

    // Actualizar el estado de la casilla en el tablero
    tablero.casillas[fila][columna] = EstadoCasilla::Disparada;

    return true;
}





void enviarResultados(const std::string& resultados, const std::vector<Cliente>& clientes) {
    for (const auto& cliente : clientes) {
        enviarMensaje(cliente.socket, resultados);
    }
}







void mostrarInformacion(const std::string& mensaje) {
    std::cout << mensaje << std::endl;
}






