/* Maneja la relacion entre Box2D y el resto del Juego.
 */

#include "Escenario.h"
#include "../elementosJuego/Pos.h"
#include "../elementosJuego/personajes/Personaje.h"
#include "../elementosJuego/objetos/ObjetoMapa.h"
#include "../elementosJuego/ElementosJuego.h"
#include "../src/Constantes.h"
#include <vector>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <Box2D/Box2D.h>
#include <Math.h>

/// Devuelve el AABB para todas las figuras de un cuerpo dado.
b2AABB GetBodyAABB( const b2Body* body )
{
   b2AABB result;
   b2Transform trans = body->GetTransform();
   const b2Fixture* first = body->GetFixtureList();

   for( const b2Fixture* fixture = first; fixture; fixture = fixture->GetNext() )
   {
      b2AABB aabb;
      fixture->GetShape()->ComputeAABB( &aabb, trans, 0 );
      if( fixture == first )
         result = aabb;
      else
         result.Combine( aabb );
   }

   return result;
}

/// Llamada para chequear si el cuerpo se superpone con otro.
struct CheckOverlapCallback : b2QueryCallback
{
   CheckOverlapCallback( const b2Body* body ) :
      m_body( body ), m_isOverlap( false ) {}

   // override
   bool ReportFixture( b2Fixture* fixture ) {
      // Skip self.
      if( fixture->GetBody() == m_body )
         return true;

      for( const b2Fixture* bodyFixture = m_body->GetFixtureList(); bodyFixture;
          bodyFixture = bodyFixture->GetNext() )
      {
         if( b2TestOverlap( fixture->GetShape(), 0, bodyFixture->GetShape(), 0,
            fixture->GetBody()->GetTransform(), m_body->GetTransform() ) ) {
            m_isOverlap = true;
            return false;
         }
      }
      return false;
   }

   const b2Body* m_body;
   bool m_isOverlap;
};

/// Devuelve true si el cuerpo se solapa con otro cuerpo en el mundo.
bool IsOverlap( const b2World* world, const b2Body* body )
{
   CheckOverlapCallback callback( body );
   world->QueryAABB( &callback, GetBodyAABB( body ) );
   return callback.m_isOverlap;
}

/*
 *	Pasa los puntos de un vector de posiciones a uno de vértices que es
 *	 la clase que maneja Box2D y les resta el centro de masa
 */
b2Vec2* PasarAVertices(ElementosJuego* elemento) {
	std::vector<Pos> unVectorDePos = elemento->getContorno();
	int cantidadDePuntos = unVectorDePos.size();

	b2Vec2* vertices = new b2Vec2[cantidadDePuntos];

	for (int j = 0; j < cantidadDePuntos; j++) {
		b2Vec2 unParOrdenado = b2Vec2(unVectorDePos.at(j).getX(), unVectorDePos.at(j).getY());
		vertices[j] = unParOrdenado;
	}

	return vertices;
}

/*
 *	Agarra el punto que devuelve el contorno de un circulo
 *	y la posicion en la que esta y devuelve su radio
 */
float CalcularRadio(ElementosJuego* circulo) {
	return circulo->getContorno().at(0).getNorma();
}

/*
 *	Convierte un angulo de radianes a grados y lo normaliza
 */
float radianesAGrados(float anguloRad) {
	float anguloGrad = (anguloRad/M_PI)*180.0;
	while (anguloGrad <= 0) {
		anguloGrad += 360;
	}
	while (anguloGrad > 360) {
		anguloGrad -= 360;
	}
	return anguloGrad;
}

/*
 *	Normaliza un angulo en grados y lo convierte a radianes
 */
float gradosARadianes(float anguloGrad) {
	return (anguloGrad/180.0)*M_PI;
}

/*
 *	Crea un elemento estatico en (posx,posy) con las dimensiones determinadas
 */
void CrearCaja(b2World* mundo, float posX, float posY, float ancho, float alto) {
	b2BodyDef elementoDef;
	elementoDef.position.Set(posX,posY);
	b2Body* elemento = mundo->CreateBody(&elementoDef);
	b2PolygonShape elementoForma;
	elementoForma.SetAsBox(ancho/2, alto/2);
	elemento->CreateFixture(&elementoForma, DENSIDAD_CERO);
}

/*
 *	Crea las paredes, el techo y el suelo del mundo.
 */
