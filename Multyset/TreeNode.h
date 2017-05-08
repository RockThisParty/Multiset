#pragma once

// Узел дерева
// файл TreeNode.h

#pragma once
#include <cstddef> // ќпределение константы NULL

template <class TreeItemType>
class TreeNode
{
	enum { BLACK = 0, RED = 1 };
private:
	TreeItemType item;
	TreeNode<TreeItemType> * left, *right, *parent;
	bool color, isEmpty;

	TreeNode() : left(NULL), right(NULL), parent(NULL), color(BLACK), isEmpty(1) {};

	TreeNode(const TreeItemType& nodeItem, TreeNode<TreeItemType> * leftPtr = NULL, TreeNode<TreeItemType> * rightPtr = NULL, TreeNode<TreeItemType> * parentPtr = NULL) :
		item(nodeItem), isEmpty(1), color(BLACK), left(leftPtr), right(rightPtr), parent(parentPtr) {};
	template <class TreeItemType> friend class BinaryTree;
};