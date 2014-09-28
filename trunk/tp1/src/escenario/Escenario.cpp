/* Maneja la relacion entre Box2D y el resto del Juego.
 */

#include <vector>
#include "Escenario.h"
#include "../objetos/Pos.h"
#include <stdio.h>

/*
 *	Pasa los puntos de un vector de posiciones a uno
 *	de vértices que es la clase que maneja Box2D
 */
b2Vec2* PasarAVertices(std::vector<Pos*>* puntos) {
	b2Vec2* vectorDePuntos;
	vectorDePuntos = new b2Vec2[puntos->size()];
	for(unsigned i=0; i<puntos->size(); i++) {
		b2Vec2* v2= new b2Vec2(puntos->at(i)->getX(), puntos->at(i)->getY());
		vectorDePuntos[i] = *v2;
	}
	// Seba dijo q los array dsp hay q eliminarlos, no encontre como D:
	return vectorDePuntos;
}

/*
 *	Agarra el punto que devuelve el contorno de un circulo
 *	y la posicion en la que esta y devuelve su radio
 */
float CalcularRadio(ObjetoMapa* circulo) {
	float distX = circulo->getPos()->getX() - circulo->getContorno()->at(0)->getX();
	float distY = circulo->getPos()->getY() - circulo->getContorno()->at(0)->getY();
	float radio = sqrt(distX*distX+distY*distY);
	return radio;
}