void CrearCaja(b2World* mundo, Config* config) {
	float anchoMundo = config->getAncho();
	float altoMundo = config->getAlto();
	float centroMundoX = config->getAncho()/2;
	float centroMundoY = config->getAlto()/2;

	// Se crea el suelo
	CrearCaja(mundo, centroMundoX, -altoMundo-GROSOR_BORDE_MUNDO/2, anchoMundo, GROSOR_BORDE_MUNDO);
	// Se crea el techo
	CrearCaja(mundo, centroMundoX, GROSOR_BORDE_MUNDO/2, anchoMundo, GROSOR_BORDE_MUNDO);
	// Se crea el pared derecha
	CrearCaja(mundo, anchoMundo+GROSOR_BORDE_MUNDO/2, -centroMundoY, GROSOR_BORDE_MUNDO, altoMundo);
	// Se crea el pared izquierda
	CrearCaja(mundo, -GROSOR_BORDE_MUNDO/2, -centroMundoY, GROSOR_BORDE_MUNDO, altoMundo);
}

/*
 *	Crea los elementos en el mundo.
 */
void CrearElementos(b2World* mundo, std::vector<ElementosJuego*>* elementos, bool ponerSensorYFijarRotacion) {
	// Crea los objetos (se supone que no todos son estáticos)
	for (unsigned i = 0; i < elementos->size(); i++) {
		b2BodyDef elementoDef;
		// Determina si es o no estático
		if (!elementos->at(i)->esEstatico()) {
			elementoDef.type = b2_dynamicBody;
		}

		// Setea posición y angulo
		elementoDef.position.Set(elementos->at(i)->getPos().getX(), elementos->at(i)->getPos().getY());
		elementoDef.angle = gradosARadianes(elementos->at(i)->getRotacion());
		b2Body* elemento = mundo->CreateBody(&elementoDef);

		// Determina la forma y la crea
		b2FixtureDef caract;
		b2PolygonShape poligono;
		b2CircleShape circulo;

		if(!(elementos->at(i)->esCirculo())) {
			b2Vec2* vertices = PasarAVertices(elementos->at(i));
			poligono.Set(vertices, elementos->at(i)->getContorno().size());
			caract.shape = &poligono;
			delete vertices;
		} else {
			float radio = CalcularRadio(elementos->at(i));
			circulo.m_radius = radio;
			caract.shape = &circulo;
		}

		// Carga las caract si no es estatico
		if (!elementos->at(i)->esEstatico()) {
			caract.density = elementos->at(i)->getDensidad();
			caract.friction = elementos->at(i)->getFriccion();
		}

		// Crea el fixture del elemento
		elemento->CreateFixture(&caract);

		if (IsOverlap(mundo, elemento)) {
			// Si se superpone con algo que estaba lo borra del mundo
			loguer->loguear("Se superpone", Log::LOG_TIPO::LOG_ERR);
			elementos->erase(elementos->begin() + i);
			i--;
			mundo->DestroyBody(elemento);
		} else {
			// Guarda su referencia al mundo
			elementos->at(i)->setLinkAMundo(elemento);

			if (ponerSensorYFijarRotacion) {
				// No deja que el elemento rote
				elemento->SetFixedRotation(true);

				//solo funciona para un personaje
				//add foot sensor fixture
				b2PolygonShape sensorForma;

				b2FixtureDef sensorFix;
				sensorForma.SetAsBox(ANCHO_PERSONAJE_UN/2-3, 0.1, b2Vec2(0,-ALTO_PERSONAJE_UN/2), 0);
				sensorFix.isSensor = true;
				sensorFix.shape = &sensorForma;
				b2Fixture* footSensorFixture = elemento->CreateFixture(&sensorFix);
				footSensorFixture->SetUserData((void*) 3);
			}
		}
	}
}


/*
 * Crea el escenario a partir de una configuracion que contiene la lista de objetos
 * y personajes a crear, y los parametros de tamaño del mundo.
 */
Escenario::Escenario(Config* config) {
	personajes = config->getPersonajes();
	objetos = config->getObjetos();

	// Se crea el mundo con la gravedad asignada en el .h
	b2Vec2 gravity(GRAVEDAD_X, GRAVEDAD_Y);
	b2World* world = new b2World(gravity);

	// Crea la caja donde se van a desarrollar los eventos
	CrearCaja(world, config);

	// Crea personajes y objetos
	CrearElementos(world, (std::vector<ElementosJuego*>*)&personajes, true);
	CrearElementos(world, (std::vector<ElementosJuego*>*)&objetos, false);

	// Se agrega al mundo el listener para los contactos de los personajes
	cuentaPasos = new MyContactListener;
	world->SetContactListener(cuentaPasos);

	this->mundo = world;
}

/*
 *	Da los impulsos a los personajes segun los eventos.
 */
