/*
 * Grafo.h
 *
 * Representa un grafo no dirigido y etiquetado en GrafoExplorer.
 * Almacena los nodos y arcos del grafo en listas indexadas por
 * posición de inserción, de modo que los nodos quedan numerados de 
 * forma consecutiva y los arcos se referencian por índice. El peso 
 * de cada arco se calcula automáticamente como la distancia euclidiana 
 * entre los dos nodos que conecta. El Grafo es el único dueño de la 
 * memoria de sus nodos y arcos.
 *
 * Funcionalidades:
 * - agregarNodo(x, y): crea un nuevo nodo en la posición (x, y),
 *   asignándole como número su índice de inserción, y lo devuelve.
 * - agregarArco(a, b): crea un arco no dirigido entre los nodos a y b,
 *   calculando su peso como la distancia euclidiana entre ambos, y
 *   registra el índice del arco en la lista de adyacencia de cada
 *   nodo extremo.
 * - obtenerNodo(numero): devuelve el puntero al nodo correspondiente a
 *   ese número.
 * - obtenerArco(indice): devuelve el puntero al arco correspondiente a
 *   ese índice.
 * - cantidadNodos() / cantidadArcos(): devuelven la cantidad actual de
 *   nodos y arcos almacenados, respectivamente.
 * - maxConexiones(): devuelve el máximo de vecinos permitido por nodo.
 * - distancia(a, b): método privado que calcula la distancia
 *   euclidiana entre dos nodos.
 *
 * Autores: Edwin Muñoz, Francisco Mora
 */

#pragma once

#include <cmath>
#include "../ed/ArrayList.h"
#include "Nodo.h"
#include "Arco.h"

class Grafo {
private:
	ArrayList<Nodo*> nodos;
	ArrayList<Arco*> arcos;
	int maxVecinos;

	float distancia(Nodo* a, Nodo* b) {
		float dx = a->x - b->x;
		float dy = a->y - b->y;
		return std::sqrt(dx * dx + dy * dy);
	}

public:
	Grafo(int cantidadNodos, int maxVecinos) :
		nodos(cantidadNodos), arcos(cantidadNodos * maxVecinos) {
		this->maxVecinos = maxVecinos;
	}
	~Grafo() {
		for (nodos.goToStart(); !nodos.atEnd(); nodos.next())
			delete nodos.getElement();
		for (arcos.goToStart(); !arcos.atEnd(); arcos.next())
			delete arcos.getElement();
	}
	Grafo(const Grafo&) = delete;
	void operator=(const Grafo&) = delete;

	int agregarNodo(float x, float y) {
		int numero = nodos.getSize();
		nodos.append(new Nodo(numero, x, y, maxVecinos));
		return numero;
	}
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

	int cantidadNodos() { return nodos.getSize(); }
	int cantidadArcos() { return arcos.getSize(); }
	int maxConexiones() const { return maxVecinos; }
};