#ifndef __EDGENODE_H_INCLUDED__   
#define __EDGENODE_H_INCLUDED__ 
#include "VertexNode.h"
template <class T>
class EdgeNode
{
private:
	VertexNode<T>* source;
	VertexNode<T>* dest;
	int cost;
public:
	EdgeNode<T>() :source(NULL), dest(NULL), cost(0), next(NULL)
	{
	};
	EdgeNode<T>(VertexNode<T>* source,VertexNode<T>* dest,int cost) :source(source), dest(dest), cost(cost), next(NULL){
	};
	EdgeNode* next;
	void setCost(int cost)
	{
		this->cost = cost;
	}
	int getCost()
	{
	return cost;
	}
	VertexNode<T>* getDestination()
	{
		return dest;
	}
	void setSource(VertexNode<T>* source)
	{
		this->source = source;
	}
	VertexNode<T>* getSource()
	{
		return source;
	}
	void printList()
	{
		EdgeNode<T>* temp = this;
		while(temp->next !=NULL)
		{
			std::cout<<temp->dest->getVertex()<<" Cost: "<< temp->cost<<" ";
			temp=temp->next;
		}
		std::cout<<temp->dest->getVertex()<<" Cost: "<< temp->cost<<std::endl;
	}
	bool operator<(EdgeNode<T>* edge2)
	{
		if(this->cost < edge2->getCost())
			return true;
		else
			return false;
	}
	
};
#endif
