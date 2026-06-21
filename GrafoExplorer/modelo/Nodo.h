/*
 * Nodo.h
 *
 * Representa un nodo del grafo en GrafoExplorer. Almacena su número
 * identificador (coincide con su índice dentro del grafo), su
 * posición geométrica (x, y) y la lista de adyacencia, que contiene
 * los índices de los arcos incidentes sobre el nodo (no los nodos
 * vecinos directamente), permitiendo acceder al peso y demás datos del
 * arco a través del Grafo.
 *
 * Funcionalidades:
 * - agregarArco(indiceArco): agrega el índice de un arco incidente a
 *   la lista de adyacencia del nodo.
 * - gradoActual(): devuelve la cantidad de arcos incidentes
 *   actualmente registrados, es decir, el grado del nodo.
 *
 * Autores: Edwin Muñoz, Francisco Mora
 */

#pragma once

#include "../ed/ArrayList.h"

class Nodo {
public:
	int numero;
	float x;
	float y;
	ArrayList<int> adyacencia;

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