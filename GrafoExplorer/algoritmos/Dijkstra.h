/*
 * Archivo: Dijkstra.h
 *
 * Implementación del algoritmo de Dijkstra para encontrar la ruta más corta
 * entre dos nodos en un grafo no dirigido y ponderado. El algoritmo calcula
 * las distancias mínimas desde un nodo inicial hasta todos los demás, y
 * reconstruye el camino hacia un nodo destino específico. Utiliza distancias
 * acumuladas (tipo float) para manejar pesos geométricos con precisión.
 *
 * Funcionalidades:
 * - dijkstra(Grafo& g, int inicio, int destino): toma una referencia al grafo
 *   base y los índices del nodo inicial y destino. Devuelve un nuevo grafo que
 *   contiene los mismos nodos que g con sus posiciones originales, pero solo
 *   los arcos que forman la ruta más corta desde inicio hasta destino.
 * - Si no existe ruta hacia el destino, devuelve un grafo solo con nodos.
 * - Memoria: el grafo resultado es responsabilidad de quien invoca liberar.
 *
 * Autores: Edwin Muñoz, Francisco Mora
 */

#pragma once

#include "../modelo/Grafo.h"
#include "../ed/ArrayList.h"

inline Grafo* dijkstra(Grafo& g, int inicio, int destino) {
	int nodos = g.cantidadNodos();
	int arcos = g.cantidadArcos();
	Grafo* arbol = new Grafo(nodos, g.maxConexiones());

	// Se replican los nodos: mismas posiciones y misma numeración que el grafo base
	for (int i = 0; i < nodos; i++) {
		Nodo* nodo = g.obtenerNodo(i);
		arbol->agregarNodo(nodo->x, nodo->y);
	}

	float* distancia = new float[nodos];
	for (int i = 0; i < nodos; i++) {
		if (i == inicio) {
			distancia[i] = 0;
		}
		else {
			distancia[i] = 1e30f;
		}
	}

	int* rutas = new int[nodos];
	rutas[inicio] = inicio;
	bool* definitivos = new bool[nodos];
	for (int i = 0; i < nodos; i++) {
		definitivos[i] = false;
	}

	while (definitivos[destino] == false) {
		int nodoActual = -1;
		float distanciaMenor = 1e30f;
		for (int i = 0; i < nodos; i++) {
			if (!definitivos[i] && distancia[i] < distanciaMenor) {
				distanciaMenor = distancia[i];
				nodoActual=i;
			}
		}

		if (nodoActual == -1)
			break;

		definitivos[nodoActual] = true;
		Nodo* n = g.obtenerNodo(nodoActual);
		for (int i = 0; i < n->gradoActual(); i++) {
			n->adyacencia.goToPos(i);
			int indiceArco = n->adyacencia.getElement();
			Arco* arco = g.obtenerArco(indiceArco);
			int vecino = arco->otroExtremo(nodoActual);

			if (!definitivos[vecino]) {
				float nuevaDistancia = distancia[nodoActual] + arco->peso;
				if (nuevaDistancia < distancia[vecino]) {
					distancia[vecino] = nuevaDistancia;
					rutas[vecino] = nodoActual;
				}
			}
		}
	}
	if (definitivos[destino]) {
		int temp = destino;
		while (temp != inicio) {
			int anterior = rutas[temp];
			arbol->agregarArco(anterior, temp);
			temp = anterior;
		}
	}

	delete[] distancia;
	delete[] rutas;
	delete[] definitivos;

	return arbol;
}