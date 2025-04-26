#include <iostream>
#include <string>
#include <limits> // Para limpiar el buffer
using namespace std;

struct Nodo {
    int dato;
    Nodo* izquierda;
    Nodo* derecha;

    Nodo(int val) : dato(val), izquierda(nullptr), derecha(nullptr) {}
};

int pedirEntero(string mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;

        if (cin.fail()) {
            cout << "Entrada inválida. Debe ser un número entero.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
    }
}

void insertarNodo(Nodo*& raiz, int nivelActual, int nivelMaximo) {
    if (nivelActual > nivelMaximo) return;

    int valor = pedirEntero("Ingrese el valor para el nodo en el nivel " + to_string(nivelActual) + ": ");
    raiz = new Nodo(valor);

    if (nivelActual < nivelMaximo) {
        while (raiz->izquierda == nullptr || raiz->derecha == nullptr) {
            if (raiz->izquierda == nullptr && raiz->derecha == nullptr) {
                // Ambos hijos están vacíos: preguntamos
                cout << "¿Quieres insertar en izquierda o derecha de " << valor << "? (i o d): ";
                char direccion;
                cin >> direccion;
                direccion = tolower(direccion);

                if (direccion == 'i') {
                    insertarNodo(raiz->izquierda, nivelActual + 1, nivelMaximo);
                } else if (direccion == 'd') {
                    insertarNodo(raiz->derecha, nivelActual + 1, nivelMaximo);
                } else {
                    cout << "Entrada inválida. Intenta otra vez.\n";
                }
            }
            else if (raiz->izquierda == nullptr) {
                // Solo falta el hijo izquierdo
                cout << "Debes insertar en el hijo izquierdo de " << valor << ":\n";
                insertarNodo(raiz->izquierda, nivelActual + 1, nivelMaximo);
            }
            else if (raiz->derecha == nullptr) {
                // Solo falta el hijo derecho
                cout << "Debes insertar en el hijo derecho de " << valor << ":\n";
                insertarNodo(raiz->derecha, nivelActual + 1, nivelMaximo);
            }
        }
    }
}

void mostrarArbol(Nodo* raiz, int espacio = 0, int nivelEspacio = 6, string prefijo = "") {
    if (raiz == nullptr) return;

    espacio += nivelEspacio;

    mostrarArbol(raiz->derecha, espacio, nivelEspacio, "|--");
    cout << string(espacio - nivelEspacio, ' ') << prefijo << raiz->dato << endl;
    mostrarArbol(raiz->izquierda, espacio, nivelEspacio, "|--");
}

int main() {
    Nodo* raiz = nullptr;

    int nivelMaximo = pedirEntero("Ingrese el nivel máximo del árbol: ");
    insertarNodo(raiz, 1, nivelMaximo);

    cout << "\nRepresentación jerárquica del árbol con líneas:\n";
    mostrarArbol(raiz);

    return 0;
}
