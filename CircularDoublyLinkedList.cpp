#include<iostream>
#include "CircularListNode.h"
#include "CircularDoublyLinkedList.h"

using namespace std;
template<class T>
CircularListNode<T>* CircularLinkedList<T>::getHead()
{
	return this->head;
}
/**
* method insertCircularListNode to insert node in doubly circular linked list. CircularListNode is inserted as the next element to head if list is not empty else inserted as h* ead.
* @param data takes data as parameter of template type T for new node.
**/
template <class T>
void CircularLinkedList<T>::insertNode(T data)
{
	if(NULL == head)
	{
		head = new CircularListNode<T>(data);
		head -> next = head;
		head -> prev = head;
	}
	else
	{
		CircularListNode<T>* temp = new CircularListNode<T>(data);
		temp -> next = head ->next;
		(head->next)->prev = temp;
		head->next = temp;
		temp->prev = head;
	}
}
/**
* method deleteCircularListNode to delete CircularListNode with specified data. 
* @param data expects data of node to be searched for.
*/
template <class T>
void CircularLinkedList<T>::deleteNode(T data)
{
	if(NULL == head)
		cout<<"List is Null";//Proper Exception Handling needs to be done.
	else
	{
		CircularListNode<T>* temp = head;
		while(temp->next!=head)
		{
		if(temp->data == data)
			break;	
		temp=temp->next;
		}
		//if head is to be deleted.
		if(temp == head && temp->data==data)
		{
			head->next->prev = head -> prev;
			head->prev->next = head -> next;
			head = head ->next;	
		}else if(temp == head) //No CircularListNode found with given data
			cout<<"No CircularListNode with specified data found."<<endl;
		else
		{
			temp->next->prev = temp->prev;
			temp->prev->next = temp->next;
			//clean(temp);
		}	
		
	}
}
/**
* method isEmpty to check if the given Doubly Circular Linked list is empty. Returns true if the list is empty else returns false.
* @returns bool returns boolean value true or false if list is empty or not respectively.
**/
template <class T>
bool CircularLinkedList<T>::isEmpty()
{
	bool isEmptyFlag = true;
	if(head == NULL)
		isEmptyFlag = true;
	else
		isEmptyFlag = false;
	return isEmptyFlag;
}
/**
* method to print all the nodes in the list.
*/
template <class T>
void CircularLinkedList<T>::printNodes()
{
	CircularListNode<T>* temp = head;
	if(head == NULL)
		cout<<"No List Exists"<<endl;
	else
	{
		while(temp->next != head)
		{
			cout<<temp->data<<endl;
			temp = temp->next;
		}
		cout<<temp->data<<endl;
	}
}
int main()
{
	CircularLinkedList<int> list;
	list.insertNode(1);
	list.insertNode(2);
	//cout<<list.getHead()->next->data<<endl;
	list.printNodes();
	return 0;
}
