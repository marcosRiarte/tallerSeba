/*
 * Controlador.h
 *
 *  Created on: 27/9/2014
 *      Author: Seba
 */

#ifndef CONTROLADOR_H_
#define CONTROLADOR_H_
#include <SDL2/SDL.h>
#include <vector>
#include "../entrada/Evento.h"

class Controlador {
public:
	static int cambiar(std::vector<Evento*>* listaDeEventos);
	virtual ~Controlador();
};

#endif /* CONTROLADOR_H_ */
