/*
#include "escenario/Escenario.h"
#include "vistas/Pantalla.h"
#include "parseo/Config.h"
#include "Constantes.h"
#include "controlador/Controlador.h"
#include <iostream>
#include <stdio.h>
#include <exception>
#include "excepciones/MVCExcepcion.h"

// Estructura del modelo
struct MC {
	Escenario* escenario;
	Config* config;
};

// Momentos de la ejecucion
MC* creacionDelModelo(const char*) throw (MC_Excepcion);
int gameLoop(MC*);
void terminar(MC*);

int main(int argc, char* argv[]) {
	int fin = CONTINUAR;
	while (FIN_DEL_JUEGO != fin) {
		try {
			MC* mvc = creacionDelModelo("prueba.json");
			fin = gameLoop(mvc);
			terminar(mvc);
		} catch (MVC_Excepcion& ex) {
			std::cout << ex.what() << "\n";
			std::cout << "Revisar log de errores" << "\n";
			return RES_OK;
		}
	}
	return RES_OK;
}

// Crea todas las partes del modelo
MC* creacionDelModelo(const char* direccionDeLaConfiguracion) throw (MVC_Excepcion) {
	MC* mvc = new MVC;
	char msg[1000];

	//Se parsea el archivo Json
	try {
		std::string asd = "prueba.json";
		mvc->config = new Config(asd);
	} catch (Config_Excepcion&) {
		throw MVC_Excepcion("No se pudo parsear el archivo .json");
	}

	//Se loguea la creación de objetos
	snprintf(msg, 1000, "Se parsearon: %d objetos",	mvc->config->getObjetos().size());
	loguer->loguear(msg, Log::LOG_DEB);

	//Se crea el escenario
	mvc->escenario = new Escenario(mvc->config);

	//Se loguea la creación del escenario
	snprintf(msg, 1000,
			"Se creo la física Box2D con ancho: %d unidades, alto %d unidades y %d objetos",
			mvc->config->getAncho(),
			mvc->config->getAlto(),
			mvc->config->getObjetos().size());
	loguer->loguear(msg, Log::LOG_DEB);

	//Se inicializa SDL
	Controlador::iniciarSDL();

	//Se crea la pantalla
	try {
		//TODO - se hardcodea el numero del personaje
		mvc->pantalla = new Pantalla(mvc->config, mvc->config->getPersonajes().at(0)->getID());
	} catch (SDL_Excepcion&) {
		throw MVC_Excepcion("No se pudo crear la pantalla \n");
	}

	//Se loguea la creación de pantalla
	snprintf(msg, 1000,
			"Se creo la pantalla con ancho: %d unidades y alto %d unidades",
			mvc->pantalla->getAncho(), mvc->pantalla->getAlto());
	loguer->loguear(msg, Log::LOG_DEB);

	return mvc;
}
*/
/**
 * Se inicia el juego. Durante el juego siempre se estará dentro de este loop.
 * @return 0 si el juego terminó.
 * @return 1 si el juego debe resetearse.
 */
/*
// Ejecuta el modelo
int gameLoop(MVC* mvc) {
	std::vector<Evento> eventosMundo = std::vector<Evento>();
	std::vector<Evento> eventosPantalla = std::vector<Evento>();

	// FRAN: hacer un vector de uno de esto...
	std::vector<std::vector<Evento>*> vectorEventosMundo;
	std::vector<int> vectorIDPersonajes;
	vectorIDPersonajes.push_back(mvc->config->getPersonajes().at(0)->getID());
	vectorEventosMundo.push_back(&eventosMundo);

	int fin = CONTINUAR;
	while (FIN_DEL_JUEGO != fin && REINICIAR != fin) {
		// Responsabilidades> ...
		fin = Controlador::cambiar(&eventosMundo, &eventosPantalla);
		mvc->escenario->cambiar(vectorEventosMundo, vectorIDPersonajes);
		mvc->pantalla->cambiar(eventosPantalla);
		SDL_Delay(10);
	}

	return fin;
}

// Libera la memoria
void terminar(MVC* mvc){
	delete mvc->escenario;
	delete mvc->pantalla;
	delete mvc->config;
	delete mvc;
	SDL_Quit();
}
*/
