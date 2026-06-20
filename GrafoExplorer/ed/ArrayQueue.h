#pragma once

#include <iostream>
#include <stdexcept>
#include "Queue.h"

using std::runtime_error;
using std::cout;

template <typename E>
class ArrayQueue : public Queue<E> {
private:
	E* elements;
	int max;
	int front;
	int back;
	int size;

public:
	ArrayQueue(int max) {
		if (max < 1)
			throw new runtime_error("Invalid max size.");
		elements = new E[max];
		this->max = max;
		front = back = size = 0;
	}
	~ArrayQueue() {
		delete[] elements;
	}
	void enqueue(E element) {
		if (size == max)
			throw runtime_error("Queue is full.");
		elements[back] = element;
		back = (back + 1) % max;
		size++;
	}
	E dequeue() {
		if (size == 0)
			throw runtime_error("Queue is empty.");
		front = (front + 1) % max;
		size--;
		return elements[(front + max - 1) % max];
	}
	const E& frontValue() {
		if (size == 0)
			throw runtime_error("Queue is empty.");
		return elements[front];
	}
	void clear() {
		front = back = size = 0;
	}
	bool isEmpty() {
		return size == 0;
	}
	int getSize() {
		return size;
	}
	void print() {
		cout << "[ ";
		for (int i = front; i != back; i = (i + 1) % max) {
			cout << elements[i];
			if (i != (back + max - 1) % max)
				cout << ", ";
		}
		cout << " ]\n";
	}
};