/*
 * PriorityQueue.h
 *
 * Interfaz genérica para una cola de prioridad.
 * Define el comportamiento base de una estructura de datos donde cada elemento
 * tiene una prioridad asociada, y el acceso a los elementos se realiza según
 * dicha prioridad en lugar del orden de inserción.
 *
 * Autores: Edwin Muñoz, Francisco Mora
 */

#pragma once

template <typename E>
class PriorityQueue {
public:
	PriorityQueue() {}
	PriorityQueue(const PriorityQueue<E>&) = delete;
	void operator=(const PriorityQueue<E>&) = delete;
	virtual ~PriorityQueue() = default;
	virtual void insert(E element, float priority) = 0;
	virtual E min() = 0;
	virtual E removeMin() = 0;
	virtual void clear() = 0;
	virtual int getSize() = 0;
	virtual bool isEmpty() = 0;
	virtual void print() = 0;
};