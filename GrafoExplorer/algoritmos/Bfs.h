#pragma once

#include "../modelo/Grafo.h"
#include "../ed/ArrayQueue.h"

inline Grafo* bfs(Grafo& g, int inicio) {
	int nodos = g.cantidadNodos();
	Grafo* arbol = new Grafo(nodos, g.maxConexiones());

	// Se replican los nodos: mismas posiciones y misma numeración que el grafo base
	for (int i = 0; i < nodos; i++) {
		Nodo* nodo = g.obtenerNodo(i);
		arbol->agregarNodo(nodo->x, nodo->y);
	}

	bool* visitado = new bool[nodos];
	for (int i = 0; i < nodos; i++)
		visitado[i] = false;

	// La queue guarda a lo mucho n índices y como se marcan visitados al encolarse
	// no hay riesgo de desborde
	ArrayQueue<int> cola(nodos);
	visitado[inicio] = true;
	cola.enqueue(inicio);

	while (!cola.isEmpty()) {
		int nodoActual = cola.dequeue();
		ArrayList<int>& adyacencia = g.obtenerNodo(nodoActual)->adyacencia;
		for (adyacencia.goToStart(); !adyacencia.atEnd(); adyacencia.next()) {
			Arco* arco = g.obtenerArco(adyacencia.getElement());
			int vecino = arco->otroExtremo(nodoActual);
			if (!visitado[vecino]) {
				visitado[vecino] = true;
				arbol->agregarArco(nodoActual, vecino);
				cola.enqueue(vecino);
			}
		}
	}

	delete[] visitado;
	return arbol;
}