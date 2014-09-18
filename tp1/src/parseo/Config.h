#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <vector>
#include "../objetos/ObjetoMapa.h"
#include "../personajes/Personaje.h"
#include "../vistas/Pantalla.h"
#include "parseo/Parser.h"

using namespace std;

class Config {

private:
	string dirArchivoConfiguracion;
	Pantalla* pantalla;
	vector<Personaje*>* personajes;
	vector<ObjetoMapa*>* objetos;
	Parser * unParser;

public:
	Config(string dirArchivoConfiguracion);
	/**
	 * Se encarga de setear los atributos de la instancia a partir
	 * 	del archivo de configuracion.
	 */
	void reset();
	void crearObjetos();
	Pantalla* getPantalla();
	vector<Personaje*>* getPersonajes();
	vector<ObjetoMapa*>* getObjetos();
	virtual ~Config();
};

#endif /* CONFIG_H_ */
