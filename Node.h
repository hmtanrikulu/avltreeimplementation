#include <iostream>
#include <string>
#ifndef NODE
#define NODE

using namespace std;

template <typename T>
struct Node {
	T data;
	Node* right;
	Node* left;
	int height;
	Node(T x) {
		this->data = x;
		this->height = 1;
		this->left = nullptr;
		this->right = nullptr;
	}
};

#endif
