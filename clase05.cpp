// Ejercicio de clase 05, estructuras anidadas para ingresar datos
// de un estudiante y las notas de sus materias

#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// Definición de la estructura Materia
struct Materia {
    string nombre;
    string horario;
    float notas[3];

    // Función para calcular el promedio de las notas
    float calcularPromedio() const {
        return (notas[0] + notas[1] + notas[2]) / 3.0;
    }
};

// Definición de la estructura Estudiante
struct Estudiante {
    string nombre;
    string apellido;
    string nombrePapa;
    string nombreMama;
    string telefono;
    string direccion;
    string id;
    vector<Materia> materias;
};

// Vector global de estudiantes
vector<Estudiante> estudiantes;

// Función para validar la entrada de números enteros positivos
int obtenerEnteroPositivo(const string &mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        
        if (cin.fail() || valor <= 0) {
            cout << "Entrada inválida. Debe ingresar un número mayor a 0.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(); // Limpiar el buffer después de un número
            return valor;
        }
    }
}

// Función para validar la entrada de un ID numérico
string obtenerIDValido() {
    string id;
    while (true) {
        cout << "Ingrese ID del estudiante (solo números, mayor a 0): ";
        cin >> id;
        
        // Verificar que solo contenga dígitos y no empiece en 0
        if (id.find_first_not_of("0123456789") == string::npos && id[0] != '0') {
            cin.ignore(); // Limpiar el buffer
            return id;
        }
        
        cout << "ID inválido. Debe contener solo números y no comenzar con 0.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Función para validar la entrada de un telefono
string obtenertelefonoValido() {
    string telefono;
    while (true) {
        cout << "Ingrese telefono del estudiante (solo números, mayor a 0): ";
        cin >> telefono;
        
        // Verificar que solo contenga dígitos y no empiece en 0
        if (telefono.find_first_not_of("0123456789") == string::npos && telefono[0] != '0') {
            cin.ignore(); // Limpiar el buffer
            return telefono;
        }
        
        cout << "ID inválido. Debe contener solo números y no comenzar con 0.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Función para validar la entrada de una nota entre 0 y 5
float obtenerNotaValida(const string &mensaje) {
    float nota;
    while (true) {
        cout << mensaje;
        cin >> nota;
        
        if (cin.fail() || nota < 0 || nota > 5) {
            cout << "Nota inválida. Debe ser un número entre 0 y 5.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(); // Limpiar el buffer después de un número
            return nota;
        }
    }
}

// Función para agregar un nuevo estudiante
void agregarEstudiante() {
    Estudiante nuevo;
    cout << "Ingrese nombre del estudiante: ";
    getline(cin, nuevo.nombre);
    
    cout << "Ingrese apellido del estudiante: ";
    getline(cin, nuevo.apellido);
    
    nuevo.id = obtenerIDValido();
    
    cout << "Ingrese nombre del papá: ";
    getline(cin, nuevo.nombrePapa);
    
    cout << "Ingrese nombre del mamá: ";
    getline(cin, nuevo.nombreMama);
    
    nuevo.telefono = obtenertelefonoValido();
    
    cout << "Ingrese direccion: ";
    getline(cin, nuevo.direccion);
    
    int numMaterias = obtenerEnteroPositivo("Ingrese cantidad de materias: ");

    for (int i = 0; i < numMaterias; i++) {
        Materia mat;
        cout << "Ingrese nombre de la materia: ";
        getline(cin, mat.nombre);
        cout << "Ingrese horario de la materia: ";
        getline(cin, mat.horario);
        
        mat.notas[0] = obtenerNotaValida("Ingrese la primera nota (0 - 5): ");
        mat.notas[1] = obtenerNotaValida("Ingrese la segunda nota (0 - 5): ");
        mat.notas[2] = obtenerNotaValida("Ingrese la tercera nota (0 - 5): ");

        nuevo.materias.push_back(mat);
    }

    estudiantes.push_back(nuevo);
    cout << "Estudiante agregado exitosamente.\n";
}

// Función para mostrar la información de todos los estudiantes
void mostrarEstudiantes() {
    if (estudiantes.empty()) {
        cout << "No hay estudiantes registrados.\n";
        return;
    }

    for (size_t i = 0; i < estudiantes.size(); i++) {
        cout << "\nNombre: " << estudiantes[i].nombre << " " << estudiantes[i].apellido;
        cout << "\nNombre Papá: " << estudiantes[i].nombrePapa;
        cout << "\nNombre Mamá: " << estudiantes[i].nombreMama;
        cout << "\nTeléfono: " << estudiantes[i].telefono;
        cout << "\nDirección: " << estudiantes[i].direccion;
        cout << "\nID: " << estudiantes[i].id;
        cout << "\nMaterias:";
        
        for (size_t j = 0; j < estudiantes[i].materias.size(); j++) {
            cout << "\n  - " << estudiantes[i].materias[j].nombre << " (" 
                 << estudiantes[i].materias[j].horario << ")";
            cout << "\n    Nota 1: " << estudiantes[i].materias[j].notas[0];
            cout << "\n    Nota 2: " << estudiantes[i].materias[j].notas[1];
            cout << "\n    Nota 3: " << estudiantes[i].materias[j].notas[2];
            cout << "\n    Promedio: " << estudiantes[i].materias[j].calcularPromedio();
            cout << "\n-----------------------------";
        }
        cout << "\n";
    }
}

// Función para buscar un estudiante por su ID
void buscarEstudiante() {
    string id;
    cout << "Ingrese ID del estudiante: ";
    cin >> id;
    cin.ignore(); // Limpiar buffer

    for (size_t i = 0; i < estudiantes.size(); i++) {
        if (estudiantes[i].id == id) {
            cout << "\nNombre: " << estudiantes[i].nombre << " " << estudiantes[i].apellido;
            cout << "\nNombre Papá: " << estudiantes[i].nombrePapa;
            cout << "\nNombre Mamá: " << estudiantes[i].nombreMama;
            cout << "\nTeléfono: " << estudiantes[i].telefono;
            cout << "\nDirección: " << estudiantes[i].direccion;
            cout << "\nID: " << estudiantes[i].id;
            cout << "\nMaterias:";
            
            for (size_t j = 0; j < estudiantes[i].materias.size(); j++) {
                cout << "\n  - " << estudiantes[i].materias[j].nombre << " (" 
                     << estudiantes[i].materias[j].horario << ")";
                cout << "\n    Nota 1: " << estudiantes[i].materias[j].notas[0];
                cout << "\n    Nota 2: " << estudiantes[i].materias[j].notas[1];
                cout << "\n    Nota 3: " << estudiantes[i].materias[j].notas[2];
                cout << "\n    Promedio: " << estudiantes[i].materias[j].calcularPromedio();
                cout << "\n-----------------------------";
            }
            cout << "\n";
            return;
        }
    }
    cout << "Estudiante no encontrado.\n";
}

// Función para actualizar las notas de una materia específica
void actualizarNota() {
    if (estudiantes.empty()) {
        cout << "No hay estudiantes registrados.\n";
        return;
    }
    
    while (true) {
        string id;
        cout << "Ingrese ID del estudiante: ";
        cin >> id;
        
        for (size_t i = 0; i < estudiantes.size(); i++) {
            if (estudiantes[i].id == id) {
                while (true) {
                    string materia;
                    cout << "Ingrese nombre de la materia a actualizar: ";
                    cin.ignore();
                    getline(cin, materia);
                    
                    for (size_t j = 0; j < estudiantes[i].materias.size(); j++) {
                        if (estudiantes[i].materias[j].nombre == materia) {
                            estudiantes[i].materias[j].notas[0] = obtenerNotaValida("Ingrese la primera nueva nota (0 - 5): ");
                            estudiantes[i].materias[j].notas[1] = obtenerNotaValida("Ingrese la segunda nueva nota (0 - 5): ");
                            estudiantes[i].materias[j].notas[2] = obtenerNotaValida("Ingrese la tercera nueva nota (0 - 5): ");
                            cout << "Notas actualizadas correctamente.\n";
                            return;
                        }
                    }
                    cout << "Materia no encontrada. Intente nuevamente.\n";
                }
            }
        }
        cout << "Estudiante no encontrado. Intente nuevamente.\n";
    }
}


// Función principal con menú interactivo
int main() {
    int opcion;
    do {
        cout << "\nMENU";
        cout << "\n1. Agregar estudiante";
        cout << "\n2. Mostrar estudiantes";
        cout << "\n3. Buscar estudiante";
        cout << "\n4. Actualizar notas";
        cout << "\n5. Salir";
        cout << "\nSeleccione una opción: ";
        
        if (!(cin >> opcion)) {
            cout << "Entrada inválida. Debe ingresar un número entre 1 y 5.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(); // Limpiar buffer después de leer el número
        
        switch (opcion) {
            case 1: agregarEstudiante(); break;
            case 2: mostrarEstudiantes(); break;
            case 3: buscarEstudiante(); break;
            case 4: actualizarNota(); break;
            case 5: cout << "Saliendo...\n"; break;
            default: cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (opcion != 5);

    return 0;
}
