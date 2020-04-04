/**
* PetriRed
* sintetizador y compilador de una red
*
*
*   @Autor Julio César Gambandé
*   @Fecha 2 de Abril del 2020
*   @Email gambande.julio@gmail.com
*/
#include "entidad.h"

class PetriRed{
  Entidad* root;
public:
  PetriRed();
  void sintetizarXML(LoaderXML* rawData);
  void compilarCfile(char* nameFile);
};
