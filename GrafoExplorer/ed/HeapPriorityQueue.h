/*
 * HeapPriorityQueue.h
 *
 * Implementación de una cola de prioridad genérica basada en un heap mínimo.
 * La estructura utiliza un MinHeap de pares (priority, value) para mantener los
 * elementos ordenados automáticamente según su prioridad, permitiendo acceder
 * siempre al elemento de menor prioridad de forma eficiente.
 *
 * Manejo de errores:
 * Esta implementación depende del MinHeap subyacente, el cual puede lanzar
 * excepciones en casos como desbordamiento o acceso a estructuras vacías.
 *
 * Autores: Edwin Muñoz, Francisco Mora
 */

#pragma once

#include <iostream>
#include <stdexcept>
#include "PriorityQueue.h"
#include "Pair.h"
#include "MinHeap.h"

using std::runtime_error;

template <typename E>
class HeapPriorityQueue : public PriorityQueue<E> {
private:
	MinHeap<Pair<float, E>>* pairs;

public:
	HeapPriorityQueue(int max) {
		pairs = new MinHeap<Pair<float, E>>(max);
	}
	~HeapPriorityQueue() {
		delete pairs;
	}
	void insert(E element, float priority) {
		Pair<float, E> p(priority, element);
		pairs->insert(p);
	}
	E min() {
		return pairs->first().value;
	}
	E removeMin() {
		return pairs->removeFirst().value;
	}
	void clear() {
		pairs->clear();
	}
	int getSize() {
		return pairs->getSize();
	}
	bool isEmpty() {
		return pairs->isEmpty();
	}
	void print() {
		pairs->print();
	}
};