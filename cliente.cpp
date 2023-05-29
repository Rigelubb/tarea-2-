#include <iostream>

#include <sys/socket.h>

#include <arpa/inet.h>

#include <unistd.h>

#include <string>


int main(int argc, char * argv[]) {
  // Verificar argumentos de línea de comandos
  if (argc != 3) {
    std::cout << "Uso: " << argv[0] << " <ip_servidor> <puerto_servidor>" << std::endl;
    return 1;
  }

  std::string ipServidor = argv[1];
  int puertoServidor = std::stoi(argv[2]);

  int socketCliente = crearSocket();
  conectarSocket(socketCliente, ipServidor, puertoServidor);

  std::string mensaje;

  // Conexión establecida, comenzar interacción con el servidor
  while (true) {
    // Leer y enviar coordenadas de disparo
    std::cout << "Ingrese las coordenadas de disparo (ejemplo: A1): ";
    std::getline(std::cin, mensaje);

    if (mensaje == "salir") {
      break;
    }

    enviarMensaje(socketCliente, mensaje);

    // Recibir y mostrar resultados del disparo
    mensaje = recibirMensaje(socketCliente);
    std::cout << "Resultado del disparo: " << mensaje << std::endl;

    // Recibir y mostrar tableros actualizados
    mensaje = recibirMensaje(socketCliente);
    std::cout << "Tableros actualizados:\n" << mensaje << std::endl;
  }

  cerrarSocket(socketCliente);

  return 0;
}

void solicitarDisparo() {
  std::string coordenadas;
  std::cout << "Ingrese las coordenadas del disparo (ejemplo: A1): ";
  std::cin >> coordenadas;

  // Enviar las coordenadas al servidor
  enviarMensaje(coordenadas);
}

void solicitarDisparo() {
    std::string coordenadas;
    std::cout << "Ingrese las coordenadas del disparo (ejemplo: A1): ";
    std::cin >> coordenadas;

    // Enviar las coordenadas al servidor
    enviarMensaje(coordenadas);
}



