#include "petri.hpp"
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
    string auxstr,atributo,ntrans;
    bool auxbool;
    Lugar auxLug;
    Transicion auxTra;
    Entidad** arryplace = net->find("place");
    Entidad** arrytrans = net->find("transition");
    Entidad** arryarc = net->find("arc");
    for(int i=0; arryplace[i];i++){
        auxstr = arryplace[i]->getHijo("name/value")->getValor(0);
        auxbool = (arryplace[i]->getHijo("initialMarking/value")->getValor(0).compare("Default,1"))?false:true;
        auxLug = Lugar(auxstr,auxbool);
        lugares.push_back(auxLug);
    }
    for(int i=0; arrytrans[i];i++){
		auxstr = arrytrans[i]->getHijo("name/value")->getValor(0);
		auxTra = Transicion(auxstr);
		transiciones.push_back(auxTra);
        for(int j=0; arryarc[j];j++){
			atributo = arryarc[j]->getValorAtributo("source");
			if(!atributo.compare(ntrans)){
				atributo = arryarc[j]->getValorAtributo("target");
				for(int k = 0; k<lugares.size();k++){
					if(!lugares[k].getname().compare(atributo)){
						transiciones[i].Add(k,"Sink");
						break;
					}
				}
			}else{ //Entonces talvez es un target
				atributo = arryarc[j]->getValorAtributo("target");
				if(!atributo.compare(ntrans)){
					atributo = arryarc[j]->getValorAtributo("source");
					for(int k = 0; k<lugares.size();k++){
						if(!lugares[k].getname().compare(atributo)){
							transiciones[i].Add(k,"Sourse");
							break;
						}
					}
				}
			}		
		}
    }
}


void PetriRed::compilarCfile(char* nameFile){
    ifstream plantilla;
    ofstream cfile;
    char buffer[200];
    string nameM;
    string comando;
    enum{RELLENANDO, COPIANDO}estado = COPIANDO;
    
    plantilla.open("plantilla.dot");
    cfile.open(nameFile);
    
    do{
        plantilla.getline(buffer,200);
        for(int i = 0;buffer[i];i++ ){
            switch(estado){
                case COPIANDO:
                if(buffer[i] == '@'){
                    estado=RELLENANDO;
                    break;
                }
                cfile.put(buffer[i]);    
                break;
                
                case RELLENANDO:
                if(buffer[i] == '\\'){
                    comando.push_back(0);
                    ejecutar(comando,&cfile);
                    estado=COPIANDO;
                    comando.clear();
                    break;
                }
                comando.push_back(buffer[i]);
                break;
                
            }    
        }
        cfile.put('\n');
        
    }while(plantilla.good());
}

void PetriRed::ejecutar(string com, ofstream* output){
    if(!com.compare("")){
        //nombre en mayusculas
    }
    else if(!com.compare("#")){
        //nombre en minusculas
    }
    else if(!com.compare("nlug")){
        //numero de lugares
    }
    else if(!com.compare("trans")){
        //numero de transiciones
    }
    else if(!com.compare("t")){
        //datos de las transiciones
    }
    else if(!com.compare("l")){
        //datos de los lugares
    }
}

void PetriRed::plot(void){
	
	cout<<"RED de petri:"<<endl;
	cout<<"    "<<"Luegares:"<<endl;
	for(int i=0 ;i< lugares.size();i++){
		cout<<"        "<<"\u001b[32mId: \u001b[0m"<<i<<" ";
		lugares[i].plot();
	}
	cout<<"    "<<"Transiciones:"<<endl;
	for(int i=0 ;i< transiciones.size();i++){
		cout<<"        "<<"\u001b[32mId: \u001b[0m"<<i<<" ";
		transiciones[i].plot();
	}
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
	if(!type.compare("sink") 
	|| !type.compare("sink") 
	|| !type.compare("SINK")
	)sinks.push_back(idx);
	else if(!type.compare("source") 
	|| !type.compare("Source") 
	|| !type.compare("SOURCE")
	)sources.push_back(idx);
}

uint8* Transicion::getSinks(){
    uint8* aux;
    int i;
    int n = (sinks.size()<8)?8:sinks.size();
    aux = new uint8[n];
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
    aux = new uint8[n];
    for(i=0; i<sources.size(); i++){
        aux[i]= sources[i];
    }
    if(i<8){
        for(i=i;i<8;i++)
            aux[i]=0xFF;
    }
    return aux;
}

void Transicion::plot(){
	const string colorBlack = "\u001b[30m";
    const string colorRed = "\u001b[31;1m";
    const string colorGreen = "\u001b[32m";
    const string colorYellow = "\u001b[33m";
    const string colorBlue = "\u001b[34m";
    const string colorMagenta = "\u001b[35m";
    const string colorCyan = "\u001b[36m";
    const string colorWhite = "\u001b[37m";
    const string colorOrange = "\u001b[38;5;202m";
    const string colorReset = "\u001b[0m";
    
    cout<<colorOrange<<"Nombre: "<<colorReset<<name
    <<colorCyan<<" Fuentes: "<<colorReset;
    for(int i =0; i<sources.size();i++) cout<<sources[i]<<" ";
    cout<<colorCyan<<" Sumideros: "<<colorReset;
    for(int i =0; i<sinks.size();i++) cout<<sinks[i]<<" ";
    cout<<endl;
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

void Lugar::plot(){
	const string colorBlack = "\u001b[30m";
    const string colorRed = "\u001b[31;1m";
    const string colorGreen = "\u001b[32m";
    const string colorYellow = "\u001b[33m";
    const string colorBlue = "\u001b[34m";
    const string colorMagenta = "\u001b[35m";
    const string colorCyan = "\u001b[36m";
    const string colorWhite = "\u001b[37m";
    const string colorOrange = "\u001b[38;5;202m";
    const string colorReset = "\u001b[0m";
    
	cout<<colorOrange<<"Nombre: "<<colorReset<<name
	<<colorCyan<<" Estado: "<<colorReset<<((value)?"marcado":"desmarcado")
	<<colorRed<<" marca inicial: "<<colorReset<<((mrcInicial)?"SI":"NO")<<endl;
}

/*
    EOF
*/
