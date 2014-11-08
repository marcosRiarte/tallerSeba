#ifndef CONFIG_H_
#define CONFIG_H_
#include <string>
#include <vector>

#include "../elementosJuego/objetos/ObjetoMapa.h"
#include "../elementosJuego/personajes/Personaje.h"
#include "../excepciones/ConfigExcepcion.h"
#include "../redes/Paquetes.h"

class Config {
private:
	std::vector<ObjetoMapa*> objetosMapa;
	std::vector<Personaje*> personajes;
	int altoPx;
	int anchoPx;
	int alto_un;
	int ancho_un;
public:
	Config(std::string nombre) throw (Config_Excepcion);
	std::vector<ObjetoMapa*> getObjetos();
	std::vector<Personaje*> getPersonajes();
	int getAltoPx();
	int getAnchoPx();
	int getAlto();
	int getAncho();

	PaqueteACliente crearPaqueteInicial();

	~Config();
};

#endif /* CONFIG_H_ */
