#include <iostream>

#include <unordered_map>
#include <map>

#include <random>
#include <windows.h>
#include <iostream>
#include <locale>
#include <string>
#include <utility>
#include <algorithm>

#include <conio.h>

#include "DynamicQueue.h"
#include "Stack.h"

//#include "NaryTreeA.h"
//#include "NaryTreeB.h"
//#include "NaryTreeC.h"
#include "NaryTreeD.h"

std::map <std::string, NaryTree<int>*> listRegistry;

int randomInt(int min, int max) {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(mt);
}

//template<typename T>
//NaryTree<T>* createRandomTree(NaryTree<T>* tree) {
//
//	int levels = randomInt(9, 12);
//	//int levels = 10;
//
//	std::cout << "l :" << levels << std::endl;
//
//	if (tree->getSize()) {
//		DynamicQueue<TreeNode<T>*> queue;
//		int label = randomInt(0, 100);
//		tree->setRoot(label);		
//		queue.push(tree->getRoot());
//		int currentLevel = 2;
//		int levelElements = 0;
//		while (currentLevel <= levels) {			
//			TreeNode<T>* temp = queue.pop();
//			int children = randomInt(0, 3);
//			levelElements = children;
//			for (int i = 0; i < children; i++) {
//				label = randomInt(0, 100);
//				TreeNode<T>* newNode = tree->add(temp, label);
//				queue.push(newNode);
//			}
//			levelElements--;
//			if (levelElements == 0)
//				currentLevel++;
//		}
//	}
//	return tree;
//}

template<typename T>
NaryTree<T>* createRandomTree(NaryTree<T>* tree) {
	DynamicQueue<TreeNode<T>*> queue;
	int levels = randomInt(9, 12);
	tree->setRoot(randomInt(0, 100));
	queue.push(tree->getRoot());

	int level = 1;
	int elementsLevel = 1;
	int nextLevel = 0;

	while (!queue.isEmpty() && level <= levels) {

		int children = randomInt(1, 4);

		for (int i = 0; i < children; i++) {
			int label = randomInt(0, 100);
			TreeNode<T>* newNode = tree->add(queue.top(), label);
			queue.push(newNode);
			nextLevel++;
		}

		queue.pop();
		elementsLevel--;
		if (elementsLevel == 0) {
			level++;
			elementsLevel = nextLevel;
			nextLevel = 0;
		}
	}
	queue.clear();
	return tree;
}

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


// Ejercicio 2.
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

// Ejercicio 5.
template<typename T>
void showLevelPreOrderRec(TreeNode<T>* pivot, NaryTree<T>* tree, int level, int currentLevel){
	if (currentLevel == level) {
		std::cout << tree->getValue(pivot) << " ";
	}
	else {
		pivot = tree->getMostLeftChild(pivot);
		while (pivot != nullptr) {
			showLevelPreOrderRec(pivot, tree, level, currentLevel + 1);
			pivot = tree->getRightSibling(pivot);
		}
	}
}

template<typename T>
void showLevelPreOrder(NaryTree<T>* tree, int level) {
	showLevelPreOrderRec(tree->getRoot(), tree, level, 1);
	std::cout << std::endl;
}

//Ejercicio 6.
template<typename T>
void showLevels(NaryTree<T>* tree, int levelToPrint) {
	DynamicQueue<TreeNode<T>*> queue;
	queue.push(tree->getRoot());
	int level = 1;
	int elementsLevel = 1;
	int nextLevel = 0;
	while (level != levelToPrint) {
		TreeNode<T>* temp = tree->getMostLeftChild(queue.top());
		while (temp != nullptr) {
			queue.push(temp);
			nextLevel++;
			temp = tree->getRightSibling(temp);
		}
		queue.pop();
		elementsLevel--;
		if (elementsLevel == 0) {
			level++;
			elementsLevel = nextLevel;
			nextLevel = 0;
		}
	}
	while (elementsLevel > 0) {
		std::cout << tree->getValue(queue.pop()) << " ";
		elementsLevel--;
	}
	queue.clear();
}

