#include <winsock2.h>
#include "redes/Conexion.h"
#include "redes/Paquetes.h"
#include "vistas/Pantalla.h"
#include "controlador/Controlador.h"
#include "Constantes.h"
#include <iostream>
#include <string>
#include <windows.h>

// Estructura para comunicarse entre hilos
typedef struct Datos {
	std::vector<Evento>* eventosPantalla;
	Conexion* conexion;
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
		datos->conexion->enviar(paquete);
	}

	// Avisa al servidor q el cliente se cerro
	paquete.tipoPaquete = TipoPaquete::FINALIZACION;
	datos->conexion->enviar(paquete);

	return 0;
}

// Hilo que recibe los datos de los cambios en el escenario y los muestra
DWORD WINAPI recibirDatos(LPVOID param) {
	PDATOS datos;
	datos = (PDATOS) param;

	PaqueteACliente paquete;
	// Se recorre los datos recibidos cambiando rot y pos y dsp se muestra.
	while (true) {
		paquete = datos->conexion->recibir();
		if (paquete.tipoPaquete == TipoPaquete::ACTUALIZACION) {
			for (unsigned int j = 0; j < paquete.contadorPersonaje; j++) {
				datos->pantalla->cambiarPersonaje(paquete.paquetePersonaje[j]);
			}
			for (unsigned int j = 0; j < paquete.contadorObjetos; j++) {
				datos->pantalla->cambiarObjetoMapa(paquete.paqueteObjeto[j]);
			}
			datos->pantalla->cambiar(*(datos->eventosPantalla));
			SDL_Delay(20);
		} else if (paquete.tipoPaquete == TipoPaquete::FINALIZACION) {
			datos->Termino = true;
		}
	}

	return 0;
}

int main(int argc, char** argv) {
	PDATOS datos;
	datos->conexion = new Conexion();
	datos->eventosPantalla = new std::vector<Evento>();
	PaqueteACliente paqueteRecibido = datos->conexion->recibir();
	if (paqueteRecibido.tipoPaquete == TipoPaquete::CONEXION_INICIAL){
		Controlador::iniciarSDL();
		datos->pantalla = new Pantalla(paqueteRecibido);
		//Comente esto pq no tngo ni idea q hace aca
		/*
		while(true){
			pantalla.cambiar(std::vector<Evento>());
			SDL_Delay(20);
		}*/
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
	delete datos->conexion;
	delete datos->eventosPantalla;
	delete datos;
	SDL_Quit();

	return 0;
}

