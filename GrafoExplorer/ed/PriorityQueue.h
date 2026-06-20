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