#include<iostream>
#include<stdlib.h>
#include<math.h>
#include "Graph.h"
#include "Graph.cpp"
#include<ctime>
#include<fstream>
#include<string.h>
#include<time.h>
using namespace std;
int main(int argc, char* argv[])
{
	Graph<int> graph;
	if(argc != 4 && argc!= 3)
	{
		cout<<"Incorrect usage: mst [-f][-s] file-name || mst -r n d"<<endl<<argc<<endl;
		return 1;
	}
	//if -f or -s option set then read input from File
	if(strcmp(argv[1],"-f") ==0 || strcmp(argv[1],"-s") == 0)
	{
	//read input from file.
		ifstream inputFile(argv[2]);
		if(inputFile.is_open())
		{
			int numVertices,numEdges;
			inputFile>>numVertices>>numEdges;
			int edgesAdded =0;
			while(edgesAdded < numEdges)
			{
				int source,destination,cost;
				inputFile>>source>>destination>>cost;
				graph.addEdge(source,destination,cost);
				edgesAdded++;
			}
			inputFile.close();
			if(graph.isGraphConnected())
			{
				if(strcmp(argv[1],"-f") == 0)
					graph.setGraphType(true);
				else
					graph.setGraphType(false);
				graph.minSpanTreeSimple(true);
			}
		}
	}
	//graph.printGraph();
	else if(strcmp(argv[1],"-r") == 0)
	{
		//Generate Random Input.
		int density = atoi(argv[3]);
		int n = atoi(argv[2]);
		graph.generateRandomGraph(n,density);
		cout<<"----------------------------------------------------------------"<<endl;
		clock_t Start, Time;
		Start = clock();
		//Simple Array
		graph.setGraphType(false);
		graph.minSpanTreeSimple(false);
		Time = clock()-Start;
		cout<<"Time::Simple Method :"<<Time<<endl;
		Start = clock();
		graph.setGraphType(true);
		graph.minSpanTreeSimple(false);
		Time = clock()-Start;
		cout<<"Time::Fibonacci Heap Method :"<<Time<<endl;
	}
	return 0;
}
