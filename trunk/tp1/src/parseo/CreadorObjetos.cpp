#include "CreadorObjetos.h"
#include "../objetos/ObjetoMapa.h"
#include "../objetos/Pos.h"
#include "../personajes/Personaje.h"

Personaje * CreadorObjetos::CrearPersonaje(int personaje_x, int personaje_y){
	Pos *posicion = new Pos(personaje_x,personaje_y);
	Personaje *unPersonaje = new Personaje(posicion);
	return unPersonaje;
}

Rectangulo * CreadorObjetos::CrearRectangulo(int x, int y, int ancho, int alto,int rotacion,std::string color,int masa,bool estatico) {
    Pos *posicion = new Pos(x,y);
    Rectangulo * unRectangulo = new Rectangulo(estatico, color, posicion, rotacion, masa, alto, ancho);
    return unRectangulo;
}

Poligono * CreadorObjetos::CrearPoligono(int x, int y, int lados, int escala, int rotacion,std::string color,int masa,bool estatico) {
	Pos *posicion = new Pos(x,y);
	Poligono *unPoligono =new Poligono(posicion, lados, escala, rotacion, color, masa, estatico);
	return unPoligono;

}

Circulo * CreadorObjetos::CrearCirculo(int x, int y, int diametro,int rotacion,std::string color,int masa,bool estatico) {
	Pos *posicion = new Pos(x,y);
	Circulo* unCirculo = new Circulo(posicion, diametro, rotacion, color, masa, estatico);
	return unCirculo;

}

Paralelogramo * CreadorObjetos::CrearParalelogramo(int x, int y, int base, int ladoaltura, int alfa,int rotacion,std::string color,int masa,bool estatico) {
	Pos *posicion = new Pos(x,y);
	Paralelogramo* unParalelogramo =new Paralelogramo(posicion,base,ladoaltura,alfa,rotacion,color,masa, estatico);
	return unParalelogramo;
}

Trapecio * CreadorObjetos::CrearTrapecio(int x, int y, int base, int altura, int alfa, int beta,int rotacion,std::string color,int masa,bool estatico) {
	Pos *posicion = new Pos(x,y);
	Trapecio* unTrapecio = new Trapecio(posicion,base,altura,alfa,beta,rotacion,color,masa, estatico);
	return unTrapecio;

}

