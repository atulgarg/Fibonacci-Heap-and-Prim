#ifndef __VERTEXNODE_H_INCLUDED__  
#define __VERTEXNODE_H_INCLUDED__ 
#include<iostream>
template<class T>
class EdgeNode;

template<class T>
class VertexNode
{
private:
	T vertex;
	bool visited;
public:
	VertexNode<T>* pi;  		//Used only for Fibonacci Heap.
	EdgeNode<T>* edgeListHead;
	VertexNode(T vertex) : vertex(vertex), edgeListHead(NULL),visited(false){
	};
	VertexNode(T vertex,EdgeNode<T>* head): vertex(vertex), edgeListHead(head),visited(false){
	};
	void setVisited(bool visited)
	{
		this->visited = visited;
	}
	bool isVisited()
	{
		return visited;
	}
	T getVertex()
	{
		return this->vertex;
	}
	/**
	* method addEdge to add Edge between source and destination vertex specified. Method creates a new instance of EdgeNode and appends to linked list in start.
	* @param VertexNode* pointer to source vertex of type VertexNode<T>
	* @param VertexNode* pointer to destination vertex of type VertexNode<T>
	* @param int Cost of edge traversal.
	*
	*/
	void addEdge(VertexNode<T>* source,VertexNode<T>* dest,int cost)
	{
		//check for edge exists
		EdgeNode<T>* temp;
		if (NULL == edgeListHead)
		{
			edgeListHead =	new EdgeNode<T>(source,dest,cost);
		}else
		{
			temp = new EdgeNode<T>(source,dest,cost);
			temp->next = edgeListHead;
			edgeListHead = temp;
		}
	}
	/**
	* method printVertex() to print vertex and associated vertex with cost of each edge. Used for debugging.
	*/
	void printVertex()
	{
		std::cout<<"Vertex: "<<vertex<<" is connected to ";
		if(edgeListHead != NULL)
			edgeListHead->printList();
		else
			std::cout<<std::endl;
	}
	/**
	* method getMinEdge() to get the minimum edge of the list and returns NULL if the list is empty.
	* @return EdgeNode<T>* pointer to edge with minimum cost.
	*/
	EdgeNode<T>* getMinEdge()
	{
		EdgeNode<T>* minEdge;
		int minCost;
		EdgeNode<T>* temp = edgeListHead;
		if(edgeListHead != NULL)
		{
			minEdge = temp;
			minCost = temp->getCost();
			while(temp->next != NULL)
			{
				if(minCost> temp->getCost())
				{
					minCost = temp->getCost();
					minEdge = temp;
				}
				temp = temp ->next;
			}
			if(minCost > temp->getCost())
				{
					minCost = temp->getCost();
					minEdge = temp;
				}
		
		}else
		{
			minEdge = NULL;
		}
		return minEdge;
	}
	/**
	* method is EdgeExists to determine if a edge to specified destination exists. Method iterates through the adjacency list to determine if a destination with specified destination exists.
	* @returns bool value true if a edgeExist and false if no edge exists.
	*/
	bool isEdgeExists(T destination)
	{
		bool edgeExists = false;
		EdgeNode<T>* temp = edgeListHead;
		while(temp!=NULL)
		{
			if(temp->getDestination()->getVertex() == destination)
			{
				edgeExists = true;
				break;
			}
			temp = temp->next;
		}
		return edgeExists;
	}
};
#endif
