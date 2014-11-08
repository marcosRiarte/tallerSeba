#ifndef CONTROLADOR_H_
#define CONTROLADOR_H_
#include <vector>
#include "Evento.h"

class Controlador {
public:

	/* Se eliminan los eventos de la lista y se lo completa con los nuevos
	 * Obtenidos por el teclado.
	 */
	static int cambiar(std::vector<Evento>* eventosMundo, std::vector<Evento>* eventosPantalla);

	// Esta función inicia SDL
	static void iniciarSDL();
};

#endif /* CONTROLADOR_H_ */
