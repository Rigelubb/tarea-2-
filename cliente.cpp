#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <vector>
#include <thread>
#include <mutex>
#include <random>
#include <chrono>
#include <iomanip>



#include <cstdlib>


#include <netinet/in.h>

using namespace std;

const int TAM_TABLERO = 10;

void imprimirTablero(char tablero[TAM_TABLERO][TAM_TABLERO]) {
    cout << "   ";
    for (int i = 0; i < TAM_TABLERO; i++) {
        cout << static_cast<char>('A' + i) << " ";
    }
    cout << endl;

    for (int i = 0; i < TAM_TABLERO; i++) {
        cout << setw(2) << i + 1 << " ";
        for (int j = 0; j < TAM_TABLERO; j++) {
            cout << tablero[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool validarCoordenadas(char coordenadas[3]) {
    if (strlen(coordenadas) != 2)
        return false;

    int fila = coordenadas[1] - '1';
    int columna = coordenadas[0] - 'A';

    return (fila >= 0 && fila < TAM_TABLERO && columna >= 0 && columna < TAM_TABLERO);
}

int main() {
    // Crear socket
    int clienteSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clienteSocket == -1) {
        cerr << "Error al crear el socket" << endl;
        return 1;
    }

    // Configurar dirección del servidor
    sockaddr_in direccionServidor;
    direccionServidor.sin_family = AF_INET;
    direccionServidor.sin_port = htons(8888);
    direccionServidor.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Conectar al servidor
    if (connect(clienteSocket, (struct sockaddr*)&direccionServidor, sizeof(direccionServidor)) == -1) {
        cerr << "Error al conectarse al servidor" << endl;
        close(clienteSocket);
        return 1;
    }

    cout << "Conexión establecida con el servidor" << endl;

    char tablero[TAM_TABLERO][TAM_TABLERO];
    memset(tablero, ' ', sizeof(tablero));

    for (int i = 0; i < 3; i++) {
        int fila = rand() % TAM_TABLERO;
        int columna = rand() % TAM_TABLERO;
        tablero[fila][columna] = 'X';
    }

    bool turnoJugador1 = true;
    bool turnoJugador2 = false;

    while (true) {
        if (turnoJugador1) {
            // Turno del Jugador 1
            imprimirTablero(tablero);
            cout << "Jugador 1: Ingresa las coordenadas para atacar (ejemplo: A1): ";
            char coordenadas[3];
            cin >> coordenadas;

            if (!validarCoordenadas(coordenadas)) {
                cout << "Coordenadas inválidas. Intenta de nuevo." << endl;
                continue;
            }

            int fila = coordenadas[1] - '1';
            int columna = coordenadas[0] - 'A';

            // Enviar coordenadas al servidor
            send(clienteSocket, coordenadas, sizeof(coordenadas), 0);

            // Recibir resultado del ataque
            char resultado;
            recv(clienteSocket, &resultado, sizeof(resultado), 0);

            if (resultado == 'X') {
                cout << "¡Jugador 1 ha hundido un barco del Jugador 2!" << endl;
                tablero[fila][columna] = ' ';
            } else {
                cout << "Jugador 1 ha fallado el ataque." << endl;
            }

            // Verificar si el Jugador 1 ganó
            bool barcosJugador2Destruidos = true;
            for (int i = 0; i < TAM_TABLERO; i++) {
                for (int j = 0; j < TAM_TABLERO; j++) {
                    if (tablero[i][j] == 'X') {
                        barcosJugador2Destruidos = false;
                        break;
                    }
                }
                if (!barcosJugador2Destruidos)
                    break;
            }

            // Comprobar si todos los barcos del Jugador 2 han sido destruidos, el Jugador 1 gana
            if (barcosJugador2Destruidos) {
                cout << "¡El Jugador 1 ha ganado!" << endl;
                break;
            }

            turnoJugador1 = false;
            turnoJugador2 = true;
        }

        if (turnoJugador2) {
            // Turno del Jugador 2
            imprimirTablero(tablero);
            cout << "Esperando turno del Jugador 1..." << endl;

            // Recibir coordenadas del Jugador 1
            char coordenadas[3];
            recv(clienteSocket, coordenadas, sizeof(coordenadas), 0);

            int fila = coordenadas[1] - '1';
            int columna = coordenadas[0] - 'A';

            if (tablero[fila][columna] == 'X') {
                cout << "¡Jugador 2 ha hundido un barco del Jugador 1!" << endl;
                tablero[fila][columna] = ' ';
            } else {
                cout << "Jugador 2 ha fallado el ataque." << endl;
            }

            // Enviar resultado del ataque al Jugador 1
            char resultado = tablero[fila][columna];
            send(clienteSocket, &resultado, sizeof(resultado), 0);

            // Verificar si el Jugador 2 ganó
            bool barcosJugador1Destruidos = true;
            for (int i = 0; i < TAM_TABLERO; i++) {
                for (int j = 0; j < TAM_TABLERO; j++) {
                    if (tablero[i][j] == 'X') {
                        barcosJugador1Destruidos = false;
                        break;
                    }
                }
                if (!barcosJugador1Destruidos)
                    break;
            }

            // Comprobar si todos los barcos del Jugador 1 han sido destruidos, el Jugador 2 gana
            if (barcosJugador1Destruidos) {
                cout << "¡El Jugador 2 ha ganado!" << endl;
                break;
            }

            turnoJugador1 = true;
            turnoJugador2 = false;
        }
    }

    // Cerrar socket
    close(clienteSocket);

    return 0;
}


