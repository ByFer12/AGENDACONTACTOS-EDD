#include <iostream>
#include "cabeceros/arbolAVL.h"
#include "utils/utils.h"
#include "cabeceros/firstHash.h"
#include "cabeceros/secondHash.h"
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <ctime>
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
void menuReportes();
void esperarEnter();
void escribirLog(const string &mensaje);
void cantDatosGrupo();
void cantDatosSistema();
void cantContactGroup();
int main()
{

    menu();

    return 0;
}

void menu()
{
    escribirLog("Sistema de contactos iniciado");
    int opcion;
    std::string entrada;

    do
    {
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
        try
        {
            opcion = std::stoi(entrada);

            // Verificar si la opción está dentro del rango deseado
            if (opcion < 1 || opcion > 7)
            {
                std::cout << "Error: Por favor, ingrese un número entre 1 y 7.\n";
                continue; // Volver al inicio del bucle
            }

            switch (opcion)
            {
            case 1:
                crearGrupo();
                esperarEnter();
                break;
            case 2:
                crearContacto();
                esperarEnter();
                break;
            case 3:
                buscarContacto();
                esperarEnter();
                break;
            case 4:
                graficar();
                esperarEnter();
            case 5:
                exportarGrupo();
                esperarEnter();
                break;
            case 6:
                menuReportes();
                break;
            case 7:
                std::cout << "Saliendo del programa\n";
                // Finalizar el programa
                break;
            }
        }
        catch (...)
        {
            std::cout << "Error: Por favor, ingrese un número válido.\n";
        }
    } while (opcion != 7);
}

void crearGrupo()
{

    string ent;

    cout << "\n\tEjemploo de comando: (ADD NEW-GROUP clientes FIELDS (nombre STRING, apellido STRING, celular INTEGER);)\n"
         << endl;
    cout << "Ingrese el comando paraa crear el nombre del grupo: ";
    getline(cin, ent);

    en.entradaGrupo(ent);

    secondHash *tabla = tabla1.insertar(nombreGrupo);

    cout << "creando segunda tabla" << endl;
    string atributos;
    for (string &dato : datos)
    {

        dato.erase(std::remove(dato.begin(), dato.end(), ' '), dato.end());
        atributos = atributos + dato + " ";
        tabla->insertar(dato, new arbolAVL<string>());
    }
    cout << "\tGrupo creado correctamente, presione enter para continuar" << endl;
    string info = "Creando grupo: " + nombreGrupo + " con atributos: " + atributos;
    escribirLog(info);
    datos.clear();
}

void crearContacto()
{
    string info;
    string ent;
    cout << "\n\tEjemplo de comando: (ADD CONTACT IN clientes FIELDS (Pedro, Alvarez, 12345678);)\n"
         << endl;
    cout << "Ingrese el comando para crear el contacto: ";
    getline(cin, ent);
    en.entradaContactos(ent);
    cout << "Datos del contactoo: " << endl;

    for (const string &dato1 : datosContacto)
    {
        cout << "Datos: " << dato1 << endl;
    }

    cout << "Nombre grupo: " << nombreGrupo << endl;
    string datosCon;
    secondHash *tabla2 = tabla1.buscar(nombreGrupo);

    if (tabla2 != nullptr)
    {
        if (tabla2->atributos.size()==datosContacto.size())
        {
            for (int i = 0; i < tabla2->atributos.size(); i++)
            {
                string atributo = tabla2->atributos[i];

                datosCon = datosCon + datosContacto[i] + " ";
                arbolAVL<string> *arbol = tabla2->buscar(atributo);
                arbol->insertar(datosContacto[i], datosContacto);
                info = "Contacto creado en grupo: " + nombreGrupo + " con los datos: " + datosCon;
            }
            cout << "\tContacto creado correctamente, presione enter para continuar" << endl;
        }else if(tabla2->atributos.size()>=datosContacto.size()){
            cout<<"\tLe asignaste mas atributos y le estas enviado pocos datos"<<endl;
        }else if(tabla2->atributos.size()<=datosContacto.size()){
             cout<<"\tLe asignaste menos atributos y le estas enviado mas datos"<<endl;
        }
    }
    else
    {
        cout << "\tEl grupo al que intenta agregar un contacto no existe" << endl;
        info = "Se intento insertar un contacto en un grupo que no existe";
    }

    escribirLog(info);
    datosContacto.clear();
}

void buscarContacto()
{
    string ent;
    cout << "\n\tEjemplo de comando: (FIND CONTACT IN clientes CONTACT-FIELD apellido=alvarez;)\n"
         << endl;
    cout << "Ingrese el comando para buscar el contacto: ";
    getline(cin, ent);
    en.buscarContacto(ent);

    secondHash *tabla2 = tabla1.buscar(nombreGrupo);
    if (tabla2 != nullptr)
    {

        arbolAVL<string> *arbol = tabla2->buscar(nombreCampo);
        if (arbol != nullptr)
        {

            arbol->buscar(valorCampo);
        }
        else
        {
            cout << "No hay ningun atributo con el campo " << nombreCampo << endl;
        }
    }
    else
    {
        cout << "El grupo no existe " << endl;
    }
    string info = "Valor " + valorCampo + " buscado en el grupo: " + nombreGrupo;
    escribirLog(info);
}

