#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <algorithm>
#include <fstream>
using namespace std;

template <typename T>
struct nodoArbol {
    T dato;
    int altura;
    nodoArbol<T>* izquierda;
    nodoArbol<T>* derecha;

 

    nodoArbol(const T& dato):dato(dato), altura(1), izquierda(nullptr), derecha(nullptr) {}
};

template <typename T>
class arbolAVL {
private:
    nodoArbol<T>* raiz;

    nodoArbol<T>* insertarNodo(nodoArbol<T>* nodo, const T& dato);
    nodoArbol<T>* buscarNodo(nodoArbol<T>* nodo, const T& dato);
    nodoArbol<T>* rotarDerecha(nodoArbol<T>* nodo);
    nodoArbol<T>* rotarIzquierda(nodoArbol<T>* nodo);
    int getAltura(nodoArbol<T>* nodo);
    int getBalance(nodoArbol<T>* nodo);
    nodoArbol<T>* balancear(nodoArbol<T>* nodo);
    void eliminarNodos(nodoArbol<T>*nodo);
    void imprimirPrueba(nodoArbol<T>*nodo);
    void graficarNodo(nodoArbol<T>*nodo, ofstream& archivoDOT);

public:
    arbolAVL() : raiz(nullptr) {}
    ~arbolAVL() {
        
        eliminarNodos(raiz);
    }

