#include "parseo/ValidadorObjetos.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "log/Log.h"
#include "../src/Constantes.h"

bool ValidadorObjetos::ValidarPersonaje(int x, int y,int ancho_un,int alto_un) {
        if ((x >= 0) && (x < ancho_un+1) && (y > -alto_un-1) && (y <= 0)) {
                return true;
        } else {
    		std::string mensaje = "Personaje fuera de pantalla, se crea en la posición por defecto";
    				const char * c = mensaje.c_str();
    				loguer->loguear(c, Log::LOG_TIPO::LOG_WAR);
    				return false;
        }
}

bool es_color(std::string const& s)
{
  return s.compare(0, 1, "#") == 0
      && s.size() > 1
      && s.find_first_not_of("0123456789abcdefABCDEF", 1) == std::string::npos;
}

bool ValidadorObjetos::ValidarBasicos(std::string tipo, int x, int y, std::string color, int rotacion, int masa, bool estatico,int ancho_un,int alto_un) {
		std::string mensaje;
        std::string str1(tipo);
	if (((str1.compare("rectangulo")) == 0) || ((str1.compare("poligono")) == 0)
			|| ((str1.compare("paralelogramo")) == 0)
			|| ((str1.compare("circulo")) == 0)
			|| ((str1.compare("trapecio")) == 0)
			|| ((str1.compare("circulo")) == 0)) {
		if (es_color(color)) {
			if ((x >= 0) && (x < ancho_un + 1) && (y > -alto_un - 1) && (y <= 0)) {
				if (rotacion >= 0) {
					if (masa > 0 || (masa == 0 && estatico == true)) {
						return true;
					} else {
						mensaje = "la masa debe ser mayor a 0 o ser 0 y el objeto estático";
					}
				} else {
					mensaje = "La rotación debe ser mayor o igual a 0";
				}
			} else {
				mensaje = "Objeto fuera de pantalla";
			}
		} else {
			mensaje = "El color no representa una sintáxis válida";
		}
	}
	mensaje = "El tipo " + tipo + " no es un tipo de objeto válido";
	std::string mensajeFinal = mensaje + ", no se creó el objeto tipo " + tipo;
	//Paso a const char* el string del mensaje.
	const char * c = mensajeFinal.c_str();
	loguer->loguear(c, Log::LOG_TIPO::LOG_WAR);
	return false;
}

bool ValidadorObjetos::ValidarPoligono(int lados, int escala) {
	std::string mensaje;
	if (((lados >= 3) && (lados <= 6))) {
		if(escala >= 1){
			return true;
		}
		else{

		}
		}
	 else {
		 mensaje = "Los lados del poligono tiene que estar entre 3 y 6, no se crea";
	}
	const char * c = mensaje.c_str();
	loguer->loguear(c, Log::LOG_TIPO::LOG_WAR);
	return false;
}

bool ValidadorObjetos::ValidarCirculo(int diametro) {
	if (0 <= diametro) {
		return true;
	} else {
		std::string mensaje = "diametro inválido";
		const char * c = mensaje.c_str();
		loguer->loguear(c, Log::LOG_TIPO::LOG_WAR);
		return false;
	}
}

bool ValidadorObjetos::ValidarParalelogramo(int alfa) {
	if ((alfa < 90) && (alfa >= 0)) {
		return true;
	} else {
		std::string mensaje = "Ángulo inválido";
		const char * c = mensaje.c_str();
		loguer->loguear(c, Log::LOG_TIPO::LOG_WAR);
		return false;
	}
}

bool ValidadorObjetos::ValidarTrapecio(int alfa, int beta) {
	if ((alfa < 90) && (beta < 90) && (alfa >= 0) && (beta >= 0)) {
		return true;
	} else {
		std::string mensaje = "Ángulo inválido";
				const char * c = mensaje.c_str();
				loguer->loguear(c, Log::LOG_TIPO::LOG_WAR);
				return false;
	}
}
