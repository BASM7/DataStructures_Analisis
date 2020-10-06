#pragma once
#include <iostream>
template<typename T>
class CircularQueue {
public:
	CircularQueue(int maxSize) {
		this->vector = new T[maxSize];
		this->size = maxSize;
		this->firstPos = this->lastPos = this->enteredValues = 0;
	}

	~CircularQueue() {
	
	}

	bool isEmpty() { enteredValues == 0 ? true : false; }
	void push(T value);
	T pop();

private:
	T *vector;
	int firstPos;
	int lastPos;
	int size;
	int enteredValues;
};

template<typename T>
void CircularQueue<T>::push(T value) {
	if (enteredValues != size) {
		if (this->lastPos == size - 1) {
			this->vector[this->lastPos] = value;
			lastPos = 0;
			enteredValues++;
		}
		else {
			this->vector[this->lastPos] = value;
			lastPos++;
			enteredValues++;
		}
	}
	else {
		std::cout << "Cola esta llena";
	}
}

template<typename T>
T CircularQueue<T>::pop() {
	T returnValue = NULL;
	if (enteredValues != 0) {
		if (this->firstPos == size - 1) {
			returnValue = this->vector[this->firstPos];
			this->firstPos = 0;
			enteredValues--;
		}
		else {
			returnValue =  this->vector[this->firstPos];
			firstPos++;
			enteredValues--;
		}
	}
	else {
		std::cout << "Cola esta llena";
	}
	return returnValue;
}