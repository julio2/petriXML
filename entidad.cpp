/**
* entidad
* Objeto generico entidad contenedora
*
*
*   @Autor Julio César Gambandé
*   @Fecha 14 de febrero del 2020
*   @Email gambande.julio@gmail.com
*/

#include "entidad.hpp"

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
    int sep = name.find("/");
    string nomb;
    string residuo;
    residuo.clear();
    if(sep > 0){
        nomb = name.substr(0,sep);
        residuo = name.substr(sep + 1);
    }
    else{
        nomb = name;
    }

  for(int i=0; i<getCantHijos(); i++){
    if(getHijoPorId(i)->nombre == nomb){
        if(residuo.size() == 0)
            return hijos[i];
        else
            return hijos[i]->getHijo(residuo);
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

    int i,j;
    for(i=0; i<level ;i++)cout<<" ";

    cout<<
    colorRed<<"OBJ: "<<
    colorReset<<nombre<<
    colorMagenta<<" DIR: "<<
    colorOrange<<"0x"<<hex<<uppercase<<(reinterpret_cast<short*>(this))[0]<<
    colorReset<<endl;

    level++;

    for(i=0;i<valor.size();i++){
        for(j=0; j<level ;j++)cout<<" ";
        cout<<colorGreen<<"VALOR: "<<colorReset<<valor[i]<<endl;
    }


    for(i=0;i<hijos.size();i++){
        hijos[i]->plot(level);
    }

}

//devuelve un arreglo de todos los objetos encontrados con el nombre dado
Entidad** Entidad::find(string objName){
    int i,j;
    Entidad** encontrados;
    Entidad** viejos;
    Entidad** nuevos;
    int n,m;
    encontrados = new Entidad*;
    *encontrados = 0;
    for(i=0;i<hijos.size();i++){
        nuevos = hijos[i]->find(objName);
        for(n=0; encontrados[n]; n++);
        for(m=0; nuevos[m]; m++);
        if(m>0){
            viejos = encontrados;
            encontrados = new Entidad*[n+m+1];
            for(j=0; j<n; j++)encontrados[j]=viejos[j];
            delete[] viejos;
            for(j=0; j<m; j++)encontrados[j+n]=nuevos[j];
            delete[] nuevos;
            encontrados[n+m]=0;
        }
    }
    if(nombre == objName){
        for(n=0; encontrados[n]; n++);
        viejos = encontrados;
        encontrados = new Entidad*[n+2];
        for(j=0; j<n; j++)encontrados[j]=viejos[j];
        delete[] viejos;
        encontrados[n]=this;
        encontrados[n+1]=0;
    }
    return encontrados;
}
