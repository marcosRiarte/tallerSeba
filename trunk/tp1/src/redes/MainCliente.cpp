#include "JuegoCliente.h"
#include "../Constantes.h"
#include "../vistas/Pantalla.h"
#include "../parseo/Config.h"
#include <exception>
#include "../excepciones/MVCExcepcion.h"
#include <iostream>
#include "../controlador/Controlador.h"

// para multi-threading
#include <windows.h>
#include <stdio.h>

DWORD WINAPI clientLoop(void *);

JuegoCliente * cliente;

// Estructura del modelo
struct MVC {
	Pantalla* pantalla;
	Config* config;
};

// Momentos de la ejecucion
MVC* creacionDelModelo(const char*) throw (MVC_Excepcion);
int gameLoop(MVC*);
void terminar(MVC*);

int main(int argc, char* argv[]) {

	// Inicia el cliente
		cliente = new JuegoCliente();

// crea hilo con un argumento arbitrario para la función correr
unsigned int myCounter = 0;
	DWORD myThreadID;
	HANDLE myHandle = CreateThread(0, 0, clientLoop, &myCounter, 0, &myThreadID);
	std::string dir = PATH_LOG;
	std::string dirArchivo = dir.append("recuperarTexto.json");
	const char* direc = dirArchivo.c_str();
	int fin = REINICIAR;
		while (FIN_DEL_JUEGO != fin) {
			try {
				MVC* mvc = creacionDelModelo(direc);
				fin = gameLoop(mvc);
				CloseHandle(myHandle);
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
		std::string archivoJson = "prueba.json";
		mvc->config = new Config(archivoJson);

	} catch (Config_Excepcion&) {
		throw MVC_Excepcion("No se pudo parsear el archivo .json");
	}

	//Se loguea la creación de objetos
	snprintf(msg, 1000, "Se parsearon: %d objetos",	mvc->config->getObjetos().size());
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

// Ejecuta el modelo
int gameLoop(MVC* mvc) {
	std::vector<Evento> listaDeEventos = std::vector<Evento>();
	listaDeEventos = std::vector<Evento>();
	int fin = CONTINUAR;
	while (FIN_DEL_JUEGO != fin && REINICIAR != fin) {
		// Responsabilidades> ...
		fin = Controlador::cambiar(&listaDeEventos);
		mvc->pantalla->cambiar(&listaDeEventos);
		SDL_Delay(10);
	}

	return fin;
}

// Libera la memoria
void terminar(MVC* mvc){
	delete mvc->pantalla;
	delete mvc->config;
	delete mvc;
	SDL_Quit();
}

DWORD WINAPI clientLoop(void * arg) {

	while (true) {
		cliente->actualizar();
	}
	return 0;
}
