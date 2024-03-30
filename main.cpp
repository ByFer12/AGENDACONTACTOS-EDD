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
void crearContacto();
void menu();
void prueba();


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

                crearContacto();
                
            break;
            case 3:

                prueba();

                break;
        
        default:

            break;
        }

        cin.clear();

    } while (opcion!=7);
    
}

void crearGrupo(){
            cout<<"\n\tEjemplo de comando: (ADD NEW-GROUP clientes FIELDS (nombre STRING, apellido STRING, celular INTEGER);)\n"<<endl;
            cout<<"Ingrese el comando para crear el nombre del grupo: ";
            getline(cin,ent);
            
            en.entradaGrupo(ent);
            cout<<"Datos ingresados: "<<endl;
                for (const string&dato:datos) {
                    cout<<"Datos: "<<dato<<endl;
                }
            cout<<"Nombre del grupo--: "<<nombreGrupo<<endl;
            tabla1.insertar(nombreGrupo,&tabla2);
    //cin.ignore(1000,'\n');

            cout<<"creando segunda tablas"<<endl;
            for (const string &dato:datos){
                arbolAVL<string>arbol;
                tabla2.insertar(dato,&arbol);
            }

            cout<<"Tablas creadas correctamente";

           tabla1.buscar("clientes");

                    
            
}

void crearContacto(){
    cout<<"\n\tEjemplo de comando: (ADD CONTACT IN amigos FIELDS (Pedro, Alvarez, 12345678, 02-05-1998);)\n"<<endl;
    cout<<"Ingrese el comando para crear el contacto: ";
    getline(cin,ent);
    en.entradaContactos(ent);

}
void prueba(){
    string hola;
    cout<<"Ingrese el nombre del grupo a buscar: ";
    cin>>hola;
    cout<<"\nLo que aparecio fue:-> "<<tabla1.buscar( hola)<<endl;
}







