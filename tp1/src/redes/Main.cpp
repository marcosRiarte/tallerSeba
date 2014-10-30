#include "JuegoServidor.h"
#include "JuegoCliente.h"

// para multi-threading
#include <windows.h>
#include <stdio.h>
#include <process.h>

DWORD WINAPI serverLoop(void *);
void clientLoop(void);

JuegoServidor * servidor;
JuegoCliente * cliente;
JuegoCliente * cliente2;

int main() {

	// Inicia el servidor
	servidor = new JuegoServidor();

	// Inicia el cliente
	cliente = new JuegoCliente();
	cliente2 = new JuegoCliente();

	// crea hilo con un argumento arbitrario para la función correr
	unsigned int myCounter = 0;
		DWORD myThreadID;
		HANDLE myHandle = CreateThread(0, 0, serverLoop, &myCounter, 0, &myThreadID);

	//_beginthread(serverLoop, 0, (void*) 12);

	clientLoop();


		CloseHandle(myHandle);
		return 0;

}

DWORD WINAPI serverLoop(void * arg) {

	while (true) {
		servidor->actualizar();
	}
	return 0;
}

void clientLoop() {

	while (true) {
		//hacer las cosas del juego
		//cliente->actualizar();
	}

}
