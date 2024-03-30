<<<<<<< HEAD
#include <string>
#include <iostream>

template <typename T>
class Node {
	T data;
	Node<T>* right;
	Node<T>* left;
};

template <typename T>
class Tree {
	Node<T>* Root;

};



int main() {

=======
#include "AVLTree.h"

int main() {
	AVLTree<int> tree;
	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	tree.insert(4);
	tree.insert(5);
	tree.insert(6);
	tree.insert(7);



    cout << "Preorder traversal of the "
        "constructed AVL tree is \n";

	tree.deleteNode(7);

    cout << "\nPreorder traversal after"
        << " deletion of 10 \n";
    tree.ordered();
	cout << endl;
	tree.preOrdered();
>>>>>>> 84ad3ac (Bugs are fixed)
	return 0;
}