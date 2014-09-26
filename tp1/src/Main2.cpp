#include "escenario/Escenario.h"
#include "vistas/Vista.h"
#include "parseo/Config.h"
/*#include "../controlador/Controlador.h"*/

// Estructura del modelo
struct MVC {
	Escenario* escenario;
	Vista* vista;
	// El controlador todavia no existe es la clase q manejaria la entra da telcado (seba y lei la ibana  hacer)
/*	Controlador* controlador;*/
	// La config no deberia estar aca, pero nose como esta implementado y capaz es necesario que siga existiendo hasta el ginal
	Config* config;
};

// Momentos de la ejecucion
MVC* creacionDelModelo(char*);
void gameLoop(MVC*);
void terminar(MVC*);

void main2(int argc, char* argv[]) {
	MVC* mvc = creacionDelModelo(argv[1]);
	gameLoop(mvc);
	terminar(mvc);
}

// Crea todas las partes del modelo
MVC* creacionDelModelo(char* direccionDeLaConfiguracion) {
	MVC* mvc = new MVC;

	mvc->config = new Config(direccionDeLaConfiguracion);
	mvc->escenario = new Escenario(mvc->config);
	// Creo que la vista necesitaba confif para crearse, pero ni idea...
/*	mvc->vista = new Vista(mvc->config);*/
	// No se si necesitan algo para crear el controlador.
/*	mvc->controlador = new Controlador();*/

	return mvc;
}

// Ejecuta el modelo
void gameLoop(MVC* mvc) {
	// es un arreglo estatico para que todo sea mas facil
	std::vector<Evento*>* listaDeEventos;
	listaDeEventos = new std::vector<Evento*>;

	bool fin = false;
	while (!fin) {
		// Cada evento que se crea deberias borrarlo, igual calculo q se sobreescribe sino o algo asi
/*		fin = mvc->controlador->cambiar(listaDeEventos);*/
		mvc->escenario->cambiar(listaDeEventos);
/*		mvc->vista->cambiar(listaDeEventos);*/
	}

	delete listaDeEventos;
}

// Libera la memoria
void terminar(MVC* mvc){
/*	delete mvc->controlador;*/
	delete mvc->escenario;
	delete mvc->vista;
	delete mvc->config;
	delete mvc;
}