Escenario::Escenario(Config* config) {
	objetos = config->getObjetos();
	personajes = config->getPersonajes();

	// Se crea el mundo con la gravedad asignada en el .h
	b2Vec2 gravity(GRAVEDAD_X, GRAVEDAD_Y);
	b2World world(gravity);

	// Se crea el suelo en la posición y con el ancho y el alto que indica la config
	b2BodyDef sueloDef;
	sueloDef.position.Set((config->getAncho())/2, MEDIO_ALTO_SUELO-(config->getAlto()));
	b2Body* suelo = world.CreateBody(&sueloDef);
	b2PolygonShape sueloForma;
	sueloForma.SetAsBox((config->getAncho())/2, MEDIO_ALTO_SUELO);
	// El segundo parámetro es la densidad
	suelo->CreateFixture(&sueloForma, 0.0f);

	// Se crea el techo en la posición y con el ancho y el alto que indica la config
	b2BodyDef techoDef;
	techoDef.position.Set((config->getAncho())/2, -MEDIO_ALTO_TECHO);
	b2Body* techo = world.CreateBody(&techoDef);
	b2PolygonShape techoForma;
	techoForma.SetAsBox((config->getAncho())/2, MEDIO_ALTO_TECHO);
	// El segundo parámetro es la densidad
	techo->CreateFixture(&techoForma, 0.0f);

	// Se crean las paredes en la posición y con el ancho y el alto que indica la config
	b2BodyDef paredIzqDef;
	paredIzqDef.position.Set(MEDIO_ANCHO_PARED, -(config->getAlto())/2);
	b2Body* paredIzq = world.CreateBody(&paredIzqDef);
	b2PolygonShape paredIzqForma;
	paredIzqForma.SetAsBox(MEDIO_ANCHO_PARED, (config->getAlto())/2-2*(MEDIO_ALTO_TECHO+MEDIO_ALTO_SUELO));
	// El segundo parámetro es la densidad
	paredIzq->CreateFixture(&paredIzqForma, 0.0f);
	b2BodyDef paredDerDef;
	paredDerDef.position.Set(MEDIO_ANCHO_PARED, -(config->getAlto())/2);
	b2Body* paredDer = world.CreateBody(&paredDerDef);
	b2PolygonShape paredDerForma;
	paredDerForma.SetAsBox(MEDIO_ANCHO_PARED, (config->getAlto())/2-2*(MEDIO_ALTO_TECHO+MEDIO_ALTO_SUELO));
	// El segundo parámetro es la densidad
	paredDer->CreateFixture(&paredDerForma, 0.0f);

	// Crea los personajes (se supone que todos son dinámicos)
	for(unsigned i=0; i<personajes->size(); i++) {
		b2BodyDef peronajeDef;
		peronajeDef.type = b2_dynamicBody;

		// Setea posición y angulo
		peronajeDef.position.Set(personajes->at(i)->getPosicion()->getX(), personajes->at(i)->getPosicion()->getY());
		b2Body* personaje = world.CreateBody(&peronajeDef);

		// El personaje es un rectangulo
		b2FixtureDef caractDef;
		b2PolygonShape forma;
		forma.SetAsBox(MEDIO_ANCHO_PERSONAJE, MEDIO_ALTO_PERSONAJE);
		caractDef.shape = &forma;
		caractDef.density = DENSIDAD_DEL_PERSONAJE;
		caractDef.friction = FRICCION_DEL_PERSONAJE;

		// La da la forma y la masa, determinando la densidad
		personaje->CreateFixture(&caractDef);
		// Guarda su referencia al mundo
		personajes->at(i)->setLinkAMundo(personaje);
	}

	// Crea los objetos (se supone que no todos son estáticos)
	for(unsigned i=0; i<objetos->size(); i++) {
		b2BodyDef objetoDef;

		// Determina si es o no estático
		if (objetos->at(i)->esEstatico()) {
			objetoDef.type = b2_dynamicBody;
		}

		// Setea posición y angulo
		objetoDef.position.Set(objetos->at(i)->getPos()->getX(), objetos->at(i)->getPos()->getY());
		objetoDef.angle = objetos->at(i)->getRotacion();
		b2Body* objeto = world.CreateBody(&objetoDef);

		// Determina la forma
		b2FixtureDef caract;
		if (objetos->at(i)->esCirculo()) {
			b2PolygonShape poligono;
			b2Vec2* vertices = PasarAVertices(objetos->at(i)->getContorno());
			int cantidadDePuntos = objetos->at(i)->getContorno()->size();
			poligono.Set(vertices, cantidadDePuntos);
			caract.shape = &poligono;
		} else {
			float radio = CalcularRadio(objetos->at(i));
			b2CircleShape circulo;
			circulo.m_radius = radio;
			caract.shape = &circulo;
		}

		if (objetos->at(i)->esEstatico()) {
			caract.density = objetos->at(i)->getDensidad();
			caract.friction = FRICCION_DE_OBJETO;
		}

		// La da la forma y la masa, determinando la densidad
		objeto->CreateFixture(&caract);
		// Guarda su referencia al mundo
		objetos->at(i)->setLinkAMundo(objeto);
	}
	this->mundo = &world;
}

void Escenario::cambiar(std::vector<Evento*>* ListaDeEventos) {
	// Avanza el mundo un step
	mundo->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

	//Recorre objetos y personajes seteandole las nuevas posiciones y ángulos
	for(unsigned i=0; i<personajes->size(); i++) {
		b2Body* personaje = personajes->at(i)->getLinkAMundo();
		// Creo q deberia borrar la pos anterior de alguna forma. No se si alcanza.
		delete personajes->at(i)->getPosicion();

		Pos* posicion = new Pos(personaje->GetPosition().x,personaje->GetPosition().y);
		personajes->at(i)->setPosicion(posicion);
	}
	for(unsigned i=0; i<objetos->size(); i++) {
		b2Body* objeto = objetos->at(i)->getLinkAMundo();
		// Creo q deberia borrar la pos anterior de alguna forma. No se si alcanza.
		delete objetos->at(i)->getPos();

		Pos* posicion = new Pos(objeto->GetPosition().x,objeto->GetPosition().y);
		objetos->at(i)->setPos(posicion);
		objetos->at(i)->setRotacion(objeto->GetAngle());
	}
}

Escenario::~Escenario(){

}
