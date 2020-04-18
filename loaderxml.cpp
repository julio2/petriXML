/**
* LoaderXML
* cargador de archivo XML
*
*
*   @Autor Julio César Gambandé
*   @Fecha 15 de febrero del 2020
*   @Email gambande.julio@gmail.com
*/


#include "loaderxml.hpp"



LoaderXML::LoaderXML(){

}

void LoaderXML::open(string archivo){
  ifstream input;
  string buffer;
  input.open(archivo);
  Entidad* punta;
  string cadena;
  string cadena2;
  bool fin=false;
  bool start=false;
  int j;
  cout<<archivo<<endl;

  enum{
    CH, //Crea Hijo y asigna padre
    T,  //Etapa inetermedia en la busqueda de atributos
    V,  //Copia valor
    CP, //Compara si el cierre es el mismo que el nombre
    CN, //Carga valor y Copia nombre de objeto
    A,  //Copia nombre atributo
    VA, //Copia valor de atributo
    AA, //Carga atributo con su valor
    VP, //Vuelve al padre
    CHU,//Crea hijo unico
    CON,//Compara nombre
    Z,  //guarda valor de atributo
  }estado = V;

  root = new Entidad("root");
  punta = root;
  bool firs= true;

  while(!input.eof()){
    string buffer;
    input>>buffer;
    buffer.push_back(' ');

    j=0;
    while(buffer[j] && !start){
      if(buffer[j]== '>' && buffer[j-1]=='?') {
        start= true;
        j++;
        break;
      }
      j++;
    }

    if(start){
      for(int i=j; i<buffer.size();i++){
        switch (estado) {
          case V:
            if(buffer[i] == ' ' && firs){
              ;//nada
            }else{
                firs= false;
                if(buffer[i] == '<'){
                  if(cadena.size()>0)punta->AddValor(cadena);
                  cadena.clear();
                  firs=true;
                  estado = CN;
                }
                else{
                  cadena.push_back(buffer[i]);
                }
              }
              break;
          case CP:
            if(buffer[i] == '>'){
              if(cadena == punta->getname()){
                punta=punta->getPadre();
                cadena.clear();
                firs= true;
                estado= V;
              }else{
                cout<<"ERROR: Se esperaba el cierre de la etiqueta "<<punta->getname()<<endl;//ERROR
                return;
              }
            }else{
              cadena.push_back(buffer[i]);
            }
            break;
          case CN:
                if((buffer[i] == '/') && firs){
                  cadena.clear();
                  estado= CP;
                  break;
                }else{
                  firs=false;
                }
                if((buffer[i-1] == '/') && (buffer[i] == '>'))
                {
                  if(cadena == punta->getPadre()->getname()){
                    punta=punta->getPadre();
                  }else
                    punta->AddHijo(new Entidad(cadena,punta));
                  i++;
                  cadena.clear();
                  firs= true;
                  estado= V;
                } else if(buffer[i] == '>'){
                  punta=punta->AddHijo(new Entidad(cadena,punta));
                  cadena.clear();
                  firs= true;
                  estado = V;
                }else if(buffer[i] == ' '){
                  punta=punta->AddHijo(new Entidad(cadena,punta));
                  cadena.clear();
                  estado = T;
                }else if(buffer[i] == '/'){
                  ;//nada
                }else{
                  cadena.push_back(buffer[i]);
                }

                break;
          case T:
              if((buffer[i-1] == '/') && (buffer[i] == '>')){
                i++;
                punta=punta->getPadre();
                firs= true;
                estado = V;
              }else if(buffer[i] == '>'){
                cadena.clear();
                firs= true;
                estado = V;
              }else if(buffer[i] == ' ' || buffer[i] == '/'){
                ;//nada
              }else{
                cadena.clear();
                cadena.push_back(buffer[i]);
                estado = A;
              }
              break;
          case A:
              if((buffer[i] == '=') && (buffer[i+1] == '\"')){
                i++;
                cadena2.clear();
                estado = VA;
              }else if((buffer[i-1] == '/') && (buffer[i] == '>')){
                i++;
                punta->AddAtributo(cadena,NULL);
                cadena.clear();
                punta=punta->getPadre();
                firs= true;
                estado = V;
              }else if(buffer[i] == '>'){
                punta->AddAtributo(cadena,NULL);
                cadena.clear();
                firs= true;
                estado = V;
              }else if(buffer[i] == ' '){
                punta->AddAtributo(cadena,NULL);
                cadena.clear();
                estado = T;
              }else if(buffer[i] == '/'){
                ;//nada
              }
              else{
                cadena.push_back(buffer[i]);
              }
              break;
          case VA:
              if(buffer[i] == '\"'){
                estado = Z;
                punta->AddAtributo(cadena,cadena2);
                cadena2.clear();
              }else{
                cadena2.push_back(buffer[i]);
              }
              break;
          case Z:
              if((buffer[i] == '>') && (buffer[i-1] == '/')){
                i++;
                punta=punta->getPadre();
                cadena.clear();
                firs= true;
                estado = V;
              }else if(buffer[i] == '>'){
                cadena.clear();
                firs= true;
                estado = V;
              }else if(buffer[i] == ' ' || buffer[i] == '/'){
                cadena.clear();
                estado = T;
              }else{
                cout<<"ERROR: Hubo un error en los atributos del objeto "<<punta->getname()<<endl;
              }
              break;


          }
        }
      }

  }

cout<<"termino!"<<endl;

}

void LoaderXML::plot(void){
    root->plot(0);
}

Entidad* LoaderXML::getRoot(void){
  return root;
}
