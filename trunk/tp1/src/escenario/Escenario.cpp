/* Maneja la relacion entre Box2D y el resto del Juego.
 */

#include <vector>
#include "Escenario.h"
#include "../entrada/Evento.h"
#include "../objetos/Pos.h"
#include "../personajes/Personaje.h"
#include <stdio.h>


/*
 *	Pasa los puntos de un vector de posiciones a uno
 *	de vértices que es la clase que maneja Box2D
 */
b2Vec2* PasarAVertices(ObjetoMapa* objeto) {
	int cantidadDePuntos = objeto->getContorno()->size();

	b2Vec2* vertices = new b2Vec2[cantidadDePuntos];
	std::vector<Pos*>* unVectorDePos = objeto->getContorno();

	for (int j = 0; j < cantidadDePuntos; j++) {
		b2Vec2 * unParOrdenado = new b2Vec2(
				unVectorDePos->at(j)->getX() - (objeto->getPos()->getX()),
				unVectorDePos->at(j)->getY() - (objeto->getPos()->getY()));
		vertices[j] = *unParOrdenado;
	}

	return vertices;
}

/*
 *	Agarra el punto que devuelve el contorno de un circulo
 *	y la posicion en la que esta y devuelve su radio
 */
float CalcularRadio(ObjetoMapa* circulo) {
	float distX = circulo->getPos()->getX()
			- circulo->getContorno()->at(0)->getX();
	float distY = circulo->getPos()->getY()
			- circulo->getContorno()->at(0)->getY();
	float radio = sqrt(distX * distX + distY * distY);
	return radio;
}

/*
 *	Crea las paredes, el techo y el suelo del mundo.
 */
void CrearCaja(b2World* world, Config* config) {
	// Se crea el suelo en la posición y con el ancho y el alto que indica la config
	b2BodyDef sueloDef;
	sueloDef.position.Set((config->getAncho()) / 2,
			MEDIO_ALTO_SUELO - (config->getAlto()));
	b2Body* suelo = world->CreateBody(&sueloDef);
	b2PolygonShape sueloForma;
	sueloForma.SetAsBox((config->getAncho()) / 2, MEDIO_ALTO_SUELO);
	// El segundo parámetro es la densidad
	suelo->CreateFixture(&sueloForma, 0.0f);

	// Se crea el techo en la posición y con el ancho y el alto que indica la config
	b2BodyDef techoDef;
	techoDef.position.Set((config->getAncho()) / 2, -MEDIO_ALTO_TECHO);
	b2Body* techo = world->CreateBody(&techoDef);
	b2PolygonShape techoForma;
	techoForma.SetAsBox((config->getAncho()) / 2, MEDIO_ALTO_TECHO);
	// El segundo parámetro es la densidad
	techo->CreateFixture(&techoForma, 0.0f);

	// Se crean las paredes en la posición y con el ancho y el alto que indica la config
	b2BodyDef paredIzqDef;
	paredIzqDef.position.Set(MEDIO_ANCHO_PARED, -(config->getAlto()) / 2);
	b2Body* paredIzq = world->CreateBody(&paredIzqDef);
	b2PolygonShape paredIzqForma;
	paredIzqForma.SetAsBox(MEDIO_ANCHO_PARED,
			(config->getAlto()) / 2
					- 2 * (MEDIO_ALTO_TECHO + MEDIO_ALTO_SUELO));
	// El segundo parámetro es la densidad
	paredIzq->CreateFixture(&paredIzqForma, 0.0f);
	b2BodyDef paredDerDef;
	paredDerDef.position.Set((config->getAncho()) - MEDIO_ANCHO_PARED,
			-(config->getAlto()) / 2);
	b2Body* paredDer = world->CreateBody(&paredDerDef);
	b2PolygonShape paredDerForma;
	paredDerForma.SetAsBox(MEDIO_ANCHO_PARED,
			(config->getAlto()) / 2
					- 2 * (MEDIO_ALTO_TECHO + MEDIO_ALTO_SUELO));
	// El segundo parámetro es la densidad
	paredDer->CreateFixture(&paredDerForma, 0.0f);
}

/*
 *	Crea los personajes en el mundo.
 */
