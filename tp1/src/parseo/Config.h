#ifndef CONFIG_H_
#define CONFIG_H_
#include "../elementosJuego/objetos/ObjetoMapa.h"
#include <vector>
#include <string>
#include "../elementosJuego/personajes/Personaje.h"
#include "../excepciones/ConfigExcepcion.h"

class Config {
private:
	std::vector<ObjetoMapa*> objetosMapa;
	std::vector<Personaje*> personajes;
	int altoPx;
	int anchoPx;
	int alto_un;
	int ancho_un;
	std::string fondo;
public:
	void liberarObjetos(std::vector<ObjetoMapa*>* a);
	void liberarPjs(std::vector<Personaje*> & a);
	Config(std::string nombre) throw (Config_Excepcion);
	std::vector<ObjetoMapa*> getObjetos();
	std::vector<Personaje*> getPersonajes();
	void setPersonajes();
	int getAltoPx();
	int getAnchoPx();
	int getAlto();
	int getAncho();
	std::string getFondo();
	~Config();
};

#endif /* CONFIG_H_ */
