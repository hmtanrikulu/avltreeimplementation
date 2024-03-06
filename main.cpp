#include <iostream>
#include <string>
#include <vector>
using namespace std;


struct Node {
	int data;
	int height;
	Node* parent;
	Node* left;
	Node* right;

	Node(int data) {
		this->data = data;
		this->height = 1;
		this->parent = nullptr;
		this->left = nullptr;
		this->right = nullptr;
	}

	int getHeight(Node* node) {
		if (node == nullptr) return 0;
		return this->height;
	}

	int getBalance(Node* node) {
		if (node == nullptr) {
			return 0;
		}
		return getHeight(node->left) - getHeight(node->right);
	}

};








struct AVL {
	Node* root;
	int size;

	Node* subtreeFirst(Node* node) {
		Node* tmp = node;
			do tmp = tmp->left;
			while (tmp->left != nullptr);
			return tmp;
	}

	Node* successor(Node* node) {
		if (node->right == nullptr) {
			return nullptr;
		}

		if (node->right != nullptr) {
			return subtreeFirst(node->right);
		}

		Node* parent = node->parent;
		while (node->parent != nullptr && node == parent->right) {
			node = parent;
			parent = parent->parent;
		}
		return parent;
	}

	void insert(Node* root, int data) {
		Node* newElement = new Node(data);
		if (!root) {
			root = newElement;
			return;
		}
		Node* tmp = root;
		Node* prev = nullptr;

		while (tmp) { // tmp != nullptr ( sawp with this just in case!)
			if (tmp->data > data) {
				prev = tmp;
				tmp = tmp->left;
			}
			else if (tmp->data < data) {
				prev = tmp;
				tmp = tmp->right;
			}
		}
		if (prev->data < data) {
			prev->right = newElement;
		}
		else
			prev->left = newElement;
	}

	void inorder(Node* root)
	{
		if (root != NULL) {
			inorder(root->left);
			cout << (root->data);
			inorder(root->right);
		}
	}

/* We need this Node* cause it represents the subtree Root
	that way we recursivly search below*/

/* We return Node* in order ____*/
	Node* deleteNode (Node* root, int key) {
		// Base case
		if (root == nullptr) return;

		if (root->data > key) {
			root->left = deleteNode(root->left, key);
			return root;
		}


	}


};




























int main() {



	return 0;
}