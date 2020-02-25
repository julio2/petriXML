/**
* entidad
* Objeto generico entidad contenedora
*
*
*   @Autor Julio César Gambandé
*   @Fecha 14 de febrero del 2020
*   @Email gambande.julio@gmail.com
*/
#define TAB "    "



#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Entidad{

    string nombre;

    vector<string> atributo;
    vector<string> valor_atrib;
    vector<string> valor;

    vector<Entidad*> hijos;



    Entidad* padre;

public:
    Entidad(const char*,Entidad*);
    Entidad(string,Entidad*);
    Entidad();
    Entidad(const char*);
    ~Entidad();

    void AddAtributo(string atributo, string valor);
    bool containAtributo(string atributo);
    string getValorAtributo(string atributo);
    int getCantAtributo(void);
    string getAtributoPorId(int);

    Entidad* AddHijo(Entidad*);
    bool containHijo(string name);
    Entidad* getHijo(string name);
    int getCantHijos(void);
    Entidad* getHijoPorId(int);

    Entidad* getPadre(void);
    void setPadre(Entidad*);

    string getValor(int);
    void AddValor(string);

    string getname(void);

    void plot(int);
};