void CrearPersonajes(b2World* world, std::vector<Personaje*>* personajes) {
	// Crea los personajes (se supone que todos son dinámicos)
	for (unsigned i = 0; i < personajes->size(); i++) {
		b2BodyDef peronajeDef;
		peronajeDef.type = b2_dynamicBody;

		// Setea posición y angulo
		peronajeDef.position.Set(personajes->at(i)->getPosicion()->getX(),
				personajes->at(i)->getPosicion()->getY());
		b2Body* personaje = world->CreateBody(&peronajeDef);

		// El personaje es un rectangulo
		b2FixtureDef caractDef;
		b2PolygonShape forma;
		forma.SetAsBox(personajes->at(i)->getAncho() / 2,
				personajes->at(i)->getAlto() / 2);
		caractDef.shape = &forma;
		caractDef.density = DENSIDAD_DEL_PERSONAJE;
		caractDef.friction = FRICCION_DEL_PERSONAJE;

		// La da la forma y la masa, determinando la densidad y no deja que rote
		personaje->CreateFixture(&caractDef);
		personaje->SetFixedRotation(true);
		// Guarda su referencia al mundo
		personajes->at(i)->setLinkAMundo(personaje);

		//solo funciona para un personaje
		//add foot sensor fixture
		b2PolygonShape sensorForma;

		b2FixtureDef sensorFix;
		sensorForma.SetAsBox(personajes->at(i)->getAncho() / 2, 0.1,
				b2Vec2(0, -(personajes->at(i)->getAlto() / 2)), 0);
		sensorFix.isSensor = true;
		sensorFix.shape = &sensorForma;
		b2Fixture* footSensorFixture = personaje->CreateFixture(&sensorFix);
		footSensorFixture->SetUserData((void*) 3);
	}
}

/*
 *	Crea los objetos en el mundo.
 */
void CrearObjetos(b2World* world, std::vector<ObjetoMapa*>* objetos) {
	// Crea los objetos (se supone que no todos son estáticos)
	for (unsigned i = 0; i < objetos->size(); i++) {
		b2BodyDef objetoDef;

		// Determina si es o no estático
		if (!objetos->at(i)->esEstatico()) {
			objetoDef.type = b2_dynamicBody;
		}
		// Setea posición y angulo
		objetoDef.position.Set(objetos->at(i)->getPos()->getX(),
				objetos->at(i)->getPos()->getY());
		objetoDef.angle = objetos->at(i)->getRotacion();
		//objetoDef.angle = 0;
		b2Body* objeto = world->CreateBody(&objetoDef);

		// Determina la forma y la crea
		b2FixtureDef caract;
		b2PolygonShape poligono;
		b2CircleShape circulo;

		if (!(objetos->at(i)->esCirculo())) {
			b2Vec2* vertices = PasarAVertices(objetos->at(i));

			poligono.Set(vertices, objetos->at(i)->getContorno()->size());
			caract.shape = &poligono;
			delete vertices;
		} else {
			float radio = CalcularRadio(objetos->at(i));
			circulo.m_radius = radio;
			caract.shape = &circulo;
		}

		// Carga las caract si no es estatico
		if (!objetos->at(i)->esEstatico()) {
			caract.density = objetos->at(i)->getDensidad();
			caract.friction = FRICCION_DE_OBJETO;
		}

		// La da la forma y la masa, determinando la densidad
		objeto->CreateFixture(&caract);

		// Guarda su referencia al mundo
		objetos->at(i)->setLinkAMundo(objeto);
	}
}

Escenario::Escenario(Config* config) {
	personajes = config->getPersonajes();
	objetos = config->getObjetos();

	// Se crea el mundo con la gravedad asignada en el .h
	b2Vec2 gravity(GRAVEDAD_X, GRAVEDAD_Y);
	b2World* world = new b2World(gravity);

	CrearCaja(world, config);
	CrearPersonajes(world, personajes);
	CrearObjetos(world, objetos);

	// Se agrega al mundo el listener para los contactos
	cuentaPasos = new MyContactListener;
	world->SetContactListener(cuentaPasos);

	this->mundo = world;
}

/*
 *	Da los impulsos a los personajes segun los eventos.
 */
