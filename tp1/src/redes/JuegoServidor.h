#ifndef JUEGOSERVIDOR_H_
#define JUEGOSERVIDOR_H_
#include "RedServidor.h"
#include "DatosRed.h"
#include "../parseo/Config.h"
#include <iostream>


/*
#include <string>

#include "../vistas/Pantalla.h"
#include "../escenario/Escenario.h"
#include "../parseo/Config.h"
#include "../Constantes.h"
#include "../controlador/Controlador.h"
#include <stdio.h>
#include <exception>
#include "../excepciones/MVCExcepcion.h"
*/
class JuegoServidor {
public:
	JuegoServidor(void);
	virtual ~JuegoServidor(void);
	void recibirDeClientes();
	void actualizar();
	void enviarPaquetesAccion();
private:

   // IDs para los clientes que se conectan en la tabla en RedServidor
    static unsigned int id_cliente;

   // El objeto RedServidor
    RedServidor* red;

    // buffer de datos
    char network_data[MAX_PACKET_SIZE];
};

#endif /* JUEGOSERVIDOR_H_ */
