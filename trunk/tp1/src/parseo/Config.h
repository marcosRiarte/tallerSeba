#ifndef CONFIG_H_
#define CONFIG_H_
#include "../objetos/ObjetoMapa.h"
#include <vector>
#include <string>
#include "../personajes/Personaje.h"
#include "../vistas/Pantalla.h"

class Config {
private:
	std::vector<ObjetoMapa*>* objetosMapa;
	std::vector<Personaje*>* personajes;
	Pantalla* pantalla;
public:
	Config(std::string nombre);
	std::vector<ObjetoMapa*>* getObjetos();
	std::vector<Personaje*>* getPersonajes();
	Pantalla* getPantalla();
};

#endif /* CONFIG_H_ */
