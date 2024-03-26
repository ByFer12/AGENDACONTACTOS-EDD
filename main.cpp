#include <iostream>
#include "cabeceros/arbolAVL.h"
int main(){
    arbolAVL<int> arbol1;
    arbol1.insertar(150);
    arbol1.insertar(100);
    arbol1.insertar(135);
    arbol1.insertar(130);;
    arbol1.insertar(95);
   // arbol1.insertar(95);
    //arbol1.insertar(56);
   // arbol1.insertar(155);
   // arbol1.insertar(160);
    //arbol1.buscar(135);
    arbol1.imprimir();
    arbol1.graficarArbol("ejemplo");
    

    return 0;
}