#include <iostream>
#include "cabeceros/arbolAVL.h"
#include "entrada/entrada.h"
#include "cabeceros/firstHash.h"
#include "cabeceros/secondHash.h"
#include <string>
#include <vector>
using namespace std;
entrada en;
string ent;
firstHash tabla1;
secondHash tabla2;
secondHash* tabla22=nullptr;
int cantAtributos=datos.size();

arbolAVL<string>*arbolll=nullptr;
void crearGrupo();
void menu();


int main(){
    
    menu();


    return 0;
}

void menu(){
    int opcion=0;
    do
    {
        cout<<"\tAGENDA DE CONTACTOS: "<<endl;
        cout<<"1--------Crear Grupo: "<<endl;
        cout<<"2--------Crear Contacto: "<<endl;
        cout<<"3--------Buscar Contacto: "<<endl;
        cout<<"4--------Graficar Arboles: "<<endl;
        cout<<"5--------Exportar contactos: "<<endl;
        cout<<"6--------Reportes: "<<endl;
        cout<<"7--------Salir: "<<endl;
        cout<<"Elija una opcion: ";
        cin>>opcion;
        cin.ignore(1000,'\n');
        switch (opcion){
        case 1:
       
            crearGrupo();

        
            break;
            case 2:

                
                
            break;
        
        default:

            break;
        }

        cin.clear();

    } while (opcion!=7);
    
}

void crearGrupo(){
            cout<<"\nEjemplo de comando: (ADD NEW-GROUP clientes FIELDS (nombre STRING, apellido STRING, celular INTEGER);)\n"<<endl;
            cout<<"Ingrese el comando para crear el nombre del grupo: ";
            getline(cin,ent);
            
            en.entradaGrupo(ent);
            cout<<"Datos ingresados: "<<endl;
                for (const string&dato:datos) {
                    cout<<"Datos: "<<dato<<endl;
                }
            cout<<"Nombre del grupo-: "<<nombreGrupo<<endl;
            tabla1.insertar(nombreGrupo,&tabla2);
    //cin.ignore(1000,'\n');

            cout<<"creando segunda tablas"<<endl;
            for (const string &dato:datos){
                arbolAVL<string>arbol;
                tabla2.insertar(dato,&arbol);
            }

            cout<<"Tablas creadas correctamente";
           
            string entr1;
            cout<<"Ingrese el grupo a buscar: ";
            cin>>entr1;
            tabla22=tabla1.buscar( entr1);
            cout<<"a"<<endl;
            cout<<tabla22<<endl;
            if(tabla22!=nullptr){

                arbolll=tabla22->buscar("nombre");
            }else{
                cout<<"La tabla esta vacia"<<endl;
            }
            //tabla22->saludar();
            cout<<"B"<<endl;
            if(arbolll!=nullptr){
                      arbolll->insertar("byron");
            cout<<"C"<<endl;
            arbolll->insertar("fernando");
            cout<<"D"<<endl;
            arbolll->insertar("eddy");
            cout<<"E"<<endl;
            arbolll->insertar("santiago");
            cout<<"F"<<endl;
            arbolll->insertar("karla");

            arbolll->buscar("karla");
            arbolll->graficarArbol("ejemplo2");
            }else{
                cout<<"El arbol no existe: "<<endl;
            }
                    
            
}







