#ifndef AVLTREE
#define AVLTREE
#include "Node.h"

template <typename T>
struct AVLTree {
	void insert(T);
	void deleteNode(T);
	void ordered();
	void preOrdered();
	AVLTree();
private:
	Node<T>* innerInsert(Node<T>*, T);
	void innerOrdered(Node<T>*);
	void innerPreOrdered(Node<T>*);
	Node<T>* root;
	int getHeight(Node<T>*);
	int max(int, int);
	int getBalance(Node<T>*);
	Node<T>* firstOfSubtree(Node<T>*);
	Node<T>* successor(Node<T>*);
	Node<T>* leftRotate(Node<T>*);
	Node<T>* rightRotate(Node<T>*);
	Node<T>* innerDeleteNode(Node<T>*, T);
	// test
};
#include "AVLTree.cpp"
#endif