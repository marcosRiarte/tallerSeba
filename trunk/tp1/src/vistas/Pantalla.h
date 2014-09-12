/* Contiene las características de la configuración de la pantalla
 */

#ifndef PANTALLA_H_
#define PANTALLA_H_

#include <string>
#include <vector>

using namespace std;

class Pantalla {
private:
	int altoPx;		// Alto en pixeles
	int anchoPx;	// Ancho en pixeles
	int alto;		// Alto para escalar las dimensiones
	int ancho;		// Ancho para escalar las dimensiones
	string dirImg;	// Dirección de la imagen de fondo
public:
	Pantalla(int altoPx, int anchoPx, int alto, int ancho, string dirImg);

	// Devuelve la dirección donde se encuentra la imagen de fondo
	string getFondo();

	// Devuelve un vector que contiene [altoPx,anchoPx]
	vector<int> getDimensionesPx();

	// Devuelve un vector que contiene [alto,ancho]
	vector<int> getDimensiones();
	virtual ~Pantalla();
};

#endif /* PANTALLA_H_ */
