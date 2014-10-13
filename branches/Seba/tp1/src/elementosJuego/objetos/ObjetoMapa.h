#ifndef OBJETOMAPA_H_
#define OBJETOMAPA_H_

#include "../ElementosJuego.h"
#include <vector>
#include <string>
#include "../Pos.h"
#include <Box2D/Box2D.h>

/**
 * Clase Abrstracta (no se pueden crear instancias de la misma) que sirve de base para
 * 	los demas objetos que hereden de ella. Es una interfaz
 * 	Objetos que heredan: Circulo, Rectángulo, Poligono, Trapecio, Paralelogramo.
 */
class ObjetoMapa : public ElementosJuego {
protected:
        bool estatico;
        long color;
        float area;
        bool circulo = false;

public:
    	/*
    	 * Inicializa un objeto
    	 */
        void initialice(bool esEstatico, std::string color, Pos pos_cm, int rotacion, int masa);

    	/*
    	 * Devuelve verdadero si el objeto no se puede mover
    	 */
        bool esEstatico();

    	/*
    	 * Devuelve verdadero si el objeto es un circulo
    	 */
        virtual bool esCirculo();

    	/*
    	 * Getter y setter para el color del objeto
    	 */
        long getColor();
        void setColor(std::string c);

    	/*
    	 * Se implementan en las clases hija, un metodo devuelve los puntos del
    	 * contorno y el otro el area del objeto
    	 */
        virtual std::vector<Pos>* getContorno() = 0;
        virtual float getArea() = 0;

        virtual ~ObjetoMapa();
};

#endif /* OBJETOMAPA_H_ */
