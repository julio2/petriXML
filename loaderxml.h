/**
* LoaderXML
* cargador de archivo XML
*
*
*   @Autor Julio César Gambandé
*   @Fecha 14 de febrero del 2020
*   @Email gambande.julio@gmail.com
*/

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
};
