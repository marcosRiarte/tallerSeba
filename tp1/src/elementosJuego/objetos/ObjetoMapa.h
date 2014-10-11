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
        void initialice(bool esEstatico, std::string color, Pos pos_cm, int rotacion, int masa);

        bool esEstatico();

        virtual bool esCirculo();

        long getColor();
        void setColor(std::string c);

        //implementar
        virtual std::vector<Pos*>* getContorno() = 0;
        virtual float getArea() = 0;

        virtual ~ObjetoMapa();
};

#endif /* OBJETOMAPA_H_ */
