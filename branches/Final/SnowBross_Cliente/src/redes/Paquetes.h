#ifndef PAQUETE_H_
#define PAQUETE_H_
#include <string.h>
#include "../elementosJuego/personajes/Personaje.h"

/**
 * TODO - Los vertices tienen que venir con x e y positivos!!!!!!!!
 */

enum TipoPaquete {
    CONEXION_INICIAL = 0,
    ACTUALIZACION = 1,
    FINALIZACION = 2,
};

struct PaqueteObjeto {
	unsigned int id;
	unsigned int x;
	unsigned int y;
	unsigned int rotacion;
	bool esEstatico;
	unsigned long color;
	unsigned cantidadVertices;
	unsigned int vx[6];
	unsigned int vy[6];
};

struct PaquetePersonaje {
	unsigned int id;
	unsigned int x;
	unsigned int y;
	Personaje::Estado estado;
};

struct PaqueteInicial {
	unsigned int altoPx;
	unsigned int anchoPx;
	unsigned int alto;
	unsigned int ancho;
	unsigned int IDPersonajePrincipal;
};

struct PaqueteACliente {
    unsigned int tipoPaquete;
    PaqueteInicial paqueteInicial;
    PaquetePersonaje paquetePersonaje[5];
    unsigned int contadorPersonaje;
    PaqueteObjeto paqueteObjeto[10];
    unsigned int contadorObjetos;
    void serialize(char * data) {
        memcpy(data, this, sizeof(PaqueteACliente));
    }
    void deserialize(char * data) {
        memcpy(this, data, sizeof(PaqueteACliente));
    }
};

struct PaqueteAServidor {
	unsigned int tipoPaquete;
	unsigned int eventos[5];
	unsigned int contador;
	void serialize(char * data) {
		memcpy(data, this, sizeof(PaqueteACliente));
	}
	void deserialize(char * data) {
		memcpy(this, data, sizeof(PaqueteACliente));
	}
};

#endif /* PAQUETE_H_ */
