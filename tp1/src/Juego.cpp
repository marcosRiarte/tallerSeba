#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h>
#include "Constantes.h"
#include "parseo/Config.h"
#include "objetos/ObjetoMapa.h"
#include "vistas/PersonajeVista.h"
#include <entrada/Evento.h>

void ayuda() {
	std::cout << "Ayuda: \n";
	std::cout << "\t Para ejecutar SnowBross ingresar dirección del archivo de configuración. \n";
	std::cout << "Ejemplo: \n";
	std::cout << "\t > SnowBross 'c:\\configuracion.json' \n";
}

/**
 * Se inicia el juego. Durante el juego siempre se estará dentro de este loop.
 * @return 0 si el juego terminó.
 * @return 1 si el juego debe resetearse.
 */
int gameloop(Pantalla* p, std::vector<ObjetoMapa*>* o) {
	bool fin = false;
	SDL_Event event;
	int i = 0;
	SDL_Delay(100);
	while (!fin) {
		SDL_PollEvent(&event);

		 //double start = getCurrentTime();
		 //processInput(event); 						//Se Obtienen los input del teclado
		 //update();							//Se realizan las modificaciones en los objetos
		i++;
		Pos* pos = o->at(0)->getPos();
		pos = new Pos(pos->getX()+1, pos->getY()+1);
		o->at(0)->setPos(pos);
		p->update();								//Se procesan las imágenes
		//sleep(start + MS_PER_FRAME - getCurrentTime());

		if (i==1000 || event.type == SDL_QUIT)
		fin = true;
	}
	return FIN_DEL_JUEGO;
}

void processInput(SDL_Event event){
	SDL_Keycode teclaT=event.key.keysym.sym;

	                                if(teclaT==SDLK_UP){
	                                       std::cout<<"tecla arriba";
	                                Evento *arriba = new Evento(3);
	                                }
	                                else if (teclaT==SDLK_RIGHT){
	                                        std::cout<< "tecla derecha";
	                                Evento* derecha = new Evento(2);
	                                }
	                                else if(teclaT==SDLK_LEFT){
	                                        std::cout<<"tecla izquierda";
	                                Evento* izquierda = new Evento(1);
	                                }
	                                else if(teclaT==SDLK_DOWN){
	                                        std::cout<<"tecla abajo";
	                                Evento* abajo = new Evento(4);
	                                }
	                                else if(teclaT==SDLK_r){
	                                        std::cout<<"tecla R";
	                                Evento* erre = new Evento(5);
	                                }
	                                else if (teclaT==SDLK_ESCAPE) {
	                                        std::cout<<"sale programa";
	                                }



	                        //Evento eventoT= new Evento(teclaT);
	                        //eventoT.procesarTecla();
}
/**
 * Se encarga de liberar la memoria que ya no se va a usar
 */
void finalizar() {
	SDL_Quit();
}



/**
 * @return devuele 0 (si resultado Ok) y distinto de 0 si hubo error.
 */
int main(int argc, char* argv[]) {
	char msg[1000]; // Se usa para crear mensajes en el log
	//Pequeña validacion de los argumentos pasados.
	if (argc != 2) {
		ayuda();
		return RES_AYUDA;
	}
	loguer->loguear("INICIO DE LA APLICACION", Log::LOG_DEB);
	std::string dirArchivoConfiguracion = argv[1];

	//Parseo y creacion de objetos
	loguer->loguear("Se parsea y se procede a crear los objetos y personajes.", Log::LOG_DEB);
	Config* config = new Config(dirArchivoConfiguracion);
	loguer->loguear("Se terminan de crear los objetos y personajes.", Log::LOG_DEB);

	bool fin = false;
	while (!fin) {

		//Se obtienen los objetos
		std::vector<ObjetoMapa*> *objetos = config->getObjetos();
		snprintf(msg, 1000, "Se crearon: %d objetos", objetos->size());
		loguer->loguear(msg, Log::LOG_DEB);

/*	@Test Permite imprimir las posiciones que integran el contorno de un objeto

		for (unsigned i = 0; i < objetos->size(); i++) {
			std::vector<Pos*>* const contorno = objetos->at(i)->getContorno();
			int cantidad = contorno->size();
			snprintf(msg, 1000, "Contorno del primer objeto (%d vertices):",
					cantidad);
			loguer->loguear(msg, Log::LOG_DEB);
			for (unsigned i = 0; i < contorno->size(); i++) {
				Pos* p = contorno->at(i);
				int x = p->getX();
				int y = p->getY();
				std::sprintf(msg, "Pos%d:(%d,%d)", i, x, y);
				loguer->loguear(msg, Log::LOG_DEB);
			}
		}
 */

		//Se obtienen los personajes
		std::vector<Personaje*> *personajes = config->getPersonajes();
		snprintf(msg, 1000, "Se crearon: %d personajes", personajes->size());
		loguer->loguear(msg, Log::LOG_DEB);

		//Se crea el escenario Box2D con los objetos y personajes

/*
 * TODO Falta crear la clase vista de los personajes, así que por ahora solo comentarios

  		for(unsigned int i = 0; i+1 < personajes->size(); i++){
			Vista* v = new PersonajeVista(personajes->at(i));
			vistas->push_back(v);
		}
*/
		//Se obtiene la pantalla
		Pantalla *pantalla = config->getPantalla();

		//Se inicia SDL creando la ventana dela aplicación
		try{
			pantalla->inicializar();

		}catch(SDL_Excepcion *e){
			finalizar();
			loguer->loguear(e->what(), Log::LOG_ERR);
			return RES_ERR;
		}

		//Se crean las vistas de los objetos y se agregan a la pantalla
		for (unsigned int i = 0; i < objetos->size(); i++) {
			Vista* v = new ObjetoMapaVista(pantalla->getRenderer(), objetos->at(i));
			pantalla->agregarVista(v);
		}

		//Se crean las vistas de los personajes y se agregan a la pantalla

/*
 * TODO Hay que hacer personajes desde cero, por ende esto no está hecho
		 for (unsigned int i = 0; i < personajes->size(); i++) {
			Vista* v = new PersonajeVista(objetos->at(i));
			pantalla->agregarVista(v);
		}
*/
		//Se inicia el juego
		if (gameloop(pantalla, objetos) == FIN_DEL_JUEGO)
			fin = true;
		//Se debe liberar lo que ya no se usa
		finalizar();

	}
	return RES_OK;
}
