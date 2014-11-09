#ifndef OBJETOMAPA_H_
#define OBJETOMAPA_H_

#include "../ElementosJuego.h"
#include <string>
#include <vector>

class ObjetoMapa: public ElementosJuego {
protected:
	float rot;
	bool estatico;
	bool circulo;
	long color;
	std::vector<Pos> vertices = std::vector<Pos>();

public:
	ObjetoMapa();
	/*
	 * Inicializa un objeto
	 */
	ObjetoMapa (bool esEstatico, long color, Pos pos_cm, int rotacion, std::vector<Pos> contorno);

	/*
	 * Devuelve verdadero si el objeto no se puede mover
	 */
	bool esEstatico();

	/*
	 * Devuelve verdadero si el objeto es un circulo
	 */
	 bool esCirculo();

	/*
	 * Getter y setter para el color del objeto
	 */
	long getColor();
	void setColor(std::string c);

	/*
	 * Getter y setter para el angulo de rotacion
	 */
	float getRotacion();
	void setRotacion(float rotacion);

	/*
	 * Devuelve los puntos del contorno del elemento
	 */
	std::vector<Pos> getContorno();

	virtual ~ObjetoMapa();
};

#endif /* OBJETOMAPA_H_ */
