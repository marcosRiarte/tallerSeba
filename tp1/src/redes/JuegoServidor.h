#ifndef JUEGOSERVIDOR_H_
#define JUEGOSERVIDOR_H_
#include "RedServidor.h"

class JuegoServidor {
public:
	JuegoServidor(void);
	virtual ~JuegoServidor(void);

	void actualizar();

private:

   // IDs para los clientes que se conectan en la tabla en RedServidor
    static unsigned int id_cliente;

   // El objeto RedServidor
    RedServidor* red;
};

#endif /* JUEGOSERVIDOR_H_ */
