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
b2Vec2* PasarAVertices(std::vector<Pos>* puntos) {
	b2Vec2 vectorDePuntos[puntos->size()];
	for(int i=0; i<puntos->size(); i++) {
		vectorDePuntos[i].Set(puntos->at(i).getX(), puntos->at(i).getY());
	}
	// Seba dijo q los array dsp hay q eliminarlos, no encontre como D:
	return vectorDePuntos;
}

/*
 *	Agarra el punto que devuelve el contorno de un circulo
 *	y la posicion en la que esta y devuelve su radio
 */
float CalcularRadio(ObjetoMapa* circulo) {
	float distX = circulo->getPos()->getX()-circulo->getContorno()->at(0).getX();
	float distY = circulo->getPos()->getY()-circulo->getContorno()->at(0).getY();
	float radio = sqrt(distX*distX+distY*distY);
	return radio;
}

Escenario::Escenario(std::vector<Personaje>* e_personajes, std::vector<ObjetoMapa>* e_objetos) {
	objetos = e_objetos;
	personajes = e_personajes;

	// Se crea el mundo con la gravedad asignada en el .h
	b2Vec2 gravity(gravedadX, gravedadY);
	b2World world(gravity);

	// Se crea el suelo en la posición y con el ancho y el alto que indica el .h
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(posSueloX, posSueloY);
	b2Body* groundBody = world.CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(medioAnchoSuelo, medioAltoSuelo);
	// El segundo parámetro es la densidad
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Crea los personajes (se supone que todos son dinámicos)
	for(int i=0; i<personajes->size(); i++) {
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;

		// Setea posición y angulo
		bodyDef.position.Set(personajes->at(i).getPosicion()->getX(), personajes->at(i).getPosicion()->getY());
		b2Body* body = world.CreateBody(&bodyDef);

		// El personaje es un rectangulo
		b2FixtureDef fixtureDef;
		b2PolygonShape forma;
		forma.SetAsBox(medioAnchoPlayer, medioAltoPlayer);
		fixtureDef.shape = &forma;

		// La da la forma y la masa, determinando la densidad
		body->CreateFixture(&fixtureDef);
		b2MassData* datosDeMasa;
		datosDeMasa->mass = masaDelPersonaje;
		body->SetMassData(datosDeMasa);
	}

	// Crea los objetos (se supone que no todos son estáticos)
	for(int i=0; i<objetos->size(); i++) {
		b2BodyDef bodyDef;

		// Determina si es o no estático
		if (objetos->at(i).esEstatico()) {
			bodyDef.type = b2_dynamicBody;
		}

		// Setea posición y angulo
		bodyDef.position.Set(objetos->at(i).getPos()->getX(), objetos->at(i).getPos()->getY());
		bodyDef.angle = objetos->at(i).getRotacion();
		b2Body* body = world.CreateBody(&bodyDef);

		// Determina la forma
		b2FixtureDef fixtureDef;
		if (true) {
			b2PolygonShape poligono;
			b2Vec2* vertices = PasarAVertices(objetos->at(i).getContorno());
			int cantidadDePuntos = objetos->at(i).getContorno()->size();
			poligono.Set(vertices, cantidadDePuntos);
			fixtureDef.shape = &poligono;
		} else {
			float radio = CalcularRadio(&objetos->at(i));
			b2CircleShape circulo;
			circulo.m_radius = radio;
			fixtureDef.shape = &circulo;
		}

		// La da la forma y la masa, determinando la densidad
		body->CreateFixture(&fixtureDef);
		b2MassData* datosDeMasa;
		datosDeMasa->mass = objetos->at(i).getMasa();
		body->SetMassData(datosDeMasa);
	}

	carla = &world;
}

void Escenario::cambiar(Evento evento) {
}

Escenario::~Escenario(){

}
