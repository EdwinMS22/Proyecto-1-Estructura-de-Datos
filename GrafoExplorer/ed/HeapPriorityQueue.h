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
	MinHeap<Pair<int, E>>* pairs;

public:
	HeapPriorityQueue(int max) {
		pairs = new MinHeap<Pair<int, E>>(max);
	}
	~HeapPriorityQueue() {
		delete pairs;
	}
	void insert(E element, int priority) {
		Pair<int, E> p(priority, element);
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