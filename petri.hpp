/**
* PetriRed
* sintetizador y compilador de una red
*
*
*   @Autor Julio César Gambandé
*   @Fecha 2 de Abril del 2020
*   @Email gambande.julio@gmail.com
*/
#ifndef _PETRI__H
#define _PETRI__H

#include "entidad.hpp"
#include "loaderxml.hpp"
#include <vector>

typedef unsigned char byte;
typedef unsigned char uint8;

class Lugar{
private:
    bool value;
    string name;
    bool mrcInicial;
public:
	Lugar(){}
    Lugar(string name, bool marcaInicial);
    Lugar(string name);
    void clear(){value=false;}
    void set(){value=true;}
    bool get(){return value;}
    string getname(){return name;}
    void plot();
};

class Transicion{
private:
    bool value;
    string name;
    vector<uint8> sinks;
    vector<uint8> sources;
public:
	Transicion(){}
    Transicion(string name);
    void Add(uint8 idx,string type);
    uint8* getSinks();
    uint8* getSources();
    void plot();
};

class PetriRed{
    string name;
    vector<Lugar> lugares;
    vector<Transicion> transiciones;
    void ejecutar(string,ofstream*);
public:
  PetriRed();
  void sintetizarXML(LoaderXML* rawData);
  void compilarCfile(char* nameFile);
  void plot(void);
};

#endif