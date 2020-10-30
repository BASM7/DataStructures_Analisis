/*
*	TP1 - Analisis de Algoritmos.
* @author B93986 Luis Alfonso Jim�nez
* @author B95346 Jes�s Alonso Moreno Montero
* @author B95092 V�ctor Jes�s Mora Abarca
*/

#pragma once
#include "PosList.h"

template <typename T>
class DynamicQueue {
public:
	PosList<T> elements;
	DynamicQueue() {};

	virtual ~DynamicQueue() {};

	void clear();
	bool isEmpty() { return elements.isEmpty(); };
	void push(T element) { elements.pushBack(element); };
	T pop();
	T top() { return elements.getFirst()->value; };
	int getSize() { return elements.getSize(); };
};

template<typename T>
void DynamicQueue<T>::clear() {
	//ListNode<T>* temp = elements.getFirst();
	elements.clear();
}

template<typename T>
T DynamicQueue<T>::pop() {
	ListNode<T>* temp = new ListNode<T>();
	temp = elements.getFirst();
	T value = temp != nullptr ? temp->value : NULL;
	elements.remove(temp);
	return value;
}




