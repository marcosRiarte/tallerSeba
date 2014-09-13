/* Maneja la relacion entre Box2D y el resto del Juego.
 */

#include <vector>
#include "Escenario.h"

Escenario::Escenario(std::vector<Personaje> e_personajes,std::vector<ObjetoMapa> e_objetos) {
	this->objetos = e_objetos;
	this->personajes = e_personajes;
}

void cambiar(Evento evento) {

}
