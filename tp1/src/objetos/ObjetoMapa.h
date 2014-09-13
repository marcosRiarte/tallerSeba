#ifndef OBJETOMAPA_H_
#define OBJETOMAPA_H_

#include <vector>
#include <map>
#include <string>
#include "Pos.h"
#include "Color.h"

using namespace std;
/**
 * Clase Abrstracta (no se pueden crear instancias de la misma) que sirve de base para
 * 	los demas objetos que hereden de ella. Es una interfaz
 * 	Objetos que heredan: Circulo, Rectángulo, Poligono, Trapecio, Paralelogramo.
 */
class ObjetoMapa {
protected:
	bool estatico;
	Color* color;
	Pos* pos;
	int rot;
	float masa;
	//este atributo es el que va a variar para las distintas clases que hereden de esta.
	map<string, int> desc; //

public:
	void initialice(bool esEstatico, Color color, Pos pos_cm, int rotacion,
			float masa) {
		this->estatico = esEstatico;
		this->color = new Color(color);
		this->pos = new Pos(pos_cm);
		this->rot = rotacion;
		this->masa = masa;
	}
	bool esEstatico() {
		return this->estatico;
	}
	Color* getColor(){
		return new Color(color);
	}
	void setColor(Color *c){
		this->color = c;
	}
	Pos* getPos(){
		return new Pos(pos);
	}
	int getRotacion(){
		return rot;
	}
	float getMasa(){
		return masa;
	}
	virtual vector<Pos> getContorno() = 0; //este método debe redefinirse en las clases que heredan. Devuelve los vertices en caso de no ser un circulo
	virtual ~ObjetoMapa() {
	}
	;
};

#endif /* OBJETOMAPA_H_ */
