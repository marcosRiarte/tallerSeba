#include "json/json.h"
#include <iostream>
#include <fstream>

int main(){

    Json::Value root;
    Json::Reader reader;
    std::ifstream test("prueba.json", std::ifstream::binary);
    bool parsingSuccessful = reader.parse( test, root, false );
    if ( !parsingSuccessful )
    {

        std::cout  << reader.getFormatedErrorMessages()
               << "\n";
    }

    std::cout<< "parseo correcto";
    //En esta parte hay que desarrollar, después de que json parsea en root, como
    //levantamos los objetos dentro de root, ya que están escritos como objetos
    //anidados (ver prueba.json), las llaves son objetos anidados.
    //las referencias están en http://json.org/
    //Si ven eso, en este caso un object es: {string:value,string:value,etc}

    return 0;

}