// Ejercicio 7.
template<typename T>
NaryTree<T>* copy(NaryTree<T>* treeA, NaryTree<T>* treeB) {
	if (!treeA->isEmpty()) {
		DynamicQueue<TreeNode<T>*> queueA;
		DynamicQueue<TreeNode<T>*> queueB;

		treeB->setRoot(treeA->getValue(treeA->getRoot()));
		queueA.push(treeA->getRoot());
		queueB.push(treeB->getRoot());

		while (!queueA.isEmpty()) {
			TreeNode<T>* tempA = queueA.pop();
			TreeNode<T>* tempB = queueB.pop();

			TreeNode<T>* childA = treeA->getMostLeftChild(tempA);
			while (childA != nullptr) {
				TreeNode<T>* childB = treeB->add(tempB, treeA->getValue(childA));
				queueA.push(childA);
				queueB.push(childB);
				childA = treeA->getRightSibling(childA);
			}
		}
	}
	return treeB;
}

//Ejercicio 8.
template<typename T>
bool equals(NaryTree<T>* tree1, NaryTree<T>* tree2) {
	if (tree1->getSize() != tree2->getSize()) {
		return false;
	}
	else {
		if (tree1->getSize() == 0) {
			return true;
		}
		else {
			if (tree1->getValue(tree1->getRoot()) != tree2->getValue(tree2->getRoot())) {
				return false;
			}
			else {
				DynamicQueue<TreeNode<T>*> queue1;
				DynamicQueue<TreeNode<T>*> queue2;
				queue1.push(tree1->getRoot());
				queue2.push(tree2->getRoot());
				bool done = true;

				while (!queue1.isEmpty() && done) {
					auto root1 = queue1.pop();
					auto root2 = queue2.pop();
					if (tree1->getSizeOfChildren(root1) != tree2->getSizeOfChildren(root2)) {
						done = false;
					}
					else {
						auto child1 = tree1->getMostLeftChild(root1);
						auto child2 = tree2->getMostLeftChild(root2);
						while (child1 != nullptr && done) {
							if (tree1->getValue(child1) != tree2->getValue(child2)) {
								done = false;
							}
							else {
								queue1.push(child1);
								queue2.push(child2);
								child1 = tree1->getRightSibling(child1);
								child2 = tree2->getRightSibling(child2);
							}
						}
					}
				}
				queue1.clear();
				queue2.clear();
				return done;
			}
		}
	}
}

// Ejercicio 9.
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
	if (!tree->isEmpty()) {
		preOrder(tree, tree->getRoot());
	}
	else {
		std::cout << "El árbol esta vacío." << std::endl;
	}
}

