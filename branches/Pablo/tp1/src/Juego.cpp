#include <iostream>
#include <SDL2/SDL.h>
#include "Constantes.h"
#include "parseo/Config.h"
#include "objetos/ObjetoMapa.h"
#include "vistas/PersonajeVista.h"

void ayuda() {
	cout << "Ayuda: \n";
	cout << "\t Para ejecutar SnowBross ingresar dirección del archivo de configuración. \n";
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
		configuracion->crearObjetos();
		std::vector<ObjetoMapa*> *objetos = configuracion->getObjetos();
		std::vector<Personaje*> *personajes = configuracion->getPersonajes();
		//Se crea el escenario con los objetos y personajes

		//Se crean las vistas de los objetos y personajes
		std::vector<Vista*> *vistas = new vector<Vista*>();
		for(int i = 0; i+1 < objetos->size(); i++){
			Vista* v = new ObjetoMapaVista(objetos->at(i));
			vistas->push_back(v);
		}
		for(int i = 0; i+1 < personajes->size(); i++){
			Vista* v = new PersonajeVista(personajes->at(i));
			vistas->push_back(v);
		}
		//Se crea la pantalla y se inicia SDL
		Pantalla *pantalla = configuracion->getPantalla();

		/*
		 * Solo para utilizar en las pruebas...
		 * Pantalla * pantalla = new Pantalla(768, 1024, 768, 1024, "img/Fondo.jpg");
		 */


		try{
			pantalla->inicializar();
		}catch(SDL_Excepcion *e){
			finalizar();
			loguer->loguear(e->what(), Log::LOG_ERR);
			return RES_ERR;
		}
		/*
		 * Solo para utilizar en las pruebas...
		 * pantalla->update();
		 * SDL_Delay(5000);
		*/

		//Se inicia el juego
		if (gameloop() == FIN_DEL_JUEGO)
			fin = true;
		//Se debe liberar lo que ya no se usa
		finalizar();
	}
	return RES_OK;
}
