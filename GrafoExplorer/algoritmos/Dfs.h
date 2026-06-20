#pragma once

#include "../modelo/Grafo.h"
#include "../ed/ArrayStack.h"

inline Grafo* dfs(Grafo& g, int inicio) {
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

	// El stack guarda a lo mucho n índices y como se marcan visitados al meter al stack
	// no hay riesgo de overflow
	ArrayStack<int> pila(nodos);
	visitado[inicio] = true;
	pila.push(inicio);

	while (!pila.isEmpty()) {
		int nodoActual = pila.pop();
		ArrayList<int>& adyacencia = g.obtenerNodo(nodoActual)->adyacencia;
		for (adyacencia.goToStart(); !adyacencia.atEnd(); adyacencia.next()) {
			Arco* arco = g.obtenerArco(adyacencia.getElement());
			int vecino = arco->otroExtremo(nodoActual);
			if (!visitado[vecino]) {
				visitado[vecino] = true;
				arbol->agregarArco(nodoActual, vecino);
				pila.push(vecino);
			}
		}
	}

	delete[] visitado;
	return arbol;
}