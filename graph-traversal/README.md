# Graph Theory

A simple C++ example of graph theory using un-directed graph.

A graph consists of vertices and edges. The UnDirectedGraph class inherits from Graph class.
The example contains various utility functions such as add/remove vertices and edges. 
Importantly, the example implements DFT traversal for an Un Directed Graph

## Simple Run-time interaction

```
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

```