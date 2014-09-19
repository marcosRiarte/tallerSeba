#include "json/json.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Parser.h"
#include "../log/Log.h"
#include "CreadorObjetos.h"
#include "ValidadorObjetos.h"

Parser::Parser(std::string nombreArchivo) {

	this->objetosMapa = std::vector<ObjetoMapa*>();
	this->personajes = std::vector<Personaje*>();

	Json::Value raiz;
	Json::Reader reader;

	std::ifstream prueba(nombreArchivo, std::ifstream::binary);
	bool parseoExitoso = reader.parse(prueba, raiz, false);
	if (!parseoExitoso) {
//		Log::Loguear(reader.getFormatedErrorMessages(), nombreArchivo);
		std::cout << reader.getFormatedErrorMessages() << "\n";
	}

	std::string escenario;
	Json::Value un_Escenario;

	// Se asume que todos los archivos json para el juego deben comenzar con la palabra escenario,
	// sino el archivo es inválido.
	un_Escenario = raiz["escenario"];

	if (un_Escenario.isNull()){
		std::string mensajeError = "No hay escenario, fallo el parseo del archivo ";
//		Log::Loguear(mensajeError, nombreArchivo);

		std::cout << mensajeError << "\n";
	}
	else{
	/* Busca el nombre de la imagen_fondo en el archivo json, si no lo encuentra crea un null
	 por defecto.*/
	std::string imagen_fondo =
			un_Escenario.get("imagen_fondo", "fondo1.png").asString();
	std::cout << imagen_fondo << "\n";

	int alto_px = un_Escenario.get("alto_px", 768).asInt();
	int ancho_px = un_Escenario.get("ancho_px", 1024).asInt();
	int alto_un = un_Escenario.get("alto_un", 100).asInt();
	int ancho_un = un_Escenario.get("ancho_un", 50).asInt();

	//Paso a const char* el string del nombre de la imagen.
	const char * c = imagen_fondo.c_str();
	Pantalla* unaPantalla = new Pantalla(alto_px,ancho_px,alto_un,ancho_un,c);
	this->pantalla= unaPantalla;
	int personaje_x = un_Escenario["personaje"].get("x", 0).asInt();
	int personaje_y = un_Escenario["personaje"].get("y", -100).asInt();

	if (ValidadorObjetos::ValidarPersonaje(personaje_x,personaje_y,ancho_un,alto_un)){
			this->personajes.push_back(CreadorObjetos::CrearPersonaje(personaje_x,personaje_y));
	}else{
			this->personajes.push_back(CreadorObjetos::CrearPersonaje(0,-alto_un));
	}

	Json::Value objetos;
	objetos = un_Escenario["objetos"];

	//En esta parte parseamos todos los objetos que haya, y creamos los objetos correspondientes
	for (size_t i = 0; i < objetos.size(); i++) {
		std::string tipo = objetos[i].get("tipo", "rectangulo").asString();
		int x = objetos[i].get("x", 5).asInt();
		int y = objetos[i].get("y", 90).asInt();
		int diametro = objetos[i].get("diametro", 1).asInt();
		int ancho = objetos[i].get("ancho", 2).asInt();
		int alto = objetos[i].get("alto", 1).asInt();

		int base = objetos[i].get("base", 1).asInt();
		int altura = objetos[i].get("altura", 1).asInt();
		int alfa = objetos[i].get("alfa", 1).asInt();
		int beta = objetos[i].get("beta", 1).asInt();

		int lados = objetos[i].get("lados", 0).asInt();
		std::string color = objetos[i].get("color", "#FF0000").asString();
		int rotacion = objetos[i].get("rot", 0).asInt();
		int masa = objetos[i].get("masa", 1).asInt();
		bool estatico = objetos[i].get("estatico", false).asBool();
		float escala = objetos[i].get("escala", 1).asFloat();

		if (ValidadorObjetos::ValidarBasicos(tipo,x,y,color,rotacion,masa,estatico,ancho_un,alto_un)){
			if(tipo=="rectangulo"){
						this->objetosMapa.push_back(CreadorObjetos::CrearRectangulo(x, y, ancho, alto,rotacion,color,masa,estatico));
			}else if (tipo=="poligono"){
					if (ValidadorObjetos::ValidarPoligono(lados,escala))
						this->objetosMapa.push_back(CreadorObjetos::CrearPoligono(x,y,lados,escala,rotacion,color,masa,estatico));
			}
			else if(tipo=="circulo"){
					if (ValidadorObjetos::ValidarCirculo(diametro))
						this->objetosMapa.push_back(CreadorObjetos::CrearCirculo(x,y,diametro,rotacion,color,masa,estatico));
			}
			else if(tipo=="paralelogramo"){
					if (ValidadorObjetos::ValidarParalelogramo(alfa))
						this->objetosMapa.push_back(CreadorObjetos::CrearParalelogramo(x,y,base,altura,alfa,rotacion,color,masa,estatico));
			}
			else if(tipo=="trapecio"){
					if (ValidadorObjetos::ValidarTrapecio(alfa,beta))
						this->objetosMapa.push_back(CreadorObjetos::CrearTrapecio(x,y,base,altura,alfa,beta,rotacion,color,masa,estatico));
			}
			}
		}
		}
}

std::vector<ObjetoMapa*>* Parser::getObjetos(){
	std::vector<ObjetoMapa*>* objetos = &objetosMapa;
	return objetos;
}

std::vector<Personaje*>* Parser::getPersona(){
	std::vector<Personaje*>* persona = &personajes;
	return persona;
}

Pantalla* Parser::getPantalla() {
	return this->pantalla;
}
