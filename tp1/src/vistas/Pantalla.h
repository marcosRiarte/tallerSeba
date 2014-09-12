/*
 * Pantalla.h
 *
 *  Created on: 6/9/2014
 *      Author: pablo_000
 */

#ifndef PANTALLA_H_
#define PANTALLA_H_

#include <string>
#include <vector>

using namespace std;

class Pantalla {
private:
	int altoPx;
	int anchoPx;
	int alto;
	int ancho;
	string dirImg;
public:
	Pantalla(int altoPx, int anchoPx, int alto, int ancho, string dirImg);
	string getFondo();
	vector<int> getDimensionesPx();
	vector<int> getDimensiones();
	virtual ~Pantalla();
};

#endif /* PANTALLA_H_ */
