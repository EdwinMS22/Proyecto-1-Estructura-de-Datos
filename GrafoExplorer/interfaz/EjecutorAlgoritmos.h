/*
 * EjecutorAlgoritmos.h
 *
 * Interfaz abstracta que desacopla la capa de interfaz de la lógica 
 * de ejecución de algoritmos, evitando dependencias circulares entre 
 * ambas capas. Define el enum Algoritmo con los cinco algoritmos disponibles 
 * (DFS, BFS, Prim, Kruskal, Dijkstra).
 *
 * Funcionalidades:
 * - enum class Algoritmo: identifica el algoritmo a ejecutar (DFS,
 *   BFS, PRIM, KRUSKAL, DIJKSTRA).
 * - ejecutarAlgoritmo(algoritmo, nodoInicio, nodoDestino): método
 *   virtual puro que ejecuta el algoritmo indicado sobre el grafo base
 *   y devuelve el Grafo* resultado, o nullptr si no hay resultado. 
 *   La propiedad del resultado pertenece a quien implementa la interfaz.
 * - regenerarGrafo(): método virtual puro que genera un nuevo grafo
 *   base y lo devuelve.
 *
 * Autores: Edwin Muñoz, Francisco Mora
 */

#pragma once

#include "../modelo/Grafo.h"

enum class Algoritmo {DFS, BFS, PRIM, KRUSKAL, DIJKSTRA};

class EjecutorAlgoritmos {
public:
	virtual ~EjecutorAlgoritmos() = default;

	virtual Grafo* ejecutarAlgoritmo(Algoritmo algoritmo, int nodoInicio, int nodoDestino) = 0;
	virtual Grafo* regenerarGrafo() = 0;
};