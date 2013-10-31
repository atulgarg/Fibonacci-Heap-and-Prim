#ifndef __FIBONACCIHEAP_CPP_INCLUDED__  
#define __FIBONACCIHEAP_CPP_INCLUDED__ 
#include<iostream>
#include "FibonacciHeap.h"
#include<math.h>
#include<vector>
using namespace std;
template<class T>
FibonacciHeap<T>::FibonacciHeap()
{
	root = NULL;
	totElemt = 0;
}
/**
*
*/
template<class T>
FibonacciNode<T>* FibonacciHeap<T>::find(T data)
{
	return ((mp.find(data))->second);
}
/**
* method to insert a node with given data of generic data T and key k. Method creates a new Fibonacci Node of type FibonacciNode<T>* and calls overloaded function insert(FibonacciNode<T>*).
* @param T data
*
*/
template<class T>
void FibonacciHeap<T>::insert(int key,T data)
{
	FibonacciNode<T>* temp = new FibonacciNode<T>(key,data);
	//mp.insert(std::pair<T,FibonacciNode<T>*>(key,temp));
	insert(temp);
}
/**
* method insert over loaded to insert a node of type  FibonacciNode<T> to root level. Method inserts the new node as right child of root and compares to reassign the root.
* @param pointer of type FibonacciNode<T>.
*/
template<class T>
void FibonacciHeap<T>::insert(FibonacciNode<T>*& node)
{
	if(node != NULL)
	{
		if(root == NULL)
		{
			node->left = node;
			node->right = node;
			root = node;
		}
		else
		{
			node->left = root;
			node->right = root->right;
			node->right->left = node;
			node->left->right = node;
			if(node->getKey()<root->getKey())
				root = node;
		}
		totElemt++;
		node->parent=NULL;
	}
}
/**
* method meld to meld two Fibonacci Heaps and update the root pointer.
* @param root1 of type pointer to FibonacciHeap<T>, root of first fibonacci heap to be merged.
* @param root2 of type pointer to FibonacciHeap<T>, root of second fibonacci heap to be merged.
* @param root of type pointer to FibonacciHeap<T>, root of the final new fibonacci heap.	
*/
template<class T>
FibonacciNode<T>* FibonacciHeap<T>::meld(FibonacciNode<T>*& root1,FibonacciNode<T>*& root2)
{
	FibonacciNode<T>* tempRoot;
	FibonacciNode<T>* temp1,*temp2;
	if(NULL == root2 && NULL == root1)
	{
		//Exception Handling needs to be done.
		return NULL;
	}
	if(NULL == root2)
		return root1;
	else if(NULL == root1)
		return root2;
	else
	{
		temp1 = root1->right;
		temp2 = root2 ->right;
		root1->right = temp2;
		root2->right = temp1;
		temp2->left = root1;
		temp1->left = root2;
		if(root1->getKey()<root2->getKey())
			tempRoot = root1;
		else
			tempRoot = root2;
	}
	return tempRoot;
}
/**
* method removeMin() to remove the minimum from FibonacciHeap. Method removes the node stored at root. 
* places all sub-trees of the removed node in the same doubly linked list of the root node.
* Iterate through this doubly linked list to pairwise combine all nodes of same degree by looking in degre table using method pairwiseCombine()
* Reinitialises root to minimum value of the heap so constructed.
* @return FibonacciNode<T>* returns minimum node pointer from the fibonacci heap and also reinitalises the heap.
**/
template<class T>
FibonacciNode<T>* FibonacciHeap<T>::removeMin()
{
	FibonacciNode<T>* minElement= NULL;
	FibonacciNode<T>* tempMin;
	if(root != NULL)
	{
		//For Degree Table.
				int size = ceil((log(totElemt))/log(2));
				std::vector<FibonacciNode<T>*> degreeTable(size);	//Degree Table to store pointer to node of index degree size (logn base 2)approx (1.66)
				//Initialise degreeTable with NULL value.
		for (int i=0; i<degreeTable.size(); i++)
					degreeTable[i]=NULL;

		FibonacciNode<T>* tempHead;
		FibonacciNode<T>* tempIter;
		//remove Min and then traverse to balance height of the tree		   
		minElement = root;
		//tempHead is pointer to leftover list
		tempHead = extractMin();
		tempMin = tempHead;
		if(tempHead != NULL)				//if something is left in heap.
		{
			tempIter = tempHead;
			int oldDegree =-1;
		//iterate through the doubly circular linked list to combine pair wise nodes of same degree and simultaneously find the min root.
			do	
			{
				if(tempMin->getKey()>tempIter->getKey())
					tempMin = tempIter;
				if(degreeTable[tempIter->getDegree()] != NULL && degreeTable[tempIter->getDegree()] > 0)
				{
					oldDegree = tempIter->getDegree();
					tempIter = pairwiseCombine(tempIter,degreeTable[tempIter->getDegree()]);
					degreeTable[oldDegree] = NULL;
					tempIter->setVisited(false);
				}
				else
				{
					degreeTable[tempIter->getDegree()] = tempIter;
					tempIter->setVisited(true);
					tempIter = tempIter->right;
				}
			}while(degreeTable[tempIter->getDegree()] != tempIter);
			//need to re-initialise root;
			root = tempMin;	
		reinitialiseRoot();
		}else
			root = NULL;
		totElemt--;
	}else
	{
		minElement = NULL;
	}
	return minElement;
}
/**
* private method to reinitialise root based on the minimum value.
*/
template<class T>
void FibonacciHeap<T>::reinitialiseRoot()
{
	FibonacciNode<T>* temp = root;
	FibonacciNode<T>* newRoot;
	if(root !=NULL)
	{
		do
		{	
			if(temp->getKey() < newRoot->getKey())
				newRoot = temp;
			temp = temp->right;
		}while(temp != root);
	}
	root = newRoot;
}
/**
* private method removeFromList() to remove min node from doubly linked list and return a random pointer to the left over elements in the list.Also
* method adds sub children of removed child to the root node's list by internally calling meld. done in constant time.
*/ 
template<class T>
FibonacciNode<T>* FibonacciHeap<T>::extractMin()
{
	FibonacciNode<T>* node = root;
	FibonacciNode<T>* tempHead = NULL;
	if(node != NULL && node->right != node)				
	{
		node->left->right = node->right;
		node->right->left = node->left;
		tempHead = node->right;
		//Remove all pointers from the node to be deleted.
		node->right = NULL;
		node->left = NULL;
	}
	else if(node !=NULL && node->right == node)			//if there is only one element in list.
	{
		tempHead = NULL;
	}
	tempHead = meld(tempHead,node->child);
	return tempHead;
}
/**
* private method pairwiseCombine to combine two sub-tree of same degree. It returns the root of the combined tree or NULL if either tree is empty.
* It expects check for same degree has already done and simply merges the two fibonacci roots based on smaller value. O(1) complexity.
* @param root1 of type pointer to FibonacciHeap<T>
* @param root2 of type pointer to FibonacciHeao<T>
* @returns root of the Fibonacci tree so generated after combining both of the input trees. Returns NULL if both are NULL;
**/
template<class T>
FibonacciNode<T>* FibonacciHeap<T>::pairwiseCombine(FibonacciNode<T>* root1,FibonacciNode<T>* root2)
{
	FibonacciNode<T>* tempRoot;
	if(root1 == NULL && root2 == NULL)
		tempRoot = NULL;
	else if(root2 == NULL)
		tempRoot =  root1;
	else if(root1 == NULL)
		tempRoot = root2;
	else
	{
		if(root1->getKey() < root2->getKey())
		{
			//put root2 as child of root1.Update degree of root2,parent.
			//remove the greater root from doubly linked list and meld it with doubly list of children of the smaller root.
			remove(root2);							
			root2->parent = root1;							//set Parent of root2 as root1
			root1->setDegree(root1->getDegree()+1);					//increament the degree of root1 by one.
			root2->left = root2;
			root2->right= root2;
			root1->child = meld(root2,root1->child) ;		//insert root2 in linked list of children of
			tempRoot = root1;
		}
		else
		{
			//put root1 as child of root2.Update degree of root1.
			remove(root1);
			root1->parent = root2;
			root2->setDegree(root2->getDegree()+1);
			root1->left = root1;
			root1->right = root1;
			root2->child = meld(root1,root2->child);
			tempRoot = root2;
		}
	}
	return tempRoot;
}
/**
* method to remove arbitrary node specified by pointer to the node to be deleted. Note this method cannot be used to remove the root.In case it is called
* with root will internally call removeMin();
* @param node pointer for FibonacchiHeap<T> for node to be deleted.
* @returns root of the fibonacci heap.
*/
//childcut and degree needs to be adjusted.
template<class T>
FibonacciNode<T>* FibonacciHeap<T>::remove(FibonacciNode<T>* node)
{
	if(root == NULL || NULL == node)
	{
		cout<<"No Node to remove";
		return NULL;
	}
	//If node to be deleted is pointed by parent.
	if((NULL != node->parent) && (node == node->parent->child))
	{
		//if node to be deleted is the only child of the parent.
		if(node->right==node)
		{
		//Set child for root Null
			node->parent = NULL;
		}else
		{
			node->parent->child = node->right;
			node->right->left = node->left;
			node->left->right = node->right;
		}
		node->parent->setDegree(node->parent->getDegree()-1);
		node->parent->setChildCut(true);
	}//If node is pointed by parent
	else
	{
		if(node == root)
		{
			removeMin();
		}
		else
		{
			node->right->left = node->left;
			node->left->right = node->right;
			if(node->parent != NULL)
			{
				node->parent->setChildCut(true);
				node->parent->setDegree(node->parent->getDegree()-1);
			}
		}

	}
	return root;
	//clean node.Delete memory for node.
}
/**
* method decreaseKey to decreament the value of key for any given node. Internally calls cut which in turn call cascading cuts which will cut all the
* parents marked childCut as true.
* @param node of type pointer to FibonacciNode<T>
* @param int new key of the node specified.
*/
template<class T>
void FibonacciHeap<T>::decreaseKey(FibonacciNode<T>* node,int newKey)
{
	cout<<"decrease key begin() "<<endl;
	if(newKey > node->getKey())
	{
		cout<<"New Key is Greater than the current Key."<<endl;
		return;
	}
	node->setKey(newKey);
	FibonacciNode<T>* parent = node->parent;
	if(parent != NULL && node->getKey()<parent->getKey())
	{
		printFibo();
		cut(node,parent);
		cascadingCut(parent);
	}
	if(node->getKey() < root->getKey())
		{
			root = node;
		}
	cout<<"decrease key end():"<<endl;
}
/**
 * method cut to prune child from child list of specified parent.
 * @param child of type FibonacciNode<T> which needs to be removed.
 * @param parent of type FibonacciNode<T> of child.
 */
