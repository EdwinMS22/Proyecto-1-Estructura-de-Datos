#pragma once

#include "../modelo/Grafo.h"
// hacer los includes de las estructuras de datos
#include "../ed/HeapPriorityQueue.h"

inline Grafo* prim(Grafo& g, int inicio) {
	int nodos = g.cantidadNodos();
	int arcos = g.cantidadArcos();
	Grafo* arbol = new Grafo(nodos, g.maxConexiones());

	// Se replican los nodos: mismas posiciones y misma numeración que el grafo base
	for (int i = 0; i < nodos; i++) {
		Nodo* nodo = g.obtenerNodo(i);
		arbol->agregarNodo(nodo->x, nodo->y);
	}

	bool* visitado = new bool[nodos];
	for (int i = 0; i < nodos; i++)
		visitado[i] = false;

	HeapPriorityQueue<Arco*> Arcos(arcos < 1 ? 1 : 2 * arcos);
	int nodoActual = inicio;
	int visitados = 0;

	while (visitados < nodos) {
		visitado[nodoActual] = true;
		visitados++;


		Nodo* n = g.obtenerNodo(nodoActual);
		for (int i = 0; i < n->gradoActual(); i++) {
			n->adyacencia.goToPos(i);
			int posArco = n->adyacencia.getElement();
			Arcos.insert(g.obtenerArco(posArco), g.obtenerArco(posArco)->peso);
		}

		if (visitados == nodos)
			break;

		Arco* arcoMenor = nullptr;
		int origen = -1, destino = -1;

		while (!Arcos.isEmpty()) {
			Arco* candidato = Arcos.removeMin();
			int nodo1 = candidato->extremoA;
			int nodo2 = candidato->extremoB;

			if (visitado[nodo1] && !visitado[nodo2]) {
				arcoMenor = candidato;
				origen = nodo1;
				destino = nodo2;
				break;
			}
			else if (visitado[nodo2] && !visitado[nodo1]) {
				arcoMenor = candidato;
				origen = nodo2;
				destino = nodo1;
				break;
			}
		}
		if (arcoMenor == nullptr)
			break;

		arbol->agregarArco(origen, destino);
		nodoActual = destino;

	}
	delete[] visitado;
	return arbol;
}