void DarImpulsos(std::vector<Evento>* ListaDeEventos, std::vector<Personaje*> personajes, MyContactListener* cuentaPasos) {
	// Evalua si algun evento es un impulso.
	for (unsigned i = 0; i < ListaDeEventos->size(); i++) {
		b2Vec2 pos = personajes.at(0)->getLinkAMundo()->GetPosition();
		if (ListaDeEventos->at(i).getTecla() == TECLA_IZQUIERDA) {
			b2Vec2 impulsoIzquierda(IMPULSO_IZQ_X, IMPULSO_IZQ_Y);
			personajes.at(0)->getLinkAMundo()->ApplyLinearImpulse(impulsoIzquierda,pos, true);
		} else if (ListaDeEventos->at(i).getTecla() == TECLA_DERECHA) {
			b2Vec2 impulsoDerecha(IMPULSO_DER_X, IMPULSO_DER_Y);
			personajes.at(0)->getLinkAMundo()->ApplyLinearImpulse(impulsoDerecha,pos, true);
		} else if ((ListaDeEventos->at(i).getTecla() == TECLA_ARRIBA) && (cuentaPasos->numFootContacts > 0)) {
			b2Vec2 impulsoArriba(IMPULSO_ARR_X, IMPULSO_ARR_Y);
			personajes.at(0)->getLinkAMundo()->ApplyLinearImpulse(impulsoArriba,pos, true);
		}
	}
}

/*
 *	Actualiza las posiciones de los objetos y personajes.
 */
void ActualizarPos(std::vector<ElementosJuego*>* elementos) {
	for (unsigned j = 0; j < elementos->size(); j++) {
			b2Body* objeto = elementos->at(j)->getLinkAMundo();

			Pos posicion = Pos(objeto->GetPosition().x,objeto->GetPosition().y);
			elementos->at(j)->setPos(posicion);
			elementos->at(j)->setRotacion(radianesAGrados(objeto->GetAngle()));
	}
}

/*
 *	Actualiza los estados de los personajes
 */
void ActualizarEstado(std::vector<Personaje*> personajes, MyContactListener* cuentaPasos) {
	//Recorre los personajes seteandole los nuevos estados
	for (unsigned i = 0; i < personajes.size(); i++) {
		b2Body* personaje = personajes.at(i)->getLinkAMundo();

		// A partir de la velocidad determina el estado
		b2Vec2 velocidad = personaje->GetLinearVelocity();
		Personaje::E_ACCION accion;
		Personaje::E_PERFIL perfil;
		if (velocidad.y < 0) {
			// Si la velocidad en y es negativa esta cayendo
			accion = Personaje::E_ACCION::CAYENDO;
		} else if (velocidad.y > 0) {
			// Si la velocidad en y es positiva esta saltando
			accion = Personaje::E_ACCION::SALTANDO;
		} else if (velocidad.x != 0) {
			// Si la velocidad en y es cero, pero tiene velocidad en x esta desplazandose
			accion = Personaje::E_ACCION::DESPLAZANDO;
		} else {
			// Si la velocidad en x tambien es cero esta quieto
			accion = Personaje::E_ACCION::QUIETO;
		}
		if (velocidad.x < 0) {
			// Si la velocidad en x es negativa, va para la izquierda
			perfil = Personaje::E_PERFIL::IZQUIERDA;
		} else if (velocidad.x > 0) {
			// Si la velocidad en x es positiva, va para la derecha
			perfil = Personaje::E_PERFIL::DERECHA;
		} else {
			// Si no tiene velocidad en x su perfil continua como estaba
			perfil = personajes.at(i)->getEstado().perfil;
		}
		personajes.at(i)->setEstado(perfil, accion);
	}
}

/*
 * Toma los eventos de entrada, aplica los cambios al mundo y pone a los personajes
 *  en sus nuevas posiciones
 */
void Escenario::cambiar(std::vector<Evento>* ListaDeEventos) {
	// Determino impulsos para los personajes segun los eventos
	DarImpulsos(ListaDeEventos, personajes, cuentaPasos);

	// Avanza el mundo dos step
	mundo->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
	mundo->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

	// Guarda las nuevas posiciones de los personajes y objetos
	ActualizarPos((std::vector<ElementosJuego*>*) &objetos);
	ActualizarPos((std::vector<ElementosJuego*>*) &personajes);

	// Actualiza el estado de los personajes
	ActualizarEstado(personajes,cuentaPasos);
}

Escenario::~Escenario() {
	delete cuentaPasos;
	delete mundo;
}
