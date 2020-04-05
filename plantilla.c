#include "petri@#\.c"

#define @\_NUMERO_LUGARES @nlug\
#define @\_NUMERO_TRANSICIONES @trans\

struct transicion{
  unsigned char value;
  unsigned char sources[8];
  unsigned char sinks[8];
};

struct lugar{
  unsigned char value;
  char nombre[5];
  unsigned char marcaInicial;
};

struct Petri@#\{
  struct transicion Trans[@\_NUMERO_TRANSICIONES];
  struct lugar Lugs[@\_NUMERO_LUGARES];
};

struct Petri@#\ _Petri@#\={
  {//trans
    @t\
  },
  { //Lugs
    @l\
  }
};

void @#\_Reset(){
  unsigned char i;
  for(i=0; i<@_NUMERO_LUGARES; i++)
    _Petri@#\.Lugs[i].value=_Petri@#\.Lugs[i].marcaInicial;
}

void @#\_Step(){
  unsigned char i,j;
  char sensibilizada = 1;
  for(i=0; i<@\_NUMERO_TRANSICIONES; i++){
    sensibilizada = 1;
    for(j=0;j<8 && (_Petri@#\.Trans[i].source[j] != 0xFF);j++){
      if(!_Petri@#\.Lugs[_Petri@#\.Trans[i].source[j]].value)
        sensibilizada=0;
    }
    if(sensibilizada && _Petri@#\.Trans[i].value){
      for(j=0;j<8 && (_Petri@#\.Trans[i].sink[j] != 0xFF);j++){
        _Petri@#\.Lugs[_Petri@#\.Trans[i].sink[j]].value=1;
      }
    }
  }
}

unsigned char @#\_strGetOput(char* nombre){
  unsigned char i;
  for(i=0; i<@\_NUMERO_LUGARES; i++){
    if(!strcmp(nombre,_Petri@#\.Lugs[i].nombre))
      return Petri@#\.Lugs[i].value;
  }
}

void @#\_SetInput(unsigned char* arry){
  unsigned char i;
  for(i=0; i<@\_NUMERO_TRANSICIONES; i++){
    _Petri@#\.Trans[i].value=arry[i];
  }
}
