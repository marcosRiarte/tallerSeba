#include "JuegoServidor.h"
#include "JuegoCliente.h"

// para multi-threading
#include <process.h>

void serverLoop(void *);
void clientLoop(void);

JuegoServidor * servidor;
JuegoCliente * cliente;

int main()
{

	// Inicia el servidor
	servidor = new JuegoServidor();

	// crea hilo con un argumento arbitrario para la función correr

	_beginthread(serverLoop, 0, (void*)12);

	// Inicia el cliente
	cliente = new JuegoCliente();

	clientLoop();

	return 0;
}

void serverLoop(void * arg)
{
    if(true)
    {
        servidor->actualizar();
    }
}

void clientLoop()
{

    while(true)
    {
        //hacer las cosas del juego
       // mas adelante..cliente->actualizar();
    	return;

    }

}