void exportarGrupo()
{
    string grupo;
    cout << "DEBES ESCRIBIR EL NOMBRE DE GRUPO A EXPORTAR" << endl;
    cout << "Lista de grupos creados: " << endl;
    tabla1.mostrarClaves();
    cout << "Escribe el nombre del grupo a exportarr: ";
    cin >> grupo;
    secondHash *tabla2 = tabla1.buscar(grupo);
    if (tabla2 != nullptr)
    {
        string atributo = tabla2->atributos[1];
        if (atributo != "")
        {

            arbolAVL<string> *arbol = tabla2->buscar(atributo);
            arbol->exportarArbol(grupo);
            cout << "Datos exportados exitosamente. " << endl;
        }
        else
        {
            cout << "Aun no hay contactos insertados." << endl;
        }
    }
    else
    {
        cout << "el Grupo no existe, ingrese un grupo existente: " << endl;
    }
    cout << "\nGrupo exportado correctamente" << endl;
    string info = "Exportando datos e informacion del grupo: " + grupo;
    escribirLog(info);
}

void graficar()
{
    string graf;
    cout << "Ingrese el grupo a graficar: ";
    cin >> graf;
    secondHash *tabla2 = tabla1.buscar(graf);
    for (const string &d : tabla2->atributos)
    {
        cout << "Atributos: " << d << endl;
        arbolAVL<string> *arbol = tabla2->buscar(d);
        cout << "Ingrese el nombre de la imagen para el arbol de " << d << " ";
        cin >> graf;
        arbol->graficarArbol(graf);
    }
}

void menuReportes()
{
    int opcion;
    std::string entrada;

    do
    {
        std::cout << "\tMENU REPORTES: \n";
        std::cout << "1--------Cantidad de datos por Grupo\n";
        std::cout << "2--------Cantidad de datos de todo el sistema\n";
        std::cout << "3--------Cantidad de Contactos con el mismo tipo de dato del campo de criterio de ordenamiento.\n";
        std::cout << "4--------Cantidad de Contactos por Grupo.\n";
        std::cout << "5--------Regresar\n";
        std::cout << "Elija una opción: ";

        // Leer la entrada del usuario como una cadena
        std::getline(std::cin, entrada);

        // Intentar convertir la entrada a un número entero
        try
        {
            opcion = std::stoi(entrada);

            // Verificar si la opción está dentro del rango deseado
            if (opcion < 1 || opcion > 7)
            {
                std::cout << "Error: Por favor, ingrese un número entre 1 y 6.\n";
                continue; // Volver al inicio del bucle
            }

            switch (opcion)
            {
            case 1:
                cantDatosGrupo();
                esperarEnter();
                break;
            case 2:
                cantDatosSistema();
                esperarEnter();
                break;
            case 3:
                esperarEnter();
                break;
            case 4:
                cantContactGroup();
                esperarEnter();
                break;
            case 5:
                std::cout << "Saliendo del programa\n";
                break;
            }
        }
        catch (...)
        {
            std::cout << "Error: Por favor, ingrese un número válido.\n";
        }
    } while (opcion != 5);
}

void cantDatosGrupo()
{
    tabla1.mostrarClaves2();
    cout << "Datos por cada grupo:" << endl;
    cout << "\n  Nombre del grupo    "
         << "Cantidad Datos" << endl;
    for (string &grupo : tabla1.grupos)
    {
        secondHash *tabla2 = tabla1.buscar(grupo);
        int tamanio = 0;
        string attr = tabla2->atributos[0];
        arbolAVL<string> *arbol = tabla2->buscar(attr);
        tamanio = arbol->cantidadDatos * tabla2->elementos;
        cout << "\n\t" << grupo << "             " << tamanio;
    }
    cout << "\nPresione enter para continuar: ";
    tabla1.grupos.clear();
}

void cantDatosSistema()
{
    tabla1.mostrarClaves2();
    cout << "Datos por cada grupo:" << endl;
    cout << "\n ";
    int tamanio = 0;
    for (string &grupo : tabla1.grupos)
    {
        secondHash *tabla2 = tabla1.buscar(grupo);
        string attr = tabla2->atributos[0];
        arbolAVL<string> *arbol = tabla2->buscar(attr);
        tamanio += arbol->cantidadDatos * tabla2->elementos;
    }
    cout << "\n\t"
         << "Todo el sistema tiene"
         << "              " << tamanio << " Datos" << endl;
    cout << "\nPresione enter para continuar: ";
    tabla1.grupos.clear();
}

void cantContactGroup()
{
    tabla1.mostrarClaves2();
    cout << "Cantidad de Contactos por cada grupo:" << endl;
    cout << "\n  Nombre del grupo    "
         << "Cantidad Contactos" << endl;
    for (string &grupo : tabla1.grupos)
    {
        secondHash *tabla2 = tabla1.buscar(grupo);
        int tamanio = 0;
        string attr = tabla2->atributos[0];
        arbolAVL<string> *arbol = tabla2->buscar(attr);
        tamanio = arbol->cantidadDatos;
        cout << "\n\t" << grupo << "             " << tamanio;
    }
    cout << "\nPresione enter para continuar: ";
    tabla1.grupos.clear();
}

void escribirLog(const string &mensaje)
{
    ofstream archivoLog("system.log", ios::app);
    if (archivoLog.is_open())
    {
        time_t tiempoActual = time(nullptr);
        archivoLog << "[" << ctime(&tiempoActual) << "]" << mensaje << endl;
        archivoLog.close();
    }
    else
    {
        cerr << "Error al abrir el archivo de log." << std::endl;
    }
}

void esperarEnter()
{
    // Mientras no se presione Enter, seguir leyendo caracteres
    while (std::cin.get() != '\n')
    {
        // No hacer nada
    }
}
