#include <iostream>
#include <limits> 
using namespace std;

// Función para llenar la matriz inicial con espacios vacíos (' ')
void inicializarTablero(char tablero[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tablero[i][j] = ' ';
        }
    }
}

// Función para mostrar el tablero en la consola
void imprimirTablero(char tablero[3][3]) {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << " " << tablero[i][j] << " ";
            if (j < 2) cout << "|"; // Separadores de columnas
        }
        cout << "\n";
        if (i < 2) cout << "---|---|---\n"; // Separadores de filas
    }
    cout << "\n";
}

// Función para revisar 3 filas, 3 columnas y 2 diagonales
bool verificarGanador(char tablero[3][3], char jugador) {
    // Recorrer filas y columnas con un ciclo for
    for (int i = 0; i < 3; i++) {
        // Validar si toda una fila o toda una columna tiene la marca del jugador
        if ((tablero[i][0] == jugador && tablero[i][1] == jugador && tablero[i][2] == jugador) ||
            (tablero[0][i] == jugador && tablero[1][i] == jugador && tablero[2][i] == jugador)) {
            return true;
        }
    }
    
    // Validar las dos diagonales
    if ((tablero[0][0] == jugador && tablero[1][1] == jugador && tablero[2][2] == jugador) ||
        (tablero[0][2] == jugador && tablero[1][1] == jugador && tablero[2][0] == jugador)) {
        return true;
    }
    
    return false;
}

// Función para detectar si ya no quedan espacios libres (empate)
bool verificarEmpate(char tablero[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tablero[i][j] == ' ') {
                return false; // Al encontrar un espacio, el juego puede continuar
            }
        }
    }
    return true; // No hay espacios vacíos
}

int main() {
    char tablero[3][3];
    char jugadorActual = 'X';
    bool juegoTerminado = false;
    int fila, columna;

    inicializarTablero(tablero);
    cout << "--- JUEGO DEL GATO ---" << endl;

    
    while (!juegoTerminado) {
        imprimirTablero(tablero);
        
        cout << "Turno del jugador " << jugadorActual << ".\n";
        cout << "Ingresa la fila (1-3) y la columna (1-3) separadas por un espacio: ";
        
        //evita que el programa se congele o cierre si ingresan letras
        if (!(cin >> fila >> columna)) {
            cout << "\n[Error] Ingresa unicamente valores numericos.\n";
            cin.clear(); // Limpia el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta la basura del buffer
            continue; // Obliga a repetir el turno inmediatamente
        }

        // Ajustamos la entrada (1-3) al índice real de la matriz en C++ (0-2)
        fila--; 
        columna--;

        // Validar: 1. Posición dentro de los límites y 2. Casilla libre (' ')
        if (fila >= 0 && fila < 3 && columna >= 0 && columna < 3 && tablero[fila][columna] == ' ') {
            
            // Registrar la jugada en la matriz
            tablero[fila][columna] = jugadorActual;

            // Detectar si el movimiento actual le da la victoria al jugador
            if (verificarGanador(tablero, jugadorActual)) {
                imprimirTablero(tablero);
                cout << "\n¡FELICIDADES! El jugador " << jugadorActual << " ha ganado la partida.\n";
                juegoTerminado = true;
            } 
            // Detectar el empate si el tablero se llenó y nadie ganó
            else if (verificarEmpate(tablero)) {
                imprimirTablero(tablero);
                cout << "\n¡ES UN EMPATE! Ya no quedan casillas libres.\n";
                juegoTerminado = true;
            } 
            // Alternar turnos
            else {
                jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
            }
        } else {
            // 3. Si la jugada no es válida, el mismo jugador repite su turno
            cout << "\n[Movimiento Invalido] La posicion esta fuera del tablero o la casilla ya esta ocupada. Intenta de nuevo.\n";
        }
    }

    return 0;
}