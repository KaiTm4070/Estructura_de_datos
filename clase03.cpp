/* Ejercisio de la clase 3  sillas del teatro*/
#include <iostream>
#include <cctype>
using namespace std;

char mappa[10][15];

//iniciar el mapa en (L)
void inicioMapa(){
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 15; j++) {
            mappa[i][j] = 'L';
        }
    }
}

// Mostrar el mapa
void mostrarMapa() {
    // Lista de letras (A - O)
    cout << "   ";  // espacio para numeración de filas
    for (char letra = 'A'; letra <= 'O'; letra++) {
        cout << letra << "       ";  // tres espacios para alineación
    }
    cout << endl;

    // Mostrar filas con numeración y asientos alineados
    for (int i = 0; i < 10; i++) {
        // Imprimir número de la fila 
        cout << (i + 1);
        if (i + 1 < 10) cout << "  "; // Agregar espacio extra para alinear con el 10
        else cout << " ";
        
        for (int j = 0; j < 15; j++) {
            cout << char('A' + j) << (i + 1) << "(" << mappa[i][j] << ") ";
            
            // Si el número es de un solo dígito (1 - 9), agregar un espacio extra
            if (i + 1 < 10) cout << "  ";
            else cout << " ";
        }
        cout << endl;
    }
}

// Obtener indice de la columna
int obtenerIndiceColumna(char letra){
    if(letra >= 'A' && letra <= 'O'){
        return letra - 'A'; //Convierte la laetras en su indice correspondiente a la columna
    }
    return -1; //retorna -1 si se ingresa una letra diferente del rango (A - O)
}

//Reservar asiento
void reservaAsiento(){
    int fila;
    char columna;
    cout << "ingrese la fila (1-10): ";
    cin >> fila;
    cout <<"Ingrese la columna (A-O): ";
    cin >> columna;
    
    columna = toupper(columna);
    
    int indice_col = obtenerIndiceColumna(columna);
    
    if(fila < 1 || fila > 10 || indice_col == -1){
        cout << "Asiento invalido. Intente nuevamente.\n";
        return;
    }
    
    if(mappa[fila - 1][indice_col] == 'L'){
        mappa[fila - 1][indice_col] = 'R';
        cout << "Asiento " << columna << fila << " reservado con éxito.\n";
    } else {
        cout << "El asiento ya esta ocupado o reservado.\n";
    }
}
    
// cancelar reservad
void cancelarReserva(){
    int fila;
    char columna;
    cout << "ingrese la fila (1-10): ";
    cin >> fila;
    cout <<"Ingrese la columna (A-O): ";
    cin >> columna;
    
    columna = toupper(columna);
    
    int indice_col = obtenerIndiceColumna(columna);
    
    if(fila < 1 || fila > 10 || indice_col == -1){
        cout << "Asiento invalido. Intente nuevamente.\n";
        return;
    }
    
    if(mappa[fila - 1][indice_col] == 'R'){
        mappa[fila - 1][indice_col] = 'L';
        cout << "Reserva cancelada con éxito.\n";
        
    } else {
        cout << "Error al cancelar, asiento sin reservar...\n";
    }
}

// Marcar como ocupado
void ocuparAsiento(){
    int fila;
    char columna;
    cout << "ingrese la fila (1-10): ";
    cin >> fila;
    cout <<"Ingrese la columna (A-O): ";
    cin >> columna;
    
    columna = toupper(columna);
    
    int indice_col = obtenerIndiceColumna(columna);
    
    if (mappa[fila - 1][indice_col] == 'L') {
        mappa[fila - 1][indice_col] = 'O';
        cout << "Asiento " << columna << fila << " Asiento ocupado con exito.\n";
    } 
    else if (mappa[fila - 1][indice_col] == 'R') {
        cout << "El asiento ya está reservado. No se puede reservar nuevamente.\n";
    } 
    else if (mappa[fila - 1][indice_col] == 'O') {
        cout << "El asiento está ocupado y no puede ser reservado.\n";
    } 
    else {
        cout << "Error desconocido. Intente nuevamente.\n";
    }
}

// Menú de opciones
void menu() {
    int opcion;
    do {
        cout << "\nMenú de opciones:" << endl;
        cout << "1. Mostrar mapa de asientos" << endl;
        cout << "2. Reservar un asiento" << endl;
        cout << "3. Cancelar una reserva" << endl;
        cout << "4. Marcar un asiento como ocupado" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1:
                mostrarMapa();
                break;
            case 2:
                reservaAsiento();
                break;
            case 3:
                cancelarReserva();
                break;
            case 4:
                ocuparAsiento();
                break;
            case 5:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción inválida. Intente nuevamente." << endl;
        }
    } while (opcion != 5);
}

int main() {
    inicioMapa();
    menu();
    return 0;
}