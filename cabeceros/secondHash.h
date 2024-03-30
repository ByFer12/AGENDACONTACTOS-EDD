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
    static constexpr double FACTOR_CARGA2=0.6;



private:


    int hashing(const string&clave){
        cout<<"adios"<<endl;
        int indice=0;
        cout<<"adios2"<<endl;
        for (char c:clave){
            cout<<"adios3"<<endl;
            indice+=c;
        }
        cout<<"adios4"<<endl;
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
    void insertar(const string&claveee, arbolAVL<string>*arbol){
         if(static_cast<double>(elementos)/tamanio>=FACTOR_CARGA2){
            reHashing();
        }

        int posicion=hashing(claveee);
        while (contactos[posicion].dato!=""){
            posicion=(posicion+1)%tamanio;
        }
        contactos[posicion]={claveee,arbol};
        ++elementos;   

    }
    void saludar(){
        cout<<"hola desde segunda tabla"<<endl;
    }
    
    arbolAVL<string>* buscar(const string&datoo){
        int posicionn=hashing(datoo);
        cout<<"hols"<<endl;
        while ((contactos[posicionn].dato!="") && (contactos[posicionn].dato!=datoo))
        {
            posicionn=(posicionn+1)%tamanio;
        }
        cout<<"hols2"<<endl;
        if(contactos[posicionn].dato==datoo){
            cout<<"hols3"<<endl;
            return contactos[posicionn].arbolString;
        }else{
            return nullptr;
        }
        
    }



};


#endif