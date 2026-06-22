/*
 * Archivo: Bfs.h
 *
 * Implementacion del algoritmo de búsqueda en anchura (BFS) para generar un 
 * árbol de expansión sobre un grafo no dirigido. El algoritmo parte de un 
 * nodo inicial, lo marca como visitado, y explora todos sus vecinos por 
 * niveles mediante una cola antes de descender a la siguiente profundidad. 
 * Solo agrega arcos hacia nodos aún no visitados, formando un árbol conexo
 * que representa el espacio alcanzable desde el inicio.
 *
 * Funcionalidades:
 * - bfs(Grafo& g, int inicio): toma una referencia al grafo base y el índice
 *   del nodo inicial. Devuelve un nuevo grafo que contiene los mismos nodos 
 *   que g con sus posiciones originales, pero solo los arcos que forman
 *   el árbol BFS a partir de inicio.
 * - Memoria: el grafo resultado es responsabilidad de quien invoca liberar.
 *
 * Autores: Edwin Muñoz, Francisco Mora
 */

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