/*
 * Archivo: Kruskal.h
 *
 * Implementación del algoritmo de Kruskal para generar un árbol (o bosque) de
 * expansión mínima sobre un grafo no dirigido. El algoritmo ordena los arcos 
 * por peso de forma ascendente y los agrega uno a uno, siempre que no creen un 
 * ciclo. Utiliza Union-Find para detectar ciclos de manera eficiente verificando 
 * si ambos extremos de un arco pertenecen al mismo conjunto.
 *
 * Funcionalidades:
 * - kruskal(Grafo& g): toma una referencia al grafo base. Devuelve un nuevo grafo
 *   que contiene los mismos nodos que g con sus posiciones originales, pero solo
 *   los arcos que forman el árbol (o bosque) de expansión mínima del grafo.
 * - Utiliza UnionFind para mantener conjuntos disjuntos de nodos. Un arco se
 *   agrega solo si su método unite() devuelve true, lo que indica que los
 *   extremos no estaban en el mismo conjunto.
 * - Si el grafo es desconectado, devuelve un bosque (múltiples árboles).
 * - Memoria: el grafo resultado es responsabilidad de quien invoca liberar.
 *
 * Autores: Edwin Muñoz, Francisco Mora
 */

#pragma once

#include "../modelo/Grafo.h"
#include "../ed/HeapPriorityQueue.h"
#include "../ed/UnionFind.h"

inline Grafo* kruskal(Grafo& g) {
	int nodos = g.cantidadNodos();
	int arcos = g.cantidadArcos();
	Grafo* bosque = new Grafo(nodos, g.maxConexiones());

	// Se replican los nodos: mismas posiciones y misma numeración que el grafo base
	for (int i = 0; i < nodos; i++) {
		Nodo* nodo = g.obtenerNodo(i);
		bosque->agregarNodo(nodo->x, nodo->y);
	}

	HeapPriorityQueue<int> cola(arcos < 1 ? 1 : arcos);
	for (int i = 0; i < arcos; i++)
		cola.insert(i, g.obtenerArco(i)->peso);

	UnionFind conjuntos(nodos);

	while (!cola.isEmpty()) {
		Arco* arco = g.obtenerArco(cola.removeMin());
		if (conjuntos.unite(arco->extremoA, arco->extremoB))
			bosque->agregarArco(arco->extremoA, arco->extremoB);
	}

	return bosque;
}