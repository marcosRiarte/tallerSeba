#ifndef VALIDADOROBJETOS_H_
#define VALIDADOROBJETOS_H_

class ValidadorObjetos {
public:
	ValidarBasicos(int x, int y,std::string color);
	ValidarPoligono(int lados, int escala, int rotacion,int masa,bool estatico);
	ValidarRectangulo();
	ValidarCirculo();
	ValidarParalelogramo();
	ValidarTrapecio();
	virtual ~ValidadorObjetos();
};

#endif /* VALIDADOROBJETOS_H_ */
