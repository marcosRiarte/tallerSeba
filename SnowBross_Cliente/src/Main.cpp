#include <winsock2.h>
#include "redes/Conexion.h"
#include "redes/Paquetes.h"
#include "vistas/Pantalla.h"
#include "controlador/Controlador.h"
#include "Constantes.h"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
	Conexion conexion = Conexion();
	PaqueteACliente paqueteRecibido = conexion.recibir();
	if (paqueteRecibido.tipoPaquete == TipoPaquete::CONEXION_INICIAL){
		Controlador::iniciarSDL();
		Pantalla pantalla = Pantalla(paqueteRecibido);
		while(true){
			pantalla.cambiar(std::vector<Evento>());
			SDL_Delay(20);
		}
	}
	//gameloop
		//CambiarPantalla
		//ModificaObjetos

	return 0;
}
