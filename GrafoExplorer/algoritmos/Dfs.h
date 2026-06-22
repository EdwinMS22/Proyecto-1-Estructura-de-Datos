/*
 * Archivo: Dfs.h
 *
 * Implementación del algoritmo de búsqueda en profundidad (DFS) para generar un
 * árbol de expansión sobre un grafo no dirigido. El algoritmo parte de un nodo
 * inicial, lo marca como visitado, y explora mediante una pila en la dirección 
 * más profunda posible antes de retroceder. Solo agrega arcos hacia nodos aún 
 * no visitados, formando un árbol conexo que representa el espacio alcanzable 
 * desde el inicio.
 *
 * Funcionalidades:
 * - dfs(Grafo& g, int inicio): toma una referencia al grafo base y el índice
 *   del nodo inicial. Devuelve un nuevo grafo que contiene los mismos nodos
 *   que g con sus posiciones originales, pero solo los arcos que forman
 *   el árbol DFS a partir de inicio.
 * - Memoria: el grafo resultado es responsabilidad de quien invoca liberar.
 *
 * Autores: Edwin Muñoz, Francisco Mora
 */

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