#ifndef OBJETOMAPAVISTA_H_
#define OBJETOMAPAVISTA_H_

#include "Vista.h"
#include "../elementosJuego/objetos/ObjetoMapa.h"

class ObjetoMapaVista : public Vista{
private:
	ObjetoMapa* objeto;
	Pos getPosDerInf(std::vector<Pos> vPos);
	Pos getPosIzqSup(std::vector<Pos> vPos);
public:
	ObjetoMapaVista(SDL_Renderer* r, ObjetoMapa* o);
	Pos* getPosCentro(std::vector<Pos*>* vPos);
	SDL_Texture* getVista();
	const SDL_Rect getVentana();
	virtual ~ObjetoMapaVista();
};

#endif /* OBJETOMAPAVISTA_H_ */
