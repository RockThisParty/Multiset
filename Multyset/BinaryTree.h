#pragma once

#include "TreeNode.h"	// Содержит определения классов TreeNode и TreeltemType
#include <cstddef>		// Определение константы NULL
#include <exception>
#include <string>
#include <queue>		// queue

class TreeException : public std::exception
{
public:
	TreeException(const std::string & message = "") : std::exception(message.c_str()) { }
};

template <class TreeItemType>
class BinaryTree
{
public:
	// Конструкторы и деструктор:
	BinaryTree();
	BinaryTree(const TreeItemType& rootltem);
	BinaryTree(const TreeItemType& rootltem, BinaryTree<TreeItemType>& leftTree, BinaryTree<TreeItemType>& rightTree);
	BinaryTree(const BinaryTree<TreeItemType>& tree);
	~BinaryTree();

	// Операции над деревом:
	TreeItemType getRootData() const;
	bool isEmpty() const;
	BinaryTree<TreeItemType> getLeftSubtree() const;
	BinaryTree<TreeItemType> getRightSubtree() const;
	void preorderTraverse(void(*visit)(TreeItemType &anitem));
	void inorderTraverse(void(*visit)(TreeItemType &anitem));
	void postorderTraverse(void(*visit)(TreeItemType &anitem));
	BinaryTree<TreeItemType>& operator=(const BinaryTree<TreeItemType>& rhs);

	unsigned int getDepth() const;
	unsigned int getDepthOfMin() const;
	unsigned int getDepthOfMax() const;
	void printLevels() const;
	void print() const;
	template <class TreeItemType> friend std::ostream& operator<<(std::ostream& out, const BinaryTree<TreeItemType> &tree);
	void attach(const TreeItemType &newItem);
	bool isExist(TreeItemType &anitem) const;
	void deleteItem(TreeItemType &anitem);

protected:
	void setRootData(const TreeItemType& newltem);
	void attachLeft(const TreeItemType& newltem);
	void attachRight(const TreeItemType& newltem);
	void attachLeftSubtree(BinaryTree<TreeItemType>& leftTree);
	void attachRightSubtree(BinaryTree<TreeItemType>& rightTree);
	void detachLeftSubtree(BinaryTree<TreeItemType>& leftTree);
	void detachRightSubtree(BinaryTree<TreeItemType>& rightTree);
	BinaryTree(TreeNode<TreeItemType> *nodePtr);
	void copyTree(TreeNode<TreeItemType> *treePtr, TreeNode<TreeItemType> *& newTreePtr) const;
	void destroyTree(TreeNode<TreeItemType> *& treePtr);
	TreeNode<TreeItemType>* rootPtr() const;
	void setRootPtr(TreeNode<TreeItemType> *newRoot);
	void getChildPtrs(TreeNode<TreeItemType> *nodePtr, TreeNode<TreeItemType> *& leftChildPtr, TreeNode<TreeItemType> *& rightChildPtr) const;
	void setChildPtrs(TreeNode<TreeItemType> *nodePtr, TreeNode<TreeItemType> *leftChildPtr, TreeNode<TreeItemType> *rightChildPtr);
	void preorder(TreeNode<TreeItemType> *treePtr, void(*visit)(TreeItemType &anitem));
	void inorder(TreeNode<TreeItemType> *treePtr, void(*visit)(TreeItemType &anitem));
	void postorder(TreeNode<TreeItemType> *treePtr, void(*visit)(TreeItemType &anitem));

	void attach_helper(const TreeItemType &newItem, TreeNode<TreeItemType> *&nodePtr);
	unsigned int getDepth_helper(TreeNode<TreeItemType> *nodePtr) const;
	unsigned int getDepthOfMin_helper(TreeNode<TreeItemType> *nodePtr) const;
	unsigned int getDepthOfMax_helper(TreeNode<TreeItemType> *nodePtr) const;
	void printLevels_helper(unsigned int level, std::queue<TreeNode<TreeItemType>*> &levelHubs) const;
	void print_helper(TreeNode<TreeItemType> *nodePtr, unsigned int level) const;
	bool isExist_helper(TreeNode<TreeItemType> *nodePtr, TreeItemType &anitem) const;
	TreeNode<TreeItemType>* deleteItem_helper(TreeNode<TreeItemType> *&nodePtr);

