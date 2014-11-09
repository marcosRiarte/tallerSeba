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
struct Datos {
	std::vector<Evento>* eventosPantalla;
	Conexion* conexion;
	Pantalla* pantalla;
	bool* Termino;
};

// Hilo que envia los eventos de entrada en teclado
DWORD WINAPI enviarEventos(LPVOID param) {
	Datos datos = (Datos) param;
	std::vector<Evento> eventosMundo = std::vector<Evento>();

	PaqueteAServidor paquete;
	paquete.tipoPaquete = Paquetes::CONEXION_INICIAL;

	// Guarda los cambio en teclado que sirven para pantalla en memoria
	// y envia los que sirven para escenario al sever
	// Este while maneja la salida del cliente
	while (FIN_DEL_JUEGO != fin && !datos->Termino) {
		fin = Controlador::cambiar(&eventosMundo, datos.eventosPantalla);
		paquete.contador = eventosMundo.size();
		for (int j = 0; j < contador; j++) {
			paquete.eventos[j] = eventosMundo.at(j).getTecla();
		}
		datos.conexion->enviar(paquete);
	}

	// Avisa al servidor q el cliente se cerro
	paquete.tipoPaquete = Paquetes::FINALIZACION;
	datos.conexion->enviar(paquete);
}

// Hilo que recibe los datos de los cambios en el escenario y los muestra
DWORD WINAPI recibirDatos(LPVOID param) {
	Datos datos = (Datos) param;
	PaqueteACliente paquete;
	// Se recorre los datos recibidos cambiando rot y pos y dsp se muestra.
	while (true) {
		paquete = datos.conexion->recibir());
		if (paquete.tipoPaquete == Paquetes::ACTUALIZACION) {
			for (int j = 0; j < paquete.contadorPersonaje; j++) {
				pantalla.cambiarPersonaje(paquete.paquetePersonaje[j]);
			}
			for (int j = 0; j < paquete.contadorObjetos; j++) {
				pantalla.cambiarPersonaje(paquete.paqueteObjeto[j]);
			}
			pantalla.cambiar(datos.eventosPantalla);
			SDL_Delay(20);
		} else if (paquete.tipoPaquete == Paquetes::FINALIZACION) {
			datos->Termino = true;
		}
	}
}

int main(int argc, char** argv) {
	Datos datos;
	datos.conexion = new Conexion();
	std::vector<Evento>* eventosPantalla = new std::vector<Evento>();
	PaqueteACliente paqueteRecibido = datos.conexion.recibir();
	if (paqueteRecibido.tipoPaquete == TipoPaquete::CONEXION_INICIAL){
		Controlador::iniciarSDL();
		datos.pantalla = new Pantalla(paqueteRecibido);
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
	hiloEnviaEventos.join();

	// Cierra el cliente
	CloseHandle(hiloEnviaEventos);
	CloseHandle(hiloRecibeDatos);
	delete datos.pantalla;
	delete datos.conexion;
	delete datos.eventosPantalla;
	SDL_Quit();

	return 0;
}

