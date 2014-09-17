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
	Pos(const Pos &p);
	bool operator == (const Pos& p);
	Pos& operator = (const Pos& p);
	virtual ~Pos();
};

#endif /* POS_H_ */
