#include "json/json.h"
#include <iostream>
#include <fstream>
#include <sstream>



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

    std::string escenario;
    std::string imagen_fondo;
    Json::Value un_Escenario;
    un_Escenario = root["escenario"];
       /* Busca imagen_fondo en el archivo json, si no lo encuentra crea un null
      	por defecto.*/
       imagen_fondo = un_Escenario.get("imagen_fondo", "imagen no encontrada").asString();
       std::cout << imagen_fondo <<"\n";
       int alto_px = un_Escenario.get("alto-px", 0).asInt();
       int ancho_px = un_Escenario.get("ancho-px", 0).asInt();
       int alto_un = un_Escenario.get("alto-un", 0).asInt();
       int ancho_un = un_Escenario.get("ancho-un", 0).asInt();

       return 0;

}
