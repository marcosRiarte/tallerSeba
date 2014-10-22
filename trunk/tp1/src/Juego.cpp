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
struct MVC {
	Escenario* escenario;
	Pantalla* pantalla;
	Config* config;
};

// Momentos de la ejecucion
MVC* creacionDelModelo(const char*) throw (MVC_Excepcion);
int gameLoop(MVC*);
void terminar(MVC*);

int main(int argc, char* argv[]) {
	int fin = REINICIAR;
	while (FIN_DEL_JUEGO != fin) {
		try {
			MVC* mvc = creacionDelModelo("prueba.json");
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
MVC* creacionDelModelo(const char* direccionDeLaConfiguracion) throw (MVC_Excepcion) {
	MVC* mvc = new MVC;
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
		mvc->pantalla = new Pantalla(mvc->config);
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

void ayuda() {
	std::cout << "Ayuda: \n";
	std::cout << "\t Para ejecutar SnowBross ingresar dirección del archivo de configuración. \n";
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
	std::vector<Evento> listaDeEventos = std::vector<Evento>();

	int fin = CONTINUAR;
	while (FIN_DEL_JUEGO != fin && REINICIAR != fin) {
		// Responsabilidades> ...
		fin = Controlador::cambiar(&listaDeEventos);
		mvc->escenario->cambiar(&listaDeEventos);
		mvc->pantalla->cambiar(&listaDeEventos);
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
