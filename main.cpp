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
#include "loaderxml.h"
using namespace std;


int main(int argc, char** argv){
    LoaderXML input;

    if(argc>1)
        input.open(argv[1]);

    cout<<endl<<endl;

    input.plot();

}
