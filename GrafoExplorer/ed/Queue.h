/*
 * Queue.h
 *
 * Interfaz genérica para una cola. Define el comportamiento base de una 
 * estructura de datos lineal donde los elementos se insertan al final y 
 * se eliminan desde el frente, manteniendo el orden de llegada.
 *
 * Autores: Edwin Muñoz, Francisco Mora
 */

#pragma once

template <typename E>
class Queue {
public:
	Queue() {}
	Queue(const Queue<E>&) = delete;
	void operator=(const Queue<E>&) = delete;
	virtual ~Queue() = default;
	virtual void enqueue(E element) = 0;
	virtual E dequeue() = 0;
	virtual const E& frontValue() = 0;
	virtual void clear() = 0;
	virtual bool isEmpty() = 0;
	virtual int getSize() = 0;
	virtual void print() = 0;
};