void DarImpulsos(std::vector<Evento*>* ListaDeEventos,
		std::vector<Personaje*>* personajes, MyContactListener* cuentaPasos) {
	// Evalua si algun evento es un impulso.
	for (unsigned i = 0; i < ListaDeEventos->size(); i++) {
		if (ListaDeEventos->at(i)->getTecla() == TECLA_IZQUIERDA) {
			b2Vec2 impulsoIzquierda(IMPULSO_IZQ_X, IMPULSO_IZQ_Y);
			personajes->at(0)->getLinkAMundo()->ApplyLinearImpulse(
					impulsoIzquierda,
					personajes->at(0)->getLinkAMundo()->GetPosition(), true);
		} else if (ListaDeEventos->at(i)->getTecla() == TECLA_DERECHA) {
			b2Vec2 impulsoDerecha(IMPULSO_DER_X, IMPULSO_DER_Y);
			personajes->at(0)->getLinkAMundo()->ApplyLinearImpulse(
					impulsoDerecha,
					personajes->at(0)->getLinkAMundo()->GetPosition(), true);
		} else if ((ListaDeEventos->at(i)->getTecla() == TECLA_ARRIBA)
				&& (cuentaPasos->numFootContacts > 0)) {
			b2Vec2 impulsoArriba(IMPULSO_ARR_X, IMPULSO_ARR_Y);
			personajes->at(0)->getLinkAMundo()->ApplyLinearImpulse(
					impulsoArriba,
					personajes->at(0)->getLinkAMundo()->GetPosition(), true);
		}
	}
}

/*
 *	Actualize las posiciones de los objetos y personajes.
 */
void UpdatePos(std::vector<Personaje*>* personajes,
		std::vector<ObjetoMapa*>* objetos) {
	//Recorre objetos y personajes seteandole las nuevas posiciones y ángulos
	for (unsigned i = 0; i < personajes->size(); i++) {
		b2Body* personaje = personajes->at(i)->getLinkAMundo();
		// Creo q deberia borrar la pos anterior de alguna forma. No se si alcanza.
		delete personajes->at(i)->getPosicion();

		Pos* posicion = new Pos(personaje->GetPosition().x,personaje->GetPosition().y);
		personajes->at(i)->setPosicion(posicion);

		printf("%4.2f %4.2f %i \n", personaje->GetPosition().x,personaje->GetPosition().y, i);

		// Determina el estado de la imagen
		b2Vec2 velocidad = personaje->GetLinearVelocity();
		if (velocidad.x<0) {
			// si la velocidad en x es negativa, va para la izq.
			if (velocidad.y<0) {
				// si la velocidad en y es negativa esta cayendo.
				personajes->at(i)->setEstado("CayendoIzq");
			} else if (velocidad.y>0) {
				// si la velocidad en y es positiva esta saltando.
				personajes->at(i)->setEstado("SaltandoIzq");
			} else if (velocidad.y==0) {
				// si la velocidad en y es cero esta quieto en y.
				personajes->at(i)->setEstado("CaminandoIzq");
			}
		} else {
			// si la velocidad en x es positiva, va para la der.
			if (velocidad.y<0) {
				// si la velocidad en y es negativa esta cayendo.
				personajes->at(i)->setEstado("CayendoDer");
			} else if (velocidad.y>0) {
				// si la velocidad en y es positiva esta saltando.
				personajes->at(i)->setEstado("SaltandoDer");
			} else if (velocidad.y==0) {
				// si la velocidad en y es cero esta quieto en y.
				personajes->at(i)->setEstado("CaminandoDer");
			}
		}
		if (velocidad.x==0 && velocidad.y==0) {
			// si la velocidad en x y en y es cero esta quieto
			personajes->at(i)->setEstado("Quieto");

		}
	}
	for (unsigned i = 0; i < objetos->size(); i++) {
		b2Body* objeto = objetos->at(i)->getLinkAMundo();
		// Creo q deberia borrar la pos anterior de alguna forma. No se si alcanza.
		delete objetos->at(i)->getPos();

		Pos* posicion = new Pos(objeto->GetPosition().x,
				objeto->GetPosition().y);
		objetos->at(i)->setPos(posicion);
		objetos->at(i)->setRotacion(objeto->GetAngle());
	}
}

void Escenario::cambiar(std::vector<Evento*>* ListaDeEventos) {
	DarImpulsos(ListaDeEventos, personajes, cuentaPasos);

	// Avanza el mundo dos step
	mundo->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
	mundo->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

	UpdatePos(personajes, objetos);
}

Escenario::~Escenario() {
	delete cuentaPasos;
	delete mundo;
}
