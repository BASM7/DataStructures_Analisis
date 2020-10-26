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
		if (this != nullptr) {
			TreeNode<T>* first = this->leftChild;
			if (first != nullptr) {
				TreeNode<T>* next = first->rightSibling;
				while (!first->nextFather) {
					delete first;
					first = next;
					next = first->rightSibling;
				}
				std::cout << first->value;
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

	void clear() { delete this;  }; //Done.
	bool isEmpty() { return this->root; };//Done.
	TreeNode<T>* add(TreeNode<T>* parent, T element); // Done.
	void removeLeaf(TreeNode<T>* node); //Done.
	void setRoot(T element); //Done.
	void setValue(TreeNode<T>* ptr, T element) { ptr->value = element; }; //Done.
	TreeNode<T>* getMostLeftChild(TreeNode<T>* ptr); //Done.
	TreeNode<T>* getRightSibling(TreeNode<T>* ptr); // Done.
	TreeNode<T>* getRoot() { return this->root; }; //Done.
	TreeNode<T>* getParent(TreeNode<T>* ptr);//Done.
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
			newNode = new TreeNode<T>(element, 0);
			newNode->rightSibling = this->getMostLeftChild(parent);
			parent->leftChild = newNode;

		}
		else {
			newNode = new TreeNode<T>(element, parent, true);
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
	TreeNode<T>* newNode = new TreeNode<T>(element, false);
	this->root = newNode;
}

template<typename T>
TreeNode<T>* NaryTree<T>::getMostLeftChild(TreeNode<T>* ptr) {
	return ptr->leftChild;
}

template<typename T>
TreeNode<T>* NaryTree<T>::getRightSibling(TreeNode<T>* ptr) {
	if (!ptr->nextFather) {
		return ptr->rightSibling;
	}
	return nullptr;
}

template<typename T>
TreeNode<T>* NaryTree<T>::getParent(TreeNode<T>* ptr) {
	TreeNode<T>* parent = nullptr;
	if (this->root != nullptr) {
		bool done = false;
		TreeNode<T>* temp = ptr;
		while (!done && temp != nullptr) {
			if (temp->nextFather) {
				done = true;
				parent = temp->rightSibling;
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