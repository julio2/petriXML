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
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
using namespace std;

void delay(unsigned int tiempo_ms);

int main(int argc, char** argv){
    LoaderXML input;
    string red;
    red.clear();

    cout<<"Cargando XML... "<<endl;

    if(argc>1){
        input.open(argv[1]);
        for(int i =0;argv[1][i] && argv[1][i] != '.';i++)
            red.push_back(argv[1][i]);
    }
    else{
        input.open("redorg.xml");
        red="redorg";
    }
    delay(1000);
    //input.plot();

//    cout<<endl<<endl<<"Buscando place:"<<endl;
//    Entidad** arry = input.getRoot()->find("place");
//    for(int i=0; arry[i];i++)cout<<"0x"<<hex<<uppercase<<((short*)arry[i])[0]<<endl;


    PetriRed net;
    cout<<"Sintetizando red: "<<red<<endl;
    net.sintetizarXML(&input);
    delay(1000);
    //net.plot();
    cout<<"Generando archivos..."<<endl;
    net.compilarCfile(red.c_str());
    delay(1000);
    cout<<"Hecho."<<endl;


}

void delay(unsigned int tiempo_ms){
    std::this_thread::sleep_for(chrono::milliseconds(tiempo_ms));
}
