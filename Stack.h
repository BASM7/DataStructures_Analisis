/*
*	TP1 - Analisis de Algoritmos.
* @author B93986 Luis Alfonso Jim�nez
* @author B95346 Jes�s Alonso Moreno Montero
* @author B95092 V�ctor Jes�s Mora Abarca
*/

#pragma once
#include <iostream>
#include <memory>

template <typename T>
class Node {
public:
	Node* next;
	T value;
	Node() {
		next = nullptr;
		value = NULL;
	}

	virtual ~Node() {}

	Node(T element) {
		next = nullptr;
		value = element;
	}

	Node(T element, Node<T>* ptr) {
		next = ptr;
		value = element;
	}
};

template <typename T>
class Stack {
	Node<T>* top;
	int counter;
public:
	Stack() {
		top = nullptr;
		counter = 0;
	}

	virtual ~Stack() {};

	int getCounter() { return this->counter; };
	Node<T>* getTop() { return this->top; };
	void clear();
	bool isEmpty() { return this->getTop() == nullptr; };
	void push(T element);
	void pop();

};

template<typename T>
void Stack<T>::clear() {
	Node<T>* temp = new Node<T>();
	temp = this->getTop();
	while (temp != nullptr) {
		Stack<T>::top = temp->next;
		delete temp;
		temp = Stack<T>::top;
	}
	counter = 0;
}

template<typename T>
void Stack<T>::push(T element)
{
	Node<T>* top = new Node<T>();
	top = this->getTop();

	if (top == nullptr) {
		this->top = new Node<T>(element);
		counter++;
	}
	else {
		Node<T>* temp = new Node<T>();
		temp = this->getTop();
		this->top = new Node<T>(element, temp);
		counter++;
	}
	
}

template<typename T>
void Stack<T>::pop()
{
	Node<T>* temp = new Node<T>();
	temp = this->getTop();
	if (temp != nullptr) {
		Stack<T>::top = temp->next;
		delete temp;
		counter--;
	}	
}

