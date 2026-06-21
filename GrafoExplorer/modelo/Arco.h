/*
 * Arco.h
 *
 * Representa un arco del grafo no dirigido en GrafoExplorer.
 * Almacena los índices de los dos nodos extremos que conecta y el peso
 * asociado, correspondiente a la distancia geométrica entre ambos
 * nodos. Permite recorrer el arco en cualquier dirección sin necesidad
 * de conocer de antemano cuál extremo es el de origen.
 *
 * Funcionalidades:
 * - otroExtremo(nodo): dado uno de los extremos del arco, devuelve el
 *   extremo opuesto, permitiendo recorrer el arco sin importar la
 *   dirección.
 *
 * Autores: Edwin Muñoz, Francisco Mora
 */

#pragma once

class Arco {
public:
	int extremoA;
	int extremoB;
	float peso;

	Arco() {
		extremoA = extremoB = -1;
		peso = 0.0f;
	}
	Arco(int extremoA, int extremoB, float peso) {
		this->extremoA = extremoA;
		this->extremoB = extremoB;
		this->peso = peso;
	}

	int otroExtremo(int nodo) const {
		return (nodo == extremoA) ? extremoB : extremoA;
	}
};