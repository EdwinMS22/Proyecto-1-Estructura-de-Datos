#pragma once

#include "../modelo/Grafo.h"
// hacer los includes de las estructuras de datos
#include "../ed/ArrayList.h"

inline Grafo* dijkstra(Grafo& g, int inicio, int destino) {
	int nodos = g.cantidadNodos();
	int arcos = g.cantidadArcos();
	Grafo* arbol = new Grafo(nodos, g.maxConexiones());

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
	delete[]distancia;
	delete[]rutas;
	delete[]definitivos;
	return arbol;
}