	TreeNode<TreeItemType>* grandparent(TreeNode<TreeItemType> *node);
	TreeNode<TreeItemType>* uncle(TreeNode<TreeItemType> *node);

	void rotate_left(TreeNode<TreeItemType> *node);
	void rotate_right(TreeNode<TreeItemType> *node);
	TreeNode<TreeItemType>* sibling(TreeNode<TreeItemType>* node);

	void delete_case1(TreeNode<TreeItemType> *node);
	void delete_case2(TreeNode<TreeItemType> *node);
	void delete_case3(TreeNode<TreeItemType> *node);
	void delete_case4(TreeNode<TreeItemType> *node);
	void delete_case5(TreeNode<TreeItemType> *node);
	void delete_case6(TreeNode<TreeItemType> *node);

	void remove(TreeNode<TreeItemType> *node);


	void insert_case1(TreeNode<TreeItemType> *node);
	void insert_case2(TreeNode<TreeItemType> *node);
	void insert_case3(TreeNode<TreeItemType> *node);
	void insert_case4(TreeNode<TreeItemType> *node);
	void insert_case5(TreeNode<TreeItemType> *node);

	void replace(TreeNode<TreeItemType> *node, TreeNode<TreeItemType>* child);

private:
	TreeNode<TreeItemType> *root;
};

/// !!! REALIZATION (MUST BE IN .CPP) !!!

#include <algorithm>	// std::max
#include <iostream>		// std::cout, std::cin
#include <iomanip>		// std::setw, std::setf, std::right

template<class TreeItemType>
TreeNode<TreeItemType>* BinaryTree<TreeItemType>::grandparent(TreeNode<TreeItemType> *node)
{
	if ((node != NULL) && (node->parent != NULL))
		return node->parent->parent;
	else
		return NULL;
}

template <class TreeItemType>
TreeNode<TreeItemType>* BinaryTree<TreeItemType>::uncle(TreeNode<TreeItemType> *node)
{
	TreeNode<TreeItemType> *g = grandparent(node);
	if (g == NULL)
		return NULL;
	if (node->parent == g->left)
		return g->right;
	else
		return g->left;
}

template<class TreeItemType>
void BinaryTree<TreeItemType>::rotate_left(TreeNode<TreeItemType> *node)
{
	TreeNode<TreeItemType> *pivot = node->right;
	pivot->parent = node->parent;
	if (node->parent != NULL) {
		if (node->parent->left == node)
			node->parent->left = pivot;
		else
			node->parent->right = pivot;
	}
	else root = pivot;

	node->right = pivot->left;
	if (pivot->left != NULL)
		pivot->left->parent = node;

	node->parent = pivot;
	pivot->left = node;
}


template<class TreeItemType>
void BinaryTree<TreeItemType>::replace(TreeNode<TreeItemType>* node, TreeNode<TreeItemType>* child)
{
	if (node->parent->left == node)
	{
		node->parent->left = child;
	}
	else
	{
		node->parent->right = child;
	}
	child->parent = node->parent;
	node = child;
}

template<class TreeItemType>
void BinaryTree<TreeItemType>::rotate_right(TreeNode<TreeItemType> *node)
{
	TreeNode<TreeItemType> *pivot = node->left;
	pivot->parent = node->parent;
	if (node->parent != NULL) {
		if (node->parent->left == node)
			node->parent->left = pivot;
		else
			node->parent->right = pivot;
	}
	else root = pivot;

	node->left = pivot->right;
	if (pivot->right != NULL)
		pivot->right->parent = node;

	node->parent = pivot;
	pivot->right = node;
}

template<class TreeItemType>
void BinaryTree<TreeItemType>::insert_case5(TreeNode<TreeItemType> *node)
{
	TreeNode<TreeItemType> *g = grandparent(node);
	node->parent->color = TreeNode<TreeItemType>::BLACK;
	g->color = TreeNode<TreeItemType>::RED;
	if ((node == node->parent->left) && (node->parent == g->left))
	{
		rotate_right(g);
	}
	else
	{
		rotate_left(g);
	}
}

