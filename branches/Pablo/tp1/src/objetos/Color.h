/*
 * Color.h
 *
 *  Created on: 9/9/2014
 *      Author: pablo_000
 */

#ifndef COLOR_H_
#define COLOR_H_

class Color {
public:
	Color();
	Color(const Color* c);
	//hay que definir el operador =
	virtual ~Color();
};

#endif /* COLOR_H_ */
