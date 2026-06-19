#pragma once

#include <cmath>
#include "../ed/ArrayList.h"
#include "Nodo.h"
#include "Arco.h"

class Grafo {
private:
	ArrayList<Nodo*> nodos;	// indexados por número
	ArrayList<Arco*> arcos; // cada conexión una sola vez
	int maxVecinos;

	float distancia(Nodo* a, Nodo* b) {
		float dx = a->x - b->x;
		float dy = a->y - b->y;
		return std::sqrt(dx * dx + dy * dy);
	}

public:
	// La capacidad de arcos usa cantidadNodos * maxVecinos como cota superior (el numero real de arcos
	// nunca supera cantidadNodos * maxVecinos / 2).
	Grafo(int cantidadNodos, int maxVecinos) :
		nodos(cantidadNodos), arcos(cantidadNodos * maxVecinos) {
		this->maxVecinos = maxVecinos;
	}

	// El grafo es único dueño de la memoria: libera los nodos y arcos
	~Grafo() {
		for (nodos.goToStart(); !nodos.atEnd(); nodos.next())
			delete nodos.getElement();
		for (arcos.goToStart(); !arcos.atEnd(); arcos.next())
			delete arcos.getElement();
	}
	Grafo(const Grafo&) = delete;
	void operator=(const Grafo&) = delete;

	// Su número es su índice de inserción y devuelve número asingnado
	int agregarNodo(float x, float y) {
		int numero = nodos.getSize();
		nodos.append(new Nodo(numero, x, y, maxVecinos));
		return numero;
	}

	// Crea un arco no dirigido entre los nodos a y b.
	void agregarArco(int a, int b) {
		Nodo* na = obtenerNodo(a);
		Nodo* nb = obtenerNodo(b);
		int indice = arcos.getSize();
		arcos.append(new Arco(a, b, distancia(na, nb)));
		na->agregarArco(indice);
		nb->agregarArco(indice);
	}

	Nodo* obtenerNodo(int numero) {
		nodos.goToPos(numero);
		return nodos.getElement();
	}

	Arco* obtenerArco(int indice) {
		arcos.goToPos(indice);
		return arcos.getElement();
	}

	int cantidadNodos() {
		return nodos.getSize();
	}

	int cantidadArcos() {
		return arcos.getSize();
	}

	int maxConexiones() const {
		return maxVecinos;
	}
};