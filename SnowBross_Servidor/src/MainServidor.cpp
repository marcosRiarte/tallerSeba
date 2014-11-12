#include <iostream>
#include <SDL2/SDL.h>
#include <sstream>
#include <string.h>
#include <windows.h>

#include "Constantes.h"
#include "escenario/Escenario.h"
#include "excepciones/ConfigExcepcion.h"
#include "excepciones/MVCExcepcion.h"
#include "parseo/Config.h"
#include "redes/Servidor.h"

// Estructuras para comunicarse entre hilos
typedef struct RDatos {
	std::vector<std::vector<Evento>*>* vectorDeListaDeEventos;
	std::vector<int>* vectorDeID;
	int numeroDeSock;
	int personajeID;
	SDL_sem* semaforo;

	void bloquear(){
		SDL_SemWait(semaforo);
	}

	void desbloquear(){
		SDL_SemPost(semaforo);
	}

} RDATOS, *PRDATOS;

// Estructuras para comunicarse entre hilos
typedef struct EDatos {
	std::vector<std::vector<Evento>*>* vectorDeListaDeEventos;
	std::vector<int>* vectorDeID;
	Escenario* escenario;
	int cantDeClientes;
	bool cambio;
	SDL_sem* semaforo;

	void bloquear() {
		SDL_SemWait (semaforo);
	}

	void desbloquear() {
		SDL_SemPost (semaforo);
	}
} EDATOS, *PEDATOS;

// Hilo que envia los eventos de entrada en teclado
DWORD WINAPI enviarDatos(void * param) {
	PEDATOS datos;
	datos = (PEDATOS) param;

	PaqueteACliente paquete;
	paquete.tipoPaquete = TipoPaquete::ACTUALIZACION;

	// No se con q condicion cerrar el server, dsp le pongo corte
	while (true) {
		Sleep(30);
		datos->bloquear();
		if (datos->cambio) {
			// Se arma el paquete para enviar
			std::vector<Personaje*> personajes = datos->escenario->getPersonajes();
			paquete.contadorPersonaje = personajes.size();
			for (unsigned int j = 0; j < personajes.size(); j++) {
				paquete.paquetePersonaje[j].estado = personajes.at(j)->getEstado();
				paquete.paquetePersonaje[j].id = personajes.at(j)->getID();
				Pos pos = personajes.at(j)->getPos().ySimetrico();
				paquete.paquetePersonaje[j].x = pos.getX();
				paquete.paquetePersonaje[j].y = pos.getY();
			}
			std::vector<ObjetoMapa*> objetos = datos->escenario->getObjetos();
			paquete.contadorObjetos = objetos.size();
			for (unsigned int j = 0; j < objetos.size(); j++) {
				ObjetoMapa* o = objetos.at(j);
				Pos p = o->getPos().ySimetrico();
				std::vector<Pos> contorno = o->getContorno();
				paquete.paqueteObjeto[j].id = o->getID();
				paquete.paqueteObjeto[j].x = p.getX();
				paquete.paqueteObjeto[j].y = p.getY();
				paquete.paqueteObjeto[j].cantidadVertices = contorno.size();
				for (unsigned k = 0; k < contorno.size(); k++) {
					Pos pAux = contorno.at(k).ySimetrico();
					paquete.paqueteObjeto[j].vx[k] = pAux.getX();
					paquete.paqueteObjeto[j].vy[k] = pAux.getY();
				}
				paquete.paqueteObjeto[j].color = o->getColor();
				paquete.paqueteObjeto[j].esEstatico = o->esEstatico();
				paquete.paqueteObjeto[j].rotacion = o->getRotacion();
			}

			// Se envia a todos los clientes
			for (int i = 0; i < datos->cantDeClientes; i++) {
				Servidor::enviar(Servidor::sock[i], paquete);
			}
			datos->cambio = false;
		}
		datos->desbloquear();
	}

	return 0;
}

