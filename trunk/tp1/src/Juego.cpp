#include <iostream>
#include <SDL2/SDL.h>
#include "Constantes.h"
#include "../test/Tests.h"
#include "parseo/Config.h"
#include "objetos/ObjetoMapa.h"

const string DIR_LOG = "./Log.txt";


void ayuda() {
	cout << "Ayuda: \n";
	cout
			<< "\t Para ejecutar SnowBross ingresar dirección del archivo de configuración. \n";
	cout << "Ejemplo: \n";
	cout << "\t > SnowBross 'c:\\configuracion.json' \n";
}

/**
 * Se inicia el juego. Durante el juego siempre se estará dentro de este loop.
 * @return 0 si el juego terminó.
 * @return 1 si el juego debe resetearse.
 */
int gameloop() {
	/*
	 while (true) {
	 double start = getCurrentTime();
	 processInput(); //Se Obtienen los input del teclado
	 update();	//Se realizan las modificaciones en los objetos
	 render();	//Se procesan las imágenes
	 sleep(start + MS_PER_FRAME - getCurrentTime());
	 }
	 */
	return 0;
}

/**
 * Se encarga de liberar la memoria que ya no se va a usar
 */
void finalizar() {
}

/**
 * @return devuele 0 (si resultado Ok) y distinto de 0 si hubo error.
 */
int main(int argc, char* argv[]) {
	//Pequeña validacion de los argumentos pasados.
	if (argc != 2) {
		ayuda();
		return RES_AYUDA;
	}
	string dirArchivoConfiguracion = argv[1];
	Config* configuracion = new Config(dirArchivoConfiguracion);
	bool fin = false;
	while (!fin) {
		//Se crea un objeto de configuracion
		// con lo necesario para crear el mapa y los personajes
		configuracion->reset();
		//Se crean los objetos y personajes

		//Se crean las vistas de los objetos y personajes




		//Se crea la pantalla y se inicia SDL

		Pantalla *pantalla = configuracion->getPantalla();
		try{
			pantalla->inicializar();

		}catch(exception *e){
			finalizar();
			cout << e->what();
			return RES_ERR;
		}

		//Se inicia el juego
		if (gameloop() == 0)
			fin = true;
		//Se debe liberar lo que ya no se usa
		finalizar();
	}
	return RES_OK;
}
