#pragma once
#include "Header.h"

class AVL
{
	struct nodeAVL {
		int key;
		struct nodeAVL* left, * right, * parent = nullptr;
		int height;

		nodeAVL(int key, nodeAVL* left = nullptr, nodeAVL* right = nullptr, int height = 1)
		{
			this->key = key;
			this->left = left;
			this->right = right;
			this->height = height;
		}
	};

	nodeAVL* root;

	int height(nodeAVL* x)
	{
		return x ? x->height : 0;
	}

	int bfactor(nodeAVL* x)
	{
		return height(x->right) - height(x->left);
	}

	void fixHeight(nodeAVL* x)
	{
		unsigned char hl = height(x->left);
		unsigned char hr = height(x->right);
		x->height = (hl > hr ? hl : hr) + 1;
	}

	nodeAVL* rotateRight(nodeAVL* x)
	{
		nodeAVL* y = x->left;
		x->left = y->right;
		y->right = x;
		fixHeight(x);
		fixHeight(y);
		return y;
	}

	nodeAVL* rotateLeft(nodeAVL* y)
	{
		nodeAVL* x = y->right;
		y->right = x->left;
		x->left = y;
		fixHeight(y);
		fixHeight(x);
		return x;
	}

	nodeAVL* balance(nodeAVL* x)
	{
		fixHeight(x);
		if (bfactor(x) == 2)
		{
			if (bfactor(x->right) < 0)
				x->right = rotateRight(x->right);
			return rotateLeft(x);
		}
		if (bfactor(x) == -2)
		{
			if (bfactor(x->left) > 0)
				x->left = rotateLeft(x->left);
			return rotateRight(x);
		}
		return x;
	}

	void addNewElement(nodeAVL*& Node, int key)
	{
		if (Node == nullptr)
		{
			Node = new nodeAVL(key);
		}
		else
		{
			if (key < Node->key)
			{
				addNewElement(Node->left, key);
			}
			else if (key > Node->key)
			{
				addNewElement(Node->right, key);
			}
	
			Node = balance(Node);
		}
	}

	nodeAVL* removeMin(nodeAVL* x)
	{
		if (x->left == 0)
			return x->right;
		x->left = removeMin(x->left);
		return balance(x);
	}

	nodeAVL* removeElement(nodeAVL* x, int key)
	{
		if (!x) return 0;
		if (key < x->key)
			x->left = removeElement(x->left, key);
		else if (key > x->key)
			x->right = removeElement(x->right, key);
		else
		{
			nodeAVL* l = x->left;
			nodeAVL* r = x->right;
			delete x;
			if (!r) return l;
			nodeAVL* min = returnMinElement(r);
			min->right = removeMin(r);
			min->left = l;
			return balance(min);
		}
		return balance(x);
	}

	int findDepth(nodeAVL* root)
	{
		int r = 0;
		if (root)
		{
			int leftDepth = findDepth(root->left);
			int rightDepth = findDepth(root->right);
			r = max(leftDepth + 1, rightDepth + 1);
		}
		return r;
	}

	nodeAVL* returnMinElement(nodeAVL*& node)
	{
		if (node->left != nullptr)
		{
			returnMinElement(node->left);
		}
		else
		{
			return node;
		}
	}

	void del(nodeAVL* curr)
	{
		if (curr)
		{
			del(curr->left);
			del(curr->right);
			delete curr;
		}
	}


public:

	AVL() {
		root = nullptr;
	}

	~AVL() {
		clear();
	}

	void clear()
	{
		del(this->root);
		root = nullptr;
	}

	void findDepthCout()
	{
		cout << findDepth(root) << endl;
	}

    void insert(int key) {
		addNewElement(this->root, key);
    }

    void remove(int key) {
		if (key == this->root->key)
		{
			this->root = removeElement(root, key);
		}
		else
		{
			removeElement(root, key);
		}
    }
};
