#ifndef POS_H_
#define POS_H_

class Pos {
private:
	float x;
	float y;
public:
	Pos(int x, int y);
	int getX();
	int getY();
	Pos(const Pos* p);
	// Devuelve verdadero si la posicion es la misma
	bool esIgual(Pos* posicion);
	//hay que definir el operador =
	virtual ~Pos();
};

#endif /* POS_H_ */
