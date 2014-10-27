#include "ServiciosRed.h"

int ServiciosRed::enviarMensaje(SOCKET SocketActual, char * mensaje, int tamanioMensaje)
{
    return send(SocketActual, mensaje, tamanioMensaje, 0);
}

int ServiciosRed::recibirMensaje(SOCKET SocketActual, char * buffer, int tamBuffer)
{
    return recv(SocketActual, buffer, tamBuffer, 0);
}

