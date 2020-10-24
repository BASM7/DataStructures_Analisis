#pragma once

template<typename T>
class TreeNode {
public:
	T value;
	int parent;
	int index;
	TreeNode<T>* parent;

	TreeNode() {
		this->value = NULL;
		this->parent_index = NULL;
	}

	TreeNode(T element) {
		this->value = element;
		this->parent = NULL;
	}

	TreeNode(T element, TreeNode<T>* parent) {
		this->value = element;
		this->parent = parent;
	}
};

template<typename T>
class NaryTree {
	TreeNode<T>* arrayOfElements;
	int numElements;
	int maxElements;

public:
	NaryTree() {
		this->arrayOfElements = nullptr;
		this->numElements = 0;
	};

	NaryTree(int maxSize) {
		this->arrayOfElements = new TreeNode<T>[maxSize];
		this->maxElements = maxElements;
		this->numElements = 0;
	};
	virtual ~NaryTree() {};

	void clear() {}; //TODO.
	bool isEmpty() { return this->numElements == 0 };
	TreeNode<T>* add(TreeNode<T>* parent, T element); // TODO.
	void removeLeaf(TreeNode<T>* node); //TODO.
	void setRoot(int element); //TODO.
	void setValue(TreeNode<T>*, T element) {}; //TODO.
	TreeNode<T>* getMostLeftChild(TreeNode<T>* ptr); //TODO.
	TreeNode<T>* getRightSibling(TreeNode<T>* ptr); // TODO.
	TreeNode<T>* getRoot(); // NOT TESTED.
	TreeNode<T>* getParent(TreeNode<T>* ptr) { return ptr->parent; };
	int getValue(TreeNode<T>* ptr) { return ptr->value; };
	int getSizeOfChildren(TreeNode<T>* ptr); //TODO.
	int getSize() {return this->numElements};
	bool isLeaf(TreeNode<T>* ptr); //TODO.

	//DEBUG.
	void printPreOrder();

};

template<typename T>
TreeNode<T>* NaryTree<T>::add(TreeNode<T>* parent, T element) {
	if (this->numElements < this->maxElements) {
		TreeNode<T>* newNode = new TreeNode<T>(element, parent);
		this->arrayOfElements[this->numElements] = newNode;
		this->numElements++;
		return newNode;
	}
	return nullptr;
}

template<typename T>
TreeNode<T>* NaryTree<T>::getRoot() {
	if (this->getSize() != 0) {
		return this->arrayOfElements[0];
	}
	return NULL;
}