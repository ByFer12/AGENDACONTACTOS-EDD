#include <iostream>
#include <string>
#include <regex>
using namespace std;
vector<string> datos;
vector<string> datosContacto;
vector<string> tipos;
vector<string> busqueda;
string nombreGrupo;
string nombreCampo;
string valorCampo;
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
    void buscarContacto(string &entrada);
};

void entrada::entradaGrupo(string &entrada){
   
    regex regex_expresion("ADD\\s+NEW-GROUP\\s+([\\w]+)\\s+FIELDS\\s*\\(((?:[\\w\\s]+\\s+(?:STRING|INTEGER|DATE|CHAR)\\s*,?\\s*)+)\\);");
    smatch coincidencias;
    if(regex_match(entrada,coincidencias, regex_expresion)){
        nombreGrupo=coincidencias[1];
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
            dato1.erase(std::remove(dato1.begin(), dato1.end(), ' '), dato1.end());
            datos.push_back(dato1);
            dato2.erase(std::remove(dato2.begin(), dato2.end(), ' '), dato2.end());
            tipos.push_back(dato2);
            ++it;
        }   
    }else{
        cout<<"Expresion no valid: "<<endl;
    }
}

void entrada::entradaContactos(string &entrada){
    regex regex_expresion("ADD\\s+CONTACT\\s+IN\\s+([\\w]+)\\s+FIELDS\\s*\\(((?:[^()]+)\\));");
    smatch coincidencias;
    
    if(regex_match(entrada, coincidencias, regex_expresion)){
         nombreGrupo = coincidencias[1];
    

        string campos = coincidencias[2];
        regex regex_campo("([^,)]+)"); // Modificamos para que la captura excluya el paréntesis de cierre
        
        sregex_iterator it(campos.begin(), campos.end(), regex_campo);
        sregex_iterator end;

        cout << "Obteniendo datos de cada grupo: " << endl;
        while (it != end){
            smatch coincidencia = *it;
            string dato = coincidencia[1];
            dato.erase(std::remove(dato.begin(), dato.end(), ' '), dato.end());
            datosContacto.push_back(dato);
            ++it;
        }
    }else{
        cout << "Expresión no válida." << endl;
    }
}

void entrada::buscarContacto(string &entrada) {
    regex regex_expresion("FIND\\s+CONTACT\\s+IN\\s+([\\w]+)\\s+CONTACT-FIELD\\s+([^=]+)=([^;]+);");
    smatch coincidencias;

    if(regex_match(entrada, coincidencias, regex_expresion)){
        nombreGrupo = coincidencias[1];
        nombreCampo = coincidencias[2];
        valorCampo = coincidencias[3];
        cout<<"Valor Campo= "<<valorCampo<<endl;

        // Realizar la búsqueda del contacto en el grupo 'nombreGrupo' con el campo 'nombreCampo' y el valor 'valorCampo'
        // Aquí deberías implementar la lógica para buscar el contacto en función de los parámetros proporcionados

        cout << "Búsqueda realizada en el grupo: " << nombreGrupo << endl;
        cout << "Campo de búsqueda: " << nombreCampo << endl;
        cout << "Valor buscado: " << valorCampo << endl;
    } else {
        cout << "Expresión no válida." << endl;
    }
}





#endif