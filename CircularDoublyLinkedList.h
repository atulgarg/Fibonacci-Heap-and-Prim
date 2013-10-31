#include<iostream>
template<class T>
class CircularLinkedList
{
private:
CircularListNode<T>* head;
public:
CircularLinkedList():head(NULL){}
CircularListNode<T>* getHead();
void insertNode(T data);
void deleteNode(T data);
bool isEmpty();
void printNodes();
};
