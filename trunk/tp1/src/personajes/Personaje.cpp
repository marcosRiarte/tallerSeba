#include "Personaje.h"

Personaje::Personaje(Pos* posicion) {
	pos = posicion;
	rot = 0;
	linkAMundo = nullptr;
	ancho = 60;
	alto = 80;
	rectanguloPersonaje = new Rectangulo(false, "#00F0A0", pos, 0, 80, alto, ancho);
}

// getter de dimensiones
int Personaje::getAlto(){
	return alto;
}
int Personaje::getAncho(){
	return ancho;
}

// getter y setter de la posicion
void Personaje::setPosicion(Pos* posicion) {
	pos = posicion;
}
Pos* Personaje::getPosicion(){
	return pos;
}

std::vector<Pos*>* Personaje::getContorno() {
	return rectanguloPersonaje->getContorno();
}
// devuelve verdadero si esta en esa posicion
bool Personaje::estaEnPos(Pos* posicion) {
	return pos->esIgual(posicion);
}

Rectangulo* Personaje::getRectangulo() {
	return rectanguloPersonaje;
}

Personaje::~Personaje() {
	// TODO Auto-generated destructor stub
}

// getter y setter de link a mundo
void Personaje::setLinkAMundo(b2Body* link){
	linkAMundo = link;
}

b2Body* Personaje::getLinkAMundo(){
	return linkAMundo;
}

/**
 * \brief	Se setea el estado del personaje, mediante 3 taxonomias (incompletas para el juego final).
 * 			E_PERFIL: 			determina el perfil a conciderar
 * 			E_MOVIMIENTO: 		detalla que clase de movimiento está ejerciendo el personaje.
 * 			E_ACCION:			da información sobre las interacciones que tiene el personaje con otros
 * 								objetos del juego. Podría llamarse E_INTERACCION...es dicutible.
 *
 * \param	\perfil
 * \param	\movimiento	Todos los movimientos permitidos en el juego
 * \param	\accion		Se utiliza para las interacciones del juego, por ahora solo tomamos
 * 						el caso de que este empujando un objeto o simplemente no haciendo nada
 */
void Personaje::setEstado(E_PERFIL perfil, E_MOVIMIENTO movimiento, E_ACCION accion){
	estadoPerfil = perfil;
	estadoMovimiento = movimiento;
	estadoAccion = accion;
}

/**
 * \brief	Al igual que el método setEstado(E_PERFIL, E_MOVIMIENTO, E_ACCION) se setea el estado
 * 			del personaje. Pero se toma para el caso de E_ACCION, el valor por defecto que es "NINGUNA"
 *
 * \param	\perfil
 * \param	\movimiento	Todos los movimientos permitidos en el juego
 */
void Personaje::setEstado(E_PERFIL perfil, E_MOVIMIENTO movimiento){
	estadoPerfil = perfil;
	estadoMovimiento = movimiento;
	estadoAccion = E_ACCION::NINGUNA;
}

/**
 * \return	Estado relacionado con el perfil del personaje
 */
Personaje::E_PERFIL Personaje::getPerfil(){
	return estadoPerfil;
}

/**
 * \return	Estado relacionado con el movimiento actual del personaje
 */
Personaje::E_MOVIMIENTO Personaje::getMovimiento(){
	return estadoMovimiento;
}

/**
 * \return	Estado relacionado con la accion que realiza el personaje
 */
Personaje::E_ACCION Personaje::getAccion(){
	return estadoAccion;
}

