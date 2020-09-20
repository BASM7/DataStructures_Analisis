#pragma once
#include "PosList.h"

template <typename T>
class DynamicQueue {
public:
	PosList<T>* elements;
	DynamicQueue() {
		elements = new PosList<T>();
	};

	virtual ~DynamicQueue() {};

	void clear();
	bool isEmpty() { return this->elements->isEmpty(); };
	void push(T element) { this->elements->pushBack(element); };
	T pop();
	T top() { return this->elements->getFirst()->value; };
	int getSize() { return this->elements->getSize(); };
};

template<typename T>
void DynamicQueue<T>::clear() {
	ListNode<T>* temp = this->elements->getFirst();
	this->elements->clear();
}

template<typename T>
T DynamicQueue<T>::pop() {
	ListNode<T>* temp = new ListNode<T>();
	temp = this->elements->getFirst();
	T value = temp != nullptr ? temp->value : NULL;
	this->elements->remove(temp);
	return value;
}




