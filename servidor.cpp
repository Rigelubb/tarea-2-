#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
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
    srand(time(0));

    // Crear socket
    int servidorSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (servidorSocket == -1) {
        cerr << "Error al crear el socket" << endl;
        return 1;
    }

    // Configurar dirección del servidor
    sockaddr_in direccionServidor;
    direccionServidor.sin_family = AF_INET;
    direccionServidor.sin_port = htons(8888);
    direccionServidor.sin_addr.s_addr = INADDR_ANY;

    // Vincular el socket a la dirección del servidor
    if (bind(servidorSocket, (struct sockaddr*)&direccionServidor, sizeof(direccionServidor)) == -1) {
        cerr << "Error al vincular el socket" << endl;
        close(servidorSocket);
        return 1;
    }

    // Escuchar conexiones entrantes
    if (listen(servidorSocket, 1) == -1) {
        cerr << "Error al escuchar conexiones entrantes" << endl;
        close(servidorSocket);
        return 1;
    }

    cout << "Esperando conexión del Jugador 2..." << endl;

    // Aceptar conexión del Jugador 2
    sockaddr_in direccionJugador2;
    socklen_t tamDireccionJugador2 = sizeof(direccionJugador2);
    int jugador2Socket = accept(servidorSocket, (struct sockaddr*)&direccionJugador2, &tamDireccionJugador2);
    if (jugador2Socket == -1) {
        cerr << "Error al aceptar la conexión del Jugador 2" << endl;
        close(servidorSocket);
        return 1;
    }

    cout << "Conexión establecida con el Jugador 2" << endl;

    // Generar tablero de barcos del Jugador 1
    char tableroJugador1[TAM_TABLERO][TAM_TABLERO];
    memset(tableroJugador1, ' ', sizeof(tableroJugador1));

    for (int i = 0; i < 3; i++) {
        int fila = rand() % TAM_TABLERO;
        int columna = rand() % TAM_TABLERO;
        tableroJugador1[fila][columna] = 'X';
    }

    // Generar tablero de barcos del Jugador 2
    char tableroJugador2[TAM_TABLERO][TAM_TABLERO];
    memset(tableroJugador2, ' ', sizeof(tableroJugador2));

    for (int i = 0; i < 3; i++) {
        int fila = rand() % TAM_TABLERO;
        int columna = rand() % TAM_TABLERO;
        tableroJugador2[fila][columna] = 'X';
    }

    bool turnoJugador1 = true;
    bool turnoJugador2 = false;

    while (true) {
        if (turnoJugador1) {
            // Turno del Jugador 1
            imprimirTablero(tableroJugador1);
            cout << "Jugador 1: Ingresa las coordenadas para atacar (ejemplo: A1): ";
            char coordenadas[3];
            cin >> coordenadas;

            if (!validarCoordenadas(coordenadas)) {
                cout << "Coordenadas inválidas. Intenta de nuevo." << endl;
                continue;
            }

            int fila = coordenadas[1] - '1';
            int columna = coordenadas[0] - 'A';

            if (tableroJugador2[fila][columna] == 'X') {
                cout << "¡Jugador 1 ha hundido un barco del Jugador 2!" << endl;
                tableroJugador2[fila][columna] = ' ';
            } else {
                cout << "Jugador 1 ha fallado el ataque." << endl;
            }

            // Verificar si el Jugador 1 ganó
            bool barcosJugador2Destruidos = true;
            for (int i = 0; i < TAM_TABLERO; i++) {
                for (int j = 0; j < TAM_TABLERO; j++) {
                    if (tableroJugador2[i][j] == 'X') {
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
            imprimirTablero(tableroJugador2);
            cout << "Jugador 2: Ingresa las coordenadas para atacar (ejemplo: A1): ";
            char coordenadas[3];
            cin >> coordenadas;

            if (!validarCoordenadas(coordenadas)) {
                cout << "Coordenadas inválidas. Intenta de nuevo." << endl;
                continue;
            }

            int fila = coordenadas[1] - '1';
            int columna = coordenadas[0] - 'A';

            if (tableroJugador1[fila][columna] == 'X') {
                cout << "¡Jugador 2 ha hundido un barco del Jugador 1!" << endl;
                tableroJugador1[fila][columna] = ' ';
            } else {
                cout << "Jugador 2 ha fallado el ataque." << endl;
            }

            // Verificar si el Jugador 2 ganó
            bool barcosJugador1Destruidos = true;
            for (int i = 0; i < TAM_TABLERO; i++) {
                for (int j = 0; j < TAM_TABLERO; j++) {
                    if (tableroJugador1[i][j] == 'X') {
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

    // Cerrar conexiones y sockets
    close(jugador2Socket);
    close(servidorSocket);

    return 0;
}

