#include <iostream>
#include <string>
#include <limits> // Para limpiar el buffer correctamente
using namespace std;

// Definición de la estructura Producto
struct Producto {
    int id;
    string nombre;
    double precio;
    int cantidad;
};

// Función para imprimir la información de un producto
void imprimirProducto(const Producto& producto) {
    cout << "ID: " << producto.id << endl;
    cout << "Nombre: " << producto.nombre << endl;
    cout << "Precio: $" << producto.precio << endl;
    cout << "Cantidad disponible: " << producto.cantidad << endl;
}

// Función para validar entrada numérica (int > 0)
int validarEntero(string mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        
        if (cin.fail() || valor <= 0) { 
            cout << "Error: Ingrese un número entero válido mayor que 0.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer
            return valor;
        }
    }
}

// Función para validar entrada numérica (double > 0)
double validarDouble(string mensaje) {
    double valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        
        if (cin.fail() || valor <= 0) {
            cout << "Error: Ingrese un número válido mayor que 0.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer
            return valor;
        }
    }
}

int main() {
    // Pedir al usuario cuántos productos desea agregar (debe ser mayor que 0)
    int numProductos = validarEntero("Ingrese la cantidad de productos a registrar: ");

    // Creación del arreglo de estructuras Producto
    Producto productos[numProductos];

    // Registro de los productos
    for (int i = 0; i < numProductos; ++i) {
        productos[i].id = i + 1; // ID autoincrementado
        
        cout << "\nIngrese los datos del producto " << productos[i].id << ":\n";
         
        cout << "Nombre: ";
        getline(cin, productos[i].nombre);
        
        // Validar precio (double > 0)
        productos[i].precio = validarDouble("Precio: ");
        
        // Validar cantidad (int > 0)
        productos[i].cantidad = validarEntero("Cantidad disponible: ");
    }

    // Mostrar la información de los productos
    cout << "\nLista de productos registrados:\n";
    for (int i = 0; i < numProductos; ++i) {
        cout << "\nInformación del producto " << i + 1 << ":\n";
        imprimirProducto(productos[i]);
    }

    return 0;
}