    void insertar(const T& dato);
    void buscar(const T& dato);
    void imprimir();
    void graficarArbol(const string&nombreArchivo);

};


    // Definiciones de las funciones miembro de la clase arbolAVL
    template <typename T>
    int arbolAVL<T>::getAltura(nodoArbol<T>* nodo) {
        if (nodo == nullptr) {
            return 0;
        }
        return nodo->altura;
    }

    template <typename T>
    int arbolAVL<T>::getBalance(nodoArbol<T>* nodo) {
        if (nodo == nullptr) {
            return 0;
        }
        return getAltura(nodo->izquierda) - getAltura(nodo->derecha);
    }

    template <typename T>
    nodoArbol<T>* arbolAVL<T>::rotarDerecha(nodoArbol<T>* nodo) {
        nodoArbol<T>* newRoot = nodo->izquierda;
        nodoArbol<T>* temp = newRoot->derecha;
        newRoot->derecha = nodo;
        nodo->izquierda = temp;
        nodo->altura =max(getAltura(nodo->izquierda), getAltura(nodo->derecha)) + 1;
        newRoot->altura =max(getAltura(newRoot->izquierda), getAltura(newRoot->derecha)) + 1;
        return newRoot;
    }

    template <typename T>
    nodoArbol<T>* arbolAVL<T>::rotarIzquierda(nodoArbol<T>* nodo) {
        nodoArbol<T>* newRoot = nodo->derecha;
        nodoArbol<T>* temp = newRoot->izquierda;
        newRoot->izquierda = nodo;
        nodo->derecha = temp;
        nodo->altura= max(getAltura(nodo->izquierda), getAltura(nodo->derecha)) + 1;
        newRoot->altura =max(getAltura(newRoot->izquierda), getAltura(newRoot->derecha)) + 1;
        return newRoot;
    }

    template <typename T>
    nodoArbol<T>* arbolAVL<T>::balancear(nodoArbol<T>* nodo) {
        if (nodo == nullptr) {
            return nullptr;
        }
        nodo->altura= max(getAltura(nodo->izquierda), getAltura(nodo->derecha)) + 1;
        int balance = getBalance(nodo);

        // Rotaciones
        if (balance > 1) {
            if (getBalance(nodo->izquierda) < 0) {
                nodo->izquierda = rotarIzquierda(nodo->izquierda);
            }
            return rotarDerecha(nodo);
        } else if (balance < -1) {
            if (getBalance(nodo->derecha) > 0) {
                nodo->derecha = rotarDerecha(nodo->derecha);
            }
            return rotarIzquierda(nodo);
        }
        return nodo;
    }

    template <typename T>
    nodoArbol<T>* arbolAVL<T>::insertarNodo(nodoArbol<T>* nodo, const T& dato) {
        if (nodo == nullptr) {
            return new nodoArbol<T>(dato);
        }
        if (dato < nodo->dato) {
            nodo->izquierda = insertarNodo(nodo->izquierda, dato);
        } else if (dato >= nodo->dato) {
            nodo->derecha = insertarNodo(nodo->derecha, dato);
        }
        return balancear(nodo);
    }

    template <typename T>
    nodoArbol<T>* arbolAVL<T>::buscarNodo(nodoArbol<T>* nodo, const T& dato) {
        if (nodo == nullptr || nodo->dato == dato) {
            return nodo;
        }
        if (dato < nodo->dato) {
            return buscarNodo(nodo->izquierda, dato);
        }
        return buscarNodo(nodo->derecha, dato);
    }
    
    template <typename T>
    void arbolAVL<T>::eliminarNodos(nodoArbol<T>*nodo){
        if(nodo!=nullptr){
            eliminarNodos(nodo->izquierda);
            eliminarNodos(nodo->derecha);
            delete nodo;
        }
    }
    template <typename T>
    void arbolAVL<T>::imprimirPrueba(nodoArbol<T>*nodo){
        if(nodo!=nullptr){
            imprimirPrueba(nodo->izquierda);
            cout<<nodo->dato<<" ";
            imprimirPrueba(nodo->derecha);
        }
        
    }

    template <typename T>
    void arbolAVL<T>::graficarNodo(nodoArbol<T>*nodo, ofstream& archivoDot){
        if (nodo == nullptr) {
                return;
            }

            // Utilizamos un identificador único para cada nodo basado en su dirección de memoria
            archivoDot << reinterpret_cast<uintptr_t>(nodo) << " [label=\"" << nodo->dato << "\"];" << endl;

            if (nodo->izquierda != nullptr) {
                archivoDot << reinterpret_cast<uintptr_t>(nodo) << " -> " << reinterpret_cast<uintptr_t>(nodo->izquierda) << ";" << endl;
                graficarNodo(nodo->izquierda, archivoDot);
            }

            if (nodo->derecha != nullptr) {
                // Si hay un nodo con el mismo valor, lo colocamos a la derecha del nodo actual
                if (nodo->derecha->dato == nodo->dato) {
                    archivoDot << reinterpret_cast<uintptr_t>(nodo) << " -> " << reinterpret_cast<uintptr_t>(nodo->derecha) << ";" << endl;
                } else {
                    archivoDot << reinterpret_cast<uintptr_t>(nodo) << " -> " << reinterpret_cast<uintptr_t>(nodo->derecha) << ";" << endl;
                }
                graficarNodo(nodo->derecha, archivoDot);
            }

    }

    //METODOS PUBLICOS

    template<typename T>
    void arbolAVL<T>::imprimir(){
        imprimirPrueba(raiz);
    }

    template <typename T>
    void arbolAVL<T>::insertar(const T& dato) {
        raiz = insertarNodo(raiz, dato);
    }

    template<typename T>
    void arbolAVL<T>::graficarArbol(const string& nombreArchivo){
        ofstream archivoDot(nombreArchivo + ".dot");

        archivoDot << "digraph Arbol {" << endl;
        graficarNodo(raiz, archivoDot);
        archivoDot << "}" << endl;

        archivoDot.close();

        // Llamar a dot para convertir el archivo DOT a PNG
        string comandoDot = "dot -Tpng " + nombreArchivo + ".dot -o " + nombreArchivo + ".png";
        system(comandoDot.c_str());
    }

template <typename T>
void arbolAVL<T>::buscar(const T& dato) {
    nodoArbol<T>* nodoEncontrado = buscarNodo(raiz, dato);
    if (nodoEncontrado != nullptr) {
        cout << "Valor encontrado: " << nodoEncontrado->dato << endl;
    } else {
        cout << "Valor no encontrado: " << dato << endl;
    }
}

#endif // AVL_TREE_H