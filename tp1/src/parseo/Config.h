#ifndef CONFIG_H_
#define CONFIG_H_
#include "../objetos/ObjetoMapa.h"
#include <vector>
#include <string>
#include "../personajes/Personaje.h"

class Config {
private:
	std::vector<ObjetoMapa*>* objetosMapa;
	std::vector<Personaje*>* personajes;
	int altoPx;
	int anchoPx;
	int alto_un;
	int ancho_un;
	std::string fondo;
public:
	Config(std::string nombre);
	std::vector<ObjetoMapa*>* getObjetos();
	std::vector<Personaje*>* getPersonajes();
	int getAltoPx();
	int getAnchoPx();
	int getAlto();
	int getAncho();
	std::string getFondo();
};

#endif /* CONFIG_H_ */
