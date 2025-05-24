#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>

using namespace std;

struct Nodo {
    int id;
    string valor;
};

struct Arista {
    int destino;
    int peso;
};

struct Ruta {
    vector<int> nodos;
    int pesoTotal;
};

vector<Nodo> nodos;
vector<vector<Arista>> grafo;
int numNodos = 0;

void crearGrafo() {
    while (true) {
        cout << "¿Cuántos nodos tendrá el grafo?: ";
        if (!(cin >> numNodos) || numNodos < 2) {
            cout << "Entrada inválida. Debes ingresar un número entero mayor o igual a 2.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    nodos.resize(numNodos);
    grafo.clear();
    grafo.resize(numNodos);

    cout << "Ingresa el valor para cada nodo (debe ser único):\n";
    for (int i = 0; i < numNodos; ++i) {
        string valor;
        bool repetido;
        do {
            repetido = false;
            cout << "Valor del nodo " << (i + 1) << ": ";
            cin >> valor;
            for (int j = 0; j < i; ++j) {
                if (nodos[j].valor == valor) {
                    cout << "Error: ya existe un nodo con el valor \"" << valor << "\". Ingresa un valor diferente.\n";
                    repetido = true;
                    break;
                }
            }
        } while (repetido);
        nodos[i].id = i;
        nodos[i].valor = valor;
    }

    cout << "Grafo creado con " << numNodos << " nodos.\n\n";
}

int obtenerIndicePorValor(const string& valor) {
    for (int i = 0; i < numNodos; ++i) {
        if (nodos[i].valor == valor) {
            return i;
        }
    }
    return -1;
}

void insertarConexiones() {
    if (numNodos == 0) {
        cout << "Primero crea el grafo (opción 1).\n\n";
        return;
    }

    int maxConexiones = numNodos * numNodos;
    int conexionesActuales = 0;
    int numConexion = 1;

    cout << "\n=== Insertar Conexiones (máximo " << maxConexiones << ") ===\n";

    while (conexionesActuales < maxConexiones) {
        string origenValor, destinoValor;
        int origen, destino, peso;
        
        while (true) {
            cout << "Conexión #" << numConexion << " - Valor del nodo origen: ";
            cin >> origenValor;
            origen = obtenerIndicePorValor(origenValor);
            if (origen == -1) {
                cout << "El nodo con valor \"" << origenValor << "\" no existe. Intenta de nuevo.\n";
                continue;
            }
            
            cout << "Valor del nodo destino: ";
            cin >> destinoValor;
            destino = obtenerIndicePorValor(destinoValor);
            if (destino == -1) {
                cout << "El nodo con valor \"" << destinoValor << "\" no existe. Intenta de nuevo.\n";
                continue;
            }
            
            bool existe = false;
            for (const Arista& a : grafo[origen]) {
                if (a.destino == destino) {
                    existe = true;
                    break;
                }
            }
            if (existe) {
                cout << "La conexión ya existe. No se agregará.\n";
                continue;
            }
            break;
        }
        
        while (true) {
            cout << "Peso de la arista: ";
            if (!(cin >> peso)) {
                cout << "Peso inválido. Intenta de nuevo.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                break;
            }
        }
        
        grafo[origen].push_back({destino, peso});
        conexionesActuales++;
        cout << "Conexión agregada: " << origenValor << " → " << destinoValor << " [peso: " << peso << "]\n";
        numConexion++;
        
        if (conexionesActuales >= maxConexiones) {
            cout << "Has alcanzado el número máximo de conexiones permitidas.\n";
            break;
        }
        
        char continuar;
        while (true) {
            cout << "¿Deseas agregar otra conexión? (s/n): ";
            cin >> continuar;
            if (continuar == 's' || continuar == 'S') {
                break;
            } else if (continuar == 'n' || continuar == 'N') {
                return;
            } else {
                cout << "Entrada inválida. Por favor ingresa 's' para sí o 'n' para no.\n";
            }
        }

    }
    cout << "\n";
}

void mostrarGrafo() {
    if (numNodos == 0) {
        cout << "No hay grafo creado.\n\n";
        return;
    }
    cout << "\nRepresentación gráfica del grafo dirigido con pesos:\n\n";

    for (const Nodo& nodo : nodos) {
        cout << "Nodo " << nodo.valor << " (" << nodo.id + 1 << "):\n";
        bool selfLoop = false;
        for (const Arista& arista : grafo[nodo.id]) {
            if (arista.destino == nodo.id) {
                selfLoop = true;
                break;
            }
        }
        if (selfLoop) {
            cout << "  ↺ (loop a sí mismo)\n";
        }
        
        for (const Arista& arista : grafo[nodo.id]) {
            if (arista.destino != nodo.id) {
                cout << "  " << nodo.valor << " (" << nodo.id + 1 << ") → "
                     << nodos[arista.destino].valor << " (" << arista.destino + 1 << ")"
                     << " [peso: " << arista.peso << "]\n";
            }
        }
        cout << "\n";
    }
}

//  funcion buscar rutas de un nodo a otro
void dfs(int actual, int destino, vector<int>& caminoActual, int pesoActual, vector<Ruta>& rutas, int profundidad = 0) {
    // Limitar la profundidad para evitar desbordamiento de pila (ajustar según necesidad)
    const int LIMITE_PROFUNDIDAD = numNodos * 3;
    if (profundidad > LIMITE_PROFUNDIDAD) return;

    // Si llegamos al destino y no es el inicio (profundidad > 0)
    if (actual == destino && profundidad > 0) {
        rutas.push_back({caminoActual, pesoActual});
        // No return aquí para permitir seguir explorando más rutas
    }

    // Explorar todas las aristas
    for (const Arista& arista : grafo[actual]) {
        caminoActual.push_back(arista.destino);
        dfs(arista.destino, destino, caminoActual, pesoActual + arista.peso, rutas, profundidad + 1);
        caminoActual.pop_back();
    }
}


// Funcion para mostrar las rutas de un nodo a otro
void mostrarRutasAscendentes() {
    if (numNodos == 0) {
        cout << "Primero debes crear el grafo.\n\n";
        return;
    }

    string origenValor, destinoValor;
    cout << "Ingresa el valor del nodo origen: ";
    cin >> origenValor;
    cout << "Ingresa el valor del nodo destino: ";
    cin >> destinoValor;

    int origen = obtenerIndicePorValor(origenValor);
    int destino = obtenerIndicePorValor(destinoValor);

    if (origen == -1 || destino == -1) {
        cout << "Uno de los nodos no existe.\n";
        return;
    }

    vector<int> caminoActual = {origen};
    vector<Ruta> rutas;
    dfs(origen, destino, caminoActual, 0, rutas);

    if (rutas.empty()) {
        cout << "No hay rutas posibles de " << origenValor << " a " << destinoValor << ".\n";
        return;
    }

    sort(rutas.begin(), rutas.end(), [](const Ruta& a, const Ruta& b) {
        return a.pesoTotal < b.pesoTotal;
    });

    cout << "\nRutas de " << origenValor << " a " << destinoValor << " ordenadas por peso total:\n";
    for (const Ruta& ruta : rutas) {
        for (size_t i = 0; i < ruta.nodos.size(); ++i) {
            cout << nodos[ruta.nodos[i]].valor;
            if (i < ruta.nodos.size() - 1) cout << " → ";
        }
        cout << " | Peso total: " << ruta.pesoTotal << "\n";
    }
}

int main() {
    int opcion;

    do {
        cout << "==== Menú de Grafo Dirigido ====\n";
        cout << "1. Crear grafo\n";
        cout << "2. Insertar valores a aristas\n";
        cout << "3. Mostrar grafo\n";
        cout << "4. Mostrar rutas de un nodo a otro\n";
        cout << "5. Salir\n";
        cout << "Elige una opción: ";
        
        if (!(cin >> opcion)) {
            cout << "Entrada inválida. Por favor ingresa un número.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcion = -1;
            continue;
        }
        
        switch (opcion) {
            case 1:
                crearGrafo();
                break;
            case 2:
                insertarConexiones();
                break;
            case 3:
                mostrarGrafo();
                break;
            case 4:
                mostrarRutasAscendentes();
                break;
            case 5:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción inválida, intenta de nuevo.\n";
        }
        cout << "\n";
    } while (opcion != 5);

    return 0;
}
