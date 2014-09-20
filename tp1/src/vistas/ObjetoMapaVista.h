#ifndef OBJETOMAPAVISTA_H_
#define OBJETOMAPAVISTA_H_

#include "Vista.h"
#include "../objetos/ObjetoMapa.h"

class ObjetoMapaVista : public Vista{
private:
	ObjetoMapa* objeto;
	Pos* getPosDerInf(std::vector<Pos*>* vPos);
	Pos* getPosIzqSup(std::vector<Pos*>* vPos);
public:
	ObjetoMapaVista(ObjetoMapa* o);
	SDL_Texture* getVista();
	virtual ~ObjetoMapaVista();
};

#endif /* OBJETOMAPAVISTA_H_ */
