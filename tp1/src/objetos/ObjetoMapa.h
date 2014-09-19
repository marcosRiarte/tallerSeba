#ifndef OBJETOMAPA_H_
#define OBJETOMAPA_H_

#include <vector>
#include <map>
#include <string>
#include "Pos.h"
#include "Color.h"

/**
 * Clase Abrstracta (no se pueden crear instancias de la misma) que sirve de base para
 * 	los demas objetos que hereden de ella. Es una interfaz
 * 	Objetos que heredan: Circulo, Rectángulo, Poligono, Trapecio, Paralelogramo.
 */
class ObjetoMapa {
protected:
	bool estatico;
	std::string color;
	Pos* pos;
	int rot;
	int masa;
	bool circulo;
	//este atributo es el que va a variar para las distintas clases que hereden de esta.
	std::map<std::string, int> desc; //

public:
	void initialice(bool esEstatico, std::string color, Pos pos_cm, int rotacion, int masa) {
		this->estatico = esEstatico;
		this->color = color;
		this->pos = new Pos(pos_cm);
		this->rot = rotacion;
		this->masa = masa;
	}
	bool esEstatico() {
		return this->estatico;
	}

	bool esCirculo() {
		return this->circulo;
	}

	//implementar
	float getDensidad() {
		return 10;
	}

	std::string getColor(){
		return color;
	}
	void setColor(std::string c){
		this->color = c;
	}
	Pos* getPos(){
		return new Pos(pos);
	}
	int getRotacion(){
		return rot;
	}
	int getMasa(){
		return masa;
	}
	virtual std::vector<Pos>* getContorno() = 0; //este método debe redefinirse en las clases que heredan. Devuelve los vertices en caso de no ser un circulo
	virtual ~ObjetoMapa() {};
};

#endif /* OBJETOMAPA_H_ */
