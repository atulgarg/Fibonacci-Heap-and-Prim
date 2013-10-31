#ifndef __GRAPH_H_INCLUDED__   
#define __GRAPH_H_INCLUDED__ 
#include "EdgeNode.h"
#include "FibonacciHeap.h"
#include "FibonacciHeap.cpp"
#include<map>
#include<vector>
#include<queue>
enum graphType {FIBO_HEAP,ARRAY};
template<class T>
class Graph
{
	private:
	std::map<T,VertexNode<T>*>* graph;
	std::vector<EdgeNode<T>*> edgeList;     //edgelist to store all edges encountered so far
	FibonacciHeap<EdgeNode<T>*> fHeap;	
	EdgeNode<T>* findMinEdge(std::vector<EdgeNode<T>*>& edgeList);
	graphType flag;
	EdgeNode<T>* removeMin();
	void insert(EdgeNode<T>*);
	void pushEdgeToQueue(std::queue<VertexNode<T>*> &nodeQueue,std::map<T,bool>& visitedMap,EdgeNode<T>* head);
	void addRandomEdge(int numVertices);
	public:
	Graph();
	void setGraphType(bool type);
	void addEdge(T source,T destination,int cost);
	void addEdge(VertexNode<T>* sourceVertex,VertexNode<T>* destination,int cost);
	void addVertex(T vertex);
	void addVertex(VertexNode<T>* vertex);
	void addVertex(VertexNode<T>*& vertex,EdgeNode<T>*& edgeList);
	void printGraph();
	void minSpanTreeSimple(bool print);
	bool isGraphConnected();
	bool isEdgeExists(T,T);
	void generateRandomGraph(int numVertices,double density);
	void mst(T inf);
};
#endif
