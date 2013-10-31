#include "FibonacciNode.h"
template<class T>
void FibonacciNode<T>::setData(T Data)
{
	this->data = data;
}
/*template<class T>
T FibonacciNode<T>::getData()
{
	return this->data;
}*/
template<class T>
void FibonacciNode<T>::setDegree(int degree)
{
	this->degree = degree;
}
template<class T>
int FibonacciNode<T>::getDegree()
{
	return this->degree;
}
template<class T>
void FibonacciNode<T>::setChildCut(bool childCut)
{
	this->childCut = childCut;
}
template<class T>
bool FibonacciNode<T>::isChildCut()
{
	return this->childCut;
}
