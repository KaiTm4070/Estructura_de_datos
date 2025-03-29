#include <iostream>
#include <limits>

using namespace std;

struct Estudiante {
    int id;
    string nombre;
    float promedio;
    Estudiante* siguiente;
};

//validad string vacio
bool esValido(const std::string& input) {
    return !input.empty() && input.find_first_not_of(' ') != std::string::npos;
}

class ListaEstudiantes {
private:
    Estudiante* cabeza;

    bool idExiste(int id) {
        if (!cabeza) return false;
        
        Estudiante* actual = cabeza;
        do {
            if (actual->id == id) return true;
            actual = actual->siguiente;
        } while (actual != cabeza);
        
        return false;
    }

public:
    ListaEstudiantes() : cabeza(nullptr) {}

    bool validarId(int id) {
        return !idExiste(id);
    }

    // Funcion agregar estudiante
    void agregarEstudiante(int id, string nombre, float promedio) {
        if (id <= 0 || nombre.empty() || promedio < 0.0 || promedio > 5.0) {
            cout << "Datos inválidos. Ingrese valores correctos.\n";
            return;
        }
        
        Estudiante* nuevo = new Estudiante{id, nombre, promedio, nullptr};
        
        if (!cabeza) {
            nuevo->siguiente = nuevo; // Lista circular, apunta a sí mismo
            cabeza = nuevo;
        } else {
            nuevo->siguiente = cabeza->siguiente;
            cabeza->siguiente = nuevo;
            cabeza = nuevo;
        }
        
        cout << "Estudiante agregado correctamente.\n";
    }

    // Funcion Mostrar los Estudiantes
    void mostrarEstudiantes() {
        if (!cabeza) {
            cout << "No hay estudiantes registrados.\n";
            return;
        }
        
        Estudiante* actual = cabeza->siguiente;
        cout << "Estudiantes registrados:\n";
        do {
            cout << "ID: " << actual->id;
            cout << ", Nombre: " << actual->nombre;
            cout << ", Promedio: " << actual->promedio;
            cout << endl;
            actual = actual->siguiente;
        } while (actual != cabeza);
    }
    
    // Funcion Buscar estudiantes por ID
    void buscarEstudiante() {
        if (!cabeza) {
            cout << "No hay estudiantes registrados.\n";
            return;
        }
        int id;
        cout<< "Ingrese el id del estudiante a buscar.";
        cin >> id;
        Estudiante* actual = cabeza->siguiente;
        do {
            if (actual->id == id) {
                cout << "ID: " << actual->id;
                cout << ", Nombre: " << actual->nombre;
                cout << ", Promedio: " << actual->promedio;
                cout << endl;
                return;
            }
            actual = actual->siguiente;
        } while (actual != cabeza);

        cout << "Estudiante no encontrado.\n";
    }

    void eliminarEstudiante() {
        if (!cabeza) {
            cout << "No hay estudiantes registrados.\n";
            return;
        }
        int id;
        cout << "Ingrese ID del estudiante a eliminar: ";
        cin >> id;
        Estudiante* actual = cabeza;
        Estudiante* prev = nullptr;
        
        do {
            if (actual->id == id) {
                if (actual == cabeza && actual->siguiente == cabeza) {
                    cabeza = nullptr;
                } else {
                    prev->siguiente = actual->siguiente;
                    if (actual == cabeza) cabeza = prev;
                }
                delete actual;
                cout << "Estudiante eliminado correctamente.\n";
                return;
            }
            prev = actual;
            actual = actual->siguiente;
        } while (actual != cabeza);
        
        cout << "Estudiante no encontrado.\n";
    }

    void actualizarPromedio() {
        if (!cabeza) {
            cout << "No hay estudiantes registrados.\n";
            return;
        }
        int id;
        cout << "Ingrese ID del estudiante para actualizar promedio: ";
        while (!(cin >> id) || id <= 0 ){
            cout << "ID inválido o no existente. Ingrese otro: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        Estudiante* actual = cabeza->siguiente;
        do {
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
        } while (actual != cabeza);

        cout << "Estudiante no encontrado.\n";
    }

    void mostrarMejorEstudiante() {
        if (!cabeza) {
            cout << "No hay estudiantes registrados.\n";
            return;
        }
        
        Estudiante* mejor = cabeza->siguiente;
        Estudiante* actual = cabeza->siguiente->siguiente;
        do {
            if (actual->promedio > mejor->promedio) mejor = actual;
            actual = actual->siguiente;
        } while (actual != cabeza->siguiente);
        
        cout << "Mejor estudiante: ID " << mejor->id;
        cout << ", Nombre: " << mejor->nombre;
        cout << ", Promedio: " << mejor->promedio;
        cout << endl;
    }

    bool hayEstudiantes() {
        return cabeza != nullptr;
    }

    ~ListaEstudiantes() {
        if (!cabeza) return;
        
        Estudiante* actual = cabeza->siguiente;
        while (actual != cabeza) {
            Estudiante* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
        delete cabeza;
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
                do{
                    cout << "Ingrese Nombre valido. Intetne otro: ";
                    getline(cin, nombre);

                    if(!esValido(nombre)){
                        cout << "Entrada no valida. Intente de nuevo nuevo \n";
                    }
                } while (!esValido(nombre));
                
                cin.ignore();
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
                lista.buscarEstudiante();
            break;
            
            case 4:
                lista.eliminarEstudiante();
            break;
            
            case 5:
                lista.actualizarPromedio();
            break;
            
            case 6:
                lista.mostrarMejorEstudiante();
            break;
        }
    } while (opcion != 7);

    return 0;
}
