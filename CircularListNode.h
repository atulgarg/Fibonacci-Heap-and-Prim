//CircularListNode.h
#include<iostream>
template <class T>
class CircularListNode
{
public:
T data;
CircularListNode* next;
CircularListNode* prev;
CircularListNode(T data) : data(data), next(NULL), prev(NULL){}
};
