#include "Personaje.h"
#include "../../Constantes.h"

Personaje::Personaje(Pos* posicion) {
	pos = posicion;
	rot = 0;
	linkAMundo = nullptr;
	ancho = ANCHO_PERSONAJE_UN;
	alto = ALTO_PERSONAJE_UN;
	masa = MASA_PERSONAJE;
	/*this->estado= "Quieto";*/

	estado->perfil = Personaje::E_PERFIL::IZQUIERDA;
	estado->accion = Personaje::E_ACCION::QUIETO;

	rectanguloPersonaje = new Rectangulo(false, "#00F0A0", pos, 0, 80, alto, ancho); // Solo para pruebas...
}

/*
 * Devuelve el area del elemento
 */
float Personaje::getArea(){
	return alto*ancho;
}

/*
 * Getter para alto y ancho del personaje en unidades reales
 */
int Personaje::getAlto(){
	return alto;
}
int Personaje::getAncho(){
	return ancho;
}

/*
 * Setter para la posicion
 */
void Personaje::setPos(Pos* posicion) {
	pos = posicion;
	rectanguloPersonaje->setPos(posicion);
}

/*
 * Devuelve el contorno del personaje
 */
std::vector<Pos*>* Personaje::getContorno() {
	return rectanguloPersonaje->getContorno();
}

/*
 * Devuelve el rectangulo que representa al personaje
 */
Rectangulo* Personaje::getRectangulo() {
	return rectanguloPersonaje;
}

/**
 * \brief	Se setea el estado del personaje, mediante 3 taxonomias (incompletas para el juego final).
 * 			E_PERFIL: 			determina el perfil a conciderar.
 * 			E_ACCION:			da informaci�n sobre las acciones que realiza el personaje.
 *
 * \param	\perfil
 * \param	\accion		Se utiliza detallar que tipo de acciones est� realizando el personaje.
 */

void Personaje::setEstado(E_PERFIL perfil, E_ACCION accion){
	estado->perfil = perfil;
	estado->accion = accion;
}

/*
 * \brief	Setea el estado del personaje.
 */
void Personaje::setEstado(Estado estado){
	this->estado->perfil = estado.perfil;
	this->estado->accion = estado.accion;
}

/*
 * \return	Estado del personaje.
 */

Personaje::Estado Personaje::getEstado(){
	return estado;
}


/*
 * Getter y setter para el estado
 */
/*void Personaje::setEstado(std::string unEstado){
	this->estado = unEstado;
}
std::string Personaje::getEstado(){
	return this->estado;
}
*/
Personaje::~Personaje() {
}
