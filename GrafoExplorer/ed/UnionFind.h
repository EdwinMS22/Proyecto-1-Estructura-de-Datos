/*
 * UnionFind.h
 *
 * Permite mantener una colección de conjuntos disjuntos y realizar operaciones
 * eficientes de unión y consulta de conectividad entre elementos. Esta implementación 
 * utiliza optimizaciones de compresión de caminos y unión por rango.
 *
 * Funcionalidades:
 * - find(x): retorna el representante (raíz) del conjunto al que pertenece x,
 *   aplicando compresión de caminos para optimización.
 * - unite(a, b): une los conjuntos que contienen a y b usando unión por rango.
 *   Retorna false si ambos ya estaban en el mismo conjunto.
 * - connected(a, b): indica si dos elementos pertenecen al mismo conjunto.
 * - getSize(): retorna la cantidad total de elementos gestionados.
 *
 * Manejo de errores:
 * - Lanza runtime_error si el tamaño inicial es inválido.
 * - No realiza validación de índices en operaciones (se asume entrada válida).
 *
 * Autores: Edwin Muñoz, Francisco Mora
 */

#pragma once

#include <stdexcept>

using std::runtime_error;

class UnionFind {
private:
	int* parent;
	int* rank;
	int size;

public:
	UnionFind(int size) {
		if (size < 1)
			throw runtime_error("Invalid union-find size.");
		this->size = size;
		parent = new int[size];
		rank = new int[size];
		for (int i = 0; i < size; i++) {
			parent[i] = i;
			rank[i] = 0;
		}
	}
	UnionFind(const UnionFind&) = delete;
	UnionFind& operator=(const UnionFind&) = delete;
	~UnionFind() {
		delete[] parent;
		delete[] rank;
	}
	int find(int x) {
		while (parent[x] != x) {
			parent[x] = parent[parent[x]];
			x = parent[x];
		}
		return x;
	}
	bool unite(int a, int b) {
		int ra = find(a);
		int rb = find(b);
		if (ra == rb)
			return false;
		if (rank[ra] < rank[rb]) {
			parent[ra] = rb;
		}
		else if (rank[ra] > rank[rb]) {
			parent[rb] = ra;
		}
		else {
			parent[rb] = ra;
			rank[ra]++;
		}
		return true;
	}
	bool connected(int a, int b) {
		return find(a) == find(b);
	}
	int getSize() const {
		return size;
	}
};