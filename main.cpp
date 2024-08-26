#include <bits/stdc++.h>
#include <cstring>
#include <iostream>

using namespace std;

int M;
int N;

struct posicion {
    int x;
    int y;
};

int *mejorSolucion = nullptr;

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

int esSolucion(struct posicion *solucion, int paso, int *mat) {
    return (solucion[paso].x == M - 1 && solucion[paso].y == N - 1);
}

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

void backtracking(struct posicion *solucion, int paso, int *mat) {
  if (esSolucion(solucion, paso, mat)) {
    cout << "\nBacktracking:\n";
    mostrarSolucion(mat);
  }else{
    paso = paso + 1;
    int NC, i;
    struct posicion candidatos[4];
    NC = generarCandidatos(solucion, candidatos, mat, paso);
    for (i = 0; i < NC; i++) {
      solucion[paso] = candidatos[i];
      //Bloquear
      mat[solucion[paso].x * N + solucion[paso].y] = 1 + paso;

      backtracking(solucion, paso, mat);
      //Desbloquear

      mat[solucion[paso].x * N + solucion[paso].y] = 0;
    }
  }
}

void poda(struct posicion *solucion, int paso, int *mat, int &mejorPaso) {
    if (esSolucion(solucion, paso, mat)) {
        if (paso < mejorPaso) {
          mejorPaso = paso;

          if (mejorSolucion == nullptr) {
            mejorSolucion = new int[M * N];
          }
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

    backtracking(solucion, 0, mat);
    poda(solucion, 0, mat, mejorPaso);

    if (mejorSolucion != nullptr) {
      cout << "\nRamificación y poda:\n";
      mostrarSolucion(mejorSolucion);
      delete [] mejorSolucion;
    }else {
      cout << "\nNo tiene mejor solución\n";
    }

    return 0;
}
