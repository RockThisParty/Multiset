#pragma once

#include "BinaryTree.h"

using namespace std;

template <class TreeItemType>
class ms :protected BinaryTree
{
public:
	ms() { BinaryTree(); };
	ms(Tree
	void erase(TreeItemType & key);
	void insert(const TreeItemType &newItem);
private:
	int key = item;
	TreeNode<TreeItemType> *begin;
	TreeNode<TreeItemType> *end;
	/*bool isExist_helper(TreeNode<TreeItemType>* nodePtr, TreeItemType & key) const;
	TreeNode<TreeItemType>* erase_helper(TreeNode<TreeItemType>*& nodePtr);
	void insert_helper(const TreeItemType & newItem, TreeNode<TreeItemType>*& nodePtr);*/
};

template<class TreeItemType>
bool ms<TreeItemType>::operator[](TreeItemType &key) const
{
	return isExist_helper(root, key);
}

//template<class TreeItemType>
//TreeNode<TreeItemType> ms<TreeItemType>::isExist_helper(TreeNode<TreeItemType> *nodePtr, TreeItemType &key) const
//{
//	if (nodePtr != NULL)
//	{
//		if (nodePtr->item == key)
//			return nodePtr;
//		else if (key > nodePtr->item)
//			return isExist_helper(nodePtr->rightChildPtr, key);
//		else
//			return isExist_helper(nodePtr->leftChildPtr, key);
//	}
//	else
//		return 0;
//}

template<class TreeItemType>
int ms<TreeItemType>::operator=(TreeItemType other)
{
	if (this != &other)
	{
		ms(other).swap(*this);
	}
	return *this;
}

template<class TreeItemType>
bool ms<TreeItemType>::operator==(TreeItemType key)
{
	if (this != &key)
	{
		return false;
	}
	else
		return true;
}

template<class TreeItemType>
void ms<TreeItemType>::erase(TreeItemType &key)
{
	if (root->item == key)
		throw TreeException("TreeException: невозможно удалить корень дерева");
	TreeNode<TreeItemType> *tmpPtr = root, *nodePtr = NULL;
	while (!tmpPtr->isEmpty && tmpPtr->item != key)
	{
		nodePtr = tmpPtr;
		if (key > tmpPtr->item)
			tmpPtr = tmpPtr->rightChildPtr;
		else
			tmpPtr = tmpPtr->leftChildPtr;
	}
	if (tmpPtr->isEmpty)
		throw TreeException("TreeException: элемент не найден");
	else
	{
		if (!nodePtr->rightChildPtr->isEmpty)
		{
			if (nodePtr->rightChildPtr->item == key)
			{
				nodePtr->rightChildPtr = erase_helper(nodePtr->rightChildPtr);
				delete_case1(nodePtr->rightChildPtr);
			}
		}
		if (!nodePtr->leftChildPtr->isEmpty)
		{
			if (nodePtr->leftChildPtr->item == key)
			{
				nodePtr->leftChildPtr = erase_helper(nodePtr->leftChildPtr);
				delete_case1(nodePtr->leftChildPtr);
			}
		}
	}
}

//template<class TreeItemType>
//TreeNode<TreeItemType>* ms<TreeItemType>::erase_helper(TreeNode<TreeItemType>*& nodePtr)
//{
//	if (nodePtr->leftChildPtr->isEmpty)
//	{
//		if (nodePtr->rightChildPtr->isEmpty)
//		{
//			delete nodePtr->rightChildPtr;
//			TreeNode<TreeItemType> *ret_ptr = nodePtr->leftChildPtr;
//			ret_ptr->parentPtr = nodePtr->parentPtr;
//			delete nodePtr;
//			return ret_ptr;
//		}
//		else // nodePtr->rightChildPtr != NULL
//		{
//			delete nodePtr->leftChildPtr;
//			TreeNode<TreeItemType> *nextNodePtr = nodePtr->rightChildPtr;
//			nextNodePtr->parentPtr = nodePtr->parentPtr;
//			delete nodePtr;
//			return nextNodePtr;
//		}
//	}
//	else // nodePtr->leftChildPtr != NULL
//	{
//		if (nodePtr->rightChildPtr->isEmpty)
//		{
//			delete nodePtr->rightChildPtr;
//			TreeNode<TreeItemType> *nextNodePtr = nodePtr->leftChildPtr;
//			nextNodePtr->parentPtr = nodePtr->parentPtr;
//			delete nodePtr;
//			return nextNodePtr;
//		}
//		else // nodePtr->leftChildPtr != NULL && nodePtr->rightChildPtr != NULL
//		{
//			TreeNode<TreeItemType> *nextNodePtr = nodePtr->rightChildPtr;
//			if (nextNodePtr->leftChildPtr->isEmpty)
//			{
//				delete nextNodePtr->leftChildPtr;
//				nodePtr->item = nextNodePtr->item;
//				nodePtr->rightChildPtr = nextNodePtr->rightChildPtr;
//				nextNodePtr->rightChildPtr->parentPtr = nodePtr;
//				delete nextNodePtr;
//				return nodePtr;
//			}
//			else
//			{
//				while (nextNodePtr->leftChildPtr->isEmpty)
//					nextNodePtr = nextNodePtr->leftChildPtr;
//				nodePtr->item = nextNodePtr->item;
//				TreeNode<TreeItemType> *parent_of_nextNodePtr = nextNodePtr->parentPtr;
//				parent_of_nextNodePtr->leftChildPtr = erase_helper(nextNodePtr);
//				return nodePtr;
//			}
//		}
//	}
//}

template <class TreeItemType>
void ms<TreeItemType>::insert(const TreeItemType &newItem)
{
	insert_helper(newItem, root);
}

//template <class TreeItemType>
//void ms<TreeItemType>::insert_helper(const TreeItemType &newItem, TreeNode<TreeItemType> *&nodePtr)
//{
//	if (nodePtr->isEmpty)
//	{
//		nodePtr->item = newItem;
//		nodePtr->isEmpty = 0;
//		nodePtr->color = TreeNode<TreeItemType>::RED;
//		nodePtr->leftChildPtr = new TreeNode<TreeItemType>;
//		nodePtr->rightChildPtr = new TreeNode<TreeItemType>;
//
//		if (nodePtr->leftChildPtr == NULL || nodePtr->rightChildPtr == NULL)
//			throw TreeException("TreeException: невозможно выделить память");
//		nodePtr->leftChildPtr->parentPtr = nodePtr;
//		nodePtr->rightChildPtr->parentPtr = nodePtr;
//		insert_case1(nodePtr);
//	}
//	else
//	{
//		if (newItem > nodePtr->item)
//			insert_helper(newItem, nodePtr->rightChildPtr);
//		else
//			insert_helper(newItem, nodePtr->leftChildPtr);
//	}
//}