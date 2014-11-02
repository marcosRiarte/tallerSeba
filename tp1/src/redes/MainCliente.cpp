#include "JuegoCliente.h"

// para multi-threading
#include <windows.h>
#include <stdio.h>

DWORD WINAPI clientLoop(void *);

JuegoCliente * cliente;

int main() {

	// Inicia el cliente
		cliente = new JuegoCliente();

// crea hilo con un argumento arbitrario para la función correr
unsigned int myCounter = 0;
	DWORD myThreadID;
	HANDLE myHandle = CreateThread(0, 0, clientLoop, &myCounter, 0, &myThreadID);
	CloseHandle(myHandle);
	return 0;
}

DWORD WINAPI clientLoop(void * arg) {

	while (true) {
		cliente->actualizar();
	}
	return 0;
}