// Hilo que recibe los datos de los cambios en el escenario y los muestra
DWORD WINAPI recibirDatos(void * param) {
	PRDATOS datos;
	datos = (PRDATOS) param;

	PaqueteAServidor paquete;
	// Se recorre los datos recibidos cambiando rot y pos y dsp se muestra.
	while (true) {
		Sleep(2);
		// Nose si esto va a tener sentido dsp.
		try{
			paquete = Servidor::recibir(Servidor::sock[datos->numeroDeSock]);
		}catch(Servidor_Excepcion &e){
			loguer->loguear(e.what(), Log::LOG_ERR);
		}
		switch (paquete.tipoPaquete) {
		case (TipoPaquete::ACTUALIZACION): {
			std::vector<Evento>* vectEventos = new std::vector<Evento>;
			for (unsigned int j = 0; j < paquete.contador; j++) {
				Evento evento = Evento(paquete.eventos[j]);
				vectEventos->push_back(evento);
			}
			datos->bloquear();
			datos->vectorDeID->push_back(datos->personajeID);
			datos->vectorDeListaDeEventos->push_back(vectEventos);
			datos->desbloquear();
			break;
		}
		case (TipoPaquete::FINALIZACION): {
			// No se que hacer si se desconecta...
			break;
		}
		}
	}
	return 0;
}

int main(int argc, char** argv) {

	Config* configuracion;
	Escenario* esc;

	unsigned int cantidadDeClientes = 1;

	//Creo el Config a partir del json
	try {
		configuracion = new Config("prueba.json");
	} catch (Config_Excepcion&) {
		throw MVC_Excepcion("No se pudo parsear el archivo .json");
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
			loguer->loguear("No se pudo iniciar SDL",Log::LOG_ERR);
			//const char* msg = ((std::string)"Error iniciando SDL: ").append(SDL_GetError()).c_str();
			//throw new SDL_Excepcion(msg);
	}

	//Creo el Escenario
	esc = new Escenario(configuracion);
	configuracion->setObjetos(esc->getObjetos());

	//Creo el servidor
	try{
		Servidor::iniciar(cantidadDeClientes);
	}catch(Servidor_Excepcion &e){
		loguer->loguear(e.what(), Log::LOG_ERR);
	}
	try{
		Servidor::enviar(Servidor::sock[0], configuracion->crearPaqueteInicial());
	}catch(Servidor_Excepcion &e){
		loguer->loguear(e.what(), Log::LOG_ERR);
		return -1;
	}

	// Se crea el vector con hilos para los clientes
	std::vector<int>* vDeID = new std::vector<int>();
	std::vector<std::vector<Evento>*>* vDeListaDeEventos = new std::vector<std::vector<Evento>*>();
	HANDLE  vectorDeHilos[cantidadDeClientes];
	PRDATOS rdatos[cantidadDeClientes];
	SDL_sem* s = SDL_CreateSemaphore(1);
	for (unsigned int i = 0; i < cantidadDeClientes; i++) {
		rdatos[i] = new RDatos();
		rdatos[i]->vectorDeID = vDeID;
		rdatos[i]->vectorDeListaDeEventos = vDeListaDeEventos;
		// Esto esta hecho asi, pq no se de q manera puedo poner el mismo numero de sock al id de personaje
		// TODO
		rdatos[i]->numeroDeSock = i;
		rdatos[i]->personajeID = i;
		rdatos[i]->semaforo = s;
		vectorDeHilos[i] = CreateThread(0, 0, recibirDatos, rdatos[i], 0, 0);
	}

	PEDATOS datos = new EDatos();
	datos->vectorDeID = vDeID;
	datos->vectorDeListaDeEventos = vDeListaDeEventos;
	datos->cantDeClientes = cantidadDeClientes;
	datos->escenario = esc;
	datos->cambio = false;
	datos->semaforo = s;
	HANDLE hiloEnviaDatos = CreateThread(0, 0, enviarDatos, datos, 0, 0);

	while (true) {
		Sleep(10);
		// TODO ver como se vacian las listas
		datos->bloquear();
		esc->cambiar(*(datos->vectorDeListaDeEventos), *(datos->vectorDeID));
		datos->cambio = true;
		// Esto no deberia perder memoria, pero si se pierde memoria en algun lugar ver aca
		datos->vectorDeListaDeEventos->clear();
		datos->vectorDeID->clear();
		datos->desbloquear();
	}

	delete vDeID;
	delete vDeListaDeEventos;
	delete esc;
	delete configuracion;
	for (unsigned int i = 0; i < cantidadDeClientes; i++) {
		CloseHandle(vectorDeHilos[i]);
		delete rdatos[i];
	}
	CloseHandle(hiloEnviaDatos);
	delete datos;
	SDL_DestroySemaphore(datos->semaforo);
	SDL_Quit();
	return 0;
}
