/**
* Class Definition for Fibonacci Node. Used to store data of generic Type T.
*/
#ifndef __FIBONACCINODE_H_INCLUDED__  
#define __FIBONACCINODE_H_INCLUDED__ 
#include<iostream>
using namespace std;
template<class T>
class FibonacciNode
{
private:
	T data;
	int key;
	int degree;
	bool childCut;
	bool visited;
public:
	
	FibonacciNode<T>* left;
	FibonacciNode<T>* right;
	FibonacciNode<T>* parent;
	FibonacciNode<T>* child; 
	FibonacciNode<T>();
	
	FibonacciNode<T>(int key,T data) :key(key), data(data), degree(0), left(NULL), right(NULL), parent(NULL), child(NULL), childCut(false), visited(false){};
	int getKey()
	{
		return key;
	}
	void setKey(int key)
	{
		this->key = key;
	}
	T getData()
	{
		return this->data;
	};
	void setData(T data)
	{
		this->data = data;
	};
	bool isChildCut()
	{
		return this->childCut;
	};
	void setChildCut(bool childCut)
	{
		this->childCut = childCut;
	};
	void setDegree(int degree)
	{
		this->degree = degree;
	};
	int getDegree()
	{
		return this->degree;
	}
	bool isVisited()
	{
		return this->visited;
	}
	void setVisited(bool visited)
	{
		this->visited = visited;
	}
	bool operator<(FibonacciNode<T>* node)
	{
		if(this->key < node->getKey())
			return true;
		else
			return false;
	}
};
#endif
