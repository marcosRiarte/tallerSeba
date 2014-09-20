#ifndef PARSER_H_
#define PARSER_H_
#include "../objetos/ObjetoMapa.h"
#include <vector>
#include <string>
#include "../personajes/Personaje.h"
#include "../vistas/Pantalla.h"

class Parser {
private:
	std::vector<ObjetoMapa*> objetosMapa;
	std::vector<Personaje*> personajes;
	Pantalla* pantalla;
public:
	Parser(std::string nombre);
	std::vector<ObjetoMapa*>* getObjetos();
	std::vector<Personaje*>* getPersona();
	Pantalla* getPantalla();
};

#endif /* PARSER_H_ */
