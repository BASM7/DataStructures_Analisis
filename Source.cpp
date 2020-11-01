/*
*	TP1 - Analisis de Algoritmos.
* @author B93986 Luis Alfonso Jiménez 
* @author B95346 Jesús Alonso Moreno Montero
* @author B95092 Víctor Jesús Mora Abarca
*/


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

#include "CircularQueue.h"		
#include "DynamicQueue.h"	// Implementación de una cola dinámica para árboles donde se desconoce el tamaño.
#include "Stack.h"

#include "PosList.h"

#include "NaryTreeA.h"
//#include "NaryTreeB.h"
//#include "NaryTreeC.h"
//#include "NaryTreeD.h"

std::map <std::string, NaryTree<int>*> treeRegistry;

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
	DynamicQueue<TreeNode<T>*> queue;
	queue.push(tree->getRoot());
	while (!queue.isEmpty()) {
		TreeNode<T>* temp = tree->getMostLeftChild(queue.top());
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
	if (!tree->isEmpty()) {
		return search(tree, tree->getRoot(), element);
	}
	return false;
}

template<typename T>
TreeNode<T>* searchNode(NaryTree<T>* tree, TreeNode<T>* node, T element) {
	bool find = false;
	TreeNode<T>* foundNode = nullptr;
	if (tree->getValue(node) == element) {
		foundNode = node;
		find = true;
	}
	else {
		TreeNode<T>* child = tree->getMostLeftChild(node);
		while (child != nullptr && !find) {
			foundNode = searchNode(tree, child, element);
			if (foundNode != nullptr)
				find = true;
			child = tree->getRightSibling(child);
		}
	}
	return foundNode;
}

template<typename T>
TreeNode<T>* searchNode(NaryTree<T>* tree, T element) {
	if (!tree->isEmpty()) {
		return searchNode(tree, tree->getRoot(), element);
	}
	return nullptr;
}

