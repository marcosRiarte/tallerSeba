#include "JuegoServidor.h"
#include "JuegoCliente.h"

// para multi-threading
#include <process.h>

void serverLoop(void *);
void clientLoop(void *);

JuegoServidor * servidor;
JuegoCliente * cliente;

int main() {

	// Inicia el servidor
	servidor = new JuegoServidor();

	// Inicia el cliente
	cliente = new JuegoCliente();

	// crea hilo con un argumento arbitrario para la función correr

	_beginthread(serverLoop, 0, (void*) 12);

	_beginthread(clientLoop, 0, (void*) 12);

}

void serverLoop(void * arg) {

	while (true) {
		servidor->actualizar();
	}
}

void clientLoop(void * arg) {

	while (true) {
		//hacer las cosas del juego
		cliente->actualizar();
	}

}
