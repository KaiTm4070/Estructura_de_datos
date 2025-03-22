#include <iostream>
#include <limits>
using namespace std;

struct Estudiante {
    int id;
    string nombre;
    float promedio;
    Estudiante* siguiente;
};

class ListaEstudiantes {
private:
    Estudiante* cabeza;

    bool idExiste(int id) {
        Estudiante* actual = cabeza;
        while (actual) {
            if (actual->id == id) return true;
            actual = actual->siguiente;
        }
        return false;
    }

public:
    ListaEstudiantes() : cabeza(nullptr) {}

    bool validarId(int id) {
        return !idExiste(id);
    }

    void agregarEstudiante(int id, string nombre, float promedio) {
        if (id <= 0 || nombre.find_first_not_of(' ') == string::npos || promedio < 0.0 || promedio > 5.0) {
            cout << "Datos inválidos. Ingrese valores correctos.\n";
            return;
        }
        Estudiante* nuevo = new Estudiante{id, nombre, promedio, cabeza};
        cabeza = nuevo;
        cout << "Estudiante agregado correctamente.\n";
    }

    void mostrarEstudiantes() {
        if (!cabeza) {
            cout << "No hay estudiantes registrados.\n";
            return;
        }
        Estudiante* actual = cabeza;
        while (actual) {
            cout << "ID: " << actual->id;
            cout << ", Nombre: " << actual->nombre;
            cout << ", Promedio: " << actual->promedio;
            cout << endl;
            actual = actual->siguiente;
        }
    }

    void buscarEstudiante(int id) {
        if (!cabeza) {
            cout << "No hay estudiantes registrados.\n";
            return;
        }
        Estudiante* actual = cabeza;
        while (actual) {
            if (actual->id == id) {
                cout << "ID: " << actual->id;
                cout << "Nombre: " << actual->nombre;
                cout << "Promedio: " << actual->promedio;
                cout << endl;
                return;
            }
            actual = actual->siguiente;
        }
        cout << "Estudiante no encontrado.\n";
    }

    void eliminarEstudiante(int id) {
        if (!cabeza) {
            cout << "No hay estudiantes registrados.\n";
            return;
        }
        Estudiante* actual = cabeza, *prev = nullptr;
        while (actual && actual->id != id) {
            prev = actual;
            actual = actual->siguiente;
        }
        if (!actual) {
            cout << "Estudiante no encontrado.\n";
            return;
        }
        if (!prev) cabeza = actual->siguiente;
        else prev->siguiente = actual->siguiente;
        delete actual;
        cout << "Estudiante eliminado correctamente.\n";
    }

    void actualizarPromedio(int id) {
        Estudiante* actual = cabeza;
        while (actual) {
            if (actual->id == id) {
                cout << "Ingrese el nuevo promedio: ";
                float nuevoPromedio;
                while (!(cin >> nuevoPromedio) || nuevoPromedio < 0.0 || nuevoPromedio > 5.0) {
                    cout << "Promedio inválido. Ingrese un valor entre 0.0 y 5.0: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                actual->promedio = nuevoPromedio;
                cout << "Promedio actualizado.\n";
                return;
            }
            actual = actual->siguiente;
        }
        cout << "Estudiante no encontrado.\n";
    }

    void mostrarMejorEstudiante() {
        if (!cabeza) {
            cout << "No hay estudiantes registrados.\n";
            return;
        }
        Estudiante* mejor = cabeza;
        Estudiante* actual = cabeza->siguiente;
        while (actual) {
            if (actual->promedio > mejor->promedio) mejor = actual;
            actual = actual->siguiente;
        }
        cout << "Mejor estudiante: ID " << mejor->id;
        cout << "Nombre: " << mejor->nombre;
        cout << "Promedio: " << mejor->promedio;
        cout << endl;
    }

    bool hayEstudiantes() {
        return cabeza != nullptr;
    }
};

int main() {
    ListaEstudiantes lista;
    int opcion, id;
    string nombre;
    float promedio;

    do {
        cout << "\nMenu:\n1. Agregar estudiante\n2. Mostrar estudiantes\n3. Buscar estudiante\n4. Eliminar Estudiante\n5. Actualizar promedio\n6. Mostrar mejor estudiante\n7. Salir\nOpcion: ";
        while (!(cin >> opcion) || opcion < 1 || opcion > 7) {
            cout << "Entrada inválida. Por favor, ingrese un número entre 1 y 7: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        switch (opcion) {
            case 1:
                cout << "Ingrese ID: ";
                while (!(cin >> id) || id <= 0 || !lista.validarId(id)) {
                    cout << "ID inválido o ya existente. Ingrese otro: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore();
                cout << "Ingrese Nombre: ";
                getline(cin, nombre);
                cout << "Ingrese Promedio: ";
                while (!(cin >> promedio) || promedio < 0.0 || promedio > 5.0) {
                    cout << "Promedio inválido. Ingrese un valor entre 0.0 y 5.0: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                lista.agregarEstudiante(id, nombre, promedio);
                break;
            case 2:
                lista.mostrarEstudiantes();
                break;
            case 3:
                cout << "Ingrese ID a buscar: ";
                cin >> id;
                lista.buscarEstudiante(id);
                break;
            case 4:
                cout << "Ingrese ID del estudiante a eliminar: ";
                cin >> id;
                lista.eliminarEstudiante(id);
                break;
            case 5:
                cout << "Ingrese ID del estudiante para actualizar promedio: ";
                while (!(cin >> id) || id <= 0 ){
                    cout << "ID inválido o no existente. Ingrese otro: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                lista.actualizarPromedio(id);
                break;
            case 6:
                lista.mostrarMejorEstudiante();
                break;
        }
    } while (opcion != 7);
    return 0;
}
