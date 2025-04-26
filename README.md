# EJERCICIOS C++

# TSP1

## Ejercicio 1. Generador de Cuadrados Mágicos

### Descripción

#### Programa en C++ que genera cuadrados mágicos de tamaño n×n (n impar entre 1 y 9). Un cuadrado mágico es una matriz donde la suma de números en cada fila, columna y diagonal principal es idéntica.

### Características

#### - Generación automática usando el algoritmo siamés

#### - Validación de entrada robusta

#### - Cálculo de la suma mágica

#### - Visualización formateada en tabla

#### - Manejo de errores para entradas inválidas

## Ejercicio 2. Sistema de Gestión de Inventarios

### Descripción

#### Programa en C++ que permite combinar y comparar inventarios de dos sucursales mediante operaciones con vectores.

### Funcionalidades

#### - Intercalación de inventarios: Combina los productos de dos sucursales alternando sus elementos

#### Diferencia de inventarios: Calcula la resta elemento por elemento entre sucursales

#### Validación de entrada: Asegura que solo se ingresen valores enteros

#### Visualización clara: Muestra los resultados de forma organizada

## Ejercicio 3. Sistema de Gestión de Pedidos - Hamburguesería

### Descripción

#### Programa en C++ que simula un sistema de pedidos para una hamburguesería, utilizando:

##### - Colas (queue) para gestionar pedidos en orden FIFO

##### - Mapas (map) para asociar códigos con productos

##### - Estructuras de datos para almacenar información de clientes

## Ejercicio 4. Árbol Binario de Búsqueda: Cálculo del Grado de un Nodo

### Descripción

#### Este programa en C++ implementa un Árbol Binario de Búsqueda (ABB) que permite:

#### 1. Insertar nodos manteniendo el orden del árbol.

#### 2. Buscar un nodo específico y determinar su grado (número de hijos: 0, 1 o 2).

### Funcionalidades

#### 1. Inserción de Nodos

##### - Los valores se insertan automáticamente en su posición correcta según el orden del ABB.

#### 2. Cálculo del Grado

##### - Grado 0: Nodo sin hijos (hoja).

##### - Grado 1: Nodo con un solo hijo (izquierdo o derecho).

##### - Grado 2: Nodo con dos hijos.

# TP1

## Ejercicio 1: Búsqueda Binaria en Grafos

### Descripción

#### Implementación de un grafo no dirigido en C++ usando POO para resolver problemas de rutas óptimas en una red de oficinas. El objetivo es encontrar el número medio de enlaces necesarios desde un nodo central hacia otras sedes.

### Componentes Clave

#### - Clases: `Nodo`, `ListaEnlazada`, `Cola`, `Grafo`

#### - Algoritmos:

#### - Floyd-Warshall (complejidad O(n³))

#### - BFS (Búsqueda en Anchura)

#### - DFS (Búsqueda en Profundidad)

#### - Estructuras: Matriz de adyacencia, listas enlazadas

### Solución

#### - Calcula rutas óptimas desde el nodo central (S) a todas las sedes

#### - Determina el número medio de enlaces (saltos)

## Ejercicio 2: Ordenación de Listas

### Descripción

#### Implementación del algoritmo Selection Sort en C++ usando POO, recursividad y estructuras dinámicas para ordenar listas de enteros.

### Características Principales

#### - Clases: `Nodo`, `ListaEnlazada`, `OrdenadorSeleccion`

#### - Algoritmo: Selection Sort recursivo (complejidad O(n²))

#### - Funcionalidades:

#### - Inserción de elementos por usuario

#### - Visualización de lista original y ordenada

#### - Implementación sin librerías externas

### Ventajas

#### - Código educativo y claro

#### - Estructuras implementadas desde cero

#### - Fácil extensión para otros tipos de datos

## Ejercicio 3: Grafo de Sedes con Quicksort y Búsqueda Binaria

### Descripción

#### Sistema que genera 999 números reales aleatorios, los ordena con Quicksort y permite búsquedas binarias recursivas.

### Componentes

#### - Clases: `Nodo`, `ListaEnlazada`, `ColaResultados`

#### - Algoritmos:

#### - Quicksort adaptado para listas enlazadas (O(n log n))

#### - Búsqueda binaria recursiva (O(log n))

#### - Funcionalidades:

#### - Generación automática de datos

#### - Múltiples búsquedas interactivas

#### - Visualización de resultados

### Diseño

#### 1. Generación de 999 números en [0, 2000]

#### 2. Ordenación con Quicksort adaptado

#### 3. Interfaz para búsquedas binarias múltiples

#### 4. Gestión eficiente de memoria
