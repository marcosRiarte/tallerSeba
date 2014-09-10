#ifndef CREADOROBJETOS_H_
#define CREADOROBJETOS_H_
#include <string>

class CreadorObjetos {
public:
	static void Crear(std::string tipo, int x, int y, int ancho, int alto, int escala, int rotacion,std::string color,int masa,bool estatico,int lados);
	virtual ~CreadorObjetos();
};

#endif /* CREADOROBJETOS_H_ */
