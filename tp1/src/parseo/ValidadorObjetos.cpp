#include "ValidadorObjetos.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../src/Constantes.h"

void ValidadorObjetos::ValidarPersonaje(int *x, int *y, int ancho_un, int alto_un) {
	if (!((*x >= 0) && (*x < ancho_un + 1) && (*y > -alto_un - 1) && (*y <= 0))) {
		std::string mensaje = "Personaje fuera de pantalla, se crea en la posición por defecto x=40 y=-80";
		const char* c = mensaje.c_str();
		loguer->loguear(c, Log::LOG_TIPO::LOG_WAR);
		*x = 40;
		*y = -80;
	}
}

bool es_color(std::string const& s) {
	return s.compare(0, 1, "#") == 0 && s.size() > 1 && s.find_first_not_of("0123456789abcdefABCDEF", 1) == std::string::npos;
}

void ValidadorObjetos::ValidarBasicos(std::string *tipo, int *x, int *y,
		std::string *color, int *rotacion, int *masa, bool estatico,
		int ancho_un, int alto_un) {
	std::string mensaje;
	std::string str1(*tipo);
	if (!(((str1.compare("rectangulo")) == 0)
			|| ((str1.compare("poligono")) == 0)
			|| ((str1.compare("paralelogramo")) == 0)
			|| ((str1.compare("circulo")) == 0)
			|| ((str1.compare("trapecio")) == 0)
			|| ((str1.compare("circulo")) == 0))) {

		mensaje = "El tipo "+*tipo+" no es un tipo de objeto válido, se crea rectangulo por defecto";
		*tipo = "rectangulo";
		//Paso a const char* el string del mensaje.
			const char * c = mensaje.c_str();
			loguer->loguear(c, Log::LOG_TIPO::LOG_WAR);
	}
	if (!(es_color(*color))) {
		mensaje =
				"El color "+*color+" no representa una sintáxis válida, se crea color por defecto";
		//Paso a const char* el string del mensaje.
			const char * c = mensaje.c_str();
			loguer->loguear(c, Log::LOG_TIPO::LOG_WAR);

		*color = "#FF00FF";
	}
	if (!((*x >= 0) && (*x < ancho_un + 1) && (*y > -alto_un - 1) && (*y <= 0))) {
		mensaje =
				"Objeto fuera de pantalla, se coloca en una posicion arbitraria";
		//Paso a const char* el string del mensaje.
			const char * c = mensaje.c_str();
			loguer->loguear(c, Log::LOG_TIPO::LOG_WAR);
		*x = 40;
		*y = -50;
	}
	if (!(*rotacion >= 0)) {
		mensaje = "La rotación debe ser mayor o igual a 0, se toma rotacion=0";
		//Paso a const char* el string del mensaje.
			const char * c = mensaje.c_str();
			loguer->loguear(c, Log::LOG_TIPO::LOG_WAR);
		*rotacion = 0;
	}
	if (!(masa > 0 || (masa == 0 && estatico == true))) {
		mensaje =
				"la masa debe ser mayor a 0 o ser 0 y el objeto estático, se toma masa 5";
		//Paso a const char* el string del mensaje.
			const char * c = mensaje.c_str();
			loguer->loguear(c, Log::LOG_TIPO::LOG_WAR);
		*masa = 5;
	}
}

void ValidadorObjetos::ValidarPoligono(int* lados, float* escala) {
	std::string mensaje;

	if ((*escala < 1)) {
		mensaje = "escala invalida, se crea con 30 por defecto";
		*escala = 30;
	}
	if (!((*lados >= 3) && (*lados <= 6))) {
		mensaje = "Cantidad de lados incorrecta, se crean 3 por defecto";
		*lados = 3;
	}
	const char * c = mensaje.c_str();
	loguer->loguear(c, Log::LOG_TIPO::LOG_WAR);
}

void ValidadorObjetos::ValidarCirculo(int *diametro) {
	if (*diametro < 1) {
		std::string mensaje = "diametro inválido, se crea con 1 por defecto";
		*diametro = 1;
		const char * c = mensaje.c_str();
		loguer->loguear(c, Log::LOG_TIPO::LOG_WAR);
	}
}

void ValidadorObjetos::ValidarParalelogramo(int *alfa) {
	if (!((*alfa < 181) && (*alfa >= 0))) {
		std::string mensaje = "Ángulo es inválido, se crea con 45% por defecto";
		*alfa = 45;
		const char * c = mensaje.c_str();
		loguer->loguear(c, Log::LOG_TIPO::LOG_WAR);
	}
}

void ValidadorObjetos::ValidarTrapecio(int alfa, int beta) {
	if (!((alfa < 90) && (alfa >= 0))) {
		std::string mensaje = "Ángulo inválido, se crea con 45% por defecto";
		const char * c = mensaje.c_str();
		loguer->loguear(c, Log::LOG_TIPO::LOG_WAR);
	}
}