template<class TreeItemType>
void BinaryTree<TreeItemType>::insert_case4(TreeNode<TreeItemType> *node)
{
	TreeNode<TreeItemType> *g = grandparent(node);
	if ((node == node->parent->right) && (node->parent == g->left))
	{
		rotate_left(node->parent);
		node = node->left;
	}
	else
		if ((node == node->parent->left) && (node->parent == g->right))
		{
			rotate_right(node->parent);
			node = node->right;
		}
	insert_case5(node);
}

template<class TreeItemType>
void BinaryTree<TreeItemType>::insert_case3(TreeNode<TreeItemType> *node)
{
	TreeNode<TreeItemType> *u = uncle(node);
	if ((u != NULL) && (u->color == TreeNode<TreeItemType>::RED) && (node->parent->color == TreeNode<TreeItemType>::RED))
	{
		node->parent->color = TreeNode<TreeItemType>::BLACK;
		u->color = TreeNode<TreeItemType>::BLACK;
		TreeNode<TreeItemType> *g = grandparent(node);
		g->color = TreeNode<TreeItemType>::RED;
		insert_case1(g);
	}
	else
	{
		insert_case4(node);
	}
}

template<class TreeItemType>
void BinaryTree<TreeItemType>::insert_case2(TreeNode<TreeItemType> *node)
{
	if (node->parent->color == TreeNode<TreeItemType>::BLACK)
		return;
	else
		insert_case3(node);
}

template<class TreeItemType>
void BinaryTree<TreeItemType>::insert_case1(TreeNode<TreeItemType> *node)
{
	if (node->parent == NULL)
		node->color = TreeNode<TreeItemType>::BLACK;
	else
		insert_case2(node);
}

template<class TreeItemType>
TreeNode<TreeItemType>*	BinaryTree<TreeItemType>::sibling(TreeNode<TreeItemType> *n)
{
	if (n == n->parent->left)
		return n->parent->right;
	else
		return n->parent->left;
}

template<class TreeItemType>
void BinaryTree<TreeItemType>::remove(TreeNode<TreeItemType>* node)
{
	//TreeNode<TreeItemType> *child = is_empty(node->rightChildPtr) ? node->leftChildPtr : node->rightChildPtr; 

	TreeNode<TreeItemType> *child = (node->right->isEmpty) ? node->left : node->right;

	replace(node, child);
	if (node->color == TreeNode <TreeItemType>::BLACK)
	{
		if (child->color == TreeNode <TreeItemType>::RED)
		{
			child->color = TreeNode <TreeItemType>::BLACK;
		}
		else
		{
			delete_case1(child);
		}
	}
	delete node;
}

template<class TreeItemType>
void BinaryTree<TreeItemType>::delete_case1(TreeNode<TreeItemType>* n)
{
	if (n->parent != NULL)
		delete_case2(n);
}

template<class TreeItemType>
void BinaryTree<TreeItemType>::delete_case2(TreeNode<TreeItemType>* n)
{
	TreeNode<TreeItemType> *s = sibling(n);

	if (s->color == TreeNode<TreeItemType>::RED)
	{
		n->parent->color = TreeNode<TreeItemType>::RED;
		s->color = 0;
		if (n == n->parent->left)
			rotate_left(n->parent);
		else
			rotate_right(n->parent);
	}
	delete_case3(n);
}

template<class TreeItemType>
void BinaryTree<TreeItemType>::delete_case3(TreeNode<TreeItemType>* n)
{
	TreeNode<TreeItemType> *s = sibling(n);

	if ((n->parent->color == TreeNode<TreeItemType>::BLACK) &&
		(s->color == TreeNode<TreeItemType>::BLACK) &&
		(s->left->color == TreeNode<TreeItemType>::BLACK) &&
		(s->right->color == TreeNode<TreeItemType>::BLACK))
	{
		s->color = TreeNode<TreeItemType>::RED;
		delete_case1(n->parent);
	}
	else
		delete_case4(n);
}

