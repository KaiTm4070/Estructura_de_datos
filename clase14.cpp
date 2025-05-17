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

    cout << "Ingresa el valor para cada nodo:\n";
    for (int i = 0; i < numNodos; ++i) {
        nodos[i].id = i;
        cout << "Valor del nodo " << (i + 1) << ": ";
        cin >> nodos[i].valor;
    }

    cout << "Grafo creado con " << numNodos << " nodos.\n\n";
}


// Función para insertar/conectar aristas con peso
void insertarConexiones() {
    if (numNodos == 0) {
        cout << "Primero crea el grafo (opción 1).\n\n";
        return;
    }

    int conexiones;
    int maxConexiones = numNodos * numNodos;

    // Validar entrada de número de conexiones
    while (true) {
        cout << "¿Cuántas conexiones (aristas dirigidas) quieres agregar? (máximo " << maxConexiones << "): ";
        if (!(cin >> conexiones) || conexiones < 1 || conexiones > maxConexiones) {
            cout << "Entrada inválida. Ingresa un número entre 1 y " << maxConexiones << ".\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    int conexionesActuales = 0;

    for (int i = 0; i < conexiones; ++i) {
        if (conexionesActuales >= maxConexiones) {
            cout << "Ya alcanzaste el máximo número de conexiones posibles para este grafo.\n";
            break;
        }
        
        int origen, destino, peso;
        
        // Validar origen y destino
        while (true) {
            cout << "Conexión #" << i + 1 << " - Origen (1 a " << numNodos << "): ";
            if (!(cin >> origen) || origen < 1 || origen > numNodos) {
                cout << "Índice inválido. Intenta de nuevo.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            
            cout << "Destino (1 a " << numNodos << "): ";
            if (!(cin >> destino) || destino < 1 || destino > numNodos) {
                cout << "Índice inválido. Intenta de nuevo.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            origen--;
            destino--;
            
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
                continue; // no aumentar contador ni repetir el índice
            }
            
            break; // entrada válida, salir del ciclo
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
        
        // Agregar la arista
        grafo[origen].push_back({destino, peso});
        conexionesActuales++;
        cout << "Conexión agregada.\n";
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

