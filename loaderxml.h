/**
* LoaderXML
* cargador de archivo XML
*
*
*   @Autor Julio César Gambandé
*   @Fecha 14 de febrero del 2020
*   @Email gambande.julio@gmail.com
*/
#ifndef _LOADER__H
#define _LOADER__H

#include <string>
#include <iostream>
#include <fstream>
#include "entidad.h"
#include <string.h>
using namespace std;

class LoaderXML{
  Entidad* root;
public:
  LoaderXML();
  void open(string);
  void plot(void);
  Entidad* getRoot(void);
  //Entidad* getRoot(void);
};

#endif
