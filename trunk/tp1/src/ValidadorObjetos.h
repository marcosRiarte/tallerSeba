#ifndef VALIDADOROBJETOS_H_
#define VALIDADOROBJETOS_H_

class ValidadorObjetos {
public:
	static bool ValidarBasicos(int x, int y, std::string color, int rotacion, int masa, bool estatico);
	static bool ValidarPoligono(int lados, int escala);
	static bool ValidarRectangulo(int ancho, int alto);
	static bool ValidarCirculo(int diametro);
	static bool ValidarParalelogramoNoRectangulo(int base, int ladoaltura, int alfa);
	static bool ValidarTrapecio(int base, int altura, int alfa, int beta);
};

#endif /* VALIDADOROBJETOS_H_ */
