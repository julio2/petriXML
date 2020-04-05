#include "petri.h"
#include <fstream>
using namespace std;

PetriRed::PetriRed(){
  lugares.clear();
  transiciones.clear();
}

void PetriRed::sintetizarXML(LoaderXML* rawData){
    Entidad* input= rawData->getRoot();
    //Solo sintetiza la primera net encontrada
    Entidad* net = (*input->find("net"));
    string auxstr;
    Lugar auxLug;
    Transicion auxTra;
    delete[] arryplace;
    Entidad** arryplace = net->find("place");
    Entidad** arrytrans = net->find("transition");
    Entidad** arryarc = net->find("arc");
    for(int i=0; arryplace[i];i++){
        auxstr = arryplace[i]->getHijo("name/value")->getValor(0);
        auxbool = (arryplace[i]->getHijo("initialMarking/value")->getValor(0) == "Default,1")?true:false;
        auxLug(auxstr,auxbool);
        lugares.push_back(auxLug);
        //TOTEST
    }
    for(int i=0; arryplace[i];i++){
        arryplace[i]
        //TODO: hacer lo mismo que en el lugar
    }


}


void PetriRed::compilarCfile(char* nameFile){

}

//TRANSICION
////////////////////////////////////////////////////

Transicion::Transicion(string name){
    value=0;
    this->name = name;
    sinks.clear();
    sources.clear();
}

void Transicion::Add(uint8 idx,string type){
    switch(type){
        case "sink":
        case "Sink":
        case "SINK":
            sinks.add(idx);
            break;
        case "source":
        case "Source":
        case "SOURCE":
            source.add(idx);
            break;
    }
}

uint8* Transicion::getSinks(){
    uint8* aux;
    int i;
    int n = (sinks.size()<8)?8:sinks.size();
    aux = new uint8[];
    for(i=0; i<sinks.size(); i++){
        aux[i]= sinks[i];
    }
    if(i<8){
        for(i=i;i<8;i++)
            aux[i]=0xFF;
    }
    return aux;
}

uint8* Transicion::getSources(){
    uint8* aux;
    int i;
    int n = (sources.size()<8)?8:sources.size();
    aux = new uint8[];
    for(i=0; i<sources.size(); i++){
        aux[i]= sources[i];
    }
    if(i<8){
        for(i=i;i<8;i++)
            aux[i]=0xFF;
    }
    return aux;
}

//LUGAR
////////////////////////////////////////////////////
Lugar::Lugar(string name, bool marcaInicial){
    value = false;
    mrcInicial = marcaInicial;
    this->name = name;
}

Lugar::Lugar(string name){
    Lugar(name,false);
}

/*
    EOF
*/
