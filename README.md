
# Laberinto 

Esta tarea resuelve un laberinto utilizando dos enfoques distintos: **Backtracking** y **Ramificación y Poda**. Se lee una matriz de entrada a través de un archivo .txt que representa el laberinto y se busca una ruta desde el origen (0,0) hasta la meta (M-1,N-1).

## Requisitos

- Un compilador de C++ (g++ recomendado)
- Linux u otro sistema operativo compatible con compiladores de C++
- Matriz en el archivo

## Compilación y Ejecución

El programa toma la entrada redireccionada desde un archivo, por ejemplo:

```bash
./Laberinto < in.txt
```

## Formato del Archivo de Entrada

El archivo de entrada `in.txt` debe tener el siguiente formato:

1. La primera línea  el entero `M` (el número de columnas)
2. La segunda línea al entero `N` (el número de filas)
   - `1` representa un camino válido.
   - `0` obstáculo

### Ejemplo

`in.txt`:

```
5
5
1 0 0 0 1
1 0 0 0 0
1 0 0 0 1
1 1 1 1 0
0 1 0 1 1
```

### Salida
Muestra todas las posibles soluciones para backtracking, y la mejor solución a través de poda, junto con unn análisis cuantitativo en eficiencia de ejecución.
```
Backtracking:
1 0 0 0 0
1 0 0 0 0
1 0 0 0 0
1 1 1 1 0
0 0 0 1 1

Ramificación y Poda - Mejor Solución:
1 0 0 0 0
1 0 0 0 0
1 0 0 0 0
1 1 1 1 0
0 0 0 1 1
```

Tiempo de Backtracking: 12028 microsegundos.
Tiempo de Ramificación y Poda: 109 microsegundos.
Ramificación y Poda es más rápido por un 99.0938%.


### Compilación

Si encuentras problemas al compilar, asegúrate de que `g++` está instalado correctamente y que el archivo `main.cpp` no contiene errores de sintaxis.

## Autores

Este proyecto fue desarrollado por Dael Chávez Ferreyra y Andrea Bahena Valdés.

Algoritmos Avanzados
