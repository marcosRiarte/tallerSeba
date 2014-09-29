#include "escenario/Escenario.h"
#include "vistas/Pantalla.h"
#include "parseo/Config.h"
#include "Constantes.h"
#include "controlador/Controlador.h"
#include <iostream>

// Estructura del modelo
struct MVC {
	Escenario* escenario;
	Pantalla* pantalla;
	Config* config;
};

// Momentos de la ejecucion
MVC* creacionDelModelo(char*);
int gameLoop(MVC*);
void terminar(MVC*);

int main(int argc, char* argv[]) {
	int fin = REINICIAR;
	while (FIN_DEL_JUEGO != fin) {
		MVC* mvc = creacionDelModelo(argv[1]);
		fin = gameLoop(mvc);
		terminar(mvc);
	}

	return RES_OK;
}

// Crea todas las partes del modelo
MVC* creacionDelModelo(char* direccionDeLaConfiguracion) {
	MVC* mvc = new MVC;

	mvc->config = new Config(direccionDeLaConfiguracion);
	mvc->escenario = new Escenario(mvc->config);
	Controlador::iniciarSDL();
	mvc->pantalla = new Pantalla(mvc->config);

	return mvc;
}

void ayuda() {
	std::cout << "Ayuda: \n";
	std::cout
			<< "\t Para ejecutar SnowBross ingresar dirección del archivo de configuración. \n";
	std::cout << "Ejemplo: \n";
	std::cout << "\t > SnowBross 'c:\\configuracion.json' \n";
}

/**
 * Se inicia el juego. Durante el juego siempre se estará dentro de este loop.
 * @return 0 si el juego terminó.
 * @return 1 si el juego debe resetearse.
 */

// Ejecuta el modelo
int gameLoop(MVC* mvc) {
	std::vector<Evento*>* listaDeEventos;
	listaDeEventos = new std::vector<Evento*>();

	int fin = CONTINUAR;
	while (FIN_DEL_JUEGO != fin && REINICIAR != fin) {
		// Responsabilidades> ...
		fin = Controlador::cambiar(listaDeEventos);
		mvc->escenario->cambiar(listaDeEventos);
		mvc->pantalla->cambiar();
		SDL_Delay(10);
	}

	delete listaDeEventos;

	return fin;
}

// Libera la memoria
void terminar(MVC* mvc){
	delete mvc->escenario;
	delete mvc->pantalla;
	delete mvc->config;
	delete mvc;
}
