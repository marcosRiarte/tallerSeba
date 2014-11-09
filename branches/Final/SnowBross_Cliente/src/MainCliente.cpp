#include <windows.h>
#include <winsock2.h>
#include <iostream>
#include <string>

#include "redes/Cliente.h"
#include "redes/Paquetes.h"
#include "vistas/Pantalla.h"
#include "controlador/Controlador.h"
#include "Constantes.h"

// Estructura para comunicarse entre hilos
typedef struct Datos {
	std::vector<Evento>* eventosPantalla;
//	Conexion* conexion;
	Pantalla* pantalla;
	bool Termino;
} DATOS, *PDATOS;;

// Hilo que envia los eventos de entrada en teclado
DWORD WINAPI enviarEventos(LPVOID param) {
	PDATOS datos;
	datos = (PDATOS) param;
	std::vector<Evento> eventosMundo = std::vector<Evento>();

	PaqueteAServidor paquete;
	paquete.tipoPaquete = TipoPaquete::ACTUALIZACION;

	bool fin = false;

	// Guarda los cambio en teclado que sirven para pantalla en memoria
	// y envia los que sirven para escenario al sever
	// Este while maneja la salida del cliente
	while (FIN_DEL_JUEGO != fin && !datos->Termino) {
		fin = Controlador::cambiar(&eventosMundo, datos->eventosPantalla);
		paquete.contador = eventosMundo.size();
		for (unsigned int j = 0; j < paquete.contador; j++) {
			paquete.eventos[j] = eventosMundo.at(j).getTecla();
		}
//		datos->conexion->enviar(paquete); TODO - Fran! se borra?
		try{
			Cliente::enviar(paquete);
		}catch(Cliente_Excepcion &e){
			loguer->loguear(e.what(), Log::LOG_ERR);
			throw &e; //TODO - Si no se hace nada con la excepcion, habria que sacar este try catch y ponerlo en una capa mas arriba
		}
	}

	// Avisa al servidor q el cliente se cerro
	paquete.tipoPaquete = TipoPaquete::FINALIZACION;
//	datos->conexion->enviar(paquete);	TODO - Fran! se borra?
	try{
		Cliente::enviar(paquete);
	}catch(Cliente_Excepcion &e){
		loguer->loguear(e.what(), Log::LOG_ERR);
		throw &e; //TODO - Si no se hace nada con la excepcion, habria que sacar este try catch y ponerlo en una capa mas arriba
	}
	return 0;
}

// Hilo que recibe los datos de los cambios en el escenario y los muestra
DWORD WINAPI recibirDatos(LPVOID param) {
	PDATOS datos;
	datos = (PDATOS) param;

	PaqueteACliente paquete;
	// Se recorre los datos recibidos cambiando rot y pos y dsp se muestra.
	while (true) {
//		paquete = datos->conexion->recibir(); TODO - Fran! se borra?
		try {
			paquete = Cliente::recibir();
		} catch (Cliente_Excepcion &e) {
			loguer->loguear(e.what(), Log::LOG_ERR);
			throw &e; //TODO - Si no se hace nada con la excepcion, habria que sacar este try catch y ponerlo en una capa mas arriba
		}
		switch (paquete.tipoPaquete) {
		case (TipoPaquete::ACTUALIZACION): {
			for (unsigned int j = 0; j < paquete.contadorPersonaje; j++) {
				datos->pantalla->cambiarPersonaje(paquete.paquetePersonaje[j]);
			}
			for (unsigned int j = 0; j < paquete.contadorObjetos; j++) {
				datos->pantalla->cambiarObjetoMapa(paquete.paqueteObjeto[j]);
			}
			datos->pantalla->cambiar(*(datos->eventosPantalla));
			SDL_Delay(20);
			break;
		}
		case (TipoPaquete::FINALIZACION): {
			datos->Termino = true;
			break;
		}
		}
	}
	return 0;
}

int main(int argc, char** argv) {
	PDATOS datos;
//	datos->conexion = new Conexion(); TODO - Fran! se borra?
	Cliente::iniciar();
	datos->eventosPantalla = new std::vector<Evento>();
//	PaqueteACliente paqueteRecibido = datos->conexion->recibir(); TODO - Fran! se borra?
	PaqueteACliente paqueteRecibido;
	try{
		paqueteRecibido = Cliente::recibir();
	}catch(Cliente_Excepcion &e){
		loguer->loguear(e.what(), Log::LOG_ERR);
		return -1;
	}
	if (paqueteRecibido.tipoPaquete == TipoPaquete::CONEXION_INICIAL){
		Controlador::iniciarSDL();
		datos->pantalla = new Pantalla(paqueteRecibido);
	}

	//gameloop
	HANDLE hiloEnviaEventos = CreateThread(0, 0, enviarEventos, &datos, 0, 0);
	HANDLE hiloRecibeDatos = CreateThread(0, 0, recibirDatos, &datos, 0, 0);

	// Espera a que el cliente quiera salir del juego
	WaitForSingleObject(hiloEnviaEventos, INFINITE);

	// Cierra el cliente
	CloseHandle(hiloEnviaEventos);
	CloseHandle(hiloRecibeDatos);
	delete datos->pantalla;
//	delete datos->conexion; TODO - Fran! se borra?
	delete datos->eventosPantalla;
	delete datos;
	SDL_Quit();

	return 0;
}

