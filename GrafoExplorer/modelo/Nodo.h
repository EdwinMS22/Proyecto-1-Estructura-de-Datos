#pragma once

#include "../ed/ArrayList.h"

class Nodo {
public:
	int numero; // identificador del nodo (coincide con índice en el grafo)
	float x;
	float y;
	ArrayList<int> adyacencia; // índice de los arcos incidentes

	Nodo(int numero, float x, float y, int maxVecinos) : adyacencia(maxVecinos) {
		this->numero = numero;
		this->x = x;
		this->y = y;
	}

	void agregarArco(int indiceArco) {
		adyacencia.append(indiceArco);
	}

	int gradoActual() {
		return adyacencia.getSize();
	}
};