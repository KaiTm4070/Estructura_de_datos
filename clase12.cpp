#include <iostream>
#include <string>
#include <limits>
#include <stack>
#include <vector>
#include <cctype>
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

void mostrarArbol(Nodo* raiz, int espacio = 0, int nivelEspacio = 6, string prefijo = "") {
    if (raiz == nullptr) return;

    espacio += nivelEspacio;

    mostrarArbol(raiz->derecha, espacio, nivelEspacio, "|--");
    cout << string(espacio - nivelEspacio, ' ') << prefijo
         << (raiz->dato == 0 ? "[ ]" : "[" + to_string(raiz->dato) + "]") << endl;
    mostrarArbol(raiz->izquierda, espacio, nivelEspacio, "|--");
}

void crearArbolCompleto(Nodo*& raiz, int nivelActual, int nivelMaximo) {
    if (nivelActual > nivelMaximo) return;

    raiz = new Nodo(0);
    crearArbolCompleto(raiz->izquierda, nivelActual + 1, nivelMaximo);
    crearArbolCompleto(raiz->derecha, nivelActual + 1, nivelMaximo);
}

void recorridoInteractivo(Nodo* raiz) {
    if (raiz == nullptr) {
        cout << "El árbol no ha sido creado aún.\n";
        return;
    }

    Nodo* actual = raiz;
    stack<Nodo*> pila;

    while (true) {
        system("cls||clear");
        cout << "ÁRBOL ACTUAL:\n";
        mostrarArbol(raiz);

        cout << "\nNODO ACTUAL:\n";
        cout << "Valor: " << (actual->dato == 0 ? "VACÍO" : to_string(actual->dato)) << "\n\n";

        cout << "OPCIONES:\n";
        cout << "1. Llenar nodo actual\n";
        cout << "2. Ir al nodo izquierdo\n";
        cout << "3. Ir al nodo derecho\n";
        cout << "4. Volver al nodo padre\n";
        cout << "5. Terminar recorrido\n";

        int opcion = pedirEntero("Seleccione (1-5): ");
        switch (opcion) {
            case 1: {
                int valor = pedirEntero("Ingrese valor para el nodo (0 para vaciar): ");
                actual->dato = valor;
                break;
            }
            case 2:
                if (actual->izquierda != nullptr) {
                    pila.push(actual);
                    actual = actual->izquierda;
                } else {
                    cout << "No hay nodo izquierdo. Presione Enter para continuar...";
                    cin.get();
                }
                break;
            case 3:
                if (actual->derecha != nullptr) {
                    pila.push(actual);
                    actual = actual->derecha;
                } else {
                    cout << "No hay nodo derecho. Presione Enter para continuar...";
                    cin.get();
                }
                break;
            case 4:
                if (!pila.empty()) {
                    actual = pila.top();
                    pila.pop();
                } else {
                    cout << "Ya estás en la raíz. Presione Enter para continuar...";
                    cin.get();
                }
                break;
            case 5:
                return;
            default:
                cout << "Opción inválida. Presione Enter para continuar...";
                cin.get();
        }
    }
}

void buscarNumeroRecursivo(Nodo* nodo, int objetivo, string camino, vector<string>& rutas, int nivel) {
    if (nodo == nullptr) return;

    if (nodo->dato == objetivo) {
        rutas.push_back(camino + to_string(nodo->dato) + " (Nivel " + to_string(nivel) + ")");
    }

    if (nodo->izquierda != nullptr) {
        buscarNumeroRecursivo(nodo->izquierda, objetivo, camino + to_string(nodo->dato) + " -> (izquierda) ", rutas, nivel + 1);
    }
    if (nodo->derecha != nullptr) {
        buscarNumeroRecursivo(nodo->derecha, objetivo, camino + to_string(nodo->dato) + " -> (derecha) ", rutas, nivel + 1);
    }
}

void buscarNumero(Nodo* raiz) {
    if (raiz == nullptr) {
        cout << "El árbol no ha sido creado aún.\n";
        return;
    }

    int objetivo = pedirEntero("Ingrese el número que desea buscar: ");
    vector<string> rutas;
    buscarNumeroRecursivo(raiz, objetivo, "", rutas, 1);

    if (rutas.empty()) {
        cout << "El número " << objetivo << " no se encuentra en el árbol.\n";
    } else {
        cout << "El número " << objetivo << " se encontró " << rutas.size() << " vez/veces.\n";
        for (const string& ruta : rutas) {
            cout << "Ruta: " << ruta << "\n";
        }
    }
}

void liberarMemoria(Nodo* nodo) {
    if (nodo == nullptr) return;
    liberarMemoria(nodo->izquierda);
    liberarMemoria(nodo->derecha);
    delete nodo;
}

int main() {
    Nodo* raiz = nullptr;
    int nivelMaximo = 0;

    while (true) {
        cout << "\nMENÚ PRINCIPAL\n";
        cout << "1. Crear árbol completo\n";
        cout << "2. Mostrar árbol\n";
        cout << "3. Recorrido interactivo\n";
        cout << "4. Buscar número en el árbol\n";
        cout << "5. Salir\n";

        int opcion = pedirEntero("Seleccione una opción (1-5): ");

        switch (opcion) {
            case 1:
                liberarMemoria(raiz);
                raiz = nullptr;
                nivelMaximo = pedirEntero("Ingrese el nivel máximo del árbol: ");
                crearArbolCompleto(raiz, 1, nivelMaximo);
                cout << "Árbol creado correctamente.\n";
                break;
            case 2:
                mostrarArbol(raiz);
                break;
            case 3:
                recorridoInteractivo(raiz);
                break;
            case 4:
                buscarNumero(raiz);
                break;
            case 5:
                liberarMemoria(raiz);
                cout << "Saliendo del programa...\n";
                return 0;
            default:
                cout << "Opción inválida.\n";
        }

        cout << "Presione Enter para continuar...";
        cin.get();
    }

    return 0;
}
