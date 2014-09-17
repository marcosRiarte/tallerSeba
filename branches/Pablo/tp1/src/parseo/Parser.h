#ifndef PARSER_H_
#define PARSER_H_
#include <string>
#include "../objetos/ObjetoMapa.h"
#include <vector>
#include <string>

class Parser {
private:
	std::vector<ObjetoMapa*> objetos;
public:
	Parser(std::string nombre);
	std::vector<ObjetoMapa*> getObjetos();
};

#endif /* PARSER_H_ */
