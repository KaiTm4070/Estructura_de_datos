#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <map>
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
            } else if (raiz->izquierda == nullptr) {
                cout << "Debes insertar en el hijo izquierdo de " << valor << ":\n";
                insertarNodo(raiz->izquierda, nivelActual + 1, nivelMaximo);
            } else if (raiz->derecha == nullptr) {
                cout << "Debes insertar en el hijo derecho de " << valor << ":\n";
                insertarNodo(raiz->derecha, nivelActual + 1, nivelMaximo);
            }
        }
    }
}

// Función para buscar el número y almacenar las rutas en un vector
int buscarYMostrarRuta(Nodo* raiz, int numero, vector<string>& rutas, string ruta = "") {
    if (raiz == nullptr) return 0;

    // Agregar el nodo actual a la ruta
    ruta += to_string(raiz->dato) + " ";

    int repeticiones = 0;

    // Si encontramos el número, almacenamos la ruta
    if (raiz->dato == numero) {
        rutas.push_back(ruta);
        repeticiones = 1;
    }

    // Buscar en el subárbol izquierdo y derecho
    repeticiones += buscarYMostrarRuta(raiz->izquierda, numero, rutas, ruta);
    repeticiones += buscarYMostrarRuta(raiz->derecha, numero, rutas, ruta);

    return repeticiones;
}

void mostrarArbol(Nodo* raiz, int espacio = 0, int nivelEspacio = 6, string prefijo = "") {
    if (raiz == nullptr) return;

    espacio += nivelEspacio;

    mostrarArbol(raiz->derecha, espacio, nivelEspacio, "|--");
    cout << string(espacio - nivelEspacio, ' ') << prefijo << raiz->dato << endl;
    mostrarArbol(raiz->izquierda, espacio, nivelEspacio, "|--");
}

// Función auxiliar para convertir ruta (string) a vector de enteros
vector<int> convertirRutaAEnteros(const string& rutaStr) {
    vector<int> numeros;
    string num = "";
    for (char c : rutaStr) {
        if (c == ' ') {
            if (!num.empty()) {
                numeros.push_back(stoi(num));
                num = "";
            }
        } else {
            num += c;
        }
    }
    return numeros;
}

void realizarOperacionConRuta(const string& rutaStr, map<pair<int, int>, int>& operacionesGuardadas) {
    vector<int> valores = convertirRutaAEnteros(rutaStr);
    if (valores.empty()) {
        cout << "Ruta vacía.\n";
        return;
    }

    double resultado = valores[0];

    for (size_t i = 1; i < valores.size(); ++i) {
        int a = static_cast<int>(resultado);
        int b = valores[i];
        
        pair<int, int> parOperacion = {a, b};
        
        int op;
        if (operacionesGuardadas.find(parOperacion) != operacionesGuardadas.end()) {
            op = operacionesGuardadas[parOperacion];
            cout << "\nYa se eligió una operación para (" << a << ", " << b << "): ";
            switch (op) {
                case 1: cout << "Sumar\n"; break;
                case 2: cout << "Restar\n"; break;
                case 3: cout << "Multiplicar\n"; break;
                case 4: cout << "Dividir\n"; break;
            }
        } else {
            cout << "\nEntre " << resultado << " y " << b << ", elija operación:\n";
            cout << "1. Sumar\n";
            cout << "2. Restar\n";
            cout << "3. Multiplicar\n";
            cout << "4. Dividir\n";
            op = pedirEntero("Ingrese opción: ");
            if (op < 1 || op > 4) {
                cout << "Opción inválida. Operación cancelada.\n";
                return;
            }
            operacionesGuardadas[parOperacion] = op;
        }
        switch (op) {
            case 1:
                resultado += b;
                break;
            case 2:
                resultado -= b;
                break;
            case 3:
                resultado *= b;
                break;
            case 4:
                if (b == 0) {
                    cout << "Error: división por cero. Operación cancelada.\n";
                    return;
                }
                resultado /= b;
                break;
        }
        cout << "Resultado parcial: " << resultado << endl;
    }

    cout << "\nResultado final de la operación sobre la ruta seleccionada: " << resultado << "\n";
}




int main() {
    Nodo* raiz = nullptr;
    int nivelMaximo = 0;
    bool arbolCreado = false;
    bool arbolLlenado = false;

    int opcion;
    map<pair<int, int>, int> operacionesGuardadas;
    do {
        cout << "\n=== MENÚ ===\n";
        cout << "1. Crear árbol (definir nivel máximo)\n";
        cout << "2. Llenar árbol\n";
        cout << "3. Buscar número\n";
        cout << "4. Mostrar árbol\n";
        cout << "5. Salir\n";
        opcion = pedirEntero("Seleccione una opción: ");
        
        switch (opcion) {
            case 1:
                nivelMaximo = pedirEntero("Ingrese el nivel máximo del árbol: ");
                raiz = nullptr;
                arbolCreado = true;
                arbolLlenado = false;
                break;
            case 2:
                if (arbolCreado) {
                    insertarNodo(raiz, 1, nivelMaximo);
                    arbolLlenado = true;
                } else {
                    cout << "Primero debes crear el árbol.\n";
                }
                break;
            case 3:
                if (arbolLlenado) {
                    int numero = pedirEntero("Ingrese el número a buscar: ");
                    vector<string> rutas;
                    int repeticiones = buscarYMostrarRuta(raiz, numero, rutas);
                    if (repeticiones > 0) {
                        cout << "El número " << numero << " se repite " << repeticiones << " veces.\n";
                        for (int i = 0; i < repeticiones; i++) {
                            cout << "\nRuta " << i + 1 << ": " << rutas[i] << endl;
                            realizarOperacionConRuta(rutas[i], operacionesGuardadas);
                        }
                        operacionesGuardadas.clear();  // Limpiar el mapa después de terminar todas las rutas
                        cout << "\nSe han limpiado las operaciones guardadas.\n";
                    } else {
                        cout << "El número " << numero << " NO se encuentra en el árbol.\n";
                    }
                } else {
                    cout << "Primero debes llenar el árbol.\n";
                }
                break;
            case 4:
                if (arbolLlenado) {
                    cout << "\nRepresentación jerárquica del árbol con líneas:\n";
                    mostrarArbol(raiz);
                } else {
                    cout << "El árbol está vacío o no ha sido llenado.\n";
                }
                break;
            case 5:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción inválida. Intenta otra vez.\n";
        }
    } while (opcion != 5);

    return 0;
}