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

	// MinHeap por peso (float). El elemento es el índice del arco en la lista central del grafo
	// La prioridad es su peso
	HeapPriorityQueue<int> cola(arcos < 1 ? 1 : arcos);
	for (int i = 0; i < arcos; i++)
		cola.insert(i, g.obtenerArco(i)->peso);

	// Union-Find sobre los nodos para detectar ciclos
	UnionFind conjuntos(nodos);

	while (!cola.isEmpty()) {
		Arco* arco = g.obtenerArco(cola.removeMin());
		if (conjuntos.unite(arco->extremoA, arco->extremoB))
			bosque->agregarArco(arco->extremoA, arco->extremoB);
	}

	return bosque;
}