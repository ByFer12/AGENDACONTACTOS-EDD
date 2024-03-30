#include <iostream>
#include <string>
#include <regex>
using namespace std;
vector<string> datos;
vector<string> datosContacto;
vector<string> tipos;
string nombreGrupo;
#ifndef ENTRADA
#define ENTRADA
class entrada
{
private:
    /* data */
public:
    entrada(){}
    ~entrada(){}

    void entradaGrupo(string &entrada);
    void entradaContactos(string &entrada);
};

void entrada::entradaGrupo(string &entrada){
   
    regex regex_expresion("ADD\\s+NEW-GROUP\\s+([\\w]+)\\s+FIELDS\\s*\\(((?:[\\w\\s]+\\s+(?:STRING|INTEGER|DATE|CHAR)\\s*,?\\s*)+)\\);");
    smatch coincidencias;
    if(regex_match(entrada,coincidencias, regex_expresion)){
        nombreGrupo=coincidencias[1];
        cout<<"Nombre del grupo "<<nombreGrupo<<endl;

        string campos= coincidencias[2];
        regex regex_campo("([\\w\\s]+)\\s+(STRING|INTEGER|DATE|CHAR)");
        sregex_iterator it(campos.begin(),campos.end(), regex_campo);
        sregex_iterator end;

        cout<<"Obteniendo datos de cada grupo: "<<endl;
        while (it!=end)
        {
            smatch coincidencia=*it;
            string dato1=coincidencia[1];
            string dato2=coincidencia[2];
            datos.push_back(dato1);
            tipos.push_back(dato2);
            ++it;
        }
        

    }else{
        cout<<"Expresion no valid: "<<endl;
    }

}

void entrada::entradaContactos(string &entrada){

    regex regex_expresion("ADD\\s+CONTACT\\s+IN\\s+([\\w]+)\\s+FIELDS\\s*\\(((?:[\\w\\s]+\\s*,?\\s*)+)\\);");
    smatch coincidencias;
    if(regex_match(entrada,coincidencias, regex_expresion)){

        string campos= coincidencias[2];
        regex regex_campo("([\\w\\s]+)\\s+)");
        sregex_iterator it(campos.begin(),campos.end(), regex_campo);
        sregex_iterator end;

        cout<<"Obteniendo datos de cada grupo: "<<endl;
        while (it!=end)
        {
            smatch coincidencia=*it;
            string dato1=coincidencia[1];
            datosContacto.push_back(dato1);
            ++it;
        }


    }else{
        cout<<"Expresion no valid: "<<endl;
    }

}



#endif