#ifndef OBJETOMAPAVISTA_H_
#define OBJETOMAPAVISTA_H_

#include "Vista.h"
#include "../objetos/ObjetoMapa.h"

class ObjetoMapaVista : public Vista{
private:
	ObjetoMapa* objeto;
	SDL_Texture* textura;
	SDL_Rect* ventana;
	Pos* getPosDerInf(std::vector<Pos*>* vPos);
	Pos* getPosIzqSup(std::vector<Pos*>* vPos);
public:
	ObjetoMapaVista(SDL_Renderer* r, ObjetoMapa* o);
	SDL_Texture* getVista();
	SDL_Rect* getVentana();
	virtual ~ObjetoMapaVista();
};

#endif /* OBJETOMAPAVISTA_H_ */