template<class TreeItemType>
void BinaryTree<TreeItemType>::delete_case4(TreeNode<TreeItemType>* n)
{
	TreeNode<TreeItemType> *s = sibling(n);

	if ((n->parent->color == TreeNode<TreeItemType>::RED) &&
		(s->color == TreeNode<TreeItemType>::BLACK) &&
		(s->left->color == TreeNode<TreeItemType>::BLACK) &&
		(s->right->color == TreeNode<TreeItemType>::BLACK))
	{
		s->color = TreeNode<TreeItemType>::RED;
		n->parent->color = TreeNode<TreeItemType>::BLACK;
	}
	else
		delete_case5(n);
}

template<class TreeItemType>
void BinaryTree<TreeItemType>::delete_case5(TreeNode<TreeItemType>* n)
{
	TreeNode<TreeItemType> *s = sibling(n);

	if (s->color == TreeNode<TreeItemType>::BLACK)
	{
		if ((n == n->parent->left) &&
			(s->right->color == TreeNode<TreeItemType>::BLACK) &&
			(s->left->color == TreeNode<TreeItemType>::RED))
		{
			s->color = TreeNode<TreeItemType>::RED;
			s->left->color = TreeNode<TreeItemType>::BLACK;
			rotate_right(s);
		}
		else
			if ((n == n->parent->right) &&
				(s->left->color == TreeNode<TreeItemType>::BLACK) &&
				(s->right->color == TreeNode<TreeItemType>::RED))
			{
				s->color = TreeNode<TreeItemType>::RED;
				s->right->color = TreeNode<TreeItemType>::BLACK;
				rotate_left(s);
			}
	}
	delete_case6(n);
}

template<class TreeItemType>
void BinaryTree<TreeItemType>::delete_case6(TreeNode<TreeItemType>* n)
{
	TreeNode<TreeItemType> *s = sibling(n);

	s->color = n->parent->color;
	n->parent->color = TreeNode<TreeItemType>::BLACK;

	if (n == n->parent->left)
	{
		s->right->color = TreeNode<TreeItemType>::BLACK;
		rotate_left(n->parent);
	}
	else
	{
		s->left->color = TreeNode<TreeItemType>::BLACK;
		rotate_right(n->parent);
	}
}

template<class TreeItemType>
void BinaryTree<TreeItemType>::deleteItem(TreeItemType &anitem)
{
	if (root->item == anitem)
	{
		if (root->left->isEmpty && root->right->isEmpty) //If the root is hasn't any children
		{
			delete root->left;
			delete root->right;
			root = new TreeNode<TreeItemType>;
			return;
		}

		if (root->left->isEmpty && !root->right->isEmpty)
		{
			root->item = root->right->item;
			root->right = new TreeNode<TreeItemType>;
			return;
		}

		if (!root->left->isEmpty && root->right->isEmpty)
		{
			root->item = root->left->item;
			root->left = new TreeNode<TreeItemType>;
			return;
		}

	}


	TreeNode<TreeItemType> *tmpPtr = root, *nodePtr = NULL;
	while (!tmpPtr->isEmpty && tmpPtr->item != anitem) // находим элемент
	{
		nodePtr = tmpPtr;
		if (anitem > tmpPtr->item)
			tmpPtr = tmpPtr->right;
		else
			tmpPtr = tmpPtr->left;
	}
	if (tmpPtr->isEmpty)
		throw TreeException("TreeException: элемент не найден");
	else // если он есть, то удаляем
	{
		if (!tmpPtr->left->isEmpty && !tmpPtr->right->isEmpty)
		{
			TreeNode<TreeItemType>* Max_in_left = tmpPtr->left;
			while (!Max_in_left->right->isEmpty)
				Max_in_left = Max_in_left->right;
			tmpPtr->item = Max_in_left->item;
			nodePtr = Max_in_left->parent;
			tmpPtr = Max_in_left;
		}
		remove(tmpPtr);
	}
}

template<class TreeItemType>
bool BinaryTree<TreeItemType>::isExist(TreeItemType &anitem) const
{
	return isExist_helper(root, anitem);
}

