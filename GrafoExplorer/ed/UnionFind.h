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

	// Raiz del conjunto de x. Aplica compresión de caminos (path halving): cada nodo del
	// camino pasa a apuntar a su abuelo, aplanando el árbol en visitas sucesivas
	int find(int x) {
		while (parent[x] != x) {
			parent[x] = parent[parent[x]];
			x = parent[x];
		}
		return x;
	}

	// Une los conjuntos de a y b por rango. Devuelve false si ya estaban en el mismo
	// conjunto y true si sí se unieron
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