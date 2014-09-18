#ifndef VALIDADOROBJETOS_H_
#define VALIDADOROBJETOS_H_

#include <string>

class ValidadorObjetos {
public:
	static bool ValidarBasicos(std::string tipo, int x, int y, std::string color, int rotacion, int masa, bool estatico);
	static bool ValidarPoligono(int lados, int escala);
	static bool ValidarRectangulo(int x, int y);
	static bool ValidarCirculo(int diametro);
	static bool ValidarParalelogramo(int alfa);
	static bool ValidarTrapecio(int alfa, int beta);
};

#endif /* VALIDADOROBJETOS_H_ */
