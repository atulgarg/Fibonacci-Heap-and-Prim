#ifndef __FIBONACCIHEAP_H_INCLUDED__  
#define __FIBONACCIHEAP_H_INCLUDED__ 
#include<iostream>
#include "FibonacciNode.h"
#include<map>
template <class T>
class FibonacciHeap
{
	private:
	FibonacciNode<T>* root;
	FibonacciNode<T>* linkedListInsert(FibonacciNode<T>* head,FibonacciNode<T>* node);
	void removeFromList(FibonacciNode<T>* head,FibonacciNode<T>* node);
	FibonacciNode<T>* pairwiseCombine(FibonacciNode<T>* root1,FibonacciNode<T>* root2);
	int totElemt;
	void reinitialiseRoot();
	void cascadingCut(FibonacciNode<T>* node);
	void cut(FibonacciNode<T>*& child,FibonacciNode<T>*& parent);
	std::map<T,FibonacciNode<T>*> mp;
	public:
	FibonacciNode<T>* find(T vertex);
	FibonacciHeap();
	void insert(int key,T data);
	void insert(FibonacciNode<T>*& node);
	FibonacciNode<T>* extractMin();
	FibonacciNode<T>* meld(FibonacciNode<T>*& root1,FibonacciNode<T>*& root2);
	FibonacciNode<T>* remove(FibonacciNode<T>* node);
	FibonacciNode<T>* removeMin();
	void decreaseKey(FibonacciNode<T>* node,int newKey);
	void printFibo();
	bool isEmpty();
};
#endif
