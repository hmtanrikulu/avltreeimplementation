#include "AVLTree.h"

template <typename T>
int AVLTree<T>::getHeight(Node<T>* node) {
	if (node == nullptr) return 0;
	else return node->height;
}


template <typename T> 
int AVLTree<T>::max(int x, int y) {
	return x > y ? x : y;
}

template <typename T>
int AVLTree<T>::getBalance(Node<T>* node) {
	if (node == nullptr);
	int leftHeight = node->left != nullptr ? node->left->height : 0;
	int rightHeight = node->right != nullptr ? node->right->height : 0;
	return leftHeight - rightHeight;
}

 template <typename T>
 Node<T>* AVLTree<T>::firstOfSubtree(Node<T>* node) {
	 if (node->left != nullptr) firstOfSubtree(node->left);
	 else return node;
 }

 template <typename T>
 Node<T>* AVLTree<T>::successor(Node<T>* node) {
	 if (node->right == nullptr) return nullptr;
	 else if (node->right != nullptr) return firstOfSubtree(node->right);
	 
 }


 // node = up
 template <typename T>
 Node<T>* AVLTree<T>::leftRotate(Node<T>* node) {
	 Node<T>* down = node->right;
	 Node<T>* child = down->left;

	 down->left = node;
	 node->right = child;

	 int leftHeight = node->left != nullptr ? node->left->height : 0;
	 int rightHeight = node->right != nullptr ? node->right->height : 0;
	 int downLeftHeight = down->left != nullptr ? down->left->height : 0;
	 int downRightHeight = down->right != nullptr ? down->right->height : 0;
	 node->height = 1 + max(leftHeight, rightHeight);
	 down->height = 1 + max(downLeftHeight, downRightHeight);
	 return down;
 }

 template <typename T>
 Node<T>* AVLTree<T>::rightRotate(Node<T>* node) {
	 Node<T>* down = node->left;
	 Node<T>* child = down->right;

	 down->right = node;
	 node->left = child;

	 int leftHeight = node->left != nullptr ? node->left->height : 0;
	 int rightHeight = node->right != nullptr ? node->right->height : 0;
	 int downLeftHeight = down->left != nullptr ? down->left->height : 0;
	 int downRightHeight = down->right != nullptr ? down->right->height : 0;
	 node->height = 1 + max(leftHeight, rightHeight);
	 down->height = 1 + max(downLeftHeight, downRightHeight);
	 return down;
 }


 template <typename T>
 void AVLTree<T>::insert(T data) {
	 this->root = innerInsert(this->root, data);

	 Node<T>* node = this->root;

	 /* 2. Update hegiht of the sub-tree */
	 int leftHeight = node->left != nullptr ? node->left->height : 0;
	 int rightHeight = node->right != nullptr ? node->right->height : 0;
	 node->height = max(leftHeight, rightHeight);

	 /* 3. Check the balance */
	 int balance = getBalance(node);
	 // LL
	 if (balance > 1 && node->left->data > data) {
		this->root = rightRotate(node);
	 }
	 // RR
	 if (balance < -1 && node->right->data < data) {
		 this->root = leftRotate(node);
	 }
	 // LR
	 if (balance > 1 && node->left->data < data) {
		 node->left = leftRotate(node->left);
		 this->root = rightRotate(node);
	 }
	 // RL
	 if (balance < -1 && node->right->data > data) {
		 node->right = rightRotate(node->right);
		 this->root = leftRotate(node);
	 }
 }


 template <typename T>
 Node<T>* AVLTree<T>::innerInsert(Node<T>* node, T data) {
	 /* 1. Perfrom implementation */
	 if (node == nullptr) return new Node<T>(data);

	 if (data < node->data) {
		 node->left = innerInsert(node->left, data);
	 }
	 else if (data > node->data) {
		 node->right = innerInsert(node->right, data);
	 }
	 else
		 return node;

	 /* 2. Update hegiht of the sub-tree */
	 int leftHeight = node->left != nullptr ? node->left->height : 0;
	 int rightHeight = node->right != nullptr ? node->right->height : 0;
	 node->height = 1 + max(leftHeight, rightHeight);

	 /* 3. Check the balance */
	 int balance = getBalance(node);
	 // LL
	 if (balance > 1 && node->left->data > data) {
		 return rightRotate(node);
	 }
	 // RR
	 if (balance < -1 && node->right->data < data) {
		 return leftRotate(node);
	 }
	 // LR
	 if (balance > 1 && node->left->data < data) {
		 node->left = leftRotate(node->left);
		 return rightRotate(node);
	 }
	 // RL
	 if (balance < -1 && node->right->data > data) {
		 node->right = rightRotate(node->right);
		 return leftRotate(node);
	 }
	 return node;
 }

 template <typename T>
 void AVLTree<T>::deleteNode(T data) {
	 innerDeleteNode(this->root, data);

	 Node<T>* node = this->root;

	 /* 2. Update hegiht of the sub-tree */
	 int leftHeight = node->left != nullptr ? node->left->height : 0;
	 int rightHeight = node->right != nullptr ? node->right->height : 0;
	 node->height = max(leftHeight, rightHeight);

	 /* 3. Maintain the balance */
	 int balance = getBalance(node);

	 // LL
	 if (balance > 1 && node->left->data > data) {
		 this->root = rightRotate(node);
	 }
	 // RR
	 else if (balance < -1 && node->right->data < data) {
		 this->root = leftRotate(node);
	 }
	 // LR
	 else if (balance > 1 && node->left->data < data) {
		 node->left = leftRotate(node->left);
		 this->root = rightRotate(node);
	 }
	 // RL
	 else if (balance < -1 && node->right->data > data) {
		 node->right = rightRotate(node->right);
		 this->root = leftRotate(node);
	 }
 }

 template <typename T>
 Node<T>* AVLTree<T>::innerDeleteNode(Node<T>* node, T data) {
	 /* 1. Perform delete */
	 if (node == nullptr) return node;

	 if (node->data > data) {
		 node->left = innerDeleteNode(node->left, data);
	 }
	 else if (node->data < data) {
		 node->right = innerDeleteNode(node->right, data);
	 }
	 else {
		 /* Assume node has 1 or 0 child */
		 if (node->left == nullptr || node->right == nullptr) {
			 Node<T>* temp = node->left != nullptr ? node->left : node->right;
			 node = temp;
		 }
		 /* Assume node has 2 children */
		 else {
			 node->data = successor(node)->data;
			 node->right = innerDeleteNode(node->right, successor(node)->data);
		 }
	 }
	 /* 2. Update the height of root */
	 if (node == nullptr) return node;
	 int leftHeight = node->left != nullptr ? node->left->height : 0;
	 int rightHeight = node->right != nullptr ? node->right->height : 0;
	 node->height = 1 + max(leftHeight, rightHeight);

	 /* 3. Maintain the balance */
	 int balance = getBalance(node);

	 // LL
	 if (balance > 1 && node->left->data > data) {
		 return rightRotate(node);
	 }
	 // RR
	 if (balance < -1 && node->right->data < data) {
		 return leftRotate(node);
	 }
	 // LR
	 if (balance > 1 && node->left->data < data) {
		 node->left = leftRotate(node->left);
		 return rightRotate(node);
	 }
	 // RL
	 if (balance < -1 && node->right->data > data) {
		 node->right = rightRotate(node->right);
		 return leftRotate(node);
	 }
	 return node;
 }


 template <typename T>
 AVLTree<T>::AVLTree() {
	 this->root = nullptr;
 }

 template <typename T>
 void AVLTree<T>::ordered()
 {
	 innerOrdered(this->root);
 }

 template <typename T>
 void AVLTree<T>::innerOrdered(Node<T>* root)
 {
	 if (root != nullptr)
	 {
		 innerOrdered(root->left);
		 cout << root->data << " ";
		 innerOrdered(root->right);
	 }
 }

 template <typename T>
 void AVLTree<T>::preOrdered()
 {
	 innerPreOrdered(this->root);
 }

 template <typename T>
 void AVLTree<T>::innerPreOrdered(Node<T>* root)
 {
	 if (root != nullptr)
	 {
		 innerOrdered(root->right);
		 cout << root->data << " ";
		 innerOrdered(root->left);
	 }
 }
