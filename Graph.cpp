#include "Graph.h"
#include "FibonacciHeap.h"
#include "FibonacciHeap.cpp"
#include <queue>
#include <stdlib.h>
template<class T>
Graph<T>::Graph()
{
	graph = new std::map<T,VertexNode<T>*>();
	setGraphType(false);
}
/**
* method to generate random graph until the graph is connected graph. Takes argument as number of vertices and density of graph to be generated.
* @param numVertices number of vertices in graph. Graph will assume to number them from 0 to numVertices-1;
* @param density of type double specified in percentage.
*/
template<class T>
void Graph<T>::generateRandomGraph(int numVertices,double density)
{
	int numEdges = ceil((density *(numVertices*numVertices - numVertices))/200);
        if(numEdges < (numVertices-1) || density >100)
	{
		cout<<"Error: Density not enough for Graph to be connected"<<endl;
		return;
	}
	srand(time(NULL));
	do
	{
		graph = new std::map<T,VertexNode<T>*>();
		for(int i=0;i<numVertices;i++)
			addVertex(i);

		while(numEdges > 0)
		{
			addRandomEdge(numVertices);
			numEdges--;
		}
	}while(!isGraphConnected());
	
}
/**
* private method addRandomEdge to generate a random edge between a random source and random destination with random cost, to be used by random graph
* graph generation.
* @param numVertices to generate source and destination in range of (0,numVertices-1)
*/
template<class T>
void Graph<T>::addRandomEdge(int numVertices)
{
	int source;
	int destination;
	int cost;
	source = rand() % numVertices;
	destination = rand() % numVertices;
	cost = rand() % 10+1;
	if(source != destination)
	{
		if(!isEdgeExists(source,destination))
			addEdge(source,destination,cost);
	}
}
/**
* method setGraphType to set type of calculation to be performed. For estimating Minimum spanning tree using Fibonacci Heap true parameter is expected
* while for false simple array is used. If not set works for array by default.
* @param bool value true for Fibonacci Heap and false for array.
*/
template<class T>
void Graph<T>::setGraphType(bool type)
{
	if(type)
		flag = FIBO_HEAP;
	else
		flag = ARRAY;
}
/**
* method isEdgeExists to check whether a edge exists between a provided source and destination. Returns true if edge exists and false if edge does not
* exists.
* returns bool value. True if a edge exists and false if no edge exists.
*/
template<class T>
bool Graph<T>::isEdgeExists(T source,T destination)
{
	bool edgeExists = false;
	//Check only if both of the vertex exists already in graph.
	
	if(graph->count(source) >= 1 && graph->count(destination) >= 1)
	{
		VertexNode<T>* sourceVertex  = graph->find(source)->second;
		edgeExists = sourceVertex->isEdgeExists(destination);
	}
	return edgeExists;
}
/**
* method addEdge overloaded by input arguments of type T. Internally invokes method addEdge(VertexNode<T>*,VertexNode<T>*,int)
* @param source
* @param destination
* @param cost
*/
template<class T>
void Graph<T>::addEdge(T source,T destination,int cost)
{
	VertexNode<T>* sourceVertex;
	VertexNode<T>* destVertex;
	// if Vertex exists for provided value retrieve the vertex else create a new vertex for source.
	if(graph->count(source) < 1)
		sourceVertex = new VertexNode<T>(source);
	else
		sourceVertex = graph->find(source)->second;
	//Same for destination as for source
	if(graph->count(destination) < 1)
		destVertex = new VertexNode<T>(destination);
	else
			destVertex = graph->find(destination)->second;
	addEdge(sourceVertex,destVertex,cost);
}
/**
* method addEdge to add any edge. If either of the nodes does not exist, node is added to  graph->and edge is then added.
* @param sourceVertex of type  pointer to VertexNode<T>
* @param destination of type  pointer to VertexNode<T>
*/
template<class T>
void Graph<T>::addEdge(VertexNode<T>* sourceVertex,VertexNode<T>* destination,int cost)
{
	EdgeNode<T>* edge ;
	if(sourceVertex !=NULL && destination != NULL)
	{
		//If the source Node does not exists in graph add the new node to graph
		if(graph->count(sourceVertex->getVertex()) < 1)
		{
			addVertex(sourceVertex);
		}		
		//If the destination Node does not exists in graph add the new node to graph
		if(graph->count(destination->getVertex()) < 1)
		{
			addVertex(destination);
		}
		//Added twice for undirected graph.
		sourceVertex->addEdge(sourceVertex,destination,cost);
		destination->addEdge(destination,sourceVertex,cost);
	}
	else
	{
		cout<<"Error: Null Value passed either as source or destination"<<endl;
	}
}
/**
* method add new vertex to Graph. Overloaded function takes in data and creates a new VertexNode.
*/
template<class T>
void Graph<T>::addVertex(T vertex)
{
	if(graph != NULL)
	{
		addVertex(new VertexNode<T>(vertex));
	}
}
/**
* method to add new vertex to Graph.
* @param VertexNode* pointer to vertex to be inserted
*/
template<class T>
void Graph<T>::addVertex(VertexNode<T>* vertex)
	{
	if(graph == NULL || graph->empty() || graph->count(vertex->getVertex()) < 1)
	{
		std::pair<T,VertexNode<T>*> vertexPair;
		vertexPair = std::make_pair(vertex->getVertex(),vertex);
		graph->insert(vertexPair);
	}else
	{
		//Exception handling
		cout<<"Node: "<< vertex->getVertex()<<". Duplicate Node insertion Not allowed"<<endl;
	}	
}
/**
* method to print nodes of Graph.
*/
template<class T>
void Graph<T>::printGraph()
{
	if(graph!= NULL && !graph->empty())
	{
		typename std::map<T,VertexNode<T>*>::iterator iter = graph->begin();
		for(;iter!=graph->end();++iter)
		{
			iter->second->printVertex();
		}
	}

}
/**
* method to insert.
*/
template<class T>
void Graph<T>::insert(EdgeNode<T>* edge)
{
	if(flag == FIBO_HEAP)
		fHeap.insert(edge->getCost(),edge);
	else
		edgeList.push_back(edge);
}
/**
* wrapper method to remove the element based on flags. In case of FIBOnacci removes from heap else from array.
*/
template<class T>
EdgeNode<T>* Graph<T>::removeMin()
{
	EdgeNode<T>* minEdge = NULL;
	if(flag == FIBO_HEAP)
		minEdge = fHeap.removeMin()->getData();
	else
		minEdge = findMinEdge(edgeList);
	return minEdge;
}
/**
* method minSpanTreeSimple() to calculate minimum Spanning Tree for the graph using simple data structrure and Prim's Algorithm.
* @param flag print whether to print the MST on standard output or not.
*/
template<class T>
void Graph<T>::minSpanTreeSimple(bool print)
{
	std::vector<EdgeNode<T>*> minSpanTree;					//to store all the edges in minimum spanning tree.
	int totalCost =0;							//stores total cost of minimum spanning tree
	if(graph != NULL && !graph->empty())
	{
		typename std::map<T,VertexNode<T>*>::iterator iter = graph->begin();
		std::map<T,bool> visitedMap;
		for(;iter!=graph->end();++iter)
		{
			VertexNode<T>* vertex = iter->second;
			visitedMap[vertex->getVertex()]=false;
		}
		iter = graph-> begin();
		VertexNode<T>* currVertex = iter->second;				//selecting first node in map.
		while(minSpanTree.size() != graph->size()-1)	//Iterate till all the vertex are included in MST.
		{
			if(currVertex!=NULL && !visitedMap[currVertex->getVertex()])
			{
				//Code for adding all edges for CurrentVertex in edgeList and also getting the minimum in same iteration.
				EdgeNode<T>* temp = currVertex->edgeListHead;		//head for the edgeList
				while(temp != NULL)
				{
				//storing the edge on vector.
					if(!visitedMap[temp->getDestination()->getVertex()])	//if(!(temp->getDestination()->isVisited()))
					{
						insert(temp);
					}
					temp = temp->next;
				}
				//Set visited for the current Vertex
				visitedMap[currVertex->getVertex()]= true;
			}

			//Find minimum of edgeList and remove it from the list.
			EdgeNode<T>* minEdge = removeMin();
			//Add minEdge to MST with current vertex to destination vertex.
			minSpanTree.push_back(minEdge);
			totalCost = totalCost + minEdge->getCost();
			currVertex = minEdge->getDestination();
		}
	}
	if(print)
	{
		cout<<totalCost<<endl;
		typename std::vector<EdgeNode<T>*>::iterator iter = minSpanTree.begin();
		for(;iter!=minSpanTree.end();++iter)
			cout<<(*iter)->getSource()->getVertex()<<" "<<(*iter)->getDestination()->getVertex()<<endl;
	}
}
/**
* method findMinEdge to find minimum cost edge in given edgelist. Method iterates over given vector and provides with minimum list.If list is empty method returns NULL.
* @param edgeList of type std::vector<EdgeNode*> containing all the edges.
*/
template<class T>
EdgeNode<T>* Graph<T>::findMinEdge(std::vector<EdgeNode<T>*>& edgeList)
{
	EdgeNode<T>* minEdge = NULL;
	int minCost;
	if(!edgeList.empty())
	{
		typename std::vector<EdgeNode<T>*>::iterator iter = edgeList.begin();
		minEdge = *iter;
		minCost = minEdge->getCost();
		int i=0,j =0;					//to track which element to delete.
		for (; iter != edgeList.end(); ++iter)
		{
			EdgeNode<T>* currEdge = *iter;
			if(currEdge->getCost() < minCost)
			{
				minCost = currEdge->getCost();
				minEdge = currEdge;
				j=i;
			}
			i++;
		}
		edgeList.erase(edgeList.begin()+j);
	}
	return minEdge;
}
/**
* method isGraphConnected to determine if the graph is connected. Method returns true if the graph is connected and false if graph is not connected or graph is empty.It uses depth first approach to traverse the graph and determine number of components. If components are found to be greater than 1 method returns false else if equal then returns true.
* @return bool boolean value true if graph is connected and false if graph is not connected or graph is empty.
*/
template<class T>
bool Graph<T>::isGraphConnected()
{
	bool isConnected;
	int numComponents = 0;
	typename std::map<T,VertexNode<T>*>::iterator iter = graph->begin();
	std::map<T,bool> visitedMap;
	for(;iter!=graph->end();++iter)
		{
			VertexNode<T>* vertex = iter->second;
			visitedMap[vertex->getVertex()]=false;
		}
	iter = graph-> begin();
	std::queue<VertexNode<T>*> nodeQueue;
	//initialisation
	for(;iter!=graph->end();++iter)
	{
		VertexNode<T>* source = iter->second;
		if(!visitedMap[source->getVertex()])
		{
			pushEdgeToQueue(nodeQueue,visitedMap,source->edgeListHead);
			while(!nodeQueue.empty())
			{
				VertexNode<T>* sourceReached = nodeQueue.front();
				visitedMap[sourceReached->getVertex()] = true;
				EdgeNode<T>* head  = sourceReached->edgeListHead;
				nodeQueue.pop();
				pushEdgeToQueue(nodeQueue,visitedMap,head);
			}
			numComponents++;
		}
		if(numComponents > 1)
			break;
	}	
	if(numComponents == 1)
		isConnected = true;
		
	else
		isConnected = false;
	return isConnected;
}
/**
* private method pushEdgeToQueue used by BFS to add all the edges in the adjacency list of the vertexnode to a queue.
* @param nodeQueue reference to node queue where edges need to be stored.
* @param visitedMap reference to map<Vertex,bool> to mark if the vertex is visited.
* @param head pointer to adjacency list of the node to be added in queue.
*/
template<class T>
void Graph<T>::pushEdgeToQueue(std::queue<VertexNode<T>*> &nodeQueue,std::map<T,bool> &visitedMap,EdgeNode<T>* head)
{
		EdgeNode<T>* temp = head;
		while(temp != NULL)
		{
		VertexNode<T>* dest = temp->getDestination();
		if(!visitedMap[dest->getVertex()])
			nodeQueue.push(dest);
		temp = temp->next;
		}
}
/**
* method minSpanTreeFibo to evaluate minimum spanning tree by usiing Fibonacci Heaps. Method initialises all vertices to not visited and set a infinitecost inf to each of the vertices. Also it keeps a map to store pointer to FibonacciNode<T> so as it can be evaluated in constant time.
*/
template<class T>
void Graph<T>::mst(T inf)
{
	
	std::vector<EdgeNode<T>*> minSpanTree;	
	typename std::map<T,VertexNode<T>*>::iterator iter = graph->begin();
	std::map<T,bool> visitedMap;
	std::map<T,FibonacciNode<EdgeNode<T>*>*> pointerList;
	FibonacciHeap<EdgeNode<T>*> fiboHeap;
	for(;iter!=graph->end();++iter)
		{
			VertexNode<T>* vertex = iter->second;
			//set visited false for each vertex
			visitedMap[vertex->getVertex()]=false;
			EdgeNode<T>* edge = new EdgeNode<T>(NULL,vertex,inf);
			//assign key to infinity.
			FibonacciNode<EdgeNode<T>*>* fNode = new FibonacciNode<EdgeNode<T>*>(inf,edge);
			pointerList[vertex->getVertex()] = fNode;
			fiboHeap.insert(fNode);
		}
	int i=0;
	while(!fiboHeap.isEmpty())
	{
		i++;
		FibonacciNode<EdgeNode<T>*>* node = fiboHeap.removeMin();
		fiboHeap.printFibo();
		if(node != NULL)
		{
		EdgeNode<T>* tempEdge = node->getData();	//just a tweak to store 
		VertexNode<T>* source = tempEdge->getDestination();
		minSpanTree.push_back(tempEdge);
		visitedMap[source->getVertex()]=true;
		EdgeNode<T>* temp = source->edgeListHead;
		while(temp != NULL)
		{
			VertexNode<T>* vertex = temp->getDestination();
			int fibKey = pointerList[vertex->getVertex()]->getKey();
			int edgeKey = temp->getCost();
			if(!visitedMap[vertex->getVertex()] && fibKey> edgeKey)
			{
				temp->setSource(source);
				temp->setCost(edgeKey);
				FibonacciNode<EdgeNode<T>*>* fibNode = pointerList.find(vertex->getVertex())->second;
				fiboHeap.decreaseKey(fibNode,edgeKey);
			}
			temp = temp->next;
		
		}
		}
	}
	//cout<<"Total cost::"<<i<<endl;
	//	typename std::vector<EdgeNode<T>*>::iterator printIter = minSpanTree.begin();
	//	for(;printIter!=minSpanTree.end();++printIter)
	//		cout<<(*printIter)->getSource()->getVertex()<<" "<<(*printIter)->getDestination()->getVertex()<<endl;

	
}
/*
int main()
{
	Graph<int> g;
	g.addEdge(0,1,5);
	g.addEdge(1,2,8);
	//g.printGraph();
	//g.minSpanTreeSimple();
	Graph<int> g1;
	g1.setGraphType(true);
	g1.addEdge(0,1,2);
	g1.addEdge(1,2,3);
	g1.addEdge(0,3,6);
	g1.addEdge(1,3,8);
	g1.addEdge(3,4,9);
	g1.addEdge(1,4,5);
	g1.addEdge(2,4,7);
	
	g1.printGraph();
	g1.mst(1001);
	
	//g1.minSpanTreeSimple(true);
	return 0;
}*/
