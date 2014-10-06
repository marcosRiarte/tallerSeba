/* Maneja la relacion entre Box2D y el resto del Juego.
 */

#include <vector>
#include "Escenario.h"
#include "../entrada/Evento.h"
#include "../objetos/Pos.h"
#include "../personajes/Personaje.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <Math.h>
#define RADIANES_A_GRADOS(_ANGULO_)((_ANGULO_)/M_PI*180.0)



/// Gets the combined AABB of all shapes of the given body.
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

/// Callback to check for overlap of given body.
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

/// Returns true if the given body overlaps any other body in the world.
bool IsOverlap( const b2World* world, const b2Body* body )
{
   CheckOverlapCallback callback( body );
   world->QueryAABB( &callback, GetBodyAABB( body ) );
   return callback.m_isOverlap;
}


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

//Convierte y normaliza el ángulo
float radAGrados(float angulo){
	float unAngulo = RADIANES_A_GRADOS(angulo);
while (unAngulo<=0){ unAngulo += 360;}
while (unAngulo>360){unAngulo -= 360;}
return unAngulo;
}

/*
 *	Crea las paredes, el techo y el suelo del mundo.
 */
void CrearCaja(b2World* world, Config* config) {
	// Se crea el suelo en la posición y con el ancho y el alto que indica la config
	b2BodyDef sueloDef;
	sueloDef.position.Set((config->getAncho()) / 2,
			-MEDIO_ALTO_SUELO - (config->getAlto()));
	b2Body* suelo = world->CreateBody(&sueloDef);
	b2PolygonShape sueloForma;
	sueloForma.SetAsBox((config->getAncho()) / 2, MEDIO_ALTO_SUELO);
	// El segundo parámetro es la densidad
	suelo->CreateFixture(&sueloForma, 0.0f);

	// Se crea el techo en la posición y con el ancho y el alto que indica la config
	b2BodyDef techoDef;
	techoDef.position.Set((config->getAncho()) / 2, MEDIO_ALTO_TECHO);
	b2Body* techo = world->CreateBody(&techoDef);
	b2PolygonShape techoForma;
	techoForma.SetAsBox((config->getAncho()) / 2, MEDIO_ALTO_TECHO);
	// El segundo parámetro es la densidad
	techo->CreateFixture(&techoForma, 0.0f);

	// Se crean las paredes en la posición y con el ancho y el alto que indica la config
	b2BodyDef paredIzqDef;
	paredIzqDef.position.Set(-MEDIO_ANCHO_PARED, -(config->getAlto()) / 2);
	b2Body* paredIzq = world->CreateBody(&paredIzqDef);
	b2PolygonShape paredIzqForma;
	paredIzqForma.SetAsBox(MEDIO_ANCHO_PARED,
			(config->getAlto()) / 2
					- 2 * (MEDIO_ALTO_TECHO + MEDIO_ALTO_SUELO));
	// El segundo parámetro es la densidad
	paredIzq->CreateFixture(&paredIzqForma, 0.0f);
	b2BodyDef paredDerDef;
	paredDerDef.position.Set((config->getAncho()) + MEDIO_ANCHO_PARED,
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
		//objetoDef.angle = b2_pi;
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

		if (!IsOverlap(world, objeto)){
		// Guarda su referencia al mundo
		objetos->at(i)->setLinkAMundo(objeto);
		}
		else{
			objetos->erase(objetos->begin()+i);
			i--;
			world->DestroyBody(objeto);
	}
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
		std::string estadoAnterior = personajes->at(i)->getEstado();

		// Determina el estado de la imagen
		b2Vec2 velocidad = personaje->GetLinearVelocity();
		std::string estado= "QuietoDer";
		if (velocidad.x<0) {
			// si la velocidad en x es negativa, va para la izq.
			if (velocidad.y<0) {
				// si la velocidad en y es negativa esta cayendo.
				estado = "CayendoIzq";
			} else if (velocidad.y>0) {
				// si la velocidad en y es positiva esta saltando.
				estado = "SaltandoIzq";
			} else if (velocidad.y==0) {
				// si la velocidad en y es cero esta quieto en y.
				estado = "CaminandoIzq";
			}
		} else {
			// si la velocidad en x es positiva, va para la der.
			if (velocidad.y<0) {
				// si la velocidad en y es negativa esta cayendo.
				estado = "CayendoDer";
			} else if (velocidad.y>0) {
				// si la velocidad en y es positiva esta saltando.
				estado = "SaltandoDer";
			} else if (velocidad.y==0) {
				// si la velocidad en y es cero esta quieto en y.
				estado = "CaminandoDer";
			}
		}
		if (velocidad.x==0 && velocidad.y==0) {
			// si la velocidad en x y en y es cero esta quieto
			if (estadoAnterior == "CayendoDer"||estadoAnterior == "SaltandoDer"||estadoAnterior == "CaminandoDer"||estadoAnterior == "QuietoDer") {
				estado = "QuietoDer";
			} else {
				estado = "QuietoIzq";
			}
		}
		personajes->at(i)->setEstado(estado);
	}

	for (unsigned j = 0; j < objetos->size(); j++) {
		b2Body* objeto = objetos->at(j)->getLinkAMundo();
		// Creo q deberia borrar la pos anterior de alguna forma. No se si alcanza.
		delete objetos->at(j)->getPos();

		Pos* posicion = new Pos(objeto->GetPosition().x,objeto->GetPosition().y);
		objetos->at(j)->setPos(posicion);
		objetos->at(j)->setRotacion(radAGrados(objeto->GetAngle()));

	}
}

void Escenario::cambiar(std::vector<Evento*>* ListaDeEventos) {
	DarImpulsos(ListaDeEventos, personajes, cuentaPasos);

	// Avanza el mundo cuatro step
	mundo->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
	mundo->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
	mundo->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
	mundo->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
	UpdatePos(personajes, objetos);
}

Escenario::~Escenario() {
	delete cuentaPasos;
	delete mundo;
}
