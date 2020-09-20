#pragma once
#include <iostream>
#include <memory>

template <typename T>
class ListNode {
public:
	ListNode* next;
	T value;
	ListNode() {
		next = nullptr;
		value = NULL;
	}

	virtual ~ListNode() {}

	ListNode(T element) {
		next = nullptr;
		value = element;
	}
};

template <typename T>
class PosList {
	ListNode<T>* first;
	ListNode<T>* last;
public:
	PosList() {
		first = nullptr;
		last = first;
	}

	virtual ~PosList() {};

	ListNode<T>* getFirst() {
		return this->first;
	}
	void setFirst(ListNode<T>* newFirst) {
		this->first = newFirst;
	}

	ListNode<T>* getLast() {
		return last;
	}
	void setLast(ListNode<T>* newLast) {
		this->last = newLast;
	}

	friend std::ostream& operator<<(std::ostream& output, PosList<T> list) {
		ListNode<T>* temp = list.getFirst();
		output << '[';
		while (temp != nullptr){
			output << list.get(temp);
			if (list.getNext(temp) != nullptr) {
				output << ", ";
			}
			temp = list.getNext(temp);
		}
		output << ']';
		return output;
	}

	void clear();
	bool isEmpty() { return this->getFirst() == nullptr; };
	void pushBack(T element);
	void push(T element, ListNode<T>* ptr);
	void remove(ListNode<T>* ptr);
	T get(ListNode<T>* ptr);
	void replace(ListNode<T>* ptr, T element);
	void swap(ListNode<T>* ptr1, ListNode<T>* ptr2);
	int getSize();
	ListNode<T>* getNext(ListNode<T>* ptr);
	ListNode<T>* getPrevious(ListNode<T>* ptr);
};

template<typename T>
void PosList<T>::clear() {
	ListNode<T>* temp = new ListNode<T>();
	temp = this->getFirst();
	while (temp != nullptr) {
		this->setFirst(this->getNext(this->getFirst()));
		delete temp;
		temp = this->getFirst();
	}
}

template <typename T>
void PosList<T>::pushBack(T element) {
	ListNode<T>* temp = new ListNode<T>(element);
	if (this->getFirst() != nullptr) {
		this->getLast()->next = temp;
		this->setLast(temp);
	}
	else {
		this->setFirst(temp);
		this->setLast(temp);
	}
}

template<typename T>
void PosList<T>::push(T element, ListNode<T>* ptr)
{
	ListNode<T>* current = new ListNode<T>();
	ListNode<T>* temp = new ListNode<T>(element);

	if (ptr == this->getFirst()) {
		// insertar al inicio.
		temp->next = this->getFirst();
		this->setFirst(temp);
	}
	else {
		current = this->getNext(this->getFirst());
		bool pushed = false;
		while (current != nullptr && !pushed) {
			if (ptr == this->getNext(current)) {
				// insertar antes;
				temp->next = this->getNext(current);
				current->next = temp;
				pushed = true;
			}
			current = this->getNext(current);
		}
	}
}

template <typename T>
void PosList<T>::remove(ListNode<T>* ptr) {
	ListNode<T>* current = new ListNode<T>();
	ListNode<T>* toDelete = new ListNode<T>();
	if (this->getSize() == 1) {
		toDelete = this->getFirst();
		delete toDelete;
		this->setFirst(nullptr);
		this->setLast(nullptr);
	}
	else {
		if (ptr == this->getFirst()) {
			toDelete = this->getFirst();
			this->setFirst(this->getNext(toDelete));
			delete toDelete;			
		}
		else {
			current = this->getFirst();
			bool removed = false;
			while (current != nullptr && !removed) {
				if (ptr == this->getNext(current)) {
					toDelete = this->getNext(current);
					if (toDelete == this->getLast()) {
						current->next = nullptr;
						this->setLast(current);
					}
					else {
						current->next = this->getNext(toDelete);
					}
					delete toDelete;
					removed = true;
				}
				current = this->getNext(current);
			}
		}
	}
}

template<typename T>
void PosList<T>::replace(ListNode<T>* ptr, T element){
	if (ptr != nullptr) {
		ptr->value = element;
	}
}

template<typename T>
void PosList<T>::swap(ListNode<T>* ptr1, ListNode<T>* ptr2){
	T temp = ptr1->value;
	ptr1->value = ptr2->value;
	ptr2->value = temp;
}

template <typename T>
int PosList<T>::getSize() {
	ListNode<T>* temp = this->getFirst();
	int counter = 0;
	while (temp != nullptr) {
		counter++;
		temp = this->getNext(temp);
	}
	return counter;
}

template <typename T>
ListNode<T>* PosList<T>::getNext(ListNode<T>* ptr) {
	return ptr == nullptr ? nullptr : ptr->next;
}

template <typename T>
ListNode<T>* PosList<T>::getPrevious(ListNode<T>* ptr){
	ListNode<T>* temp = this->getFirst();
	ListNode<T>* previous = nullptr;
	bool found = false;
	while (temp != nullptr && !found) {
		if (this->getNext(temp) == ptr) {
			previous = temp;
			found = true;
		}
		temp = this->getNext(temp);
	}
	return previous;
}

template <typename T>
T PosList<T>::get(ListNode<T>* ptr) {
	return ptr == nullptr ? NULL : ptr->value;
}

