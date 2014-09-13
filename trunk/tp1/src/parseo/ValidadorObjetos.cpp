#include "ValidadorObjetos.h"
#include <regex>
#include <iostream>
#include <string>

bool ValidadorObjetos::ValidarBasicos(std::string tipo, int x, int y, std::string color, int rotacion, int masa, bool estatico) {

	std::regex e ("(sub)(.*)");

	if (((tipo=="poligono") || (tipo=="rectangulo") || (tipo=="circulo") || (tipo=="paralelogramo") || (tipo=="trapecio") || (tipo=="personaje"))  ^ (0<x<100) ^ (0<y<100) ^ (std::regex_match(color,e)) ^ (rotacion>=0) ^ (masa>0 || (masa==0 ^ estatico ==true))){
	return true;
	}
	return false;
}

bool ValidadorObjetos::ValidarPoligono(int lados, int escala){

	if (4<=lados<=6 ^ escala>=1){return true;}
	return false;
}

bool ValidadorObjetos::ValidarRectangulo(int ancho, int alto){
	if (0<=ancho<=100 ^ 0<=alto<=100){return true;}
	return false;
}

bool ValidadorObjetos::ValidarCirculo(int diametro){
	if (0<=diametro<=100){return true;}
	return false;

}

bool ValidadorObjetos::ValidarParalelogramo(int base, int ladoaltura, int alfa){
	if (0<=base<=10 ^ 0<=ladoaltura<=10 ^ 0<=alfa<90 ){return true;}
	return false;
}

bool ValidadorObjetos::ValidarTrapecio(int base, int altura, int alfa, int beta){
	if (0<=base<=10 ^ 0<=altura<=10 ^ 0<=alfa<90 ^ 0<=beta<90 ){return true;}
	return false;
}
