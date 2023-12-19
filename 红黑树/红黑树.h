#pragma once
#include <iostream>
#include <queue>
#include <algorithm>
#include<Windows.h>
using namespace std;

#define scta(a) SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE),a);

enum color
{
	Black = true,
	Red = false
};

class RBNode
{
public:
	RBNode(int key, int value, color color, RBNode* left, RBNode* right, RBNode* parent)
	{
		this->key = key;
		this->value = value;
		this->parent = parent;
		this->left = left;
		this->right = right;
		this->color = color;
	}
	void changeColor()
	{
		if (color)
			color = Red;
		else
			color = Black;
	}
public:
	RBNode* parent;
	RBNode* left;
	RBNode* right;
	color color;
	int key;
	int value;
};

class RBTree
{
public:
	RBTree()
	{
		root = NULL;
	}

	RBNode* getRoot() const
	{
		return root;
	}
	void push(int k, int value);
	void push(int k);
	static RBNode* createRBNode(int key, int value);
	static RBNode* createRBNode(int key, int value, color color);
	static RBNode* createRBNode(int key, int value, RBNode* left, RBNode* right);
	static RBNode* createRBNode(int key, int value, RBNode* parent);
	static RBNode* createRBNode(int key, int value, RBNode* left, RBNode* right, RBNode* parent);
	void PrintRBNode(RBNode* node);
	RBNode* predecessor(RBNode* node);
	RBNode* sucessor(RBNode* node);
	int remove(int key);


	//以下节点都是为了防止为空
	//原版规定getColor默认返回Black,主要防止节点为空
	static color colorOf(RBNode* node)
	{
		return node == NULL ? Black : node->color;
	}
	RBNode* parentOf(RBNode* node)
	{
		return node == NULL ? NULL : node->parent;
	}
	RBNode* leftOf(RBNode* node)
	{
		return node == NULL ? NULL : node->left;
	}
	RBNode* rightOf(RBNode* node)
	{
		return node == NULL ? NULL : node->right;
	}
	void setColor(RBNode* node, color color)
	{
		if (node != NULL)
		{
			node->color = color;
		}
	}
private:
	void leftRotate(RBNode* p);
	void rightRotate(RBNode* p);
	bool compare(int k1, int k2);
	void fixAfterPut(RBNode* node);
	void putNodeQueue(RBNode* node);
	int getDeepth(RBNode* node);
	queue<RBNode*>* PrintRBNode(queue<RBNode*>* q, int length);
	RBNode* getNode(int key);
	void deleteNode(RBNode* node);
	void fixAfterRemove(RBNode* node);
private:
	RBNode* root;

	//用于遍历的队列
	queue<RBNode*> qRBNode;
};
