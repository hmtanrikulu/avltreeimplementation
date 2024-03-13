#include <iostream>
#include <string>
#include <algorithm>
using namespace std;


struct Node {
	int data;
	Node* left;
	Node* right;
	int height;

	Node(int data) : data(data), left(nullptr), right(nullptr), height(1) {}
};



	int getHeight(Node* node) {
		if (node == nullptr) return 0;
		return node->height;
	}

	int max(int x, int y) {
		return (x > y) ? x : y;
	}

	int getBlanceFactor(Node* node) {
		if (node == nullptr) return 0;
		return getHeight(node->left) - getHeight(node->right);
	}

	Node* rightRotate(Node* up) {
		Node* z = up;
		Node* y = z->left;
		Node* T3 = y->right;

		// Perform Rotation
		y->right = z;
		z->left = T3;

		// Update heights
		y->height = max(getHeight(y->left), getHeight (y->right));
		z->height = max(getHeight(z->left), getHeight(z->right));

		// Return new tree root
		return y;
	}

	Node* leftRotate(Node* up) {
		Node* y = up;
		Node* z = y->right;
		Node* T3 = z->left;

		// Perform rotation
		z->left = y;
		y->right = T3;

		// Update heights

		y->height = max(getHeight(y->left), getHeight(y->right));
		z->height = max(getHeight(z->left), getHeight(z->right));

		// Return new root;

		return z;
	}

	Node* insert(Node* root, int data) {
		if (root == nullptr) return new Node(data);

		if (data < root->data) {
			root->left = insert(root->left, data);
		}

		else if (data > root->data) {
			root->right = insert(root->right, data);
		}

		else return root;

		// Update height 

		root->height = 1 + max(getHeight(root->right), getHeight(root->left));

		// Get balance factor

		int balance = getBlanceFactor(root);

		// LL
		if (balance > 1 && data < root->left->data) {
			return rightRotate(root);
		}
		// RR
		if (balance < 1 && data > root->right->data) {
			return leftRotate(root);
		}
		// LR
		if (balance > 1 && data > root->left->data) {
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
		// RL
		if (balance < 1 && data < root->right->data) {
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
		return root;
	}

	void preOrder(Node* root)
	{
		if (root != NULL)
		{
			cout << root->data << " ";
			preOrder(root->left);
			preOrder(root->right);
		}
	}

	Node* deleteNode(Node* node, int data) {

	}
	


	// Driver Code 
	int main()
	{
		Node* root = NULL;

		/* Constructing tree given in
		the above figure */
		root = insert(root, 10);
		root = insert(root, 20);
		root = insert(root, 30);
		root = insert(root, 40);
		root = insert(root, 50);
		root = insert(root, 25);

		/* The constructed AVL Tree would be
					30
				/ \
				20 40
				/ \ \
			10 25 50
		*/
		cout << "Preorder traversal of the "
			"constructed AVL tree is \n";
		preOrder(root);

		return 0;
	}