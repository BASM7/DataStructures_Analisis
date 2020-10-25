#pragma once

template<typename T>
class TreeNode {
public:
	T value;
	TreeNode<T>* leftChild;
	TreeNode<T>* rightSibling;
	bool nextFather;

	TreeNode() {
		this->value = NULL;
		this->leftChild = this->rightSibling = nullptr;
	}

	TreeNode(T element, bool tag) { //Tag 0 = siguiente hermano, Tag 1 = siguiente es el padre
		this->value = element;
		this->nextFather = tag;
		this->leftChild = this->rightSibling = nullptr;
	}

	TreeNode(T element, TreeNode<T>* parent, bool tag) {
		this->value = element;
		this->nextFather = tag;
		this->rightSibling = parent;
		this->leftChild = nullptr;
	}

	virtual ~TreeNode() {
		delete leftChild;
		delete rightSibling;
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


	virtual ~NaryTree() {};

	void clear() {}; //TODO.
	bool isEmpty() { return this->root; };//Done.
	void add(TreeNode<T>* parent, T element); // Done.
	void removeLeaf(TreeNode<T>* node); //TODO.
	void setRoot(T element); //Done.
	void setValue(TreeNode<T>* ptr, T element) { ptr->value = element; }; //Done.
	TreeNode<T>* getMostLeftChild(TreeNode<T>* ptr); //Done.
	TreeNode<T>* getRightSibling(TreeNode<T>* ptr); // Done.
	TreeNode<T>* getRoot() { return this->root; }; //Done.
	TreeNode<T>* getParent(TreeNode<T>* ptr);//Done.
	int getValue(TreeNode<T>* ptr) { return ptr->value; }; //Done.
	int getSizeOfChildren(TreeNode<T>* ptr); //Done.
	bool isLeaf(TreeNode<T>* ptr) { return this->getSizeOfChildren(ptr) == 0; }; //Done.
	int size();//

	//DEBUG.
	void printPreOrder();

};



template<typename T>
void NaryTree<T>::add(TreeNode<T>* parent, T element) {
	if (this->getRoot() != nullptr) {
		if (parent->leftChild != nullptr) {
			TreeNode<T>* newNode = new TreeNode<T>(this->getMostLeftChild(parent)->value, 
				this->getRightSibling(getMostLeftChild(parent)), this->getMostLeftChild(parent)->nextFather);
			this->getMostLeftChild(parent)->rightSibling = newNode;
			this->getMostLeftChild(parent)->value = element;
			this->getMostLeftChild(parent)->nextFather = false;
		}
		else {
			TreeNode<T>* newNode = new TreeNode<T>(element, parent, true);
			parent->leftChild = newNode;
		}
	}
}

template<typename T>
void NaryTree<T>::removeLeaf(TreeNode<T>* node) {
	TreeNode<T>* temp = node;
	while (!temp->nextFather) {
		temp = this->getRightSibling(temp);
	}

	bool done = false;
	temp = this->getMostLeftChild(temp);
	while (!done) {
		if (this->getRightSibling(temp) == node) {
			TreeNode<T>* toDelete = this->getRightSibling(temp);
			temp->rightSibling = this->getRightSibling(toDelete);
			delete toDelete;
			done = true;
		}
		else {
			temp = this->getRightSibling(temp);
		}
	}
}

template<typename T>
void NaryTree<T>::setRoot(T element) {
	TreeNode<T>* newNode = new TreeNode<T>(element, false);
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
	if (this->root != nullptr) {
		bool done = false;
		TreeNode<T>* temp = ptr;
		while (!done) {
			if (temp->nextFather) {
				done = true;
				parent = this->getRightSibling(temp);
			}
			else {
				temp = this->getRightSibling(temp);
			}
		} 
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
			if (temp->nextFather) {
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
int NaryTree<T>::size() {
	int count = 0;
	if (this->getRoot() != nullptr) {
		count++;
		TreeNode<T>* temp = this->getMostLeftChild(this->getRoot());
		while (temp != nullptr) {
			
		}
	}
	return 0;
}