#include "quiensabe.h"

#define QUIENSABE_NUMERO_LUGARES 4
#define QUIENSABE_NUMERO_TRANSICIONES 3

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

struct Petri_quiensabe{
  struct transicion Trans[QUIENSABE_NUMERO_TRANSICIONES];
  struct lugar Lugs[QUIENSABE_NUMERO_LUGARES];
};

struct Petri_quiensabe _Petriquiensabe={
  {//transiciones
    {0,{0x00,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0x02,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}},
    {0,{0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}},
    {0,{0x02,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}}
  },
  { //Lugares
    {0,"P0",1},
    {0,"P1",1},
    {0,"P2",0},
    {0,"P3",0}
  }
};

void quiensabe_Reset(){
  unsigned char i;
  for(i=0; i<QUIENSABE_NUMERO_LUGARES; i++)
    _Petriquiensabe.Lugs[i].value=_Petriquiensabe.Lugs[i].marcaInicial;
}

void quiensabe_Step(){
  unsigned char i,j;
  char sensibilizada = 1;
  for(i=0; i<QUIENSABE_NUMERO_TRANSICIONES; i++){
    sensibilizada = 1;
    for(j=0;j<8 && (_Petriquiensabe.Trans[i].source[j] != 0xFF);j++){
      if(!_Petriquiensabe.Lugs[_Petriquiensabe.Trans[i].source[j]].value)
        sensibilizada=0;
    }
    if(sensibilizada && _Petriquiensabe.Trans[i].value){
      for(j=0;j<8 && (_Petriquiensabe.Trans[i].sink[j] != 0xFF);j++){
        _Petriquiensabe.Lugs[_Petriquiensabe.Trans[i].sink[j]].value=1;
      }
    }
  }
}

unsigned char quiensabe_strGetOput(char* nombre){
  unsigned char i;
  for(i=0; i<QUIENSABE_NUMERO_LUGARES; i++){
    if(!strcmp(nombre,_Petriquiensabe.Lugs[i].nombre))
      return Petriquiensabe.Lugs[i].value;
  }
}

void quiensabe_SetInput(unsigned char* arry){
  unsigned char i;
  for(i=0; i<QUIENSABE_NUMERO_TRANSICIONES; i++){
    _Petriquiensabe.Trans[i].value=arry[i];
  }
}

