#include <iostream>
#include <string>
using namespace std;

struct Nodo {
    char letra;
    Nodo* siguiente;
};

// Funciones para la pila (LIFO)
void insertarPila(Nodo*& pila, char letra) {
    Nodo* nuevo = new Nodo();
    nuevo->letra = letra;
    nuevo->siguiente = pila;
    pila = nuevo;
}

void mostrarPila(Nodo* pila) {
    cout << "Resultado como Pila (LIFO): ";
    while (pila != nullptr) {
        cout << pila->letra;
        pila = pila->siguiente;
    }
    cout << endl;
}

// Funciones para la cola (FIFO)
void insertarCola(Nodo*& frente, Nodo*& fin, char letra) {
    Nodo* nuevo = new Nodo();
    nuevo->letra = letra;
    nuevo->siguiente = nullptr;
    if (frente == nullptr) {
        frente = nuevo;
    } else {
        fin->siguiente = nuevo;
    }
    fin = nuevo;
}

void mostrarCola(Nodo* frente) {
    cout << "Resultado como Cola (FIFO): ";
    while (frente != nullptr) {
        cout << frente->letra;
        frente = frente->siguiente;
    }
    cout << endl;
}

void liberarMemoria(Nodo*& lista) {
    while (lista != nullptr) {
        Nodo* temp = lista;
        lista = lista->siguiente;
        delete temp;
    }
}

// Programa principal
int main() {
    string palabra;
    char opcion;
    char repetir;

    do {
        cout << "Ingrese una palabra o frase: ";
        getline(cin, palabra);

        cout << "¿Desea verla como Pila (p) o como Cola (c)? ";
        cin >> opcion;

        if (opcion == 'p' || opcion == 'P') {
            Nodo* pila = nullptr;
            for (char c : palabra) {
                insertarPila(pila, c);
            }
            mostrarPila(pila);
            liberarMemoria(pila);
        } else if (opcion == 'c' || opcion == 'C') {
            Nodo* frente = nullptr;
            Nodo* fin = nullptr;
            for (char c : palabra) {
                insertarCola(frente, fin, c);
            }
            mostrarCola(frente);
            liberarMemoria(frente);
        } else {
            cout << "Opción no válida. Use 'p' para pila o 'c' para cola." << endl;
        }

        cout << "¿Desea ingresar otra palabra o frase? (s/n): ";
        cin >> repetir;
        cin.ignore(); // ← Esta línea es clave para que getline funcione correctamente después
        cout << endl;

    } while (repetir == 's' || repetir == 'S');

    return 0;
}
