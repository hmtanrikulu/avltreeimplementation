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
};

int getHeight(Node* node) {
	if (node == nullptr) return 0;
	return node->height;
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int getBalance(Node* node) {
	if (node == nullptr) {
		return 0;
	}
	return getHeight(node->left) - getHeight(node->right);
}

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

	Node* rightRotate(Node* up) {
		Node* down = up->left;
		Node* rightChildOfDown = down->right; // read access violation ?

		down->right = up;
		up->left = rightChildOfDown;

		up->height = max(getHeight(up->left), getHeight(up->right));
		down->height = max(getHeight(down->left), getHeight(down->right));

		return down;
	}

	Node* leftRotate(Node* up) {
		Node* down = up->right;
		Node* childOfDown = down->left;

		down->left = up;
		up->right = childOfDown;


		up->height = max(getHeight(down->left), getHeight(up->right));
		down->height = max(getHeight(down->left), getHeight(up->right));

		return down;
	}

	void inorder(Node* root)
	{
		if (root != NULL) {
			inorder(root->left);
			cout << (root->data);
			inorder(root->right);
		}
	}





	/* Argument node = root 
		
	*/


	Node* insert(Node* node, int data) {

		/* base case*/
		if (node == nullptr) return new Node(data);

		if (data < node->data) {
			node->left = insert(node->left, data);
		}
		else if (data > node->data) {
			node->right = insert(node->right, data);
		}
		else {
			return node;
		}

		/* 2. Update the height*/
		node->height = 1 + max(getHeight(node->left), getHeight(node->right));

		/* 3. Balance factor to check imbalance*/
		int balance = getBalance(node);


		/* Return new root everytime you make a change so that 
			other ->left ->right pointer can update themselves;*/

		// LL
		if (balance > 1 && data < node->left->data) {
			return rightRotate(node);
		}
		// RR
		if (balance < -1 && data > node->right->data) {
			return leftRotate(node);
		}
		//LR
		if (balance > 1 && data > node->left->data) {
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}
		// RL
		if (balance < -1 && data < node->right->data) {
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}
		return node;
	}

/* We need this Node* cause it represents the subtree Root
	that way we recursivly search below*/

	/*Delete the item in node <X> from <X>’s subtree
		– If <X> is a leaf, detach from parent and return
		– Otherwise, <X> has a child
		∗ If <X> has a left child, swap items with the predecessor of <X> and recurse
		∗ Otherwise <X> has a right child, swap items with the successor of <X> and recurse*/

	Node* deleteNode(Node* root, int key) {
		// Base case
		if (root == nullptr) return root;

		if (key > root->data) {
			root->right = deleteNode(root->right, key);
		}
		else if (key < root->data) {
			root->left = deleteNode(root->left, key);
		}

		// Assume we found the key
		else {
			// Assume there are 1 or 0 child
			if (root->left == nullptr) {
				Node* tmp = root->right; // check for access violation error if necessary !
				delete root;
				return tmp;
			}

			else if (root->right == nullptr) {
				Node* tmp = root->left;
				delete root;
				return tmp;
			}

			// Assume there are 2 branches
			else {
				Node* temp = successor(root);
				root->data = temp->data;
				deleteNode(root->right, temp->data);

			}
		}

		/* 2. Update the height*/
		root->height = 1 + max(root->left->height, root->right->height);

		/* 3. Balance factor to check imbalance*/
		int balance = getBalance(root);

		/* 4. Now handle the rotations if necessary*/

		// LL case
		if (balance > 1 && key < root->left->data) {
			return rightRotate(root);
		}

		// RR case
		if (balance < -1 && key > root->right->data) {
			return leftRotate(root);
		}

		// LR case
		if (balance > 1 && key > root->left->data) {
			root->left =leftRotate(root->left);
			return rightRotate(root);
		}

		// RL case
		if (balance < -1 && key < root->right->data) {
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
		return root;
	}

	Node* deleteNode(Node* node, int key) {

		Node* tmp = node;
		Node* prev = tmp;

		while (tmp->data != key) {
			if (key < tmp->data) {
				prev = tmp;
				tmp = tmp->left;
			}
			if (key > tmp->data) {
				prev = tmp;
				tmp = tmp->right;
			}

			// Assume you found the node
			else if (tmp->data == key) {

				// Assume it has 1 child or none

				if (tmp->left == nullptr || tmp->right == nullptr) {
					if (tmp->left) {

						Node* tempChild = tmp->left;
						tmp->data > prev->data ? prev->right = tempChild : prev->left = tempChild;
						delete tmp;
						break;
					}
					else {

						Node* tempChild = tmp->right;
						tmp->data > prev->data ? prev->right = tempChild : prev->left = tempChild;
						delete tmp;
						break;
					}
				}
				// Assume it has 2 branches

				if (tmp->right != nullptr && tmp->left != nullptr) {
					// swap with successor

					Node* tmp2 = successor(tmp);
					tmp->data = tmp2->data;


				}




			}
			
			// Assume you couldn't find

			else {

			}

		}



	}


	
	// & referans araştırmanı yap