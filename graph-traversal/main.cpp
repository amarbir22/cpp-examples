#include "Graph.h"
#include "UnDirectedGraph.hpp"
using namespace std;
/**
Topics Implemented
1) Inheritence
	Un-directed class inherts from Base Class Graph
2) Polynorphism
   Virtual method DFT in Base Class Graph is Implemented in UnDirecrted
3) Operator Overloading
   All classes include operator overloading for assignment, output etc
4) Exception Handling
	addEdge() Method handles exception in case the vertices does not exisit already
	All add methods verufy the logic if item can be added
5) Smart Logic
	Method such as RemoveVertix also removes corresponding edges
6) Use of STL container Vector for better Memory management and avoid memory leaks
	consume power of STL methods for better implement the functionality.
*/

int main() {
    
    Graph directedGraph;
    UnDirectedGraph unDirectedGraph;
    
    cout<<"---------Test Case: Test printing empty graph----------\n";
    cout<<"Graph: "<<directedGraph<<endl;
	cout<<"--------END---------\n\n";

	//Adds six Vertices
	cout<<"---------Test Case: Test adding valid vertices----------\n";
	for (int i = 1; i <= 6; i++) {
		directedGraph.addVertix(*new Vertix(i));
	}
	cout<<"Graph: "<<directedGraph<<endl;
	cout<<"--------END---------\n\n";
	
	
	cout<<"---------Test Case: Test adding invalid vertices with exisitng name: 3----------\n";
	directedGraph.addVertix(*new Vertix(3));
	cout<<"Graph: "<<directedGraph<<endl;
	cout<<"--------END---------\n\n";
	
	
	cout<<"---------Test Case: Test adding valid edges----------\n";
	directedGraph.addEdge(1, 2);
	directedGraph.addEdge(1, 3);
	directedGraph.addEdge(1, 4);
	directedGraph.addEdge(2, 3);
	directedGraph.addEdge(4, 2);
	directedGraph.addEdge(5, 2);
    directedGraph.addEdge(5, 4);
	cout<<"Graph: "<<directedGraph<<endl;
	cout<<"--------END---------\n\n";
	
	
	cout<<"---------Test Case: Test adding invalid edges----------\n";
	directedGraph.addEdge(9, 2);
	directedGraph.addEdge(0, 7);
	cout<<"Graph: "<<directedGraph<<endl;
	cout<<"--------END---------\n\n";
	
	
	cout<<"---------Test Case: Test removing valid vertices: Also removes associated Edges----------\n";
	cout<<"Remove Vertix with name 4\n";
	directedGraph.removeVertix(4);
	cout<<"Graph: "<<directedGraph<<endl;
	cout<<"--------END---------\n\n";
	
	cout<<"---------Test Case: Test removing invalid vertices----------\n";
	cout<<"Remove Vertix with name 99\n";
	directedGraph.removeVertix(99);
	cout<<"Graph: "<<directedGraph<<endl;
	cout<<"--------END---------\n\n";
	
	cout<<"---------Test Case: Test removing valid edges----------\n";
	cout<<"Remove Edge 4-2\n";
	directedGraph.removeEdge(5, 4);	
	cout<<"Graph: "<<directedGraph<<endl;
	cout<<"--------END---------\n\n";
    
    cout<<"---------Test Case: Test removing invalid edges----------\n";
	cout<<"Remove Edge 4-2\n";
	directedGraph.removeEdge(9, 2);	
	cout<<"Graph: "<<directedGraph<<endl;
	cout<<"--------END---------\n\n";
	
	cout<<"---------Test Case: Test if vertix exist----------\n";
	if(directedGraph.isVertixExist(2)) {
		cout<<"Vertix 2 exists\n";
	}
	else {
		cout<<"Vertix 2 not exists\n";
	}
	cout<<"Graph: "<<directedGraph<<endl;
	cout<<"--------END---------\n\n";
	
	cout<<"---------Test Case: Test if edge exist----------\n";
	Edge testData1 = Edge(1,3);
	if(directedGraph.isEdgeExists(testData1)) {
		cout<<"Edge "<<testData1<<" exists\n";
	}
	else {
	cout<<"Edge "<<testData1<<" not exists\n";
	}
	cout<<"Graph: "<<directedGraph<<endl;
	cout<<"--------END---------\n\n";
    
    cout<<"---------Test Case: DFT all paths from valid vertix 1----------\n";
    cout<<"\nPath from vertix 1: ";
    directedGraph.DFT(1);
    cout<<endl;
    cout<<"--------END---------\n\n";
    
    cout<<"---------Test Case: DFT all paths from invalid vertix 4: No Output----------\n";
    cout<<"\nPath from vertix 4: ";
    directedGraph.DFT(4); 
    cout<<endl;
    cout<<"--------END---------\n\n";
    
    
    cout<<"------------- UN DIRECTED GRAPH ONLY ---------------\n\n";
    
	cout<<"---------Test Case: Test adding valid vertices----------\n";
    for (int i = 1; i <= 4; i++) {
        unDirectedGraph.addVertix(*new Vertix(i));
    }
    cout<<"--------END---------\n\n";
    
	cout<<"---------Test Case: Test adding valid edges----------\n";
    unDirectedGraph.addEdge(1, 2);
    unDirectedGraph.addEdge(0, 3);
    unDirectedGraph.addEdge(1, 2);
    unDirectedGraph.addEdge(1, 3);
    unDirectedGraph.addEdge(1, 4);
    unDirectedGraph.addEdge(2, 3);

    cout<<unDirectedGraph;
    cout<<"--------END---------\n\n";
    
    cout<<"---------Test Case: DFT all paths from valid vertix 1----------\n";
    cout<<"\nPath from vertix 1: ";
    unDirectedGraph.DFT(1);
    cout<<endl;
	cout<<"--------END---------\n\n";	
	
	cout<<"--------END OF ALL TESTS---------\n\n";


	return 0;
} 

