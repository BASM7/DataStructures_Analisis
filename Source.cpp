#include <iostream>
#include "PosList.h"
#include "DynamicQueue.h"
#include "NaryTree.h"

int main() {

	NaryTree<int> tree;
	tree.setRoot(2);
	tree.add(tree.getRoot(), 3);
	tree.add(tree.getRoot(), 4);
	tree.add(tree.getRoot(), 1);
	tree.add(tree.getRoot(), 9);
	tree.add(tree.getRoot(), 10);

	auto node = tree.getRoot()->children->getFirst()->value;
	auto node2 = tree.getRoot()->children->getLast()->value;
	tree.add(node, 90);
	tree.add(node, 45);
	tree.add(node, 36);
	tree.add(node, 12);

	//std::cout << tree.getSize() << std::endl;

	tree.add(node2, 15);
	tree.add(node2, 11);
	tree.add(node2, 28);

	//std::cout << tree.getSize() << std::endl;

	auto test = tree.getRoot()->children->getLast()->value;
	//std::cout << ((tree.getRightSibling(test) == nullptr) ? -1 : tree.getRightSibling(test)->value) << std::endl;

	//std::cout << ((tree.getParent(tree.getRoot()) == nullptr) ? -1 : tree.getParent(test)->value) << std::endl;
	//std::cout << ((tree.getParent(test) == nullptr) ? -1 : tree.getParent(test)->value) << std::endl;
	//std::cout << ((tree.getParent(node) == nullptr) ? -1 : tree.getParent(node)->value) << std::endl;

	auto test2 = tree.getRoot()->children->getFirst()->value->children->getFirst()->value;	
	//std::cout << ((tree.getParent(test2) == nullptr) ? -1 : tree.getParent(test2)->value) << std::endl;

	//tree.printPreOrder();

	//std::cout << tree.getSizeOfChildren(tree.getRoot()) << std::endl;
	//std::cout << tree.preOrderGetCantNodesOnLevel(1) << std::endl;
	//std::cout << tree.preOrderGetCantNodesOnLevel(2) << std::endl;
	//std::cout << tree.preOrderGetCantNodesOnLevel(3) << std::endl;
	//std::cout << tree.preOrderGetCantNodesOnLevel(4) << std::endl;

	std::cout << tree.getHeight(tree.getRoot()) << std::endl;

	auto node3 = tree.getRoot()->children->getLast()->value->children->getFirst()->value;
	
	tree.add(node3, 56);

	std::cout << tree.getHeight(tree.getRoot()) << std::endl;
	std::cout << tree.getHeight(node) << std::endl;
	std::cout << tree.getHeight(node->children->getFirst()->value) << std::endl;

	return 0;
}