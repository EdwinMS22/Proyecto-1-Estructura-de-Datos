/*
 * MinHeap.h
 *
 * Implementación de un heap mínimo genérico basado en arreglo.
 * La estructura mantiene un árbol binario completo representado en un arreglo
 * contiguo, garantizando que cada nodo padre sea menor o igual que sus hijos.
 *
 * Manejo de errores:
 * La clase lanza excepciones runtime_error en casos como:
 * - Inserción en heap lleno.
 * - Acceso o eliminación en heap vacío.
 * - Índices fuera de rango.
 *
 * Autores: Edwin Muñoz, Francisco Mora
 */

#pragma once

#include <iostream>
#include <stdexcept>

using std::runtime_error;
using std::cout;

template <typename E>
class MinHeap {
private:
	E* elements;
	int max;
	int size;
	
	int leftChild(int pos) {
		return 2 * pos + 1;
	}
	int rightChild(int pos) {
		return 2 * pos + 2;
	}
	int parent(int pos) {
		return (pos - 1) / 2;
	}
	void swap(int pos1, int pos2) {
		E temp = elements[pos1];
		elements[pos1] = elements[pos2];
		elements[pos2] = temp;
	}
	void siftUp(int pos) {
		while (pos > 0 && elements[pos] < elements[parent(pos)]) {
			swap(pos, parent(pos));
			pos = parent(pos);
		}
	}
	bool isLeaf(int pos) {
		return leftChild(pos) >= size;
	}
	int minChild(int pos) {
		if (rightChild(pos) < size && elements[rightChild(pos)] < elements[leftChild(pos)])
			return rightChild(pos);
		else
			return leftChild(pos);
	}
	void siftDown(int pos) {
		while (!isLeaf(pos) && elements[minChild(pos)] < elements[pos]) {
			int minPos = minChild(pos);
			swap(pos, minPos);
			pos = minPos;
		}
	}

public:
	MinHeap(int max) {
		if (max < 1)
			throw runtime_error("Invalid heap max size.");
		elements = new E[max];
		this->max = max;
		size = 0;
	}
	~MinHeap() {
		delete[] elements;
	}
	void insert(E element) {
		if (size == max)
			throw runtime_error("Heap is full.");
		elements[size] = element;
		siftUp(size);
		size++;
	}
	E first() {
		if (size == 0)
			throw runtime_error("Heap is empty.");
		return elements[0];
	}
	E removeFirst() {
		return remove(0);
	}
	E remove(int pos) {
		if (size == 0)
			throw runtime_error("Heap is empty.");
		if (pos < 0 || pos >= size)
			throw runtime_error("Index out of range.");
		swap(pos, size - 1);
		size--;
		siftDown(pos);
		return elements[size];
	}
	void clear() {
		size = 0;
	}
	int getSize() {
		return size;
	}
	bool isEmpty() {
		return size == 0;
	}
	void print() {
		cout << "[ ";
		for (int i = 0; i < size; i++) {
			cout << elements[i];
			if (i != size - 1) cout << ", ";
		}
		cout << " ]\n";
	}
};