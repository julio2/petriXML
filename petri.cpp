#include "petri.hpp"
#include <fstream>
#include <stdlib.h>
using namespace std;

char* itoa(int num, char* str, int base);

PetriRed::PetriRed(){
  lugares.clear();
  transiciones.clear();
}

const string PetriRed::version = "v0.0.2";

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
		ntrans = arrytrans[i]->getHijo("name/value")->getValor(0);
		auxTra = Transicion(ntrans);
		transiciones.push_back(auxTra);
        bool isSourse = false;

        for(int j=0; arryarc[j];j++){
            string ATTDesde = arryarc[j]->getValorAtributo("source");
            string ATTHasta = arryarc[j]->getValorAtributo("target");
            if(!ATTDesde.compare(ntrans) + !ATTHasta.compare(ntrans)){ // IF match!
                int k;
                if(ATTDesde.compare(ntrans)){//look for place ID by source
                    for(k = 0; ATTDesde.compare(lugares[k].getname());k++);
                    transiciones[i].Add(k,"Source");
                }else{ //look for place ID but handled by target
                    for(k = 0; ATTHasta.compare(lugares[k].getname());k++);
                    transiciones[i].Add(k,"Sink");
                }
            }

        }
    }
}



void PetriRed::compilarCfile(const char* nameFile){
    ifstream plantilla;
    ofstream cfile,hfile;
    char buffer[200];
    string nameM;
    string comando;
    enum{RELLENANDO, COPIANDO}estado = COPIANDO;

    for(int i=0;nameFile[i]!='.' && nameFile[i];i++){
        if(nameFile[i]==' ')
            name.push_back('_');
        else
            name.push_back(nameFile[i]);
    }

    string nameCppFile = "output/";
    nameCppFile.append(name);
    nameCppFile.append(".c");
    plantilla.open("plantillaC.dot");
    cfile.open(nameCppFile.c_str());

    do{
        plantilla.getline(buffer,200);
        for(int i = 0;buffer[i];i++ ){
            switch(estado){
                case COPIANDO:
                if(buffer[i] == '$'){
                    estado=RELLENANDO;
                    break;
                }
                cfile.put(buffer[i]);
                break;

                case RELLENANDO:
                if(buffer[i] == '\\'){
                    char buffer[30];
                    if(!comando.compare("")){
                        const char* p;
                        char mayus[30];
                        p = name.c_str();
                        for(int i=0; i<name.size();i++){
                            if(p[i]>='a')mayus[i]=p[i]-32;
                            cfile.put(mayus[i]);
                        }
                    }
                    else if(!comando.compare("#")){
                        for(int i=0; i<name.size();i++){
                            cfile.put(name[i]);
                        }
                    }
                    else if(!comando.compare("nlug")){
                        itoa(lugares.size(),buffer,10);
                        cfile.write(buffer, strlen(buffer));
                    }
                    else if(!comando.compare("trans")){
                        itoa(transiciones.size(),buffer,10);
                        cfile.write(buffer, strlen(buffer));
                    }
                    else if(!comando.compare("t")){
                        for(int i=0;i<transiciones.size();i++){
                            cfile.write("{0,{",4);
                            for(int j=0; j<8;j++){
                                cfile.write("0x",2);
                                itoa(transiciones[i].getSources()[j],buffer,16);
                                if(buffer[1]==0){
                                    buffer[2]=0;
                                    buffer[1]=buffer[0];
                                    buffer[0]='0';
                                }
                                cfile.write(buffer, 2);
                                if(j!=7)cfile.put(',');
                            }
                            cfile.write("},{",3);
                            for(int j=0; j<8;j++){
                                cfile.write("0x",2);
                                itoa(transiciones[i].getSinks()[j],buffer,16);
                                if(buffer[1]==0){
                                    buffer[2]=0;
                                    buffer[1]=buffer[0];
                                    buffer[0]='0';
                                }
                                cfile.write(buffer, 2);
                                if(j!=7)cfile.put(',');
                            }
                            if(i!=transiciones.size()-1)
                                cfile.write("}},\n\r    ",9);
                            else
                                cfile.write("}}",2);
                        }
                    }
                    else if(!comando.compare("l")){
                        const char* p;
                        for (int i = 0; i < lugares.size(); i++) {
                            cfile.put('{');
                            if(lugares[i].get())cfile.put('1');
                            else cfile.put('0');
                            cfile.put(',');
                            cfile.put('\"');

                            p= lugares[i].getname().c_str();
                            int k = lugares[i].getname().size();
                            cfile.write(p,(k<5)?k:4);
                            cfile.write("\",",2);
                            if(lugares[i].getMI())cfile.put('1');
                            else cfile.put('0');
                            if(i < lugares.size()-1)cfile.write("},\n\r    ",8);
                            else cfile.put('}');
                        }
                    }
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

    plantilla.close();

    string nameHppFile = "output/";
    nameHppFile.append(name);
    nameHppFile.append(".h");
    plantilla.open("plantilla.dot");
    hfile.open(nameHppFile.c_str());

    plantilla.open("plantillaH.dot");


    do{
        plantilla.getline(buffer,200);
        for(int i = 0;buffer[i];i++ ){
            switch(estado){
                case COPIANDO:
                if(buffer[i] == '$'){
                    estado=RELLENANDO;
                    break;
                }
                hfile.put(buffer[i]);
                break;

                case RELLENANDO:
                if(buffer[i] == '\\'){
                    char buffer[30];
                    if(!comando.compare("")){
                        const char* p;
                        char mayus[30];
                        p = name.c_str();
                        for(int i=0; i<name.size();i++){
                            if(p[i]>='a')mayus[i]=p[i]-32;
                            hfile.put(mayus[i]);
                        }
                    }
                    else if(!comando.compare("#")){
                        for(int i=0; i<name.size();i++){
                            hfile.put(name[i]);
                        }
                    }
                    else if(!comando.compare("fecha")){

                    }
                    else if(!comando.compare("vers")){
                        hfile.write(getVersion().c_str(),getVersion().size());
                    }
                    else if(!comando.compare("tr")){
                        for(int i =0; i<transiciones.size();i++){
                            hfile.write("    ",4);
                            hfile.write(transiciones[i].getname().c_str(),lugares[i].getname().size());
                            if(i!=transiciones.size()-1)hfile.write(",\n\r",3);
                        }
                    }
                    else if(!comando.compare("slugs")){
                        for(int i =0; i<lugares.size();i++){
                            hfile.write("//    \"",7);
                            hfile.write(lugares[i].getname().c_str(),lugares[i].getname().size());
                            if(i!=lugares.size()-1)hfile.write("\"\n\r",3);
                            else hfile.put('\"');
                        }
                    }
                    estado=COPIANDO;
                    comando.clear();
                    break;
                }
                comando.push_back(buffer[i]);
                break;
            }
        }
        hfile.put('\n');
    }while(plantilla.good());
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
	|| !type.compare("Sink")
	|| !type.compare("SINK")
    ){
        sinks.push_back(idx);
        //cout<<"sink "<<(int)idx<<endl;
    }else if(!type.compare("source")
	|| !type.compare("Source")
	|| !type.compare("SOURCE")
    ){
        sources.push_back(idx);
        //cout<<"sink "<<(int)idx<<endl;
    }else cout<<"Not match! "<<type<<endl;
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
    for(int i =0; i<sources.size();i++)
        cout<<(int)sources[i]<<" ";
    cout<<colorCyan<<" Sumideros: "<<colorReset;
    for(int i =0; i<sinks.size();i++)
        cout<<(int)sinks[i]<<" ";
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

/* A utility function to reverse a string  */
void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        swap(*(str+start), *(str+end));
        start++;
        end--;
    }
}

// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;

    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }

    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'A' : rem + '0';
        num = num/base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str, i);

    return str;
}

/*
    EOF
*/