template<class T>
void FibonacciHeap<T>::cut(FibonacciNode<T>*& child,FibonacciNode<T>*& parent)
{
	cout<<"cut begin"<<endl;
	parent->setDegree(parent->getDegree()-1);

	if(child->right!=child)
	{
		if(child->parent->child == child)					//if parent points to this child, point to next child.
			child->parent->child = child->right;
		child->left->right = child->right;
		child->right->left = child->left;
		child->left = child->right = NULL;
	}else
		child->parent->child = NULL;
	//Adding child to root list
	printFibo();
	insert(child);
	child->parent = NULL;
	child->setChildCut(false);
	cout<<"cut end"<<endl;
}
/**
 * method cascadingCut to cut down all the parent who are loosing there second child, while mark child cut to true for others.
 * @param node of type FibonacciNode<T> which is pruned as a part of cut.
 */
template<class T>
void FibonacciHeap<T>::cascadingCut(FibonacciNode<T>* node)
{
	FibonacciNode<T>* parent = node->parent;
	if(parent != NULL)
	{
		if(parent->isChildCut() == false)
			parent->setChildCut(true);
		else
		{
			cut(node,parent);
			cascadingCut(parent);
		}
	}
}
/**
* Method to initialise root of the fibonacci heap based on minimum value. Given a random head of the doubly linked list. Method iterates through the loop and finds the minimum value.
* @param FibonacciNode<T>* head pointer to any node in Fibonacci heap's doubly linked list.
*/
template <class T>
void FibonacciHeap<T>::printFibo()
{
	FibonacciNode<T>* temp = root;
	if(root != NULL)
	{
		do
		{
			cout<<temp->getKey()<<" ";
			temp = temp->right;
		}while(temp != root);

	}
}
template<class T>
bool FibonacciHeap<T>::isEmpty()
{
	if(root == NULL)
		return true;
	else
		return false;
}
/*
int main()
{
	FibonacciHeap<int> minHeap;
	minHeap.insert(2,2);
	minHeap.insert(6,6);
	minHeap.insert(5,5);
	minHeap.insert(7,7);
	minHeap.insert(9,9);
	minHeap.printFibo();
	cout<<endl;
	minHeap.removeMin();
	minHeap.printFibo();
	minHeap.decreaseKey(minHeap.find(6),1);
	minHeap.printFibo();
	//minHeap.removeMin();

minHeap.insert(8,8);
minHeap.insert(5,5);
minHeap.insert(3,3);
minHeap.removeMin();
minHeap.insert(7,7);
minHeap.removeMin();
minHeap.insert(9,9);
minHeap.removeMin();
minHeap.removeMin();
minHeap.removeMin();
minHeap.removeMin();
return 0;
}
*/
#endif
