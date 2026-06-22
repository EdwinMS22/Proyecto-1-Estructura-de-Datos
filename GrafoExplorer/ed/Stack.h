/*
 * Stack.h
 *
 * Interfaz genérica para una pila. Define el comportamiento base de 
 * una estructura de datos lineal donde el último elemento en entrar 
 * es el primero en salir.
 * 
 * Autores: Edwin Muñoz, Francisco Mora
 */

#pragma once

template <typename E>
class Stack {
public:
	Stack() {}
	Stack(const Stack<E>&) = delete;
	void operator=(const Stack<E>&) = delete;
	virtual ~Stack() = default;
	virtual void push(E element) = 0;
	virtual E pop() = 0;
	virtual const E& topValue() = 0;
	virtual void clear() = 0;
	virtual bool isEmpty() = 0;
	virtual int getSize() = 0;
	virtual void print() = 0;
};