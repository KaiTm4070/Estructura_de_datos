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
        int cantidadEstudiantes;

        bool idExiste(int id) {
            if (!cabeza) return false;
            Estudiante* actual = cabeza;
            do {
                if (actual->id == id) return true;
                actual = actual->siguiente;
            } while (actual != cabeza);
            return false;
        }

        bool esValido(const std::string& input) {
            return !input.empty() && input.find_first_not_of(' ') != std::string::npos;
        }

    public:
        ListaEstudiantes() : cabeza(nullptr), cantidadEstudiantes(0) {}

        bool validarId(int id) {
            return !idExiste(id);
        }

        void agregarEstudiante(int id, string nombre, float promedio, int posicion) {
            if (id <= 0 || nombre.empty() || promedio < 0.0 || promedio > 5.0) {
                cout << "Datos inválidos. Ingrese valores correctos.\n";
                return;
            }

            Estudiante* nuevo = new Estudiante{id, nombre, promedio, nullptr};

            if (!cabeza) {
                nuevo->siguiente = nuevo;
                cabeza = nuevo;
            } else {
                if (posicion <= 1) {
                    nuevo->siguiente = cabeza->siguiente;
                    cabeza->siguiente = nuevo;
                } else {
                    Estudiante* actual = cabeza->siguiente;
                    Estudiante* anterior = cabeza;
                    int i = 1;

                    while (i < posicion - 1 && actual != cabeza) {
                        anterior = actual;
                        actual = actual->siguiente;
                        i++;
                    }

                    nuevo->siguiente = actual;
                    anterior->siguiente = nuevo;

                    if (actual == cabeza) {
                        cabeza = nuevo;
                    }
                }
            }

            cantidadEstudiantes++;
            cout << "Estudiante agregado correctamente en la posición " << posicion << ".\n";
        }

        void mostrarEstudiantes() {
            if (!cabeza) {
                cout << "No hay estudiantes registrados.\n";
                return;
            }

            Estudiante* actual = cabeza->siguiente;
            int pos = 1;
            cout << "Lista de estudiantes:\n";
            do {
                cout << "Posición " << pos << " -> ID: " << actual->id
                    << ", Nombre: " << actual->nombre
                    << ", Promedio: " << actual->promedio << endl;
                actual = actual->siguiente;
                pos++;
            } while (actual != cabeza->siguiente);
        }

        void buscarEstudiante() {
            if (!cabeza) {
                cout << "No hay estudiantes registrados.\n";
                return;
            }

            int id;
            cout << "Ingrese el ID del estudiante a buscar: ";
            cin >> id;

            Estudiante* actual = cabeza->siguiente;
            do {
                if (actual->id == id) {
                    cout << "ID: " << actual->id << ", Nombre: " << actual->nombre << ", Promedio: " << actual->promedio << endl;
                    return;
                }
                actual = actual->siguiente;
            } while (actual != cabeza->siguiente);

            cout << "Estudiante no encontrado.\n";
        }

        void eliminarEstudiante() {
            if (!cabeza) {
                cout << "No hay estudiantes registrados.\n";
                return;
            }

            int id;
            cout << "Ingrese el ID del estudiante a eliminar: ";
            cin >> id;

            Estudiante* actual = cabeza;
            Estudiante* anterior = nullptr;

            do {
                if (actual->id == id) {
                    if (actual == cabeza && actual->siguiente == cabeza) {
                        delete actual;
                        cabeza = nullptr;
                    } else {
                        if (anterior) {
                            anterior->siguiente = actual->siguiente;
                            if (actual == cabeza) cabeza = anterior;
                        } else {
                            Estudiante* temp = cabeza;
                            while (temp->siguiente != cabeza) temp = temp->siguiente;
                            temp->siguiente = cabeza->siguiente;
                            delete cabeza;
                            cabeza = temp;
                        }
                    }
                    cout << "Estudiante eliminado correctamente.\n";
                    return;
                }

                anterior = actual;
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
            cout << "Ingrese el ID del estudiante para actualizar promedio: ";
            while (!(cin >> id) || id <= 0) {
                cout << "ID inválido. Intente de nuevo: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            Estudiante* actual = cabeza->siguiente;
            do {
                if (actual->id == id) {
                    float nuevoPromedio;
                    cout << "Ingrese el nuevo promedio: ";
                    while (!(cin >> nuevoPromedio) || nuevoPromedio < 0.0 || nuevoPromedio > 5.0) {
                        cout << "Promedio inválido. Intente nuevamente (0.0 - 5.0): ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    actual->promedio = nuevoPromedio;
                    cout << "Promedio actualizado correctamente.\n";
                    return;
                }
                actual = actual->siguiente;
            } while (actual != cabeza->siguiente);

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
                if (actual->promedio > mejor->promedio) {
                    mejor = actual;
                }
                actual = actual->siguiente;
            } while (actual != cabeza->siguiente);

            cout << "Mejor estudiante: ID " << mejor->id
                << ", Nombre: " << mejor->nombre
                << ", Promedio: " << mejor->promedio << endl;
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
    int opcion, id, posicion;
    string nombre;
    float promedio;

    do {
        cout << "\nMenu:\n1. Agregar estudiante\n2. Mostrar estudiantes\n3. Buscar estudiante\n4. Eliminar estudiante\n5. Actualizar promedio\n6. Mostrar mejor estudiante\n7. Salir\nOpcion: ";
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
                do {
                    cout << "Ingrese Nombre: ";
                    getline(cin, nombre);
                    if (!lista.validarId(id) || !lista.hayEstudiantes() || nombre.empty()) {
                        cout << "Nombre inválido. Intente de nuevo.\n";
                    }
                } while (nombre.empty());

                cout << "Ingrese Promedio: ";
                while (!(cin >> promedio) || promedio < 0.0 || promedio > 5.0) {
                    cout << "Promedio inválido. Ingrese un valor entre 0.0 y 5.0: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                cout << "Ingrese la posición en la que desea insertar: ";
                while (!(cin >> posicion) || posicion <= 0) {
                    cout << "Posición inválida. Ingrese un número positivo: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                lista.agregarEstudiante(id, nombre, promedio, posicion);
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