void printTreeNames() {
	for (auto it = treeRegistry.begin(); it != treeRegistry.end(); ++it) {
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
	bool valid = false;
	int num;
	while (!valid) {
		std::cout << message << std::endl;
		std::cin >> num;
		node = searchNode(tree, num);
		if (node == nullptr) {
			std::cout << "\tNo se pudo encontrar ese valor..." << std::endl;
		}
		else {
			valid = true;
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
		if (!(treeRegistry.find(name) == treeRegistry.end())) {			
			validName = true;
		}
	}
	return name;
}

void pressEnter() {
	std::cout << "\tIngrese Enter para continuar..." << std::endl;
	_getch();
}

void showMenu() {

	

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
		std::cout << "| 1) Iniciar.\t\t13) HermanoIzquierdo." << std::endl;
		std::cout << "| 2) Destruir.\t\t14) EtiquetasRepetidas." << std::endl;
		std::cout << "| 3) Vaciar.\t\t15) Altura." << std::endl;
		std::cout << "| 4) PonerRaiz.\t\t16) Profundidad." << std::endl;
		std::cout << "| 5) AgregarHijo.\t17) ListarEtiquetasEnNivelRecPreOrden." << std::endl;
		std::cout << "| 6) BorrarHoja.\t18) ListarEtiquetasEnNivelRecNiveles." << std::endl;
		std::cout << "| 7) ModificarEtiqueta.\t19) Copiar." << std::endl;
		std::cout << "| 8) Raiz.\t\t20) Iguales." << std::endl;
		std::cout << "| 9) Padre.\t\t21) ListarPreOrdenRecursivo." << std::endl;
		std::cout << "| 10) HijoMasIzquierdo.\t22) ListarPreOrdenPila." << std::endl;
		std::cout << "| 11) HermanoDerecho.\t23) ListaNiveles." << std::endl;
		std::cout << "| 12) BuscarEtiqueta.\t24) NumElementos." << std::endl;
		std::cout << std::endl;
		std::cout << "| 0) Salir." << std::endl;
		std::cout << "| =====================================================================" << std::endl;
		std::cin >> option;

		NaryTree<int>* temp_tree = new NaryTree<int>();
		NaryTree<int>* temp_treeB = new NaryTree<int>();
		TreeNode<int>* temp_node = nullptr;
		int num = -1;
		std::string name = "";

		switch (option)
		{
		case 0:
			finished = true;

			delete temp_tree;
			delete temp_treeB;

			break;
		case 1:
			std::cout << "\tNombre del arbol: " << std::endl;
			std::cin >> name;
			treeRegistry.insert({ name, temp_tree });
			pressEnter();
			break;
		case 2:
			std::cout << "\tNombre del arbol: " << std::endl;
			std::cin >> name;
			temp_tree = treeRegistry.find(name)->second;
			treeRegistry.erase(treeRegistry.find(name));
			delete temp_tree;
			break;
		case 3:
			temp_tree = treeRegistry.find(getTreeName())->second;
			temp_tree->clear();
			pressEnter();
			break;
		case 4:
			temp_tree = treeRegistry.find(getTreeName())->second;
			std::cout << "\tIngrese el valor: " << std::endl;
			std::cin >> num;
			temp_tree->setRoot(num);
			break;
		case 5:
			//AgregarHijo.
			temp_tree = treeRegistry.find(getTreeName())->second;
			temp_node = getValidNode(temp_tree, "\tIngrese el valor del padre: ");
			std::cout << "\t Agregando a: " << temp_tree->getValue(temp_node) << std::endl;
			std::cout << "\tIngrese el valor: " << std::endl;
			std::cin >> num;
			temp_tree->add(temp_node, num);
			pressEnter();
			break;
		case 6:
			//BorrarHoja.
			temp_tree = treeRegistry.find(getTreeName())->second;
			temp_node = getValidNode(temp_tree, "\tIngrese la hoja a borrar: ");
			temp_tree->removeLeaf(temp_node);
			break;
		case 7:
			//MoficarEtiqueta.
			temp_tree = treeRegistry.find(getTreeName())->second;
			temp_node = getValidNode(temp_tree, "\tIngrese el valor a cambiar: ");
			std::cout << "\tIngrese el valor: " << std::endl;
			std::cin >> num;
			temp_tree->setValue(temp_node, num);
			pressEnter();
			break;
		case 8:
			// Obtener raiz.
			temp_tree = treeRegistry.find(getTreeName())->second;
			std::cout << "\t La raíz es: " << temp_tree->getValue(temp_tree->getRoot()) << std::endl;
			pressEnter();
			break;
		case 9:
			//Padre
			temp_tree = treeRegistry.find(getTreeName())->second;
			temp_node = getValidNode(temp_tree, "\tIngrese el valor: ");
			temp_node = temp_tree->getParent(temp_node);
			if (temp_node == nullptr)
				std::cout << "\t La raíz no tiene padre." << std::endl;
			else
				std::cout << "\t El padre es: " << temp_tree->getValue(temp_node) << std::endl;
			pressEnter();
			std::cin.get();
			break;
		case 10:
			//HijoMasIzq
			std::cout << "\tBúscando hijo más izquierdo..." << std::endl;
			temp_tree = treeRegistry.find(getTreeName())->second;
			temp_node = getValidNode(temp_tree, "\tIngrese el valor: ");
			temp_node = temp_tree->getMostLeftChild(temp_node);
			if (temp_node == nullptr)
				std::cout << "\t El valor ingresado no tiene hijo más izquierdo." << std::endl;
			else
				std::cout << "\t El hijo más izquierdo es: " << temp_tree->getValue(temp_node) << std::endl;
			pressEnter();
			std::cin.get();
			break;
		case 11:
			//BuscarHermanoDer			
			std::cout << "\tBúscando hermano derecho..." << std::endl;
			temp_tree = treeRegistry.find(getTreeName())->second;
			temp_node = getValidNode(temp_tree, "\tIngrese el valor: ");
			temp_node = temp_tree->getRightSibling(temp_node);
			if (temp_node == nullptr)
				std::cout << "\t El valor ingresado no tiene hermano derecho." << std::endl;
			else
				std::cout << "\t El hermano derecho es: " << temp_tree->getValue(temp_node) <<std::endl;
			pressEnter();
			break;
		case 12:
			//BuscarEtiqueta.
			temp_tree = treeRegistry.find(getTreeName())->second;
			std::cout << "\tIngrese el valor a buscar: " << std::endl;
			std::cin >> num;
			if (search(temp_tree, num))
				std::cout << "\t El árbol si tiene ese valor." << std::endl;
			else
				std::cout << "\t El árbol no tiene ese valor." << std::endl;
			pressEnter();
			break;
		case 13:
			//Hermano Izq.
			std::cout << "\tBúscando hermano izquierdo..." << std::endl;
			temp_tree = treeRegistry.find(getTreeName())->second;
			temp_node = getValidNode(temp_tree, "\tIngrese el valor: ");
			temp_node = getLeftSibling(temp_tree, temp_node);
			if (temp_node == nullptr)
				std::cout << "\t El valor ingresado no tiene hermano izquierdo." << std::endl;
			else
				std::cout << "\t El hermano izquierdo es: " << temp_tree->getValue(temp_node) << std::endl;
			pressEnter();
			break;
		case 14:
			//EtiquetasRepetidas.
			temp_tree = treeRegistry.find(getTreeName())->second;
			if (hasRepeated(temp_tree))
				std::cout << "\t El árbol si tiene valores repetidos." << std::endl;
			else
				std::cout << "\t El árbol no tiene valores repetidos." << std::endl;
			pressEnter();
			break;
		case 15:
			//Altura.
			temp_tree = treeRegistry.find(getTreeName())->second;
			temp_node = getValidNode(temp_tree, "\tIngrese el valor: ");
			std::cout << "\t La altura de " << temp_tree->getValue(temp_node) << " es: " << getHeight(temp_tree, temp_node) << std::endl;
			pressEnter();
			break;
		case 16:
			//Profundidad.
			temp_tree = treeRegistry.find(getTreeName())->second;
			temp_node = getValidNode(temp_tree, "\tIngrese el valor: ");
			std::cout << "\t La profundidad de " << temp_tree->getValue(temp_node) << " es: " << getDepth(temp_tree, temp_node) << std::endl;
			pressEnter();
			break;
		case 17:
			temp_tree = treeRegistry.find(getTreeName())->second;
			std::cout << "\tIngrese el nivel a imprimir: " << std::endl;
			std::cin >> num;
			std::cout << "\t Valores en el nivel " << num << " son: ";
			showLevelPreOrder(temp_tree, num);
			std::cout << std::endl;
			pressEnter();
			break;
		case 18:
			//ListasNivelPorNiveles
			temp_tree = treeRegistry.find(getTreeName())->second;
			std::cout << "\tIngrese el nivel a imprimir: " << std::endl;
			std::cin >> num;
			std::cout << "\t Valores en el nivel "<< num <<" son: ";
			showLevels(temp_tree, num);
			std::cout << std::endl;
			pressEnter();
			break;
		case 19:
			//Copiar
			std::cout << "\tPrimer árbol..." << std::endl;
			temp_tree = treeRegistry.find(getTreeName())->second;
			std::cout << "\Segundo árbol..." << std::endl;
			temp_treeB = treeRegistry.find(getTreeName())->second;
			copy(temp_tree, temp_treeB);
			std::cout << "\t El árbol fue copiado." << std::endl;
			pressEnter();
			break;
		case 20:
			//Iguales
			std::cout << "\tPrimer árbol..." << std::endl;
			temp_tree = treeRegistry.find(getTreeName())->second;
			std::cout << "\Segundo árbol..." << std::endl;
			temp_treeB = treeRegistry.find(getTreeName())->second;
			if (equals(temp_tree, temp_treeB))
				std::cout << "\t Los árboles son iguales." << std::endl;
			else
				std::cout << "\t Los árboles no son iguales." << std::endl;
			pressEnter();
			break;
		case 21:
			//Listar preOrden Rec.
			temp_tree = treeRegistry.find(getTreeName())->second;
			std::cout << "\t El árbol es: ";
			preOrderRec(temp_tree);
			std::cout << std::endl;
			pressEnter();
			break;
		case 22:
			//Listar Pila.
			temp_tree = treeRegistry.find(getTreeName())->second;
			std::cout << "\t El árbol es: ";
			preOrderStack(temp_tree);
			std::cout << std::endl;
			pressEnter();
			break;
		case 23:
			//Listar Cola.
			temp_tree = treeRegistry.find(getTreeName())->second;
			std::cout << "\t El árbol es: ";
			levelsDynamicQueue(temp_tree);
			std::cout << std::endl;
			pressEnter();
			break;
		case 24:
			temp_tree = treeRegistry.find(getTreeName())->second;
			std::cout << "\t La cantidad de elementos es: " << temp_tree->getSize() << std::endl;
			pressEnter();
			break;
		default:
			break;
		}

	} while (!finished);

}

int main() {	

	NaryTree<int>* tree = new NaryTree<int>();
	//tree->setRoot(12);

	//auto node = tree->add(tree->getRoot(), 4);
	//auto node2 = tree->add(tree->getRoot(), 5);
	//auto node3 = tree->add(node2, 3);
	//auto node6 = tree->add(node2, 6);
	//auto node4 = tree->add(tree->getRoot(), 9);
	//auto node5 = tree->add(node3, 10);
	//auto node7 = tree->add(tree->getRoot(), 12);

	//std::cout << tree->getValue(tree->getParent(node5)) << std::endl;
	//std::cout << tree->getValue(tree->getRightSibling(node4)) << std::endl;

	treeRegistry.insert({ "A1", tree });

	showMenu();

	return 0;

}