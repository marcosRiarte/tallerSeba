#ifndef VALIDADOROBJETOS_H_
#define VALIDADOROBJETOS_H_
#include <string>

class ValidadorObjetos {
public:
	static void ValidarBasicos(std::string *tipo, int *x, int *y, std::string *color, int *rotacion, int *masa, bool estatico,int ancho_un,int alto_un);
	static void ValidarPersonaje(int *x, int *y, int ancho_un, int alto_un);
	static void ValidarPoligono(int *lados, float *escala);
	static void ValidarCirculo(int *diametro);
	static void ValidarParalelogramo(int *alfa);
	static void ValidarTrapecio(int alfa, int beta);
};

#endif /* VALIDADOROBJETOS_H_ */
