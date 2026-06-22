/*
 * List.h
 *
 * Interfaz genérica para una lista abstracta.
 * Define el comportamiento base de una estructura de datos lineal que permite
 * almacenamiento ordenado de elementos con acceso mediante una posición interna
 * (cursor) que representa la posición actual sobre la cual se realizan operaciones 
 * de inserción, eliminación y acceso.
 *
 * Autores: Edwin Muñoz, Francisco Mora
 */

#pragma once

template <typename E>
class List {
public:
	List() {}
	List(const List<E>&) = delete;
	void operator=(const List<E>&) = delete;
	virtual ~List() = default;
	virtual void insert(E element) = 0;
	virtual void append(E element) = 0;
	virtual void setElement(E element) = 0;
	virtual const E& getElement() = 0;
	virtual E remove() = 0;
	virtual void clear() = 0;
	virtual void goToStart() = 0;
	virtual void goToEnd() = 0;
	virtual void goToPos(int pos) = 0;
	virtual void next() = 0;
	virtual void previous() = 0;
	virtual bool atStart() = 0;
	virtual bool atEnd() = 0;
	virtual int getPos() = 0;
	virtual int getSize() = 0;
	virtual void print() = 0;
};