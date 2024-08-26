/*
 Actividad 1.3 Técnicas de Ramificación y Poda
 Análisis y diseño de algoritmos avanzados

 A01771963 -  Dael Chávez Ferreyra
 A01369019 -  Andrea Bahena Valdés

 Este programa encuentra la solución a un laberinto
 a través de dos enfoques.

    a) Backtracking: Algoritmo de búsqueda en profundidad
    b) Ramificación: Algoritmo de búsqueda en amplitud
                     y búsqueda por costo (caminos mínimos)


 Adicionalmente, se incluyó un análisis numérico de la eficiencia
 de cada enfoque.

 Fecha de la última modificación: 25 de agosto del 2024

*/

#include <bits/stdc++.h>
#include <chrono>
#include <cstring>
#include <iostream>

using namespace std;
using namespace std::chrono;

int M;      // Columnas del laberinto
int N;      // Filas del laberinto


// Posición en el laberinto

struct posicion {
    int x;
    int y;
};

int *mejorSolucion = nullptr;


/*
 Función: despliega en la pantalla la matriz de solución
 Parámetros: mat - matriz con la solución
 Valor de retorno: -
*/
void mostrarSolucion(int *mat) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (mat[i * N + j] == INT_MAX) {
                cout << "0 ";
            } else if (mat[i * N + j] == 0) {
                cout << "0 ";
            } else {
                cout << "1 ";
            }
        }
        cout << "\n";
    }
}

/*
 Función: verifica si la posición actual es la posición de salida
 Parámetros: solucion = arreglo del camino actual, paso, mat = laberinto
 Valor de retorno: booleano de si ya está en la salida
*/

int esSolucion(struct posicion *solucion, int paso, int *mat) {
    return (solucion[paso].x == M - 1 && solucion[paso].y == N - 1);
}

/*

 Función: almacena las posiciones candidatas
 Parámetros: solucion, candidatos: posiciones candidatas, mat, paso
 Valor de retorno: total de candidatos

*/
int generarCandidatos(struct posicion *solucion, struct posicion candidatos[], int *mat, int paso) {
    int NC = 0;
    int X = solucion[paso - 1].x;
    int Y = solucion[paso - 1].y;

    // arriba
    if (X > 0 && mat[(X - 1) * N + Y] == 0) {
        candidatos[NC].x = X - 1;
        candidatos[NC].y = Y;
        NC++;
    }
    // abajo
    if (X < M - 1 && mat[(X + 1) * N + Y] == 0) {
        candidatos[NC].x = X + 1;
        candidatos[NC].y = Y;
        NC++;
    }
    // derecha
    if (Y < N - 1 && mat[X * N + (Y + 1)] == 0) {
        candidatos[NC].x = X;
        candidatos[NC].y = Y + 1;
        NC++;
    }
    // izquierda
    if (Y > 0 && mat[X * N + (Y - 1)] == 0) {
        candidatos[NC].x = X;
        candidatos[NC].y = Y - 1;
        NC++;
    }
    return NC;
}

/*

 Función: búsqueda en profundidad para encontrar todas las soluciones
 Parámetros: solucion, paso, mat
 Valor de retorno: -
 Complejidad Algorítmica: O(b^d) b= promedio de hijos, d= profundidad


*/
void backtracking(struct posicion *solucion, int paso, int *mat) {
    if (esSolucion(solucion, paso, mat)) {
        cout << "\nBacktracking:\n";
        mostrarSolucion(mat);
    } else {
        paso = paso + 1;
        int NC, i;
        struct posicion candidatos[4];
        NC = generarCandidatos(solucion, candidatos, mat, paso);
        for (i = 0; i < NC; i++) {
            solucion[paso] = candidatos[i];
            // Bloquear
            mat[solucion[paso].x * N + solucion[paso].y] = 1 + paso;

            backtracking(solucion, paso, mat);
            // Desbloquear

            mat[solucion[paso].x * N + solucion[paso].y] = 0;
        }
    }
}

/*

 Función: Optimización de búsqueda de profundidad
 Parámetros: solucion, paso, mat, mejorPaso= longitud del mejor camino
 Valor de retorno: -
 Complejidad Algorítmica: O(b^d) b= promedio de hijos, d= profundidad

 El beneficio sobre la poda es que no tiene que buscar a todos los hijos


*/

void poda(struct posicion *solucion, int paso, int *mat, int &mejorPaso) {
    if (esSolucion(solucion, paso, mat)) {
        if (paso < mejorPaso) {
            mejorPaso = paso;

            if (mejorSolucion == nullptr) {
                mejorSolucion = new int[M * N];
            }

// Se hace una copia en memoria para prevenir violaciones de segmentos 'core'
            memcpy(mejorSolucion, mat, M * N * sizeof(int));
        }
        return;
    }
    if (paso >= mejorPaso) {
        return;
    } else {
        paso = paso + 1;
        int NC, i;
        struct posicion candidatos[4];
        NC = generarCandidatos(solucion, candidatos, mat, paso);
        for (i = 0; i < NC; i++) {
            solucion[paso] = candidatos[i];
            // Bloquear
            mat[solucion[paso].x * N + solucion[paso].y] = 1 + paso;

            poda(solucion, paso, mat, mejorPaso);

            // Desbloquear
            mat[solucion[paso].x * N + solucion[paso].y] = 0;
        }
    }
}

int main(int argc, char *argv[]) {
    cin >> M >> N;

    int mat[M * N];
    struct posicion solucion[M * N];

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cin >> mat[i * N + j];
            if (mat[i * N + j] == 0) {
                mat[i * N + j] = INT_MAX;
            }
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (mat[i * N + j] == 1) {
                mat[i * N + j] = 0;
            }
        }
    }

    solucion[0].x = 0;
    solucion[0].y = 0;
    mat[0] = 1;

    int mejorPaso = INT_MAX;

    /* Medir tiempo de ejecución para Backtracking y de la ramificación y poda
       Esto funciona mediante la librería Chrono
    */
    auto start = high_resolution_clock::now();
    backtracking(solucion, 0, mat);
    auto stop = high_resolution_clock::now();
    auto durationBacktracking = duration_cast<microseconds>(stop - start);

    start = high_resolution_clock::now();
    poda(solucion, 0, mat, mejorPaso);
    stop = high_resolution_clock::now();
    auto durationPoda = duration_cast<microseconds>(stop - start);

    if (mejorSolucion != nullptr) {
        cout << "\nRamificación y poda:\n";
        mostrarSolucion(mejorSolucion);
        delete[] mejorSolucion;
    } else {
        cout << "\nNo tiene mejor solución\n";
    }

    cout << "\nTiempo de Backtracking: " << durationBacktracking.count() << " microsegundos.\n";
    cout << "Tiempo de Ramificación y Poda: " << durationPoda.count() << " microsegundos.\n";

    if (durationPoda.count() < durationBacktracking.count()) {
        double porcentaje = (double)(durationBacktracking.count() - durationPoda.count()) / durationBacktracking.count() * 100;
        cout << "Ramificación y Poda es más rápido por un " << porcentaje << "%.\n";
    } else {
        double porcentaje = (double)(durationPoda.count() - durationBacktracking.count()) / durationPoda.count() * 100;
        cout << "Backtracking es más rápido por un " << porcentaje << "%.\n";
    }

    return 0;
}
