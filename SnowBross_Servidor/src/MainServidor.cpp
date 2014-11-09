#include "parseo/Config.h"
#include "escenario/Escenario.h"
#include "redes/Servidor.h"
#include <iostream>
#include <string.h>
#include <windows.h>

#include "excepciones/ConfigExcepcion.h"
#include "excepciones/MVCExcepcion.h"
#include "Constantes.h"


int main(int argc, char** argv) {

	Config* configuracion;
	Escenario* escenario;

	//Creo el Config a partir del json
	try {
		configuracion = new Config("prueba.json");
	} catch (Config_Excepcion&) {
		throw MVC_Excepcion("No se pudo parsear el archivo .json");
	}

	//Creo el Escenario
	escenario = new Escenario(configuracion);

	//Creo el servidor
	unsigned int cantidadDeClientes = 1;
	try{
		Servidor::iniciar(cantidadDeClientes);
	}catch(Servidor_Excepcion &e){
		loguer->loguear(e.what(), Log::LOG_ERR);
	}

/*
	//Cuando hay una conexion creo un paquete inicial y lo mando
	PaqueteAServidor pRecibido = servidor->recibir();
	if (pRecibido.tipoPaquete == TipoPaquete::CONEXION_INICIAL) {
		Servidor::enviar(configuracion->crearPaqueteInicial());
	}

	while(true){
		Sleep(10000);
	}
*/
}
