#include <iostream>
#include <string>
#include "arbolAVL.h"
#include <vector>
using namespace std;
#ifndef HASH_SECOND
#define HASH_SECOND

struct Contacto
{
    string dato;
    arbolAVL<string>*arbolString;

};

class secondHash{
    Contacto* contactos;
    int tamanio=5;
    int elementos;
    double FACTOR_CARGA2=0.6;



private:


    int hashing(const string&clave){

        int indice=0;

        for (char c:clave){

            indice+=c;
        }
         return indice%tamanio;        
    }

    void reHashing(){
        int newSize=tamanio*2;
        Contacto* newContactos=new Contacto[newSize];
        for (int i = 0; i < newSize; i++){
           newContactos[i]={"",nullptr};
        }
        for (int i = 0; i < tamanio; i++){
            if(contactos[i].dato!=""){
                int indice=hashing(contactos[i].dato)%newSize;

                while (newContactos[indice].dato!=""){//resolucion de colisiones               {
                    indice=(indice+1)%newSize;
                }

                newContactos[indice]=contactos[i];
                
            }
        }

        delete [] contactos;
        contactos=newContactos;
        tamanio=newSize;    
    }
public:
    vector<string> atributos;
    secondHash(){

        contactos=new Contacto[tamanio];
        elementos=0;
        for (int i = 0; i < tamanio; i++){
           contactos[i]={""};
        }
        

    }
    ~secondHash(){
        delete[] contactos;
    }

    void setTamanio(int tam){
        tamanio=tam;
    }
    void insertar(const string&clave, arbolAVL<string>*arbol){
         if(static_cast<double>(elementos/tamanio)>=FACTOR_CARGA2){
            reHashing();
        }

        int posicion=hashing(clave);
        while (contactos[posicion].dato!=""){
            posicion=(posicion+1)%tamanio;
        }
        atributos.push_back(clave);
        contactos[posicion]={clave,arbol};
        ++elementos;   

    }
    int getTamanio(){
        return tamanio;
    }

    const Contacto& getContacto(int indice)const{
        return contactos[indice];
    }
    bool esVacio(int indice)const{
        return contactos[indice].dato.empty();
    }
    
    arbolAVL<string>* buscar(const string&datoo){
        int posicionn=hashing(datoo);
        while ((contactos[posicionn].dato!="") && (contactos[posicionn].dato!=datoo))
        {
            posicionn=(posicionn+1)%tamanio;
        }
        if(contactos[posicionn].dato==datoo){
            return contactos[posicionn].arbolString;
        }else{
            return nullptr;
        }
        
    }



};


#endif