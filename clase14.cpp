#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

struct Nodo {
    int id;
    string valor;
};

// Arista con destino y peso
struct Arista {
    int destino;
    int peso;
};

vector<Nodo> nodos;
vector<vector<Arista>> grafo;
int numNodos = 0;

// Función para crear nodos
// Función para crear nodos
void crearGrafo() {
    while (true) {
        cout << "¿Cuántos nodos tendrá el grafo?: ";
        if (!(cin >> numNodos) || numNodos < 2) {
            cout << "Entrada inválida. Debes ingresar un número entero mayor o igual a 2.\n";
            cin.clear(); // limpia el error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignora la línea incorrecta
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpia resto de la línea
            break; // entrada válida, sal del ciclo
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
            // Verificar si el valor ya fue usado
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

// Función auxiliar para obtener índice por valor
int obtenerIndicePorValor(const string& valor) {
    for (int i = 0; i < numNodos; ++i) {
        if (nodos[i].valor == valor) {
            return i;
        }
    }
    return -1; // no encontrado
}

// Función para insertar/conectar aristas con peso usando el valor del nodo
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
        // Validar entrada de valores
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
            // Verificar si la conexión ya existe
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
        // Validar peso
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
        cout << "¿Deseas agregar otra conexión? (s/n): ";
        cin >> continuar;
        if (continuar != 's' && continuar != 'S') {
            break;
        }
    }
    cout << "\n";
}


// Mostrar grafo con pesos y conexiones
void mostrarGrafo() {
    if (numNodos == 0) {
        cout << "No hay grafo creado.\n\n";
        return;
    }

    cout << "\nRepresentación gráfica del grafo dirigido con pesos:\n\n";

    for (const Nodo& nodo : nodos) {
        cout << "Nodo " << nodo.valor << " (" << nodo.id + 1 << "):\n";
        
        // Self-loop
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
        
        // Mostrar conexiones con pesos
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

int main() {
    int opcion;

    do {
        cout << "==== Menú de Grafo Dirigido ====\n";
        cout << "1. Crear grafo\n";
        cout << "2. Insertar valores a aristas\n";
        cout << "3. Mostrar grafo\n";
        cout << "4. Salir\n";
        cout << "Elige una opción: ";
        
        if (!(cin >> opcion)) {  // Si no es un entero válido
            cout << "Entrada inválida. Por favor ingresa un número.\n\n";
            cin.clear(); // Limpia el error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora la línea incorrecta
            opcion = -1; // Opción inválida para evitar salir
            continue; // vuelve al inicio del loop
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
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción inválida, intenta de nuevo.\n";
        }
        cout << "\n";
    } while (opcion != 4);

    return 0;
}
