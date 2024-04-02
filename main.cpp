#include <iostream>
#include "cabeceros/arbolAVL.h"
#include "entrada/entrada.h"
#include "cabeceros/firstHash.h"
#include "cabeceros/secondHash.h"
#include <string>
#include <vector>
#include<algorithm>
#include <filesystem>

using namespace std;
entrada en;
firstHash tabla1;


void buscarContacto();
void crearGrupo();
void crearContacto();
void menu();
void prueba();
void graficar();
void exportarGrupo();
int main(){
    
    menu();



    return 0;
}

void menu(){
   int opcion;
    std::string entrada;

    do {
        std::cout << "\tAGENDA DE CONTACTOS: \n";
        std::cout << "1--------Crear Grupo\n";
        std::cout << "2--------Crear Contacto\n";
        std::cout << "3--------Buscar Contacto\n";
        std::cout << "4--------Graficar Arboles\n";
        std::cout << "5--------Exportar contactos\n";
        std::cout << "6--------Reportes\n";
        std::cout << "7--------Salir\n";
        std::cout << "Elija una opción: ";

        // Leer la entrada del usuario como una cadena
        std::getline(std::cin, entrada);

        // Intentar convertir la entrada a un número entero
        try {
            opcion = std::stoi(entrada);

            // Verificar si la opción está dentro del rango deseado
            if (opcion < 1 || opcion > 7) {
                std::cout << "Error: Por favor, ingrese un número entre 1 y 7.\n";
                continue;  // Volver al inicio del bucle
            }

            switch (opcion) {
                case 1:
                    crearGrupo();
                    break;
                case 2:
                    crearContacto();
                    break;
                case 3:
                    buscarContacto();
                    break;
                case 4:
                    graficar();
                case 5:
                   exportarGrupo();
                    break;
                case 6:
                    std::cout << "Reportes\n";
                    // Lógica para generar reportes
                    break;
                case 7:
                    std::cout << "Saliendo del programa\n";
                    // Finalizar el programa
                    break;
            }
        } catch (...) {
            std::cout << "Error: Por favor, ingrese un número válido.\n";
        }
    } while (opcion != 7);
    
}

void crearGrupo(){
   
            string ent;
         
            cout<<"\n\tEjemploo de comando: (ADD NEW-GROUP clientes FIELDS (nombre STRING, apellido STRING, celular INTEGER);)\n"<<endl;
            cout<<"Ingrese el comando paraa crear el nombre del grupo: ";
            getline(cin,ent);
            
            en.entradaGrupo(ent);
            cout<<"Nombre del grupo--: "<<nombreGrupo<<endl;

            secondHash*tabla=tabla1.insertar(nombreGrupo);
            cout<<"referencia tabla2: "<<tabla<<endl;
   

            cout<<"creando segunda tabla"<<endl;
            for ( string &dato:datos){

                dato.erase(std::remove(dato.begin(), dato.end(), ' '), dato.end());
                cout<<dato<<endl;
                tabla->insertar(dato, new arbolAVL<string>());
            }
            

            cout<<"Tablas creadas correctamente";
            datos.clear();

          

                    
            
}

void crearContacto(){
    string ent;
    cout<<"\n\tEjemplo de comando: (ADD CONTACT IN clientes FIELDS (Pedro, Alvarez, 12345678);)\n"<<endl;
    cout<<"Ingrese el comando para crear el contacto: ";
    getline(cin,ent);
    en.entradaContactos(ent);
    cout<<"Datos del contactoo: "<<endl;
    
    for (const string&dato1:datosContacto) {
        cout<<"Datos: "<<dato1<<endl;
    }
    
    cout<<"Nombre grupo: "<<nombreGrupo<<endl;

    secondHash*tabla2=tabla1.buscar(nombreGrupo);
    cout<<"ATRIBUTOOOOS"<<endl;
    for (int i = 0; i < tabla2->atributos.size(); i++)
    {
        string atributo=tabla2->atributos[i];
       cout<<"Atributos: "<<tabla2->atributos[i]<<endl;

       arbolAVL<string>*arbol=tabla2->buscar(atributo);
       arbol->insertar(datosContacto[i],datosContacto);
 
    }
    datosContacto.clear();
}

void buscarContacto(){
    string ent;
    cout<<"\n\tEjemplo de comando: (FIND CONTACT IN clientes CONTACT-FIELD apellido=alvarez;)\n"<<endl;
    cout<<"Ingrese el comando para buscar el contacto: ";
    getline(cin,ent);
    en.buscarContacto(ent);
    cout<<"El nombre del grupo ess: "<<nombreGrupo<<endl;
    secondHash*tabla2=tabla1.buscar(nombreGrupo);
    arbolAVL<string>*arbol=tabla2->buscar(nombreCampo);
    arbol->buscar(valorCampo);

}

void exportarGrupo(){
    string grupo;
    cout<<"DEBES ESCRIBIR EL NOMBRE DE GRUPO A EXPORTAR"<<endl;
    cout<<"Lista de grupos creados: "<<endl;
    tabla1.mostrarClaves();
    cout<<"Escribe el nombre del grupo a exportarr: ";
    cin>>grupo;
    secondHash*tabla2=tabla1.buscar(grupo);
    if(tabla2!=nullptr){
        string atributo=tabla2->atributos[1];
        if(atributo!=""){

        arbolAVL<string>*arbol=tabla2->buscar(atributo);
        arbol->exportarArbol(grupo);
        }else{
            cout<<"Aun no hay contactos insertados."<<endl;
        }
    }else{
        cout<<"el Grupo no existe, ingrese un grupo existente: "<<endl;
    }
    
}

void graficar(){
    string graf;
    cout<<"Ingrese el grupo a graficar: ";
    cin>>graf;
    secondHash*tabla2=tabla1.buscar(graf);
    for(const string&d:tabla2->atributos){
        cout<<"Atributos: "<<d<<endl;
        arbolAVL<string>*arbol=tabla2->buscar(d);
        cout<<"Ingrese el nombre de la imagen para el arbol de "<<d<<" ";
        cin>>graf;
        arbol->graficarArbol(graf);
    }
}










