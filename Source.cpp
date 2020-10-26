#include <iostream>
#include <unordered_map> 
#include <vector>
#include <set>

#include "PosList.h"
#include "DynamicQueue.h"
#include "Stack.h"

#include "NaryTreeA.h"
//#include "NaryTreeC.h"
//#include "NaryTreeD.h"
//#include "NaryTree.h"

#include <math.h>

//NaryTree<int> crearArbolKario(int hijos, int niveles, NaryTree<int> arbol) {
//	if (arbol.getSize() == 0) {
//
//		DynamicQueue<TreeNode<int>*> cola;
//
//		int etiqueta = 1;
//		arbol.setRoot(etiqueta);
//		
//		cola.push(arbol.getRoot());
//
//		int nivelActual = 2;
//		while (nivelActual <= niveles) {			
//			TreeNode<int>* temp = cola.pop();
//			for (int i = 0; i < hijos; i++) {
//				etiqueta++;
//				TreeNode<int>* nuevoNodo = arbol.add(temp, etiqueta);
//				if (nivelActual < niveles) {
//					cola.push(nuevoNodo);
//				}				
//			}
//			int nodoMaximoEnNivel = (pow(hijos, nivelActual) - 1) / (hijos - 1.0);
//			if (etiqueta == nodoMaximoEnNivel) {
//				nivelActual++;				
//			}
//		}
//	}
//	return arbol;
//}
//
//int cantHojasR(TreeNode<int>* nodo, NaryTree<int> arbol) {
//	int hojas = 0;
//	TreeNode<int>* temp = arbol.getMostLeftChild(nodo);
//	if (temp != nullptr) {
//		while (temp != nullptr) {
//			hojas = hojas + cantHojasR(temp, arbol);
//			temp = arbol.getRightSibling(temp);
//		}
//	}
//	else {
//		hojas = hojas + 1;
//	}
//	return hojas;
//}
//
//int cantHojas(NaryTree<int> arbol) {
//	return cantHojasR(arbol.getRoot(), arbol);
//}

// Ejercicio 1.
template<typename T>
TreeNode<T>* getLeftSibling(NaryTree<T>* tree, TreeNode<T>* node) {
	TreeNode<T>* leftSibling = nullptr;
	if (node != nullptr) {
		TreeNode<T>* parent = tree->getParent(node);
		TreeNode<T>* temp = tree->getMostLeftChild(parent);
		bool found = false;
		while (temp != node && temp != nullptr && !found) {
			auto rightSibling = tree->getRightSibling(temp);
			if (rightSibling == node) {
				leftSibling = temp;
			}
			temp = tree->getRightSibling(temp);
		}
	}
	return leftSibling;
}

// Ejercicio 3.
template<typename T>
int getHeight(NaryTree<T>* tree, TreeNode<T>* node) {
	if (node == nullptr || tree->isLeaf(node)) {
		return 0;
	}
	int maxHeight = 0;
	TreeNode<T>* child = tree->getMostLeftChild(node);
	while (child != nullptr) {
		int newHeight = getHeight(tree, child);
		if (maxHeight < newHeight) {
			maxHeight = newHeight;
		}
		child = tree->getRightSibling(child);
	}
	return maxHeight + 1;
}

// Ejercicio 4.
template<typename T>
int getDepth(NaryTree<T>* tree, TreeNode<T>* node) {
	int count = 0;
	if (node != nullptr) {
		TreeNode<T>* parent = tree->getParent(node);
		while (parent != nullptr) {
			count++;
			parent = tree->getParent(parent);
		}
	}
	return count;
}

template<typename T>
void preOrder(NaryTree<T>* tree, TreeNode<T>* node) {
	std::cout << tree->getValue(node) << " ";
	TreeNode<T>* child = tree->getMostLeftChild(node);
	while (child != nullptr) {
		preOrder(tree, child);
		child = tree->getRightSibling(child);
	}
}

template<typename T>
void preOrderRec(NaryTree<T>* tree) {
	preOrder(tree, tree->getRoot());
}

template<typename T>
void preOrderStack(NaryTree<T>* tree) {
	Stack<TreeNode<T>*> stack;	
	Stack<TreeNode<T>*> auxStack;
	stack.push(tree->getRoot());
	while (!stack.isEmpty()) {
		TreeNode<T>* current = stack.getTop()->value;
		stack.pop();
		std::cout << tree->getValue(current) << " ";

		TreeNode<T>* child = tree->getMostLeftChild(current);		
		while (child != nullptr) {
			auxStack.push(child);
			child = tree->getRightSibling(child);
		}

		while (!auxStack.isEmpty()) {
			stack.push(auxStack.getTop()->value);
			auxStack.pop();
		}
	}
}

template<typename T>
bool hasRepeated(NaryTree<T>* tree) {
	std::unordered_map<int, int> map;
	DynamicQueue<TreeNode<int>*> queue;

	if (tree->getRoot() != nullptr) {
		TreeNode<int>* current = tree->getRoot();
		queue.push(current);
		while (!queue.isEmpty()) {
			current = queue.pop();
			if (map.find(tree->getValue(current)) == map.end()) {
				map.insert(std::make_pair(tree->getValue(current), 0));
			}
			else {
				return true;
			}
			TreeNode<int>* child = tree->getMostLeftChild(current);
			while (child != nullptr) {
				queue.push(child);
				child = tree->getRightSibling(child);
			}
		}
	}
	return false;
}

// Ejercicio 12.
template<typename T>
bool search(NaryTree<T>* tree, TreeNode<T>* node, T element) {
	bool find = false;
	if (tree->getValue(node) == element) {
		find = true;
	}
	else {
		TreeNode<T>* child = tree->getMostLeftChild(node);
		while (child != nullptr && !find) {
			find = search(tree, child, element);
			child = tree->getRightSibling(child);
		}
	}
	return find;
}

template<typename T>
bool search(NaryTree<T>* tree, T element) {
	return search(tree, tree->getRoot(), element);
}

int main() {
	//NaryTree<int>* test_tree = new NaryTree<int>(10);

	NaryTree<int>* tree = new NaryTree<int>();
	tree->setRoot(12);
	auto node = tree->add(tree->getRoot(), 4);
	auto node2 = tree->add(tree->getRoot(), 5);
	auto node3 = tree->add(node2, 3);
	auto node6 = tree->add(node2, 6);
	auto node4 = tree->add(tree->getRoot(), 9);
	auto node5 = tree->add(node3, 10);
	auto node7 = tree->add(tree->getRoot(), 12);

	std::cout << tree->getValue(getLeftSibling(tree, node2)) << std::endl;
	//std::cout << tree->getValue(tree->getMostLeftChild(tree->getRoot())) << std::endl;
	//std::cout << getHeight(tree, node3) << std::endl;
	//std::cout << getDepth(tree, node3) << std::endl;
	//preOrderRec(tree);
	//std::cout << " - " << std::endl;
	//preOrderStack(tree);


	//std::cout << hasRepeated(tree) << std::endl;

	std::cout << search(tree, 7) << std::endl;
	//delete tree;

	return 0;
}