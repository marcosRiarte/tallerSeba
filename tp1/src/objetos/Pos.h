#ifndef POS_H_
#define POS_H_

class Pos {
private:
	int x;
	int y;
public:
	Pos(int x, int y);
	int getX();
	int getY();
	Pos(const Pos* p);
	bool esIgual(Pos* posicion);
	float getNorma();
	virtual ~Pos();
};

#endif /* POS_H_ */
