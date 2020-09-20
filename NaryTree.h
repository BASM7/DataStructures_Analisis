#pragma once
#include "PosList.h"
#include "DynamicQueue.h"
#include <memory>

/*
Estructura del nodo del árbol n-ario. Tiene apuntador al padre y una lista simple de nodos como hijos.
*/
template<typename T>
class TreeNode {
public:
	T value;
	TreeNode<T>* parent;
	PosList<TreeNode<T>*>* children;

	TreeNode() {
		children = new PosList<TreeNode<T>*>();
		this->parent = nullptr;
		this->value = NULL;
	}

	TreeNode(T element, TreeNode<T>* parent) {
		children = new PosList<TreeNode<T>*>();
		this->parent = parent;
		this->value = element;
	}

};

template<typename T>
class NaryTree {
	TreeNode<T>* root;
	void preOrder(TreeNode<T>* pivot);
	int preOrderCantNodesOnLevel(TreeNode<T>* pivot, int count, int level);
public:
	NaryTree() {
		this->root = nullptr;
	};
	virtual ~NaryTree() {};

	void clear() {}; //TODO.
	bool isEmpty() { return this->getRoot() == nullptr; };
	TreeNode<T>* add(TreeNode<T>* parent, T element);
	void removeLeaf(TreeNode<T>* ptr) {}; //TODO.
	void setRoot(int element) { this->root = new TreeNode<T>(element, nullptr); };
	void setValue(TreeNode<T>*, T element) {};
	TreeNode<T>* getMostLeftChild(TreeNode<T>* ptr);
	TreeNode<T>* getRightSibling(TreeNode<T>* ptr);
	TreeNode<T>* getRoot() { return this->root; };
	TreeNode<T>* getParent(TreeNode<T>* ptr);
	int getValue(TreeNode<T>* ptr) { return ptr->value; };
	int getSizeOfChildren(TreeNode<T>* ptr);
	int getSize();
	bool isLeaf(TreeNode<T>* ptr) { return ptr->children->isEmpty(); };
	void printPreOrder();
	int preOrderGetCantNodesOnLevel(int level);
	int getHeight(TreeNode<T>* ptr);
};

template<typename T>
TreeNode<T>* NaryTree<T>::add(TreeNode<T>* parent, T element){
	if (parent != nullptr) {
		TreeNode<T>* newNode = new TreeNode<T>(element, parent);
		parent->children->pushBack(newNode);
		return newNode;
	}
	return nullptr;
}

template<typename T>
TreeNode<T>* NaryTree<T>::getMostLeftChild(TreeNode<T>* ptr)
{
	if (ptr != nullptr) {
		if (ptr->children->getFirst() != nullptr) {
			return ptr->children->getFirst()->value;
		}
	}
	return nullptr;
}

template<typename T>
TreeNode<T>* NaryTree<T>::getRightSibling(TreeNode<T>* ptr){
	bool found = false;
	TreeNode<T>* sibling = nullptr;
	if (ptr != nullptr) {
		ListNode<TreeNode<int>*>* temp = ptr->parent->children->getFirst();
		while (temp != nullptr && !found) {
			if (temp->value == ptr) {
				if (ptr->parent->children->getNext(temp) != nullptr) {
					sibling = ptr->parent->children->getNext(temp)->value;
					found = true;
				}
			}
			temp = ptr->parent->children->getNext(temp);
		}		
	}
	return sibling;
}


template<typename T>
TreeNode<T>* NaryTree<T>::getParent(TreeNode<T>* ptr){
	TreeNode<T>* parent = nullptr;
	if (ptr != nullptr) {
		DynamicQueue<TreeNode<T>*> queue;
		if (this->getSize() == 0 || this->getRoot() == nullptr) {
			return nullptr;
		}
		else {
			bool done = false;			
			queue.push(this->getRoot());
			while (!queue.isEmpty() && !done) {
				TreeNode<T>* child = this->getMostLeftChild(queue.top());
				while (child != nullptr && !done) {
					if (ptr == child) {
						done = true;
						parent = queue.pop();
					}
					else {
						queue.push(child);
						child = this->getRightSibling(child);
					}
				}
				queue.pop();
			}
		}
		queue.clear();
		return parent;
	}
	return nullptr;
}

template<typename T>
int NaryTree<T>::getSizeOfChildren(TreeNode<T>* ptr){
	int count = 0;
	if (ptr != nullptr) {
		TreeNode<T>* child = this->getMostLeftChild(ptr);
		while (child != nullptr) {
			count++;
			child = this->getRightSibling(child);
		}
	}
	return count;
}

template<typename T>
int NaryTree<T>::getSize(){
	DynamicQueue<TreeNode<T>*> queue;
	int counter = 0;

	if (this->getRoot() != nullptr) {
		queue.push(this->getRoot());
		while (!queue.isEmpty()) {
			counter++;
			TreeNode<T>* child = this->getMostLeftChild(queue.pop());
			while (child != nullptr) {
				queue.push(child);
				child = this->getRightSibling(child);
			}
		}
	}	
	queue.clear();
	return counter;
}


template<typename T>
void NaryTree<T>::preOrder(TreeNode<T>* pivot) {
	std::cout << this->getValue(pivot) << std::endl;
	TreeNode<T>* child = this->getMostLeftChild(pivot);
	while (child != nullptr) {
		this->preOrder(child);
		child = this->getRightSibling(child);
	}
}


template<typename T>
void NaryTree<T>::printPreOrder()
{
	if (!this->isEmpty()) {
		preOrder(this->getRoot());
	}
}

template<typename T>
int NaryTree<T>::preOrderGetCantNodesOnLevel(int level) {
	if (!this->isEmpty()) {
		int count = 1;
		if (level == count) {
			return count;
		}
		return preOrderCantNodesOnLevel(this->getRoot(), count, level);
	}
	return 0;
}

template<typename T>
int NaryTree<T>::preOrderCantNodesOnLevel(TreeNode<T>* pivot, int count, int level){
	int sum = 0;
	if (count > level) {
		return 0;
	}
	else {
		if (level == count) {
			sum++;
		}
		else {
			count++;
			TreeNode<T>* child = this->getMostLeftChild(pivot);
			while (child != nullptr) {				
				sum = sum + this->preOrderCantNodesOnLevel(child, count, level);
				child = this->getRightSibling(child);
			}
			delete child;
		}
	}
	return sum;	
}

template<typename T>
int NaryTree<T>::getHeight(TreeNode<T>* ptr){
	if (ptr == nullptr || this->isLeaf(ptr)) {
		return 0;
	}
	int maxHeight = 0;
	TreeNode<T>* child = this->getMostLeftChild(ptr);
	while (child != nullptr) {
		int newHeight = this->getHeight(child);
		if (maxHeight < newHeight) {
			maxHeight = newHeight;
		}
		child = this->getRightSibling(child);
	}
	delete child;
	return maxHeight + 1;
}