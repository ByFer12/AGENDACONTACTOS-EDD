#include <iostream>
#include <string>
#include "secondHash.h"
using namespace std;
#ifndef HASH_FRIST
#define HASH_FRIST


struct Valores{

    string clave;
    secondHash *valor;
};

class firstHash
{
private:
    static const int TAMANIO=5;
    static constexpr double FACTOR_CARGA=0.6;
    Valores* valores;
    int tamanio;
    int elementos;

    int hash(const string &clave){
        int valHash=0;
        for(char c: clave){
            valHash+=c;
        }
        return valHash%TAMANIO;
    }

    void reHashing(){
        int nuevoTamanio=tamanio*2;
        Valores* nuevaTabla= new Valores [nuevoTamanio];
        for (int i=0;i<nuevoTamanio;i++){
            nuevaTabla[i]={"",nullptr};
                    }
        for (int i = 0; i < tamanio; i++){
            if(valores[i].clave!=""){
                int indice=hash(valores[i].clave)%nuevoTamanio;

                while (nuevaTabla[indice].clave!=""){//resolucion de colisiones               {
                    indice=(indice+1)%nuevoTamanio;
                }

                nuevaTabla[indice]=valores[i];
                
            }
        }

        delete [] valores;
        valores=nuevaTabla;
        tamanio=nuevoTamanio;      

    }

public:
    firstHash(){
        tamanio=TAMANIO;
        elementos=0;
        valores=new Valores[tamanio];
        for (int i = 0; i < tamanio; i++)
        {
            valores[i]={"",nullptr};
        }
        
    }
    ~firstHash(){
        delete[]valores;
    }

    secondHash* insertar(const string& clave){
        
        if(static_cast<double>(elementos)/tamanio>=FACTOR_CARGA){
            reHashing();
        }
        int posicion=hash(clave);
        while (valores[posicion].clave!=""){
            posicion=(posicion+1)%tamanio;
        }
        secondHash*valor=new secondHash();
        valores[posicion]={clave,valor};
        ++elementos;
        return valores[posicion].valor;     
    }

    secondHash* buscar(const string&clavee){
        int posicionn=hash(clavee);
        while (valores[posicionn].clave!=""&&valores[posicionn].clave!=clavee)
        {
            posicionn=(posicionn+1)%tamanio;
        }
        if(valores[posicionn].clave==clavee){
            return valores[posicionn].valor;
        }else{
            return nullptr;
        }
        
    }
    void mostrarClaves() {
        int index=0;
    for (int i = 0; i < tamanio; ++i) {
        if (valores[i].clave != "") {
            index++;
            cout << index<<". " << valores[i].clave << endl;
        }
    }
}
};
#endif