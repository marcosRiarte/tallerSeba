#ifndef OBJETOMAPAVISTA_H_
#define OBJETOMAPAVISTA_H_

#include "Vista.h"
#include "../objetos/ObjetoMapa.h"

class ObjetoMapaVista : public Vista{
private:
	ObjetoMapa* objeto;
	Pos* getPosDerInf(std::vector<Pos*>* vPos);
	Pos* getPosIzqSup(std::vector<Pos*>* vPos);
	Pos* getPosCentro(std::vector<Pos*>* vPos);
	SDL_Texture* rotar(SDL_Texture* t, float grados);
public:
	ObjetoMapaVista(SDL_Renderer* r, ObjetoMapa* o);
	SDL_Texture* getVista();
	const SDL_Rect* getVentana();
	virtual ~ObjetoMapaVista();
};

#endif /* OBJETOMAPAVISTA_H_ */