/** Sample Output
---------Test Case: Test printing empty graph----------
Graph: V = {}
E = {}

--------END---------

---------Test Case: Test adding valid vertices----------
Info Vertix Added: 1
Info Vertix Added: 2
Info Vertix Added: 3
Info Vertix Added: 4
Info Vertix Added: 5
Info Vertix Added: 6
Graph: V = {1, 2, 3, 4, 5, 6}
E = {}

--------END---------

---------Test Case: Test adding invalid vertices with exisitng name: 3----------
Error: Vertix with name: 3 already exist
Graph: V = {1, 2, 3, 4, 5, 6}
E = {}

--------END---------

---------Test Case: Test adding valid edges----------
Graph: V = {1, 2, 3, 4, 5, 6}
E = {{1, 2} , {1, 3} , {1, 4} , {2, 3} , {4, 2} , {5, 2} , {5, 4} }

--------END---------

---------Test Case: Test adding invalid edges----------
An Exception has occured while adding Edge 9:2
Exception: Vertix not found
An Exception has occured while adding Edge 0:7
Exception: Vertix not found
Graph: V = {1, 2, 3, 4, 5, 6}
E = {{1, 2} , {1, 3} , {1, 4} , {2, 3} , {4, 2} , {5, 2} , {5, 4} }

--------END---------

---------Test Case: Test removing valid vertices: Also removes associated Edges----------
Remove Vertix with name 4
Info Vertix removed: 4
Info Edge Removed: {2, 3}
Info Edge Removed: {4, 2}
Info Edge Removed: {5, 2}
Graph: V = {1, 2, 3, 5, 6}
E = {{1, 2} , {1, 3} , {1, 4} , {5, 4} }

--------END---------

---------Test Case: Test removing invalid vertices----------
Remove Vertix with name 99
Unable to remove vertix with name: 99
Graph: V = {1, 2, 3, 5, 6}
E = {{1, 2} , {1, 3} , {1, 4} , {5, 4} }

--------END---------

---------Test Case: Test removing valid edges----------
Remove Edge 4-2
Info Edge Removed: {5, 4}
Graph: V = {1, 2, 3, 5, 6}
E = {{1, 2} , {1, 3} , {1, 4} }

--------END---------

---------Test Case: Test removing invalid edges----------
Remove Edge 4-2
Unable to remove Edge : {9, 2}
Graph: V = {1, 2, 3, 5, 6}
E = {{1, 2} , {1, 3} , {1, 4} }

--------END---------

---------Test Case: Test if vertix exist----------
Vertix 2 exists
Graph: V = {1, 2, 3, 5, 6}
E = {{1, 2} , {1, 3} , {1, 4} }

--------END---------

---------Test Case: Test if edge exist----------
Edge {1, 3}  exists
Graph: V = {1, 2, 3, 5, 6}
E = {{1, 2} , {1, 3} , {1, 4} }

--------END---------

---------Test Case: DFT all paths from valid vertix 1----------

Path from vertix 1: {1, 2} {1, 3} {1, 4}
--------END---------

---------Test Case: DFT all paths from invalid vertix 4: No Output----------

Path from vertix 4:
--------END---------

------------- UN DIRECTED GRAPH ONLY ---------------

---------Test Case: Test adding valid vertices----------
Info Vertix Added: 1
Info Vertix Added: 2
Info Vertix Added: 3
Info Vertix Added: 4
--------END---------

---------Test Case: Test adding valid edges----------
An Exception has occured while adding Edge 0:3
Exception: Vertix not found
V = {1, 2, 3, 4}
E = {{1, 2} , {1, 2} , {1, 3} , {1, 4} , {2, 3} }
--------END---------

---------Test Case: DFT all paths from valid vertix 1----------

Path from vertix 1: {1, 2} {2, 3} {1, 2} {2, 3} {1, 3} {1, 4}
--------END---------

--------END OF ALL TESTS---------


--------------------------------
Process exited after 0.08999 seconds with return value 0
Press any key to continue . . .
*/
