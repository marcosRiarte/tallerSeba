#ifndef PARSER_H_
#define PARSER_H_
#include <string>
#include "../objetos/ObjetoMapa.h"
#include <vector>
#include <string>
#include "personajes/Personaje.h"

class Parser {
private:
	std::vector<ObjetoMapa*> objetosMapa;
	std::vector<Personaje*> personajes;
public:
	Parser(std::string nombre);
	std::vector<ObjetoMapa*>* getObjetos();
	std::vector<Personaje*>* getPersona();
};

#endif /* PARSER_H_ */