template<class TreeItemType>
bool BinaryTree<TreeItemType>::isExist_helper(TreeNode<TreeItemType> *nodePtr, TreeItemType &anitem) const
{
	if (nodePtr != NULL)
	{
		if (nodePtr->item == anitem)
			return 1;
		else if (anitem > nodePtr->item)
			return isExist_helper(nodePtr->right, anitem);
		else
			return isExist_helper(nodePtr->left, anitem);
	}
	else
		return 0;
}

template<class TreeItemType>
void BinaryTree<TreeItemType>::print() const
{
	print_helper(root, getDepth());
}

template<class TreeItemType>
std::ostream& operator<<(std::ostream& out, const BinaryTree<TreeItemType> &tree)
{
	tree.print_helper(tree.root, tree.getDepth());
	return out;
}

template<class TreeItemType>
void BinaryTree<TreeItemType>::print_helper(TreeNode<TreeItemType> *nodePtr, unsigned int level) const
{
	if (nodePtr)
	{
		print_helper(nodePtr->right, level - (unsigned int)1);
		std::cout << std::setw(level << (unsigned int)3) << std::setfill('-') << std::right << nodePtr->item << "(" << nodePtr->color << ")" << std::endl;
		print_helper(nodePtr->left, level - (unsigned int)1);
	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::printLevels() const
{
	std::queue<TreeNode<TreeItemType>*> levelHubs;
	levelHubs.push(root);
	printLevels_helper((unsigned int)0, levelHubs);
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::printLevels_helper(unsigned int level, std::queue<TreeNode<TreeItemType>*> &levelHubs) const
{
	std::cout << "LEVEL " << level << ':' << std::endl;
	std::queue<TreeNode<TreeItemType>*> nextLevelHubs;
	while (!levelHubs.empty())
	{
		std::cout << levelHubs.front()->item << std::endl;
		if (levelHubs.front()->left != NULL)
			nextLevelHubs.push(levelHubs.front()->left);
		if (levelHubs.front()->right != NULL)
			nextLevelHubs.push(levelHubs.front()->right);
		levelHubs.pop();
	}
	if (nextLevelHubs.empty())
		return;
	else
		printLevels_helper(level + (unsigned int)1, nextLevelHubs);
}

template <class TreeItemType>
unsigned int BinaryTree<TreeItemType>::getDepth() const
{
	if (root == NULL)
		throw TreeException("TreeException: дерево не построено");
	else
	{
		return getDepth_helper(root);
	}
}

template <class TreeItemType>
unsigned int BinaryTree<TreeItemType>::getDepth_helper(TreeNode<TreeItemType> *nodePtr) const
{
	if (nodePtr == NULL)
		return 0;
	else
	{
		return (unsigned int)1 + std::max(getDepth_helper(nodePtr->left), getDepth_helper(nodePtr->right));
	}
}

template <class TreeItemType>
unsigned int BinaryTree<TreeItemType>::getDepthOfMin() const
{
	if (root == NULL)
		throw TreeException("TreeException: дерево не построено");
	else
		return getDepthOfMin_helper(root);
}

template <class TreeItemType>
unsigned int BinaryTree<TreeItemType>::getDepthOfMin_helper(TreeNode<TreeItemType> *nodePtr) const
{
	if (nodePtr == NULL)
		return (unsigned int)0;
	else
		return (unsigned int)1 + getDepthOfMin_helper(nodePtr->left);
}

template <class TreeItemType>
unsigned int BinaryTree<TreeItemType>::getDepthOfMax() const
{
	if (root == NULL)
		throw TreeException("TreeException: дерево не построено");
	else
		return getDepthOfMax_helper(root);
}

template <class TreeItemType>
unsigned int BinaryTree<TreeItemType>::getDepthOfMax_helper(TreeNode<TreeItemType> *nodePtr) const
{
	if (root == NULL)
		return (unsigned int)0;
	else
		return (unsigned int)1 + getDepthOfMax_helper(nodePtr->right);
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::attach(const TreeItemType &newItem)
{
	attach_helper(newItem, root);
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::attach_helper(const TreeItemType &newItem, TreeNode<TreeItemType> *&nodePtr)
{
	if (nodePtr->isEmpty)
	{
		nodePtr->item = newItem;
		nodePtr->isEmpty = 0;
		nodePtr->color = TreeNode<TreeItemType>::RED;
		nodePtr->left = new TreeNode<TreeItemType>;
		nodePtr->right = new TreeNode<TreeItemType>;
		if (nodePtr->left == NULL || nodePtr->right == NULL)
			throw TreeException("TreeException: невозможно выделить память");
		nodePtr->left->parent = nodePtr;
		nodePtr->right->parent = nodePtr;
		insert_case1(nodePtr);
	}
	else
	{
		if (newItem > nodePtr->item)
			attach_helper(newItem, nodePtr->right);
		else
			attach_helper(newItem, nodePtr->left);
	}
}

template <class TreeItemType>
BinaryTree<TreeItemType>::BinaryTree()
{
	root = new TreeNode<TreeItemType>;
}

template <class TreeItemType>
BinaryTree<TreeItemType>::BinaryTree(const TreeItemType& rootitem)
{
	root = new TreeNode<TreeItemType>(rootitem);
}

template <class TreeItemType>
BinaryTree<TreeItemType>::BinaryTree(const TreeItemType& rootitem, BinaryTree<TreeItemType>& leftTree, BinaryTree<TreeItemType>& rightTree)
{
	root = new TreeNode<TreeItemType>(rootitem, NULL, NULL);
	attachLeftSubtree(leftTree);
	attachRightSubtree(rightTree);
}

template <class TreeItemType>
BinaryTree<TreeItemType>::BinaryTree(const BinaryTree<TreeItemType>& tree)
{
	copyTree(tree.root, root);
}

template <class TreeItemType>
BinaryTree<TreeItemType>::~BinaryTree()
{
	destroyTree(root);
}

template <class TreeItemType>
BinaryTree<TreeItemType>::BinaryTree(TreeNode<TreeItemType> *nodePtr) : root(nodePtr) {}

template <class TreeItemType>
bool BinaryTree<TreeItemType>::isEmpty() const
{
	return (root == NULL);
}

template <class TreeItemType>
TreeItemType BinaryTree<TreeItemType>::getRootData() const
{
	if (isEmpty())
		throw TreeException("TreeException: дерево пусто");
	return root->item;
} // Конец функции getRootData

template <class TreeItemType>
void BinaryTree<TreeItemType>::setRootData(const TreeItemType& newitem)
{
	if (!isEmpty())
		root->item = newitem;
	else
	{
		root = new TreeNode<TreeItemType>(newitem, NULL, NULL);
		if (root == NULL)
			throw TreeException(
				"TreeException: невозможно выделить память");
	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::attachLeft(const TreeItemType& newitem)
{
	if (isEmpty())
		throw TreeException("TreeException: дерево пусто");
	else if (root->left != NULL)
		throw TreeException("TreeException: переписать левое поддерево невозможно");
	else
	{
		root->left = new TreeNode<TreeItemType>(newitem, NULL, NULL);
		if (root->left == NULL)
			throw TreeException("TreeException: невозможно выделить память ");
	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::attachRight(const TreeItemType& newitem)
{
	if (isEmpty())
		throw TreeException("TreeException: дерево пусто");
	else if (root->right != NULL)
		throw TreeException("TreeException: невозможно переписать правое поддерево ");
	else
	{
		root->right = new TreeNode<TreeItemType>(newitem, NULL, NULL);
		if (root->right == NULL)
			throw TreeException("TreeException: невозможно выделить память");
	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::attachLeftSubtree(BinaryTree& leftTree)
{
	if (isEmpty())
		throw TreeException("TreeException: дерево пусто");
	else if (root->left != NULL)
		throw TreeException("TreeException: невозможно переписать левое поддерево");
	else
	{
		root->left = leftTree.root;
		leftTree.root = NULL;
	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::attachRightSubtree(BinaryTree& rightTree)
{
	if (isEmpty())
		throw TreeException("TreeException: дерево пусто");
	else if (root->right != NULL)
		throw TreeException("TreeException: невозможно переписать правое поддерево");
	else
	{
		root->right = rightTree.root;
		rightTree.root = NULL;

	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::detachLeftSubtree(BinaryTree& leftTree)
{
	if (isEmpty())
		throw TreeException("TreeException: дерево пусто");
	else if (root->left == NULL)
		throw TreeException("TreeException: левого поддерева не существует");
	else
	{
		leftTree = BinaryTree<TreeItemType>(root->left);
		root->left = NULL;
	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::detachRightSubtree(BinaryTree& rightTree)
{
	if (isEmpty())
		throw TreeException("TreeException: дерево пусто");
	else if (root->right == NULL)
		throw TreeException("TreeException: правого поддерева не существует");
	else
	{
		rightTree = BinaryTree<TreeItemType>(root->right);
		root->right = NULL;
	}
}

template <class TreeItemType>
BinaryTree<TreeItemType> BinaryTree<TreeItemType>::getLeftSubtree() const
{
	TreeNode<TreeItemType> *subTreePtr;
	if (isEmpty())
		return BinaryTree();
	else
	{
		copyTree(root->left, subTreePtr);
		return BinaryTree<TreeItemType>(subTreePtr);
	}
}

template <class TreeItemType>
BinaryTree<TreeItemType> BinaryTree<TreeItemType>::getRightSubtree() const
{
	TreeNode<TreeItemType> *subTreePtr;
	if (isEmpty())
		return BinaryTree();
	else
	{
		copyTree(root->right, subTreePtr);
		return BinaryTree<TreeItemType>(subTreePtr);
	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::preorderTraverse(void(*visit)(TreeItemType &anitem))
{
	preorder(root, visit);
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::inorderTraverse(void(*visit)(TreeItemType &anitem))
{
	inorder(root, visit);
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::postorderTraverse(void(*visit)(TreeItemType &anitem))
{
	postorder(root, visit);
}

template <class TreeItemType>
BinaryTree<TreeItemType>& BinaryTree<TreeItemType>::operator=(const BinaryTree& rhs)
{
	if (this != &rhs)
	{
		destroyTree(root);
		copyTree(rhs.root, root);
	}
	return *this;
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::copyTree(TreeNode<TreeItemType> *treePtr, TreeNode<TreeItemType> *& newTreePtr) const
{
	if (treePtr != NULL)
	{
		newTreePtr = new TreeNode<TreeItemType>(treePtr->item, NULL, NULL);
		if (newTreePtr == NULL)
			throw TreeException("TreeException: невозможно выделить память");
		copyTree(treePtr->left, newTreePtr->left);
		copyTree(treePtr->right, newTreePtr->right);
	}
	else
		newTreePtr = NULL;
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::destroyTree(TreeNode<TreeItemType> *& treePtr)
{
	if (treePtr != NULL)
	{
		destroyTree(treePtr->left);
		destroyTree(treePtr->right);
		delete treePtr;
		treePtr = NULL;
	}
}

template <class TreeItemType>
TreeNode<TreeItemType> *BinaryTree<TreeItemType>::rootPtr() const
{
	return root;
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::setRootPtr(TreeNode<TreeItemType> *newRoot)
{
	root = newRoot;
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::preorder(TreeNode<TreeItemType> *treePtr, void(*visit)(TreeItemType &anitem))
{
	if (treePtr != NULL)
	{
		visit(treePtr->item);
		preorder(treePtr->left, visit);
		preorder(treePtr->right, visit);
	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::inorder(TreeNode<TreeItemType> *treePtr, void(*visit)(TreeItemType &anitem))
{
	if (treePtr != NULL)
	{
		inorder(treePtr->left, visit);
		visit(treePtr->item);
		inorder(treePtr->right, visit);
	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::postorder(TreeNode<TreeItemType> *treePtr, void(*visit)(TreeItemType &anitem))
{
	if (treePtr != NULL)
	{
		postorder(treePtr->left, visit);
		postorder(treePtr->right, visit);
		visit(treePtr->item);
	}
}