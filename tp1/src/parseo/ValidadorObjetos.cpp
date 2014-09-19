#include "ValidadorObjetos.h"


bool ValidadorObjetos::ValidarBasicos(std::string tipo, int x, int y,
                std::string color, int rotacion, int masa, bool estatico) {

        std::regex e("(#)((0-9)(a-f)(A-F){3}){1,2}");

        std::string str1(tipo);
        if ((((str1.compare("rectangulo")) == 0)
                        || ((str1.compare("poligono")) == 0)
                        || ((str1.compare("paralelogramo")) == 0)
                        || ((str1.compare("circulo")) == 0)
                        || ((str1.compare("trapecio")) == 0
                                        || ((str1.compare("circulo")) == 0))
                        || ((str1.compare("personaje")) == 0)) && (x >= 0) && (x < 51)
                        && (y > -101) && (y <= 0) && (rotacion >= 0)
                        && (masa > 0 || (masa == 0 && estatico == true))) {
                return true;
        } else {
                return false;
        }
}

bool ValidadorObjetos::ValidarPoligono(int lados, int escala) {

        if (((lados >= 3) && (lados <= 6)) && (escala >= 1)) {
                return true;
        }
        else{
        return false;
        }
}

bool ValidadorObjetos::ValidarRectangulo(int x, int y) {
        if ((x >= 0) && (x <= 50) && (y >= -100) && (y <= 0)) {
                return true;
        } else {
                return false;
        }
}

bool ValidadorObjetos::ValidarCirculo(int diametro) {
        if (0 <= diametro) {
                return true;
        }
        else{
        return false;
        }
}

bool ValidadorObjetos::ValidarParalelogramo(int alfa) {
        if (alfa < 90) {
                return true;
        }
        else{
        return false;
        }
}

bool ValidadorObjetos::ValidarTrapecio(int alfa,int beta) {
        if ((alfa < 90) && (beta < 90)) {
                return true;
        }
        else{
        return false;
        }
}
