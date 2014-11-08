#ifndef OBJETOMAPAVISTA_H_
#define OBJETOMAPAVISTA_H_

#include "Vista.h"
#include "../elementosJuego/objetos/ObjetoMapa.h"

class ObjetoMapaVista : public Vista{
private:
	ObjetoMapa objeto;
	Pos getPosDerInf(std::vector<Pos> vPos);
	Pos getPosIzqSup(std::vector<Pos> vPos);
	void setID();
public:
	ObjetoMapaVista(SDL_Renderer* r, ObjetoMapa o);
	SDL_Texture* getVista();
	SDL_Rect getVentana();
	Pos getPos();
	void setPos(Pos posicion);
	void setRotacion(int rotacion);
	virtual ~ObjetoMapaVista();
};

#endif /* OBJETOMAPAVISTA_H_ */
