#include "../src/Pantalla.h"
#include <iostream>

void runPantallaTest() {
	Pantalla* p = new Pantalla(768, 1024, 50, 90, "unaDireccionCualquiera");
	vector<int> dimensiones = p->getDimensionesPx();
	if ((dimensiones[0] != 768) || (dimensiones[1] != 1024)) {
		cout << "ERROR - Pantalla::getDimensionesPx() \n";
		return;
	}
	dimensiones = p->getDimensiones();
	if ((dimensiones[0] != 50) || (dimensiones[1] != 90)) {
		cout << "ERROR - Pantalla::getDimensiones() \n";
		return;
	}
	if (p->getFondo() != "unaDireccionCualquiera"){
		cout << "ERROR - Pantalla::getFondo() \n";
		return;
	}
	cout << "RES_OK - PantallaTest \n";
}