// Ejercicio 10.
template<typename T>
void preOrderStack(NaryTree<T>* tree) {
	if (!tree->isEmpty()) {
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
	else {
		std::cout << "El árbol esta vacío." << std::endl;
	}
	
}

//Ejercicio 11.
template<typename T>
void levelsDynamicQueue(NaryTree<T>* tree) {
	DynamicQueue<TreeNode<T>> queue;
	queue.push(tree->getRoot());
	while (!queue.isEmpty()) {
		TreeNode<T> temp = tree->getMostLeftChild(queue.top());
		while (temp != nullptr) {
			queue.push(temp);
			temp = tree->getRightSibling(temp);
		}
		std::cout << tree->getValue(queue.pop()) << " ";
	}
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

template<typename T>
TreeNode<T>* searchNode(NaryTree<T>* tree, TreeNode<T>* node, T element) {
	bool find = false;
	if (tree->getValue(node) == element) {
		find = true;
		return node;
	}
	else {
		TreeNode<T>* child = tree->getMostLeftChild(node);
		while (child != nullptr && !find) {
			find = searchNode(tree, child, element);
			child = tree->getRightSibling(child);
		}
	}
	return nullptr;
}

template<typename T>
TreeNode<T>* searchNode(NaryTree<T>* tree, T element) {
	return searchNode(tree, tree->getRoot(), element);
}

void printTreeNames() {
	for (auto it = listRegistry.begin(); it != listRegistry.end(); ++it) {
		std::cout << "\t" << it->first << std::endl;
	}
}

void clear()
{
#if defined _WIN32
	system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
#elif defined (__APPLE__)
	system("clear");
#endif
}

template<typename T>
TreeNode<T>* getValidNode(NaryTree<T>* tree, std::string message) {
	TreeNode<T>* node = nullptr;
	bool valid_parent = false;
	int num;
	while (!valid_parent) {
		std::cout << message << std::endl;
		std::cin >> num;
		node = searchNode(tree, num);
		if (node == nullptr) {
			std::cout << "\tNo se pudo encontrar ese valor..." << std::endl;
		}
		else {
			valid_parent = true;
		}
	}
	return node;
}

std::string getTreeName() {
	bool validName = false;
	std::string name = ""; 
	while (!validName) {
		std::cout << "\tIngrese el nombre del arbol: " << std::endl;
		std::cin >> name;
		if (!(listRegistry.find(name) == listRegistry.end())) {			
			validName = true;
		}
	}
	return name;
}

int main() {

	NaryTree<int>* tree = new NaryTree<int>();
	tree->setRoot(12);
	//tree->removeLeaf(tree->getRoot());

	//auto node = tree->add(tree->getRoot(), 4);
	//auto node2 = tree->add(tree->getRoot(), 5);
	//auto node3 = tree->add(node2, 3);
	//auto node6 = tree->add(node2, 6);
	//auto node4 = tree->add(tree->getRoot(), 9);
	//auto node5 = tree->add(node3, 10);
	//auto node7 = tree->add(tree->getRoot(), 12);

	listRegistry.insert({"arbol1", tree});

	setlocale(LC_ALL, "spanish");
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);

	bool finished = false;

	int option;

	do {
		clear();
		std::cout << "| Menú de prueba para operadores y algoritmos básicos del modelo Árbol." << std::endl;
		std::cout << "| Arboles actuales:" << std::endl;
		printTreeNames();
		std::cout << "| =====================================================================" << std::endl;
		std::cout << "| 1) Iniciar.\t\t14) HermanoIzquierdo." << std::endl;
		std::cout << "| 2) Destruir.\t\t15) EtiquetasRepetidas." << std::endl;
		std::cout << "| 3) Vaciar.\t\t16) Altura." << std::endl;
		std::cout << "| 4) PonerRaiz.\t\t17) Profundidad." << std::endl;
		std::cout << "| 5) AgregarHijo.\t18) ListarEtiquetasPreOrden." << std::endl;
		std::cout << "| 6) BorrarHoja.\t19) ListarEtiquetasNiveles." << std::endl;
		std::cout << "| 7) ModificarEtiqueta.\t20) Copiar." << std::endl;
		std::cout << "| 8) Raiz.\t\t21) Iguales." << std::endl;
		std::cout << "| 9) Padre.\t\t22) ListarPreOrdenRecursivo." << std::endl;
		std::cout << "| 11) HijoMasIzquierdo.\t23) ListarPreOrdenPila." << std::endl;
		std::cout << "| 12) HermanoDerecho.\t24) ListaNiveles." << std::endl;
		std::cout << "| 13) Etiqueta.\t\t25) BuscarEtiqueta." << std::endl;
		std::cout << std::endl;
		std::cout << "| 0) Salir." << std::endl;
		std::cout << "| =====================================================================" << std::endl;
		std::cin >> option;

		NaryTree<int>* temp_tree = new NaryTree<int>();
		TreeNode<int>* temp_node = nullptr;
		int num = -1;
		std::string name = "";

		switch (option)
		{
		case 0:
			finished = true;
			break;
		case 1:
			std::cout << "\tNombre del arbol: " << std::endl;
			std::cin >> name;
			listRegistry.insert({ name, temp_tree });
			break;
		case 2:
			std::cin.get();
			break;
		case 3:
			std::cin.get();
			break;
		case 4:
			temp_tree = listRegistry.find(getTreeName())->second;
			std::cout << "\tIngrese el valor: " << std::endl;
			std::cin >> num;
			temp_tree->setRoot(num);
			break;
		case 5:
			//AgregarHijo.
			temp_tree = listRegistry.find(getTreeName())->second;
			temp_node = getValidNode(temp_tree, "\tIngrese el valor del padre: ");
			std::cout << "\t Agregando a: " << temp_tree->getValue(temp_node) << std::endl;
			std::cout << "\tIngrese el valor: " << std::endl;
			std::cin >> num;
			temp_tree->add(temp_node, num);
			_getch();
			break;
		case 6:
			//BorrarHoja.
			temp_tree = listRegistry.find(getTreeName())->second;
			temp_node = getValidNode(temp_tree, "\tIngrese la hoja a borrar: ");
			temp_tree->removeLeaf(temp_node);
			break;
		case 7:
			//MoficarEtiqueta.
			std::cin.get();
			break;
		case 8:
			// Obtener raiz.
			temp_tree = listRegistry.find(getTreeName())->second;
			std::cout << "\t La raíz es: " << temp_tree->getValue(temp_tree->getRoot()) << std::endl;
			_getch();
			break;
		case 9:
			std::cin.get();
			break;
		case 10:
			std::cin.get();
			break;
		case 11:
			std::cin.get();
			break;
		case 12:
			std::cin.get();
			break;
		case 13:
			std::cin.get();
			break;
		case 14:
			std::cin.get();
			break;
		case 15:
			std::cin.get();
			break;
		case 16:
			std::cin.get();
			break;
		case 17:
			std::cin.get();
			break;
		case 18:
			std::cin.get();
			break;
		case 19:
			std::cin.get();
			break;
		case 20:
			std::cin.get();
			break;
		case 21:
			std::cin.get();
			break;
		case 22:
			//Listar preOrden Rec.
			temp_tree = listRegistry.find(getTreeName())->second;
			std::cout << "\t El árbol es: ";
			preOrderRec(temp_tree);
			std::cout << std::endl;
			_getch();
			break;
		case 23:
			std::cin.get();
			break;
		case 24:
			std::cin.get();
			break;
		case 25:
			std::cin.get();
			break;
		default:
			break;
		}

	} while (!finished);


	//NaryTree<int>* treeC = new NaryTree<int>();

	//treeC = createRandomTree(treeC);
	//preOrderRec(treeC);


	//std::cout << tree->getValue(getLeftSibling(tree, node2)) << std::endl;
	//std::cout << tree->getValue(tree->getMostLeftChild(tree->getRoot())) << std::endl;
	//std::cout << getHeight(tree, node3) << std::endl;
	//std::cout << getDepth(tree, node3) << std::endl;
	//preOrderRec(tree);
	//std::cout << " - " << std::endl;
	//preOrderStack(tree);

	//showLevelPreOrder(tree, 4);

	//NaryTree<int>* treeB = new NaryTree<int>();
	//treeB = copy(tree, treeB);

	//preOrderStack(tree);
	//std::cout << " - " << std::endl;
	//preOrderRec(treeB);
	//std::cout << std::endl;

	//std::cout << equals(tree, treeB) << std::endl;

	//std::cout << "c:" << treeB->getSizeOfChildren(treeB->getRoot()) << std::endl;

	//auto nodeB = treeB->getRightSibling(treeB->getMostLeftChild(treeB->getRoot()));
	//auto nodeB2 = treeB->getMostLeftChild(nodeB);
	//std::cout << treeB->getValue(treeB->getParent(nodeB2)) << std::endl;

	//std::cout << hasRepeated(tree) << std::endl;

	//std::cout << search(tree, 7) << std::endl;
	//delete tree;

	return 0;
}