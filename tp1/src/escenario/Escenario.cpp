/* Maneja la relacion entre Box2D y el resto del Juego.
 */

#ifndef ESCENARIO_H_
#define ESCENARIO_H_

#include <vector>
#include "../entrada/Evento.h"
#include "../personajes/Personaje.h"
#include "../objetos/ObjetoMapa.h"

using namespace std;

class Escenario {
private:
	vector<Personaje> personajes;
	vector<ObjetoMapa> objetos;
public:
	//void Escenario(vector<Personaje> personajes,vector<ObjetoMapa> objetos);

	// Genera un nuevo de step, pone a los personajes en sus nuevas posiciones,
	// avisando si cambiar en relacion a su posicion anterior.
	void cambiar(Evento evento);

	virtual ~Escenario();
};


#endif /* ESCENARIO_H_ */
