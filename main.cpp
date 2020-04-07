/**
* PIPE2C
* Conversor PIPE to C
*
*
*   @Autor Julio César Gambandé
*   @Fecha 14 de febrero del 2020
*   @Email gambande.julio@gmail.com
*/

#include <iostream>
#include "loaderxml.hpp"
#include "petri.hpp"
using namespace std;


int main(int argc, char** argv){
    LoaderXML input;

    if(argc>1)
        input.open(argv[1]);
    else
        input.open("redorg.xml");
    cout<<endl<<endl;
    input.plot();

    cout<<endl<<endl<<"Buscando place:"<<endl;
    Entidad** arry = input.getRoot()->find("place");
    for(int i=0; arry[i];i++)cout<<"0x"<<hex<<uppercase<<((short*)arry[i])[0]<<endl;

    cout<<endl<<endl;

    PetriRed net;

    net.sintetizarXML(&input);
    net.plot();

    net.compilarCfile("quiensabe.c");

}
