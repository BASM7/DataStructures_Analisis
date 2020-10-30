/*
*	TP1 - Analisis de Algoritmos.
* @author B93986 Luis Alfonso Jiménez
* @author B95346 Jesús Alonso Moreno Montero
* @author B95092 Víctor Jesús Mora Abarca
*/

#pragma once

template<typename T>
class TreeNode {
public:
	T value;
	TreeNode<T>* leftChild;
	TreeNode<T>* rightSibling;

	TreeNode() {
		this->value = NULL;
		this->leftChild = this->rightSibling = nullptr;
	}

	TreeNode(T element) { 
		this->value = element;
		this->leftChild = this->rightSibling = nullptr;
	}


	virtual ~TreeNode() {
		if (this != nullptr) {
			TreeNode<T>* first = this->leftChild;
			if (first != nullptr) {
				TreeNode<T>* next = first->rightSibling;
				while (first != nullptr) {
					delete first;
					first = next;
					if (next != nullptr)
						next = first->rightSibling;
				}
				delete first;
			}
		}
	}

};

template<typename T>
class NaryTree {
	TreeNode<T>* root;

public:
	NaryTree() {
		this->root = nullptr;
	};

	NaryTree(T element) {
		root = new TreeNode(element);
	};


	virtual ~NaryTree() { delete this->root; };// Done.

	void clear() { root = nullptr; }; //Done.
	bool isEmpty() { return this->root == nullptr; };//Done.
	TreeNode<T>* add(TreeNode<T>* parent, T element); // Done.
	void removeLeaf(TreeNode<T>* node); //.
	void setRoot(T element); //Done.
	void setValue(TreeNode<T>* ptr, T element) { ptr->value = element; }; //Done.
	TreeNode<T>* getMostLeftChild(TreeNode<T>* ptr); //Done.
	TreeNode<T>* getRightSibling(TreeNode<T>* ptr); // Done.
	TreeNode<T>* getRoot() { return this->root; }; //Done.
	TreeNode<T>* getParent(TreeNode<T>* ptr);//.
	T getValue(TreeNode<T>* ptr) { return ptr->value; }; //Done.
	int getSizeOfChildren(TreeNode<T>* ptr); //Done.
	bool isLeaf(TreeNode<T>* ptr) { return this->getSizeOfChildren(ptr) == 0; }; //Done.
	int getSize();//Done.
	int getSize(TreeNode<T>* ptr);
};

template<typename T>
TreeNode<T>* NaryTree<T>::add(TreeNode<T>* parent, T element) {
	TreeNode<T>* newNode = nullptr;
	if (this->getRoot() != nullptr) {
		if (parent->leftChild != nullptr) {
			newNode = new TreeNode<T>(element);
			newNode->rightSibling = this->getMostLeftChild(parent);
			parent->leftChild = newNode;

		}
		else {
			newNode = new TreeNode<T>(element);
			parent->leftChild = newNode;
		}
	}
	return newNode;
}

template<typename T>
void NaryTree<T>::removeLeaf(TreeNode<T>* node) {
	if (this->getRoot() != nullptr) {
		auto temp = this->getMostLeftChild(this->getParent(node));
		auto nextTemp = this->getRightSibling(temp);
		if (temp == node) {
			if (nextTemp != nullptr) {
				this->getParent(node)->leftChild = nextTemp;
				temp->rightSibling = nullptr;
				delete temp;
			}
			else {
				this->getParent(node)->leftChild = nullptr;
				delete temp;
			}
		}
		else {
			while (nextTemp != node) {
				temp = nextTemp;
				nextTemp = this->getRightSibling(nextTemp);
			}
			temp->rightSibling = this->getRightSibling(nextTemp);
			nextTemp->rightSibling = nullptr;
			delete nextTemp;
		}
	}
}

template<typename T>
void NaryTree<T>::setRoot(T element) {
	TreeNode<T>* newNode = new TreeNode<T>(element);
	this->root = newNode;
}

template<typename T>
TreeNode<T>* NaryTree<T>::getMostLeftChild(TreeNode<T>* ptr) {
	return ptr->leftChild;
}

template<typename T>
TreeNode<T>* NaryTree<T>::getRightSibling(TreeNode<T>* ptr) {
	return ptr->rightSibling;
}

template<typename T>
TreeNode<T>* NaryTree<T>::getParent(TreeNode<T>* ptr) {
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
	}
	return parent;
}

template<typename T>
int NaryTree<T>::getSizeOfChildren(TreeNode<T>* ptr) {
	int count = 0;
	TreeNode<T>* temp = this->getMostLeftChild(ptr);
	if (temp != nullptr) {
		bool done = false;
		while (!done) {
			count++;
			if (temp->rightSibling == nullptr) {
				done = true;
			}
			else {
				temp = this->getRightSibling(temp);
			}
		}
	}
	return count;
}

template<typename T>
int NaryTree<T>::getSize() {
	int count = this->getSize(this->getRoot());
	return count;
}

template<typename T>
int NaryTree<T>::getSize(TreeNode<T>* ptr) {
	int count = 0;
	if (ptr != nullptr) {
		count++;
		auto temp = this->getMostLeftChild(ptr);
		while (temp != ptr && temp != nullptr) {
			count += this->getSize(temp);
			temp = this->getRightSibling(temp);
		}
	}
	return count;
}