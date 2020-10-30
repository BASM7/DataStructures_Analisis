#pragma once
#include <iostream>

template<typename T>
class TreeCell;

template<typename T>
class TreeNode {
public:
	T value;
	TreeNode<T>* nextElement;
	TreeCell<T>* child;

	TreeNode() {
		this->value = NULL;
		this->nextElement = nullptr;
		this->child = nullptr;
	}

	TreeNode(T element) {
		this->value = element;
		this->nextElement = nullptr;
		this->child = nullptr;
	}

	virtual ~TreeNode() {
		delete nextElement;
		delete child;
	}
};

template<typename T>
class TreeCell {
public:
	TreeNode<T>* element;
	TreeCell<T>* next;

	TreeCell() {
		this->element = nullptr;
		this->next = nullptr;
	}

	TreeCell(TreeNode<T>* element) {
		this->element = element;
		this->next = nullptr;
	}

	virtual ~TreeCell() {
		delete element;
		delete next;
	}
};

template<typename T>
class NaryTree {
	TreeNode<T>* root;
	int size;

public:
	NaryTree() {
		root = nullptr;
	};

	virtual ~NaryTree() {
		delete root;
	};

	void clear();
	bool isEmpty() { return root == nullptr; };										//listo
	TreeNode<T>* add(TreeNode<T>* parent, T element);
	void setValue(TreeNode<T>* ptr, T element) { ptr->value = element; };			//listo
	TreeNode<T>* getRoot() { return root; };									//listo
	TreeNode<T>* getMostLeftChild(TreeNode<T>* ptr);	//listo
	T getValue(TreeNode<T>* ptr) { return ptr->value; };							//listo
	int getSize() { return size; };										//accesar a tamaño porque es privado
	bool isLeaf(TreeNode<T>* ptr) { return ptr->child == nullptr; };				//listo
	int getSizeOfChildren(TreeNode<T>* ptr);	
	void removeLeaf(TreeNode<T>* node); //.
	void setRoot(T element); //Done.
	TreeNode<T>* getRightSibling(TreeNode<T>* ptr);
	TreeNode<T>* getParent(TreeNode<T>* ptr);//.
	int getSize(TreeNode<T>* ptr);
};

template<typename T>
TreeNode<T>* NaryTree<T>::getMostLeftChild(TreeNode<T>* ptr) {
	if (ptr != nullptr) {
		if (ptr->child != nullptr) {
			return ptr->child->element;
		}
	}
	return nullptr;
}

template<typename T>
TreeNode<T>* NaryTree<T>::getRightSibling(TreeNode<T>* ptr) {
	TreeNode<T>* rightSibling = nullptr;
	if (ptr != nullptr) {
		TreeNode<T>* parent = getParent(ptr);
		TreeCell<T>* temp_child = parent->child;
		bool done = false;
		while (temp_child != nullptr && !done) {
			if (temp_child->element == ptr) {
				if (temp_child->next != nullptr) {
					rightSibling = temp_child->next->element;
					done = true;
				}				
			}
			temp_child = temp_child->next;
		}
	}
	return rightSibling;
}

template<typename T>
TreeNode<T>* NaryTree<T>::add(TreeNode<T>* parent, T element) {
	TreeNode<T>* newNodeElement = new TreeNode<T>(element);
	TreeCell<T>* newNodeChild = new TreeCell<T>(newNodeElement);

	TreeNode<T>* temp = parent->nextElement;
	parent->nextElement = newNodeElement;
	newNodeElement->nextElement = temp;

	TreeCell<T>* temp_child = parent->child;
	newNodeChild->next = temp_child;
	parent->child = newNodeChild;
	size++;
	return newNodeElement;
}

template<typename T>
TreeNode<T>* NaryTree<T>::getParent(TreeNode<T>* ptr) {
	TreeNode<T>* temp_parent = nullptr;
	TreeCell<T>* temp_child = nullptr;
	if (!isEmpty() && ptr != nullptr && ptr != getRoot()) {
		temp_parent = getRoot();		
		if (temp_parent != ptr) {
			bool done = false;
			while (temp_parent != nullptr && !done) {
				temp_child = temp_parent->child;
				while (temp_child != nullptr && !done) {
					if (temp_child->element == ptr) {
						return temp_parent;
					}
					temp_child = temp_child->next;
				}
				temp_parent = temp_parent->nextElement;
			}
		}
	}
	return temp_parent;
}

template<typename T>
int NaryTree<T>::getSizeOfChildren(TreeNode<T>* ptr) {
	int count = 0;
	TreeCell<T>* temp = ptr->child;
	if (temp != nullptr) {
		bool done = false;
		while (!done) {
			if (temp == nullptr) {
				done = true;
			}
			else {
				temp = temp->next;
				count++;
			}
		}
	}
	return count;
}

template<typename T>
void NaryTree<T>::setRoot(T element) {
	TreeNode<T>* newNode = new TreeNode<T>(element);
	root = newNode;
	size++;
}

template<typename T>
void NaryTree<T>::clear() {
	TreeNode<T>* temp = getRoot();
	while (temp->nextElement != nullptr) {
		TreeCell<T>* temp2 = temp->child;
		temp->child = nullptr;
		while (temp2->next != nullptr) {
			TreeCell<T>* toDelete = temp2->next;
			temp2->next = temp2->next->next;
			delete toDelete;
		}
		delete temp2;

		TreeNode<T>* toDelete = temp;
		root = temp->nextElement;
		delete toDelete;
	}
	temp->value = NULL;
	size = 0;
}

template<typename T>
void NaryTree<T>::removeLeaf(TreeNode<T>* node) {
	TreeNode<T>* temp = this->getRoot();
	if (temp == node) {
		temp = nullptr;
	}
	else {
		bool done = false;
		bool done2 = false;
		TreeCell<T>* temp2 = temp->child;
		while (temp != nullptr && !done) {
			TreeNode<T>* toDelete = temp2->element;    //QUE PASA SI TEMP2 ES NULLPTR?
			if (toDelete == node) {
				temp->child = temp->child->next;
				delete toDelete;
				done2 = true;
			}
			else {
				toDelete = temp2->element;
				while (temp2 != nullptr && !done2) {
					if (toDelete == node) {
						temp2->next = temp2->next->next;
						delete toDelete;
						done2 = true;
					}
					else {
						temp2 = temp2->next;
					}
				}
				if (temp->nextElement == node) {
					TreeNode<T>* toDelete2 = temp->nextElement;
					temp->nextElement = temp->nextElement->nextElement;
					delete toDelete2;
					done = true;
				}
				else {
					temp = temp->nextElement;
				}
			}
		}
	}
	this->size--;
}