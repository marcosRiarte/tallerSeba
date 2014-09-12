#ifndef CREADOROBJETOS_H_
#define CREADOROBJETOS_H_
#include <string>

class CreadorObjetos {
public:
	static void CrearRectangulo(int x, int y, int ancho, int alto,int rotacion,std::string color,int masa,bool estatico);
	static void CrearPoligono(int x, int y, int lados, int escala, int rotacion,std::string color,int masa,bool estatico);
	static void CrearCirculo(int x, int y, int diametro,int rotacion,std::string color,int masa,bool estatico);
	static void CrearParalelogramo(int x, int y, int base, int ladoaltura, int alfa,int rotacion,std::string color,int masa,bool estatico);
	static void CrearTrapecio(int x, int y, int base, int altura, int alfa, int beta,int rotacion,std::string color,int masa,bool estatico);

	virtual ~CreadorObjetos();
};

#endif /* CREADOROBJETOS_H_ */
