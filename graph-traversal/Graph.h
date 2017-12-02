#ifndef GRAPH_H_
#define GRAPH_H_
#include "Vertix.hpp"
#include "Edge.hpp"
#include <vector>
#include <iostream>

class Graph {
public:
	std::vector <Vertix> vertices;
	std::vector <Edge> edges;
    
    // default constructor
	Graph(); 

	//Add vertix to a graph
	void addVertix(Vertix);
	
	//Both directed and un directed graph has different logic to add edge
	virtual void addEdge(int, int);
	
	//Remove Edge from the vertix names
	void removeEdge(int, int);
	void removeEdge(Edge);
	
	//Remove Vertix from name (also removes all associated edges)
	void removeVertix(int);

	// can be redefined for un-directed graph
	virtual void DFT(int); 
	
    //Overloaded Methods
    friend std::ostream &operator<<( std::ostream &output,
                                    const Graph &G );

	//Utility Methods
	bool isVertixExist(int name);
	bool isEdgeExists(Edge);
	Vertix getVertixByName(int name);

	virtual ~Graph();
};

//Non member function - Utility Method
void printEdge(std::vector<Edge> edges);

#endif /* GRAPH_H_ */
