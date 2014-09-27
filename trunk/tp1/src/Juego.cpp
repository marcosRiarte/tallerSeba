#include "escenario/Escenario.h"
#include "vistas/Pantalla.h"
#include "parseo/Config.h"
#include "Constantes.h"
#include "controlador/Controlador.h"

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
	// Creo que la vista necesitaba confif para crearse, pero ni idea...
/*	mvc->pantalla = new Pantalla(mvc->config);*/

	return mvc;
}

// Ejecuta el modelo
int gameLoop(MVC* mvc) {
	std::vector<Evento*>* listaDeEventos;
	listaDeEventos = new std::vector<Evento*>();

	int fin = false;
	while (FIN_DEL_JUEGO != fin && REINICIAR != fin) {
		// Responsabilidades> ...
		fin = Controlador::cambiar(listaDeEventos);
		mvc->escenario->cambiar(listaDeEventos);
/*		mvc->pantalla->cambiar();*/
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
