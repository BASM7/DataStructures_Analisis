/*
*	TP1 - Analisis de Algoritmos.
* @author B93986 Luis Alfonso Jiménez
* @author B95346 Jesús Alonso Moreno Montero
* @author B95092 Víctor Jesús Mora Abarca
*/

#pragma once

int const SIZE_TREE = 100000; //cambiar para probar arboles más grandes.

template<typename T>
class TreeNode {
	T element;
	int parent;
	int index;
public:

	TreeNode() {
		element = NULL;
		index = NULL;
		parent = NULL;
	}

	TreeNode(T element) {
		this->element = element;
		parent = NULL;
		index = NULL;
	}

	TreeNode(T element, int parent, int index) {
		this->element = element;
		this->parent = parent;
		this->index = index;
	}

	~TreeNode() {}

	int getValue() {
		return element;
	}

	int getParentIndex() {
		return parent;
	}

	int getIndex() {
		return index;
	}


	void setValue(int newValue) {
		element = newValue;
	}

	void setParentIndex(int newParent) {
		parent = newParent;
	}

	void setIndex(int newIndex) {
		index = newIndex;
	}
};

template<typename T>
class NaryTree {
	TreeNode<T>* elements[SIZE_TREE];
	int numElements;

public:
	NaryTree() {
		numElements = 0;
	};

	~NaryTree() {};
	void clear() { numElements = 0; };
	bool isEmpty() { return numElements == 0; };
	TreeNode<T>* add(TreeNode<T>* parent, T element);
	void removeLeaf(TreeNode<T>* node);
	void setRoot(T element);
	void setValue(TreeNode<T>* node, T element) { node->setValue(element); };
	TreeNode<T>* getMostLeftChild(TreeNode<T>* node);
	TreeNode<T>* getRightSibling(TreeNode<T>* node);
	TreeNode<T>* getRoot();
	TreeNode<T>* getParent(TreeNode<T>* node);
	int getValue(TreeNode<T>* node);
	int getSizeOfChildren(TreeNode<T>* node);
	int getSize() { return numElements; };
	bool isLeaf(TreeNode<T>* node);
};

template<typename T>
TreeNode<T>* NaryTree<T>::getParent(TreeNode<T>* node) {
	if (node != nullptr && node != this->getRoot()) {
		return elements[node->getParentIndex()];
	}
	return nullptr;
}

template<typename T>
TreeNode<T>* NaryTree<T>::add(TreeNode<T>* parent, T element) {
	if (numElements < SIZE_TREE) {
		TreeNode<T>* newNode = new TreeNode<T>(element, parent->getIndex(), numElements);
		elements[numElements] = newNode;
		numElements++;
		return newNode;
	}
	return nullptr;
}

template<typename T>
void NaryTree<T>::setRoot(T element) {
	TreeNode<T>* newNode = new TreeNode<T>(element, NULL, numElements);
	elements[numElements] = newNode;
	numElements++;
}

template<typename T>
TreeNode<T>* NaryTree<T>::getRightSibling(TreeNode<T>* node) {
	int parentIndex = node->getParentIndex();	
	int currentIndex = node->getIndex();
	for (int i = currentIndex+1; i < numElements; i++) {
		if (elements[i]->getParentIndex() == parentIndex) {
			return elements[i];
		}
	}
	return nullptr;
}

template<typename T>
TreeNode<T>* NaryTree<T>::getMostLeftChild(TreeNode<T>* node) {
	if (node != nullptr) {
		int currentIndex = node->getIndex();
		for (int i = currentIndex + 1; i < numElements; i++) {
			if (elements[i]->getParentIndex() == currentIndex) {
				return elements[i];
			}
		}
	}
	return nullptr;
}

template<typename T>
int NaryTree<T>::getSizeOfChildren(TreeNode<T>* node) {
	int currentIndex = node->getIndex();
	int count = 0;
	for (int i = currentIndex + 1; i < numElements; i++) {
		if (elements[i]->getParentIndex() == currentIndex) {
			count++;
		}
	}
	return count;
}

template<typename T>
bool NaryTree<T>::isLeaf(TreeNode<T>* node) {
	return getSizeOfChildren(node) == 0;
}

template<typename T>
void NaryTree<T>::removeLeaf(TreeNode<T>* node) {
	if (isLeaf(node)) {
		if (numElements == 1) {
			numElements == 0;
		}
		else {
			int i = node->getIndex();
			int indexToDelete = i;
			while (i+1 < numElements){
				elements[i] = elements[i+1];
				elements[i]->setIndex(elements[i]->getIndex() - 1);
				elements[i+1] = nullptr;
				if (elements[i]->getParentIndex() > indexToDelete) {
					elements[i]->setParentIndex(elements[i]->getParentIndex() - 1);
				}
				i++;
			}
		}
		numElements--;
	}
	delete node;
}

template<typename T>
TreeNode<T>* NaryTree<T>::getRoot() {
	if (!isEmpty()) {
		return elements[0];
	}
	return nullptr;
}

template<typename T>
int NaryTree<T>::getValue(TreeNode<T>* node) {
	if (node) {
		return node->getValue();
	}
	return NULL;
}