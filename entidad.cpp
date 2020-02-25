/**
* entidad
* Objeto generico entidad contenedora
*
*
*   @Autor Julio César Gambandé
*   @Fecha 14 de febrero del 2020
*   @Email gambande.julio@gmail.com
*/

#include "entidad.h"

//constructor--------------------------------------------
Entidad::Entidad( const char* name, Entidad* padre):nombre(name){
  //valor();
  this->padre = padre;
}

Entidad::Entidad( string name, Entidad* padre):nombre(name){
  //valor();
  this->padre = padre;
}

Entidad::Entidad(){
  this->padre=NULL;
}

Entidad::Entidad(const char* name):nombre(name){
  this->padre=NULL;
}

//destructor--------------------------------------------
Entidad::~Entidad(){
  for(int i=0;i<hijos.size();i++)
    delete hijos[i];
}

// atributos---------------------------------------------
void Entidad::AddAtributo(string atributo, string valor){
  this->atributo.push_back(atributo);
  this->valor_atrib.push_back(valor);
}


bool Entidad::containAtributo(string atributo){
  for(int i=0; i<getCantAtributo(); i++){
    if(!getAtributoPorId(i).compare(atributo)){
      return true;
    }
  }
  return false;
}

string Entidad::getValorAtributo(string atributo){
  for(int i=0; i<getCantAtributo(); i++){
    if(!getAtributoPorId(i).compare(atributo)){
      return valor_atrib[i];
    }
  }
  return "";
}

int Entidad::getCantAtributo(void){
  return atributo.size();
}

string Entidad::getAtributoPorId(int id){
  return atributo[id];
}

//HIJOS--------------------------------------------
Entidad* Entidad::AddHijo(Entidad* obj){
  hijos.push_back(obj);
  obj->setPadre(this);
  return obj;
}

bool Entidad::containHijo(string name){
  for(int i=0; i<getCantHijos(); i++){
    if(getHijoPorId(i)->nombre == name){
      return true;
    }
  }
  return false;
}

Entidad* Entidad::getHijo(string name){
  for(int i=0; i<getCantHijos(); i++){
    if(getHijoPorId(i)->nombre == name){
      return hijos[i];
    }
  }
  return NULL;
}

int Entidad::getCantHijos(void){
  return hijos.size();
}

Entidad* Entidad::getHijoPorId(int id){
  return hijos[id];
}

// padre----------------------------------------------
Entidad* Entidad::getPadre(void){
  return padre;
}

void Entidad::setPadre(Entidad* newpadre){
  padre = newpadre;
}

// valor----------------------------------------------
string Entidad::getValor(int i){
  return valor[i];
}

void Entidad::AddValor(string val){
      this->valor.push_back(val);
}

//get
string Entidad::getname(void){
  return nombre;
}


//plot
void Entidad::plot(int level){
  int i=0;
  for(int i=0; i<level ;i++)cout<<" ";
  cout<<"OBJ: "<<nombre<<endl;
  level++;

  for(i=0;i<valor.size();i++){
    for(int i=0; i<level ;i++)cout<<" ";
    cout<<"VALOR: "<<valor[i]<<endl;
  }

  for(i=0;i<hijos.size();i++){
    hijos[i]->plot(level);
  }

}
