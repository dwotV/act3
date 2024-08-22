#include <bits/stdc++.h>
#include <iostream>

using namespace std;

#define M 4
#define N 4

struct posicion {
  int x;
  int y;
};

void mostrarSolucion(int mat[M][N]) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if (mat[i][j] == INT_MAX) {
        cout << "0" << " ";
      } else {
        if (mat[i][j] == 0) {
          cout << "0" << " ";
        } else {
          if (mat[i][j] != 0 && mat[i][j] != INT_MAX) {
            cout << "1" << " ";
          } else {
            cout << mat[i][j] << " ";
          }
        }
      }
    }
    cout << "\n";
  }
}

int esSolucion(struct posicion *solucion, int paso, int mat[M][N]) {
  return (solucion[paso].x == M-1 && solucion[paso].y == N-1);
}

int generarCandidatos(struct posicion *solucion, struct posicion candidatos[], int mat[M][N], int paso) {
  int NC = 0;
  int X = solucion[paso - 1].x;
  int Y = solucion[paso - 1].y;

  //arriba
  if(mat[X - 1][Y] == 0 && (X > 0)) {
    candidatos[NC].x = X - 1;
    candidatos[NC].y = Y;
    NC++;
  }
  //abajo
  if(mat[X + 1][Y] == 0 && (X < M - 1)) {
    candidatos[NC].x = X + 1;
    candidatos[NC].y = Y;
    NC++;
  }
  //derecha
  if(mat[X][Y + 1] == 0 && (Y < N - 1)) {
    candidatos[NC].x = X;
    candidatos[NC].y = Y + 1;
    NC++;
  }
  //izquierda
  if(mat[X][Y - 1] == 0 && (Y > 0)) {
    candidatos[NC].x = X;
    candidatos[NC].y = Y - 1;
    NC++;
  }
  return NC;
}

void backtracking(struct posicion *solucion, int paso, int mat[M][N]) {
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
      mat[solucion[paso].x][solucion[paso].y] = 1 + paso;

      backtracking(solucion, paso, mat);
      //Desbloquear

      mat[solucion[paso].x][solucion[paso].y] = 0;
    }
  }
}

int main (int argc, char *argv[]) {

  struct posicion solucion[M*N];

  int mat[M][N];
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      cin >> mat[i][j];
      if (mat[i][j] == 0) {
        mat[i][j] = INT_MAX;
      }
    }
  }

  for (int i = 0; i < M; i++){
    for (int j = 0; j < N; j++) {
      if (mat[i][j] == 1) {
        mat[i][j] = 0;
      }
    }
  }

  solucion[0].x = 0;
  solucion[0].y = 0;
  mat[0][0] = 1;

  backtracking(solucion, 0, mat);

  return 0;
}
